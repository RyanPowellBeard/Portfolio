#include "DatabaseManager.h"
#include <QStandardPaths>
#include <QDir>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QThread>
#include <QCoreApplication>

// Constructor
DatabaseManager::DatabaseManager()
    : m_connectionName("app_sqlite_connection") {}

// Destructor guarantees RAII cleanup if closeDatabase() was not manually called
DatabaseManager::~DatabaseManager() {
    closeDatabase();
}

QSqlDatabase DatabaseManager::database() const {
    // Check which thread is calling this function
    QString connectionName = m_connectionName;
    if (QThread::currentThread() != qApp->thread()) {
        // Generate a unique connection name for worker threads
        connectionName += QString("_thread_%1").arg(quintptr(QThread::currentThreadId()));
    }

    // If thread has an active connection, return it
    if (QSqlDatabase::contains(connectionName)) {
        return QSqlDatabase::database(connectionName);
    }

    // If a worker thread needs its own connection, open a clone connection
    QSqlDatabase threadDb = QSqlDatabase::addDatabase("QSQLITE", connectionName);
    threadDb.setDatabaseName(m_db.databaseName()); // Same database file path
    if (threadDb.open()) {
        QSqlQuery q(threadDb);
        q.exec("PRAGMA foreign_keys = ON;"); // Pragma set per connection
    }
    else {
        qCritical() << "Failed to open thread database connection:" << threadDb.lastError().text();
    }

    return threadDb;
}

bool DatabaseManager::initDatabase() {
    // Finds the platform-safe app storage directory
    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(appDataPath);
    if (!dir.exists()) {
        if (!dir.mkpath(".")) { // Will create folder structure if missing
            qCritical() << "Error: Could not create app directory structure at:" << appDataPath;
            return false;
        }
    }

    QString dbPath = dir.filePath("OSIinvoices.db");
    qDebug() << "Database path initialized at:" << dbPath;

    // Load the SQLite driver and bind to m_db using m_connectionName
    m_db = QSqlDatabase::addDatabase("QSQLITE", m_connectionName);
    if (!m_db.isValid()) {
        qCritical() << "Error: QSQLITE driver is missing or invalid!";
        return false;
    }

    m_db.setDatabaseName(dbPath);

    // Open Connection
    if (!m_db.open()) {
        qCritical() << "Error: Could not open database!" << m_db.lastError().text();
        return false;
    }

    // Enable Foreign Keys and PRAGMAs immediately upon opening
    QSqlQuery pragmaQuery(m_db);
    if (!pragmaQuery.exec("PRAGMA foreign_keys = ON;")) {
        qCritical() << "Failed to enable foreign keys:" << pragmaQuery.lastError().text();
        return false;
    }

    // Optimize performance with Write-Ahead Logging (WAL)
    if (!pragmaQuery.exec("PRAGMA journal_mode = WAL;")) {
        qWarning() << "Could not enable WAL mode:" << pragmaQuery.lastError().text();
    }

    // Build tables
    return createTables();
}

// Close db and safely unregister connection from Qt pool
void DatabaseManager::closeDatabase() {
    if (m_db.isOpen()) {
        m_db.close();
    }

    // Assign default-constructed invalid database to drop internal reference count
    m_db = QSqlDatabase();

    // Safely unregister connection string without triggering Qt warnings
    if (QSqlDatabase::contains(m_connectionName)) {
        QSqlDatabase::removeDatabase(m_connectionName);
    }
}

bool DatabaseManager::createTables() {
    QSqlQuery query(m_db); // Pass connection explicitly

    // Clients Table
    if (!query.exec(
            "CREATE TABLE IF NOT EXISTS clients ("
            "client_id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "first_name TEXT NOT NULL,"
            "last_name TEXT NOT NULL,"
            "business_name TEXT,"
            "email TEXT,"
            "phone_number TEXT,"
            "created_at TEXT DEFAULT CURRENT_TIMESTAMP"
            ");"
            )) {
        qCritical() << "Failed to create Clients Table:" << query.lastError().text();
        return false;
    }

    // Address Table
    if (!query.exec(
            "CREATE TABLE IF NOT EXISTS addresses ("
            "address_id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "client_id INTEGER,"
            "address_type TEXT NOT NULL,"
            "street_address TEXT,"
            "address_line2 TEXT,"
            "city TEXT,"
            "state TEXT,"
            "postal_code TEXT,"
            "country TEXT,"
            "FOREIGN KEY(client_id) REFERENCES clients(client_id) ON DELETE CASCADE"
            ");"
            )) {
        qCritical() << "Failed to create Address Table:" << query.lastError().text();
        return false;
    }

    // Invoices Table
    if (!query.exec(
            "CREATE TABLE IF NOT EXISTS invoices ("
            "invoice_id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "client_id INTEGER,"
            "invoice_number TEXT NOT NULL UNIQUE,"
            "issue_date TEXT NOT NULL,"
            "due_date TEXT,"
            "status TEXT NOT NULL,"
            "tax_rate INTEGER," // Stored as integer basis points or whole percentage
            "discount_amount INTEGER," // Stored in cents (multiply by 100 on write, divide by 100 on read)
            "notes TEXT,"
            "FOREIGN KEY(client_id) REFERENCES clients(client_id) ON DELETE SET NULL"
            ");"
            )) {
        qCritical() << "Failed to create Invoice Table:" << query.lastError().text();
        return false;
    }

    // Services Table
    if (!query.exec(
            "CREATE TABLE IF NOT EXISTS services ("
            "service_id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "service_name TEXT NOT NULL,"
            "service_description TEXT,"
            "service_price INTEGER NOT NULL," // Stored in cents
            "is_active INTEGER DEFAULT 1 NOT NULL CHECK (is_active IN (0, 1))"
            ");"
            )) {
        qCritical() << "Failed to create Service Table:" << query.lastError().text();
        return false;
    }

    // Invoice Items Table
    // FIX: Explicitly ROUND and CAST quantity * price to INTEGER to eliminate floating point issues in SQLite
    if (!query.exec(
            "CREATE TABLE IF NOT EXISTS invoice_items ("
            "item_id INTEGER PRIMARY KEY AUTOINCREMENT,"
            "invoice_id INTEGER NOT NULL,"
            "service_id INTEGER,"
            "description TEXT,"
            "quantity REAL NOT NULL DEFAULT 1.00,"
            "snapshot_unit_price INTEGER NOT NULL," // Price in cents frozen at time of invoice creation
            "line_total INTEGER GENERATED ALWAYS AS (CAST(ROUND(quantity * snapshot_unit_price) AS INTEGER)) STORED,"
            "FOREIGN KEY(invoice_id) REFERENCES invoices(invoice_id) ON DELETE CASCADE,"
            "FOREIGN KEY(service_id) REFERENCES services(service_id) ON DELETE SET NULL"
            ");"
            )) {
        qCritical() << "Failed to create Invoice Items Table:" << query.lastError().text();
        return false;
    }

    // Create Performance Indexes
    query.exec("CREATE INDEX IF NOT EXISTS idx_clients_names ON clients(last_name, first_name, business_name);");
    query.exec("CREATE INDEX IF NOT EXISTS idx_addresses_client ON addresses(client_id);");
    query.exec("CREATE INDEX IF NOT EXISTS idx_invoices_client ON invoices(client_id);");
    query.exec("CREATE INDEX IF NOT EXISTS idx_invoice_items_invoice ON invoice_items(invoice_id);");
    query.exec("CREATE INDEX IF NOT EXISTS idx_invoice_number ON invoices(invoice_number);");

    return true;
}
