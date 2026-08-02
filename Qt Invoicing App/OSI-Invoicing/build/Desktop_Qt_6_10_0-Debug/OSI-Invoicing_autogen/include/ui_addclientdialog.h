/********************************************************************************
** Form generated from reading UI file 'addclientdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDCLIENTDIALOG_H
#define UI_ADDCLIENTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_AddClientDialog
{
public:
    QFrame *frame;
    QFormLayout *formLayout;
    QLabel *AddressType_Label;
    QComboBox *AddressType_SelectionBox;
    QLabel *FirstName_Label;
    QLineEdit *FirstName_LineEdit;
    QLabel *LastName_Label;
    QLineEdit *LastName_LineEdit;
    QLabel *BusinessName_Label;
    QLineEdit *BusinessName_LineEdit;
    QLabel *Email_Label;
    QLineEdit *Email_LineEdit;
    QLabel *PhoneNumber_Label;
    QLineEdit *PhoneNumber_LineEdit;
    QLabel *Address1_Label;
    QLineEdit *Address1_LineEdit;
    QLabel *Address2_Label;
    QLineEdit *Address2_LineEdit;
    QLabel *City_Label;
    QLineEdit *City_LineEdit;
    QLabel *State_Label;
    QLineEdit *State_LineEdit;
    QLabel *PostalCode_Label;
    QLineEdit *PostalCode_LineEdit;
    QLabel *County_Label;
    QComboBox *County_SelectionBox;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *Cancel_PushButton;
    QPushButton *Save_PushButton;

    void setupUi(QDialog *AddClientDialog)
    {
        if (AddClientDialog->objectName().isEmpty())
            AddClientDialog->setObjectName("AddClientDialog");
        AddClientDialog->resize(380, 419);
        AddClientDialog->setMaximumSize(QSize(420, 440));
        frame = new QFrame(AddClientDialog);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(10, 0, 361, 364));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        formLayout = new QFormLayout(frame);
        formLayout->setObjectName("formLayout");
        AddressType_Label = new QLabel(frame);
        AddressType_Label->setObjectName("AddressType_Label");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, AddressType_Label);

        AddressType_SelectionBox = new QComboBox(frame);
        AddressType_SelectionBox->addItem(QString());
        AddressType_SelectionBox->addItem(QString());
        AddressType_SelectionBox->setObjectName("AddressType_SelectionBox");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, AddressType_SelectionBox);

        FirstName_Label = new QLabel(frame);
        FirstName_Label->setObjectName("FirstName_Label");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, FirstName_Label);

        FirstName_LineEdit = new QLineEdit(frame);
        FirstName_LineEdit->setObjectName("FirstName_LineEdit");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, FirstName_LineEdit);

        LastName_Label = new QLabel(frame);
        LastName_Label->setObjectName("LastName_Label");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, LastName_Label);

        LastName_LineEdit = new QLineEdit(frame);
        LastName_LineEdit->setObjectName("LastName_LineEdit");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, LastName_LineEdit);

        BusinessName_Label = new QLabel(frame);
        BusinessName_Label->setObjectName("BusinessName_Label");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, BusinessName_Label);

        BusinessName_LineEdit = new QLineEdit(frame);
        BusinessName_LineEdit->setObjectName("BusinessName_LineEdit");

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, BusinessName_LineEdit);

        Email_Label = new QLabel(frame);
        Email_Label->setObjectName("Email_Label");

        formLayout->setWidget(4, QFormLayout::ItemRole::LabelRole, Email_Label);

        Email_LineEdit = new QLineEdit(frame);
        Email_LineEdit->setObjectName("Email_LineEdit");

        formLayout->setWidget(4, QFormLayout::ItemRole::FieldRole, Email_LineEdit);

        PhoneNumber_Label = new QLabel(frame);
        PhoneNumber_Label->setObjectName("PhoneNumber_Label");

        formLayout->setWidget(5, QFormLayout::ItemRole::LabelRole, PhoneNumber_Label);

        PhoneNumber_LineEdit = new QLineEdit(frame);
        PhoneNumber_LineEdit->setObjectName("PhoneNumber_LineEdit");

        formLayout->setWidget(5, QFormLayout::ItemRole::FieldRole, PhoneNumber_LineEdit);

        Address1_Label = new QLabel(frame);
        Address1_Label->setObjectName("Address1_Label");

        formLayout->setWidget(6, QFormLayout::ItemRole::LabelRole, Address1_Label);

        Address1_LineEdit = new QLineEdit(frame);
        Address1_LineEdit->setObjectName("Address1_LineEdit");

        formLayout->setWidget(6, QFormLayout::ItemRole::FieldRole, Address1_LineEdit);

        Address2_Label = new QLabel(frame);
        Address2_Label->setObjectName("Address2_Label");

        formLayout->setWidget(7, QFormLayout::ItemRole::LabelRole, Address2_Label);

        Address2_LineEdit = new QLineEdit(frame);
        Address2_LineEdit->setObjectName("Address2_LineEdit");

        formLayout->setWidget(7, QFormLayout::ItemRole::FieldRole, Address2_LineEdit);

        City_Label = new QLabel(frame);
        City_Label->setObjectName("City_Label");

        formLayout->setWidget(8, QFormLayout::ItemRole::LabelRole, City_Label);

        City_LineEdit = new QLineEdit(frame);
        City_LineEdit->setObjectName("City_LineEdit");

        formLayout->setWidget(8, QFormLayout::ItemRole::FieldRole, City_LineEdit);

        State_Label = new QLabel(frame);
        State_Label->setObjectName("State_Label");

        formLayout->setWidget(9, QFormLayout::ItemRole::LabelRole, State_Label);

        State_LineEdit = new QLineEdit(frame);
        State_LineEdit->setObjectName("State_LineEdit");

        formLayout->setWidget(9, QFormLayout::ItemRole::FieldRole, State_LineEdit);

        PostalCode_Label = new QLabel(frame);
        PostalCode_Label->setObjectName("PostalCode_Label");

        formLayout->setWidget(10, QFormLayout::ItemRole::LabelRole, PostalCode_Label);

        PostalCode_LineEdit = new QLineEdit(frame);
        PostalCode_LineEdit->setObjectName("PostalCode_LineEdit");

        formLayout->setWidget(10, QFormLayout::ItemRole::FieldRole, PostalCode_LineEdit);

        County_Label = new QLabel(frame);
        County_Label->setObjectName("County_Label");

        formLayout->setWidget(11, QFormLayout::ItemRole::LabelRole, County_Label);

        County_SelectionBox = new QComboBox(frame);
        County_SelectionBox->setObjectName("County_SelectionBox");

        formLayout->setWidget(11, QFormLayout::ItemRole::FieldRole, County_SelectionBox);

        frame_2 = new QFrame(AddClientDialog);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(10, 370, 361, 44));
        frame_2->setFrameShape(QFrame::Shape::StyledPanel);
        frame_2->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout = new QHBoxLayout(frame_2);
        horizontalLayout->setObjectName("horizontalLayout");
        Cancel_PushButton = new QPushButton(frame_2);
        Cancel_PushButton->setObjectName("Cancel_PushButton");

        horizontalLayout->addWidget(Cancel_PushButton);

        Save_PushButton = new QPushButton(frame_2);
        Save_PushButton->setObjectName("Save_PushButton");

        horizontalLayout->addWidget(Save_PushButton);

#if QT_CONFIG(shortcut)
        AddressType_Label->setBuddy(AddressType_SelectionBox);
        FirstName_Label->setBuddy(FirstName_LineEdit);
        LastName_Label->setBuddy(LastName_LineEdit);
        BusinessName_Label->setBuddy(BusinessName_LineEdit);
        Email_Label->setBuddy(Email_LineEdit);
        PhoneNumber_Label->setBuddy(PhoneNumber_LineEdit);
        Address1_Label->setBuddy(Address1_LineEdit);
        Address2_Label->setBuddy(Address2_LineEdit);
        City_Label->setBuddy(City_LineEdit);
        State_Label->setBuddy(State_LineEdit);
        PostalCode_Label->setBuddy(PostalCode_LineEdit);
        County_Label->setBuddy(County_SelectionBox);
#endif // QT_CONFIG(shortcut)

        retranslateUi(AddClientDialog);

        QMetaObject::connectSlotsByName(AddClientDialog);
    } // setupUi

    void retranslateUi(QDialog *AddClientDialog)
    {
        AddClientDialog->setWindowTitle(QCoreApplication::translate("AddClientDialog", "New Customer", nullptr));
        AddressType_Label->setText(QCoreApplication::translate("AddClientDialog", "Address Type:", nullptr));
        AddressType_SelectionBox->setItemText(0, QCoreApplication::translate("AddClientDialog", "Billing Address", nullptr));
        AddressType_SelectionBox->setItemText(1, QCoreApplication::translate("AddClientDialog", "Shipping Address", nullptr));

        FirstName_Label->setText(QCoreApplication::translate("AddClientDialog", "First Name:", nullptr));
        FirstName_LineEdit->setText(QString());
        LastName_Label->setText(QCoreApplication::translate("AddClientDialog", "Last Name:", nullptr));
        LastName_LineEdit->setText(QString());
        BusinessName_Label->setText(QCoreApplication::translate("AddClientDialog", "Business Name:", nullptr));
        BusinessName_LineEdit->setText(QString());
        Email_Label->setText(QCoreApplication::translate("AddClientDialog", "Email:", nullptr));
        PhoneNumber_Label->setText(QCoreApplication::translate("AddClientDialog", "Phone Number:", nullptr));
        Address1_Label->setText(QCoreApplication::translate("AddClientDialog", "Address Line 1:", nullptr));
        Address2_Label->setText(QCoreApplication::translate("AddClientDialog", "Address Line 2:", nullptr));
        City_Label->setText(QCoreApplication::translate("AddClientDialog", "City:", nullptr));
        State_Label->setText(QCoreApplication::translate("AddClientDialog", "State:", nullptr));
        State_LineEdit->setText(QString());
        PostalCode_Label->setText(QCoreApplication::translate("AddClientDialog", "Postal Code:", nullptr));
        County_Label->setText(QCoreApplication::translate("AddClientDialog", "Country:", nullptr));
        Cancel_PushButton->setText(QCoreApplication::translate("AddClientDialog", "CANCEL", nullptr));
        Save_PushButton->setText(QCoreApplication::translate("AddClientDialog", "SAVE", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AddClientDialog: public Ui_AddClientDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDCLIENTDIALOG_H
