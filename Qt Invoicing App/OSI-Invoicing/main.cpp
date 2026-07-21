#include "mainwindow.h"
#include "DatabaseManager.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Instantiate and start backend
    DatabaseManager dbManager;
    if (!dbManager.initDatabase()) {
        QMessageBox::critical(nullptr, "Database Error", "Could not initialize local data storage. The application will close.");
        return -1;
    }

    MainWindow w;
    w.show();
    return a.exec();
}
