
#include "clientdao.h"
#include "DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

// Client Data Access Object for searching clients name or business
ClientDao::ClientDao(DatabaseManager &dbManager)
    : m_dbManager(dbManager) {}

QVector<Client> ClientDao::searchClients(const QString& searchTerm) const {
    qWarning() << ">>>> RUNNING FRESH BUILD - marker 001 <<<<";
    QVector<Client> results;

    // Fetch the thread-safe connection from DatabaseManager
    QSqlDatabase db = m_dbManager.database();
    if (!db.isOpen()) {
        qCritical() << "ClientDao::searchClients - Database connection is not open!";
        return results;
    }

    // Prepare parameterized SQL query
    // Utilize idx_clients_names (last_name, first_name, business_name)
    QSqlQuery query(db);
    query.prepare(
        "SELECT client_id, first_name, last_name, business_name, email, phone_number, created_at "
        "FROM clients "
        "WHERE first_name LIKE :term1 "
        "   OR last_name LIKE :term2 "
        "   OR business_name LIKE :term3 "
        "ORDER BY last_name ASC, first_name ASC, business_name ASC;"
        );

    // Format wildcards for substring matching ("Acme" -> "%Acme%)
    QString formattedPattern = "%" + searchTerm.trimmed() + "%";
    query.bindValue(":term1", formattedPattern);
    query.bindValue(":term2", formattedPattern);
    query.bindValue(":term3", formattedPattern);

    // Execute query
    if (!query.exec()) {
        qCritical() << "Error executing client search:" << query.lastError().text();
        return results;
    }

    // Extract fows into Clients structs
    while (query.next()) {
        Client client;
        client.id = query.value("client_id").toInt();
        client.firstName = query.value("first_name").toString();
        client.lastName = query.value("last_name").toString();
        client.businessName = query.value("business_name").toString();
        client.email = query.value("email").toString();
        client.phoneNumber = query.value("phone_number").toString();
        client.createdAt = query.value("created_at").toString();

        results.append(client);
    }

    return results;
}

bool ClientDao::insertClient(const Client& client) {
    QSqlDatabase db = m_dbManager.database();
    if (!db.isOpen()) {
        qCritical() << "ClientDao::insertClient - Database connection is not open!";
        return false;
    }

    db.transaction();

    // Insert the core client record
    QSqlQuery query(db);
    query.prepare(
        "INSERT INTO clients (first_name, last_name, business_name, email, phone_number) "
        "VALUES (:first_name, :last_name, :business_name, :email, :phone_number);"
        );
    query.bindValue(":first_name", client.firstName);
    query.bindValue(":last_name", client.lastName);
    query.bindValue(":business_name", client.businessName);
    query.bindValue(":email", client.email);
    query.bindValue(":phone_number", client.phoneNumber);

    if (!query.exec()) {
        qCritical() << "Error inserting client:" << query.lastError().text();
        db.rollback();
        return false;
    }

    const QVariant clientIdVariant = query.lastInsertId();
    if (!clientIdVariant.isValid()) {
        qCritical() << "ClientDao::insertClient - Failed to retrieve inserted client_id";
        db.rollback();
        return false;
    }
    const int clientId = clientIdVariant.toInt();

    // Only insert an address row if the caller actually supplied address data
    const bool hasAddressData = !client.address1.isEmpty() || !client.city.isEmpty()
                                || !client.state.isEmpty() || !client.postalCode.isEmpty() || !client.country.isEmpty();

    if (hasAddressData) {
        QSqlQuery addressQuery(db);
        addressQuery.prepare(
            "INSERT INTO addresses (client_id, address_type, street_address, address_line2, city, state, postal_code, country) "
            "VALUES (:client_id, :address_type, :street_address, :address_line2, :city, :state, :postal_code, :country);"
            );
        addressQuery.bindValue(":client_id", clientId);
        addressQuery.bindValue(":address_type", "Billing Address");
        addressQuery.bindValue(":street_address", client.address1);
        addressQuery.bindValue(":address_line2", client.address2);
        addressQuery.bindValue(":city", client.city);
        addressQuery.bindValue(":state", client.state);
        addressQuery.bindValue(":postal_code", client.postalCode);
        addressQuery.bindValue(":country", client.country);

        if (!addressQuery.exec()) {
            qCritical() << "Error inserting address:" << addressQuery.lastError().text();
            db.rollback();
            return false;
        }
    }

    if (!db.commit()) {
        qCritical() << "ClientDao::insertClient - Failed to commit transaction:" << db.lastError().text();
        db.rollback();
        return false;
    }

    return true;
}
