#ifndef CLIENTDAO_H
#define CLIENTDAO_H

#include <QVector>
#include <QString>
#include "client.h"

// Forward declaration
class DatabaseManager;

// Client Data Access Object
class ClientDao
{
public:
    explicit ClientDao(DatabaseManager& dbManager);

    // Search clients across first_name, last_name, or business_name
    QVector<Client> searchClients(const QString& searchTerm) const;

    // Insert a new client, address
    bool insertClient(const Client& client);

private:
    DatabaseManager& m_dbManager;
};

#endif // CLIENTDAO_H
