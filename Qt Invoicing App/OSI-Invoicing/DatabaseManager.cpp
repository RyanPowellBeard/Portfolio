#include "DatabaseManager.h"
#include <QStandardPaths>
#include <QDir>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

DatabaseManager::DatabaseManager() {}
DatabaseManager::~DatabaseManager() {}

QSqlDatabase DatabaseManager::db() {
    // Fetches the default app connection safely from anywere in the code
    return QSqlDatabase::database();
}

bool DatabaseManager::initDatabase() {
    // Finds the platform-safe app storage directory
    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir dir(appDataPath);
    if (!dir.exists()) {
        if (!dir.mkpath(".")) {// Will create folder if missing
            qCritical() << "Error: Could not create app directory structures at:" << appDataPath;
            return false;
        }
    }

    QString dbPath = dir.filePath("OSIinvoices.db");
    qDebug() << "Database path initialized at:" << dbPath;

    // Load the SQLite driver
    QSqlDatabase database = QSqlDatabase::addDatabase("QSQLITE");
    if (!database.isValid()) {
        qCritical() << "Error: QSQLITE driver is missing or invalid!";
        return false;
    }

    database.setDatabaseName(dbPath);

    // Open Connection
    if (!database.open()) {
        qCritical() << "Error: Could not log into database!" << database.lastError().text();
        return false;
    }

    // Build tables
    return createTables();
}

bool DatabaseManager::createTables(){
    QSqlQuery query;


    // Enable Foreign Key Support in SQLite
    if (!query.exec("PRAGMA foreign_keys = ON;")) {
        qCritical() << "Failed to enable foreign keys:" << query.lastError().text();
        return false;
    }

    // Optimize performance with Write-Ahead Logging (WAL)
    if (!query.exec("PRAGMA journal_mode = WAL")) {
        // Wal is nice to have, but is not fatal if it fails, DO NOT CRASH OUT.
        qWarning() << "Could not enable WAL mode:" << query.lastError().text();
    }

    // Clients Table
    if (!query.exec(
        "CREATE TABLE IF NOT EXISTS clients ("
        "client_id INTEGER PRIMARY KEY AUTOINCREMENT," // Primary Key
        "first_name TEXT NOT NULL,"
        "last_name TEXT NOT NULL,"
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
        "address_id INTEGER PRIMARY KEY AUTOINCREMENT," // PRIMARY KEY
        "client_id INTEGER," // Holds Foreign Key
        "address_type TEXT NOT NULL,"
        "street_address TEXT,"
        "address_line2 TEXT,"
        "city TEXT,"
        "state TEXT,"
        "postal_code TEXT,"
        "country TEXT,"
        "FOREIGN KEY(client_id) REFERENCES clients(client_id) ON DELETE CASCADE" // FOREIGN KEY
        ");"
            )) {
        qCritical() << "Failed to create Address Table:" << query.lastError().text();
        return false;
    }

    // Invoices Table
    if (!query.exec(
        "CREATE TABLE IF NOT EXISTS invoices ("
        "invoice_id INTEGER PRIMARY KEY AUTOINCREMENT," // PRIMARY KEY
        "client_id INTEGER," // Holds Foreign Key
        "invoice_number TEXT NOT NULL UNIQUE," // Requires a Unique invoice number
        "issue_date TEXT NOT NULL," // Not handled here to allow user to be able to change date
        "due_date TEXT," // Will be adjusted based on terms off of issue_date
        "status TEXT NOT NULL,"
        "tax_rate INTEGER,"
        "discount_amount INTEGER," // Before saving multiply by 100, to display data divide the retrieved interger by 100
        "notes TEXT,"
        "FOREIGN KEY(client_id) REFERENCES clients(client_id) ON DELETE SET NULL" // FOREIGN KEY
        ");"
            )) {
        qCritical() << "Failed to create Invoice Table:" << query.lastError().text();
        return false;
    }

    // Services Table
    /*
     * Used for consistant priced items and services
     * Included is an is_active flag. When price is changed, mark the old one inactive and create a new row
     *  ensuring the frontend only graphs current items
     */
    if (!query.exec(
        "CREATE TABLE IF NOT EXISTS services ("
        "service_id INTEGER PRIMARY KEY AUTOINCREMENT," // PRIMARY KEY
        "service_name TEXT NOT NULL,"
        "service_description TEXT,"
        "service_price INTEGER NOT NULL," // Before saving multiply by 100, to display data divide the retrieved interger by 100, @ time of sale!!!
        "is_active INTEGER DEFAULT 1 NOT NULL CHECK (is_active IN (0, 1))" // SQLite uses 0 & 1, True maps to 1 and False maps to 0
        ");"
            )) {
        qCritical() << "Failed to create Service Table:" << query.lastError().text();
        return false;
    }

    // Invoice Items
    if (!query.exec(
        "CREATE TABLE IF NOT EXISTS invoice_items ("
        "item_id INTEGER PRIMARY KEY AUTOINCREMENT," // PRIMARY KEY
        "invoice_id INTEGER NOT NULL," // Holds Foreign Key
        "service_id INTEGER," // Holds Foreign Key
        "description TEXT,"
        "quantity REAL NOT NULL DEFAULT 1.00," //Kept as REAL for partial hours (e.g., 2.5 hours)
        // Freeze the price in time
        "snapshot_unit_price INTEGER NOT NULL," // Before saving multiply by 100, to display data divide the retrieved interger by 100
        "line_total REAL GENERATED ALWAYS AS (quantity * snapshot_unit_price) STORED," // Automatically calculated by SQLite
        // ON DELETE CASCADE is set for invoice_id
        "FOREIGN KEY(invoice_id) REFERENCES invoices(invoice_id) ON DELETE CASCADE," // FOREIGN KEY
        // service_id is set to ON DELETE SET NULL to retain the record line with snapshot_unit_price
        "FOREIGN KEY(service_id) REFERENCES services(service_id) ON DELETE SET NULL" // FOREIGN KEY
        ");"
            )) {
        qCritical() << "Failed to create Invoice Items Table:" << query.lastError().text();
        return false;
    }

    // Create Performance Indexes
    query.exec("CREATE INDEX IF NOT EXISTS idx_addresses_client ON addresses(client_id);");
    query.exec("CREATE INDEX IF NOT EXISTS idx_invoices_client ON invoices(client_id);");
    query.exec("CREATE INDEX IF NOT EXISTS idx_invoice_items_invoice ON invoice_items(invoice_id);");

    return true;
}