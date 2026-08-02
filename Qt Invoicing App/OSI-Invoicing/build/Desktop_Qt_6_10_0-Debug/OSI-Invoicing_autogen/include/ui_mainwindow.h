/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMdiArea>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSave;
    QAction *actionSave_As;
    QAction *actionImport;
    QAction *actionExport_As;
    QAction *actionPrint;
    QAction *actionExit;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionCut;
    QAction *actionCopy;
    QAction *actionPaste;
    QAction *actionSelect_All;
    QAction *actionShow_Clipboard;
    QAction *actionMinimize;
    QAction *actionMaximize_Restore;
    QAction *actionZoom_In;
    QAction *actionZoom_Out;
    QAction *actionRefresh_Page;
    QAction *actionDashboard;
    QAction *actionTaxes;
    QAction *actionNew_Invoice;
    QAction *actionRecurring_Invoices;
    QAction *actionEstimates_Quotes;
    QAction *actionCredit_Notes;
    QAction *actionProducts_Services;
    QAction *actionReceipt_Upload;
    QAction *actionMileage_Hour_Tracking;
    QAction *actionAccounts_Payable_Bills;
    QAction *actionVendor_Suppliers;
    QAction *actionReceived_Payments;
    QAction *actionPayments_Gateways;
    QAction *actionBank_Reconciliation;
    QAction *actionClients_Customers;
    QAction *actionGroups;
    QAction *actionA_R_Aging_Open_Invoices;
    QAction *actionA_P_Aging;
    QAction *actionSales_Reports;
    QAction *actionJobs_Time_Mileage;
    QAction *actionTax_Summary;
    QAction *actionCompany_Profile;
    QAction *actionUser_Settings;
    QAction *actionInvoice_Customization;
    QAction *actionTax_Settings;
    QAction *actionCompany_Information;
    QAction *actionDocumentation;
    QAction *actionUpdates;
    QAction *actionApp_Version_Information;
    QAction *actionAbout_Qt;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QFrame *TopButton_Frame;
    QHBoxLayout *horizontalLayout;
    QPushButton *CreateInvoice_Button;
    QPushButton *ReceivePayment_Button;
    QPushButton *Statements_Button;
    QPushButton *Customers_Button;
    QPushButton *Reports_Button;
    QPushButton *Dashboard_Button;
    QMdiArea *mdiArea;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuView;
    QMenu *menuTools;
    QMenu *menuSales_Billing;
    QMenu *menuPurchases_Expenses;
    QMenu *menuPayments;
    QMenu *menuContacts;
    QMenu *menuReports;
    QMenu *menuSettings;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 648);
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName("actionSave");
        actionSave_As = new QAction(MainWindow);
        actionSave_As->setObjectName("actionSave_As");
        actionImport = new QAction(MainWindow);
        actionImport->setObjectName("actionImport");
        actionExport_As = new QAction(MainWindow);
        actionExport_As->setObjectName("actionExport_As");
        actionPrint = new QAction(MainWindow);
        actionPrint->setObjectName("actionPrint");
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName("actionExit");
        actionUndo = new QAction(MainWindow);
        actionUndo->setObjectName("actionUndo");
        actionRedo = new QAction(MainWindow);
        actionRedo->setObjectName("actionRedo");
        actionCut = new QAction(MainWindow);
        actionCut->setObjectName("actionCut");
        actionCopy = new QAction(MainWindow);
        actionCopy->setObjectName("actionCopy");
        actionPaste = new QAction(MainWindow);
        actionPaste->setObjectName("actionPaste");
        actionSelect_All = new QAction(MainWindow);
        actionSelect_All->setObjectName("actionSelect_All");
        actionShow_Clipboard = new QAction(MainWindow);
        actionShow_Clipboard->setObjectName("actionShow_Clipboard");
        actionMinimize = new QAction(MainWindow);
        actionMinimize->setObjectName("actionMinimize");
        actionMaximize_Restore = new QAction(MainWindow);
        actionMaximize_Restore->setObjectName("actionMaximize_Restore");
        actionZoom_In = new QAction(MainWindow);
        actionZoom_In->setObjectName("actionZoom_In");
        actionZoom_Out = new QAction(MainWindow);
        actionZoom_Out->setObjectName("actionZoom_Out");
        actionRefresh_Page = new QAction(MainWindow);
        actionRefresh_Page->setObjectName("actionRefresh_Page");
        actionDashboard = new QAction(MainWindow);
        actionDashboard->setObjectName("actionDashboard");
        actionTaxes = new QAction(MainWindow);
        actionTaxes->setObjectName("actionTaxes");
        actionNew_Invoice = new QAction(MainWindow);
        actionNew_Invoice->setObjectName("actionNew_Invoice");
        actionRecurring_Invoices = new QAction(MainWindow);
        actionRecurring_Invoices->setObjectName("actionRecurring_Invoices");
        actionEstimates_Quotes = new QAction(MainWindow);
        actionEstimates_Quotes->setObjectName("actionEstimates_Quotes");
        actionCredit_Notes = new QAction(MainWindow);
        actionCredit_Notes->setObjectName("actionCredit_Notes");
        actionProducts_Services = new QAction(MainWindow);
        actionProducts_Services->setObjectName("actionProducts_Services");
        actionReceipt_Upload = new QAction(MainWindow);
        actionReceipt_Upload->setObjectName("actionReceipt_Upload");
        actionMileage_Hour_Tracking = new QAction(MainWindow);
        actionMileage_Hour_Tracking->setObjectName("actionMileage_Hour_Tracking");
        actionAccounts_Payable_Bills = new QAction(MainWindow);
        actionAccounts_Payable_Bills->setObjectName("actionAccounts_Payable_Bills");
        actionVendor_Suppliers = new QAction(MainWindow);
        actionVendor_Suppliers->setObjectName("actionVendor_Suppliers");
        actionReceived_Payments = new QAction(MainWindow);
        actionReceived_Payments->setObjectName("actionReceived_Payments");
        actionPayments_Gateways = new QAction(MainWindow);
        actionPayments_Gateways->setObjectName("actionPayments_Gateways");
        actionBank_Reconciliation = new QAction(MainWindow);
        actionBank_Reconciliation->setObjectName("actionBank_Reconciliation");
        actionClients_Customers = new QAction(MainWindow);
        actionClients_Customers->setObjectName("actionClients_Customers");
        actionGroups = new QAction(MainWindow);
        actionGroups->setObjectName("actionGroups");
        actionA_R_Aging_Open_Invoices = new QAction(MainWindow);
        actionA_R_Aging_Open_Invoices->setObjectName("actionA_R_Aging_Open_Invoices");
        actionA_P_Aging = new QAction(MainWindow);
        actionA_P_Aging->setObjectName("actionA_P_Aging");
        actionSales_Reports = new QAction(MainWindow);
        actionSales_Reports->setObjectName("actionSales_Reports");
        actionJobs_Time_Mileage = new QAction(MainWindow);
        actionJobs_Time_Mileage->setObjectName("actionJobs_Time_Mileage");
        actionTax_Summary = new QAction(MainWindow);
        actionTax_Summary->setObjectName("actionTax_Summary");
        actionCompany_Profile = new QAction(MainWindow);
        actionCompany_Profile->setObjectName("actionCompany_Profile");
        actionUser_Settings = new QAction(MainWindow);
        actionUser_Settings->setObjectName("actionUser_Settings");
        actionInvoice_Customization = new QAction(MainWindow);
        actionInvoice_Customization->setObjectName("actionInvoice_Customization");
        actionTax_Settings = new QAction(MainWindow);
        actionTax_Settings->setObjectName("actionTax_Settings");
        actionCompany_Information = new QAction(MainWindow);
        actionCompany_Information->setObjectName("actionCompany_Information");
        actionDocumentation = new QAction(MainWindow);
        actionDocumentation->setObjectName("actionDocumentation");
        actionUpdates = new QAction(MainWindow);
        actionUpdates->setObjectName("actionUpdates");
        actionApp_Version_Information = new QAction(MainWindow);
        actionApp_Version_Information->setObjectName("actionApp_Version_Information");
        actionAbout_Qt = new QAction(MainWindow);
        actionAbout_Qt->setObjectName("actionAbout_Qt");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        TopButton_Frame = new QFrame(centralwidget);
        TopButton_Frame->setObjectName("TopButton_Frame");
        TopButton_Frame->setFrameShape(QFrame::Shape::StyledPanel);
        TopButton_Frame->setFrameShadow(QFrame::Shadow::Raised);
        horizontalLayout = new QHBoxLayout(TopButton_Frame);
        horizontalLayout->setObjectName("horizontalLayout");
        CreateInvoice_Button = new QPushButton(TopButton_Frame);
        CreateInvoice_Button->setObjectName("CreateInvoice_Button");

        horizontalLayout->addWidget(CreateInvoice_Button);

        ReceivePayment_Button = new QPushButton(TopButton_Frame);
        ReceivePayment_Button->setObjectName("ReceivePayment_Button");

        horizontalLayout->addWidget(ReceivePayment_Button);

        Statements_Button = new QPushButton(TopButton_Frame);
        Statements_Button->setObjectName("Statements_Button");

        horizontalLayout->addWidget(Statements_Button);

        Customers_Button = new QPushButton(TopButton_Frame);
        Customers_Button->setObjectName("Customers_Button");

        horizontalLayout->addWidget(Customers_Button);

        Reports_Button = new QPushButton(TopButton_Frame);
        Reports_Button->setObjectName("Reports_Button");

        horizontalLayout->addWidget(Reports_Button);

        Dashboard_Button = new QPushButton(TopButton_Frame);
        Dashboard_Button->setObjectName("Dashboard_Button");

        horizontalLayout->addWidget(Dashboard_Button);


        verticalLayout->addWidget(TopButton_Frame);

        mdiArea = new QMdiArea(centralwidget);
        mdiArea->setObjectName("mdiArea");

        verticalLayout->addWidget(mdiArea);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 24));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName("menuFile");
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName("menuEdit");
        menuView = new QMenu(menubar);
        menuView->setObjectName("menuView");
        menuTools = new QMenu(menubar);
        menuTools->setObjectName("menuTools");
        menuSales_Billing = new QMenu(menuTools);
        menuSales_Billing->setObjectName("menuSales_Billing");
        menuPurchases_Expenses = new QMenu(menuTools);
        menuPurchases_Expenses->setObjectName("menuPurchases_Expenses");
        menuPayments = new QMenu(menuTools);
        menuPayments->setObjectName("menuPayments");
        menuContacts = new QMenu(menuTools);
        menuContacts->setObjectName("menuContacts");
        menuReports = new QMenu(menuTools);
        menuReports->setObjectName("menuReports");
        menuSettings = new QMenu(menuTools);
        menuSettings->setObjectName("menuSettings");
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName("menuHelp");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menubar->addAction(menuView->menuAction());
        menubar->addAction(menuTools->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_As);
        menuFile->addSeparator();
        menuFile->addAction(actionImport);
        menuFile->addAction(actionExport_As);
        menuFile->addSeparator();
        menuFile->addAction(actionPrint);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuEdit->addAction(actionUndo);
        menuEdit->addAction(actionRedo);
        menuEdit->addSeparator();
        menuEdit->addAction(actionCut);
        menuEdit->addAction(actionCopy);
        menuEdit->addAction(actionPaste);
        menuEdit->addAction(actionSelect_All);
        menuEdit->addSeparator();
        menuEdit->addAction(actionShow_Clipboard);
        menuView->addAction(actionMinimize);
        menuView->addAction(actionMaximize_Restore);
        menuView->addSeparator();
        menuView->addAction(actionZoom_In);
        menuView->addAction(actionZoom_Out);
        menuView->addSeparator();
        menuView->addAction(actionRefresh_Page);
        menuTools->addAction(actionDashboard);
        menuTools->addSeparator();
        menuTools->addAction(menuSales_Billing->menuAction());
        menuTools->addAction(menuPurchases_Expenses->menuAction());
        menuTools->addAction(menuPayments->menuAction());
        menuTools->addAction(actionTaxes);
        menuTools->addSeparator();
        menuTools->addAction(menuContacts->menuAction());
        menuTools->addAction(menuReports->menuAction());
        menuTools->addSeparator();
        menuTools->addAction(menuSettings->menuAction());
        menuSales_Billing->addAction(actionNew_Invoice);
        menuSales_Billing->addAction(actionRecurring_Invoices);
        menuSales_Billing->addSeparator();
        menuSales_Billing->addAction(actionEstimates_Quotes);
        menuSales_Billing->addAction(actionCredit_Notes);
        menuSales_Billing->addSeparator();
        menuSales_Billing->addAction(actionProducts_Services);
        menuPurchases_Expenses->addAction(actionReceipt_Upload);
        menuPurchases_Expenses->addAction(actionMileage_Hour_Tracking);
        menuPurchases_Expenses->addSeparator();
        menuPurchases_Expenses->addAction(actionAccounts_Payable_Bills);
        menuPurchases_Expenses->addSeparator();
        menuPurchases_Expenses->addAction(actionVendor_Suppliers);
        menuPayments->addAction(actionReceived_Payments);
        menuPayments->addAction(actionPayments_Gateways);
        menuPayments->addSeparator();
        menuPayments->addAction(actionBank_Reconciliation);
        menuContacts->addAction(actionClients_Customers);
        menuContacts->addAction(actionGroups);
        menuReports->addAction(actionA_R_Aging_Open_Invoices);
        menuReports->addAction(actionA_P_Aging);
        menuReports->addSeparator();
        menuReports->addAction(actionSales_Reports);
        menuReports->addAction(actionJobs_Time_Mileage);
        menuReports->addSeparator();
        menuReports->addAction(actionTax_Summary);
        menuSettings->addAction(actionCompany_Profile);
        menuSettings->addAction(actionUser_Settings);
        menuSettings->addSeparator();
        menuSettings->addAction(actionInvoice_Customization);
        menuSettings->addSeparator();
        menuSettings->addAction(actionTax_Settings);
        menuHelp->addAction(actionCompany_Information);
        menuHelp->addSeparator();
        menuHelp->addAction(actionDocumentation);
        menuHelp->addAction(actionUpdates);
        menuHelp->addSeparator();
        menuHelp->addAction(actionApp_Version_Information);
        menuHelp->addAction(actionAbout_Qt);

        retranslateUi(MainWindow);
        QObject::connect(actionExit, &QAction::triggered, MainWindow, qOverload<>(&QMainWindow::close));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        actionSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        actionSave_As->setText(QCoreApplication::translate("MainWindow", "Save As", nullptr));
        actionImport->setText(QCoreApplication::translate("MainWindow", "Import", nullptr));
        actionExport_As->setText(QCoreApplication::translate("MainWindow", "Export As", nullptr));
        actionPrint->setText(QCoreApplication::translate("MainWindow", "Print", nullptr));
        actionExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        actionUndo->setText(QCoreApplication::translate("MainWindow", "Undo", nullptr));
        actionRedo->setText(QCoreApplication::translate("MainWindow", "Redo", nullptr));
        actionCut->setText(QCoreApplication::translate("MainWindow", "Cut", nullptr));
        actionCopy->setText(QCoreApplication::translate("MainWindow", "Copy", nullptr));
        actionPaste->setText(QCoreApplication::translate("MainWindow", "Paste", nullptr));
        actionSelect_All->setText(QCoreApplication::translate("MainWindow", "Select All", nullptr));
        actionShow_Clipboard->setText(QCoreApplication::translate("MainWindow", "Show Clipboard", nullptr));
        actionMinimize->setText(QCoreApplication::translate("MainWindow", "Minimize", nullptr));
        actionMaximize_Restore->setText(QCoreApplication::translate("MainWindow", "Maximize/Restore", nullptr));
        actionZoom_In->setText(QCoreApplication::translate("MainWindow", "Zoom In", nullptr));
        actionZoom_Out->setText(QCoreApplication::translate("MainWindow", "Zoom Out", nullptr));
        actionRefresh_Page->setText(QCoreApplication::translate("MainWindow", "Refresh Page", nullptr));
        actionDashboard->setText(QCoreApplication::translate("MainWindow", "Dashboard", nullptr));
        actionTaxes->setText(QCoreApplication::translate("MainWindow", "Taxes", nullptr));
        actionNew_Invoice->setText(QCoreApplication::translate("MainWindow", "New Invoice", nullptr));
        actionRecurring_Invoices->setText(QCoreApplication::translate("MainWindow", "Recurring Invoices", nullptr));
        actionEstimates_Quotes->setText(QCoreApplication::translate("MainWindow", "Estimates/Quotes", nullptr));
        actionCredit_Notes->setText(QCoreApplication::translate("MainWindow", "Credit Notes", nullptr));
        actionProducts_Services->setText(QCoreApplication::translate("MainWindow", "Products & Services", nullptr));
        actionReceipt_Upload->setText(QCoreApplication::translate("MainWindow", "Receipt Upload", nullptr));
        actionMileage_Hour_Tracking->setText(QCoreApplication::translate("MainWindow", "Mileage & Hour Tracking", nullptr));
        actionAccounts_Payable_Bills->setText(QCoreApplication::translate("MainWindow", "Accounts Payable (Bills)", nullptr));
        actionVendor_Suppliers->setText(QCoreApplication::translate("MainWindow", "Vendor/Suppliers", nullptr));
        actionReceived_Payments->setText(QCoreApplication::translate("MainWindow", "Received Payments", nullptr));
        actionPayments_Gateways->setText(QCoreApplication::translate("MainWindow", "Payments Gateways", nullptr));
        actionBank_Reconciliation->setText(QCoreApplication::translate("MainWindow", "Bank Reconciliation", nullptr));
        actionClients_Customers->setText(QCoreApplication::translate("MainWindow", "Clients/Customers", nullptr));
        actionGroups->setText(QCoreApplication::translate("MainWindow", "Groups", nullptr));
        actionA_R_Aging_Open_Invoices->setText(QCoreApplication::translate("MainWindow", "A/R Aging/Open Invoices", nullptr));
        actionA_P_Aging->setText(QCoreApplication::translate("MainWindow", "A/P Aging", nullptr));
        actionSales_Reports->setText(QCoreApplication::translate("MainWindow", "Sales Reports", nullptr));
        actionJobs_Time_Mileage->setText(QCoreApplication::translate("MainWindow", "Jobs, Time, & Mileage", nullptr));
        actionTax_Summary->setText(QCoreApplication::translate("MainWindow", "Tax Summary", nullptr));
        actionCompany_Profile->setText(QCoreApplication::translate("MainWindow", "Company Profile", nullptr));
        actionUser_Settings->setText(QCoreApplication::translate("MainWindow", "User Settings", nullptr));
        actionInvoice_Customization->setText(QCoreApplication::translate("MainWindow", "Invoice Customization", nullptr));
        actionTax_Settings->setText(QCoreApplication::translate("MainWindow", "Tax Settings", nullptr));
        actionCompany_Information->setText(QCoreApplication::translate("MainWindow", "Company Information", nullptr));
        actionDocumentation->setText(QCoreApplication::translate("MainWindow", "Documentation", nullptr));
        actionUpdates->setText(QCoreApplication::translate("MainWindow", "Updates", nullptr));
        actionApp_Version_Information->setText(QCoreApplication::translate("MainWindow", "App Version Information", nullptr));
        actionAbout_Qt->setText(QCoreApplication::translate("MainWindow", "About Qt", nullptr));
        CreateInvoice_Button->setText(QCoreApplication::translate("MainWindow", "Create Invoice", nullptr));
        ReceivePayment_Button->setText(QCoreApplication::translate("MainWindow", "Receive Payment", nullptr));
        Statements_Button->setText(QCoreApplication::translate("MainWindow", "Statements", nullptr));
        Customers_Button->setText(QCoreApplication::translate("MainWindow", "Customers", nullptr));
        Reports_Button->setText(QCoreApplication::translate("MainWindow", "Reports", nullptr));
        Dashboard_Button->setText(QCoreApplication::translate("MainWindow", "Dashboard", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuEdit->setTitle(QCoreApplication::translate("MainWindow", "Edit", nullptr));
        menuView->setTitle(QCoreApplication::translate("MainWindow", "View", nullptr));
        menuTools->setTitle(QCoreApplication::translate("MainWindow", "Office", nullptr));
        menuSales_Billing->setTitle(QCoreApplication::translate("MainWindow", "Sales/Billing", nullptr));
        menuPurchases_Expenses->setTitle(QCoreApplication::translate("MainWindow", "Purchases/Expenses", nullptr));
        menuPayments->setTitle(QCoreApplication::translate("MainWindow", "Payments", nullptr));
        menuContacts->setTitle(QCoreApplication::translate("MainWindow", "Contacts", nullptr));
        menuReports->setTitle(QCoreApplication::translate("MainWindow", "Reports", nullptr));
        menuSettings->setTitle(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
        (void)MainWindow;
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
