#ifndef CONTACTS_CUSTOMER_H
#define CONTACTS_CUSTOMER_H

#include <QWidget>

namespace Ui {
class Contacts_Customer;
}

class Contacts_Customer : public QWidget
{
    Q_OBJECT

public:
    explicit Contacts_Customer(QWidget *parent = nullptr);
    ~Contacts_Customer();

private slots:
    void on_NewCustomer_Button_clicked();

    //void on_pushButton_2_clicked();

    void on_CsvImport_Button_clicked();

    //void on_lineEdit_returnPressed();

    void on_CustomerSearch_Field_returnPressed();

private:
    Ui::Contacts_Customer *ui;

};

#endif // CONTACTS_CUSTOMER_H
