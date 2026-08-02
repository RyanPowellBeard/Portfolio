#ifndef ADDCLIENTDIALOG_H
#define ADDCLIENTDIALOG_H

#include <QDialog>

// Forward declaration
class DatabaseManager;

namespace Ui {
class AddClientDialog;
}

class AddClientDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddClientDialog(DatabaseManager& dbManager, QWidget *parent = nullptr);
    ~AddClientDialog();

private slots:
    void on_Cancel_PushButton_clicked();

    void on_Save_PushButton_clicked();

private:
    Ui::AddClientDialog *ui;
    DatabaseManager& m_dbManager; // Store reference to manager
};

#endif // ADDCLIENTDIALOG_H
