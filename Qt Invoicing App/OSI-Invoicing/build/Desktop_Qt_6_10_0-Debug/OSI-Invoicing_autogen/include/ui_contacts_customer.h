/********************************************************************************
** Form generated from reading UI file 'contacts_customer.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONTACTS_CUSTOMER_H
#define UI_CONTACTS_CUSTOMER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Contacts_Customer
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *ContactsWindow;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *CustomerSearch_Field;
    QSpacerItem *horizontalSpacer;
    QPushButton *CsvImport_Button;
    QPushButton *NewCustomer_Button;
    QTableWidget *clientsTableWidget;

    void setupUi(QWidget *Contacts_Customer)
    {
        if (Contacts_Customer->objectName().isEmpty())
            Contacts_Customer->setObjectName("Contacts_Customer");
        Contacts_Customer->resize(411, 483);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Contacts_Customer->sizePolicy().hasHeightForWidth());
        Contacts_Customer->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(Contacts_Customer);
        verticalLayout->setObjectName("verticalLayout");
        ContactsWindow = new QFrame(Contacts_Customer);
        ContactsWindow->setObjectName("ContactsWindow");
        ContactsWindow->setFrameShape(QFrame::Shape::StyledPanel);
        ContactsWindow->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout = new QHBoxLayout(ContactsWindow);
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(ContactsWindow);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        CustomerSearch_Field = new QLineEdit(ContactsWindow);
        CustomerSearch_Field->setObjectName("CustomerSearch_Field");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(CustomerSearch_Field->sizePolicy().hasHeightForWidth());
        CustomerSearch_Field->setSizePolicy(sizePolicy1);
        CustomerSearch_Field->setMaximumSize(QSize(400, 16777215));

        horizontalLayout->addWidget(CustomerSearch_Field);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        CsvImport_Button = new QPushButton(ContactsWindow);
        CsvImport_Button->setObjectName("CsvImport_Button");
        CsvImport_Button->setMaximumSize(QSize(300, 16777215));

        horizontalLayout->addWidget(CsvImport_Button);

        NewCustomer_Button = new QPushButton(ContactsWindow);
        NewCustomer_Button->setObjectName("NewCustomer_Button");
        NewCustomer_Button->setMaximumSize(QSize(300, 16777215));

        horizontalLayout->addWidget(NewCustomer_Button);


        verticalLayout->addWidget(ContactsWindow);

        clientsTableWidget = new QTableWidget(Contacts_Customer);
        if (clientsTableWidget->columnCount() < 4)
            clientsTableWidget->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        clientsTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        clientsTableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        clientsTableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        clientsTableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        clientsTableWidget->setObjectName("clientsTableWidget");
        clientsTableWidget->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout->addWidget(clientsTableWidget);


        retranslateUi(Contacts_Customer);

        QMetaObject::connectSlotsByName(Contacts_Customer);
    } // setupUi

    void retranslateUi(QWidget *Contacts_Customer)
    {
        Contacts_Customer->setWindowTitle(QCoreApplication::translate("Contacts_Customer", "Form", nullptr));
        label->setText(QCoreApplication::translate("Contacts_Customer", "SEARCH", nullptr));
        CsvImport_Button->setText(QCoreApplication::translate("Contacts_Customer", "CSV IMPORT", nullptr));
        NewCustomer_Button->setText(QCoreApplication::translate("Contacts_Customer", "New Customer", nullptr));
        QTableWidgetItem *___qtablewidgetitem = clientsTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("Contacts_Customer", "Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = clientsTableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("Contacts_Customer", "Business", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = clientsTableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("Contacts_Customer", "Email", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = clientsTableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("Contacts_Customer", "Phone", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Contacts_Customer: public Ui_Contacts_Customer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTACTS_CUSTOMER_H
