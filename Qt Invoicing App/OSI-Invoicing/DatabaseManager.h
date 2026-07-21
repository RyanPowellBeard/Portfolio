#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QSqlDatabase>

class DatabaseManager {
public:
    DatabaseManager();
    ~DatabaseManager();

    bool initDatabase();

    // Helper to test or fetch the active connection safely
    static QSqlDatabase db();

private:
    bool createTables();
};

#endif // DATABASEMANAGER_H
