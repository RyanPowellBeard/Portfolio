#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DatabaseManager.h"
#include "contacts_customer.h"

#include <QMdiSubWindow>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>


// Window Classes
#include "contacts_customer.h"



MainWindow::MainWindow(DatabaseManager& dbManager, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_dbManager(dbManager) // Bind reference passed from main.cpp
{
    ui->setupUi(this);



    // Main Menu Bar File Menu Exit clicked()

    /*
     * Adding Exit single in MainWindow constructor allows
     * for resources to be cleaned properly, and ensure
     * that user has finished saving and closed child
     * windows.
    */
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::close);


}

MainWindow::~MainWindow()
{
    delete ui;
}


//------------------------------------------------Top Frame Buttons------------------------------------------------

// Create Invoice Button
void MainWindow::on_CreateInvoice_Button_clicked()
{

}

// Recieve Payment Button
void MainWindow::on_ReceivePayment_Button_clicked()
{

}

// Statements Button
void MainWindow::on_Statements_Button_clicked()
{

}

// Customers Button on 366
void MainWindow::on_Customers_Button_clicked()
{
    // Allocate the Window on the Heap so it persists after this function
    Contacts_Customer *contactWindow = new Contacts_Customer(m_dbManager, this);

    // Add sub-window inside the MDI Area
    // This locks it to the boundaries of the MDI Area
    QMdiSubWindow *subContactWindow = ui->mdiArea->addSubWindow(contactWindow);

    // Deletes the memory automactically when the window is closed
    subContactWindow->setAttribute(Qt::WA_DeleteOnClose);

    // Opens Window
    subContactWindow->showMaximized();

}

// Reports Button
void MainWindow::on_Reports_Button_clicked()
{

}

// Dashboard Button
void MainWindow::on_Dashboard_Button_clicked()
{

}




//------------------------------------------------Main Window Menu Bar------------------------------------------------

//------------File Tab------------

// Save
void MainWindow::on_actionSave_triggered()
{

}

// Save As
void MainWindow::on_actionSave_As_triggered()
{

}

// Import
void MainWindow::on_actionImport_triggered()
{

}

// Export As
void MainWindow::on_actionExport_As_triggered()
{

}

// Print
void MainWindow::on_actionPrint_triggered()
{

}

//------------Edit Tab------------

// Undo
void MainWindow::on_actionUndo_triggered()
{

}

// Redo
void MainWindow::on_actionRedo_triggered()
{

}

// Cut
void MainWindow::on_actionCut_triggered()
{

}

// Copy
void MainWindow::on_actionCopy_triggered()
{

}

// Paste
void MainWindow::on_actionPaste_triggered()
{

}

// Select All
void MainWindow::on_actionSelect_All_triggered()
{

}

// Show Clipboard
void MainWindow::on_actionShow_Clipboard_triggered()
{

}

//------------View Tab------------

// Minimize
void MainWindow::on_actionMinimize_triggered()
{

}

// Maximize/Restore
void MainWindow::on_actionMaximize_Restore_triggered()
{

}

// Zoom In
void MainWindow::on_actionZoom_In_triggered()
{

}

// Zoom Out
void MainWindow::on_actionZoom_Out_triggered()
{

}

// Refresh Page
/*
 * Refresh Page will refresh the top window in the main MDI area
 */
void MainWindow::on_actionRefresh_Page_triggered()
{

}

//------------Office Tab------------

// Dashboard
/*
 * Dashboard will bring up the Company analytics
 * This is linked to the same window as
 * Dashboard button
 */
void MainWindow::on_actionDashboard_triggered()
{

}

// Taxes
void MainWindow::on_actionTaxes_triggered()
{

}

//------------Help Tab------------

// Company Information
void MainWindow::on_actionCompany_Information_triggered()
{

}

// Documentation
void MainWindow::on_actionDocumentation_triggered()
{

}

// Check for Updates
/*
 * This will compare app version to latest version
 * on github
 */
void MainWindow::on_actionUpdates_triggered()
{

}

// App Version
/*
 * Will show what version of the app and dependent software
 */
void MainWindow::on_actionApp_Version_Information_triggered()
{

}

//------------Office Tab Sub-Menu------------



//------------Sales/Billing------------

//New Invoice
/*
 * New Invoice is linked to New Invoice button
 * Will open window to create a new invoice
 * and save to database
 */
void MainWindow::on_actionNew_Invoice_triggered()
{

}

// Recurring Invoice
/*
 * Will display invoice that are set for Recurring Invoicing
 * i.e. auto invoicing
 */
void MainWindow::on_actionRecurring_Invoices_triggered()
{

}

// Estimates/Quotes
void MainWindow::on_actionEstimates_Quotes_triggered()
{

}

// Credits/Notes
void MainWindow::on_actionCredit_Notes_triggered()
{

}

// Products & Services
void MainWindow::on_actionProducts_Services_triggered()
{

}

//------------Purchases/Expenses------------


// Receipt Upload
void MainWindow::on_actionReceipt_Upload_triggered()
{

}

// Mileage/Hour Tracking
void MainWindow::on_actionMileage_Hour_Tracking_triggered()
{

}

// AP
void MainWindow::on_actionAccounts_Payable_Bills_triggered()
{

}

// Vendor/Suppliers
void MainWindow::on_actionVendor_Suppliers_triggered()
{

}

//------------Payments------------


// Received Payments
void MainWindow::on_actionReceived_Payments_triggered()
{

}

// Payment Gateway
void MainWindow::on_actionPayments_Gateways_triggered()
{

}

// Bank Reconciliation
void MainWindow::on_actionBank_Reconciliation_triggered()
{

}

//------------Contacts------------


// Clients/Customers
void MainWindow::on_actionClients_Customers_triggered()
{
    // Allocate the Window on the Heap so it persists after this function
    Contacts_Customer *contactWindow = new Contacts_Customer(m_dbManager, this);

    // Add sub-window inside the MDI Area
    // This locks it to the boundaries of the MDI Area
    QMdiSubWindow *subContactWindow = ui->mdiArea->addSubWindow(contactWindow);

    // Deletes the memory automactically when the window is closed
    subContactWindow->setAttribute(Qt::WA_DeleteOnClose);

    // Opens Window
    subContactWindow->showMaximized();

}

// Groups
void MainWindow::on_actionGroups_triggered()
{

}

//------------Reports------------


// AR Aging
void MainWindow::on_actionA_R_Aging_Open_Invoices_triggered()
{

}

// AP Aging
void MainWindow::on_actionA_P_Aging_triggered()
{

}

// Sales Reports
void MainWindow::on_actionSales_Reports_triggered()
{

}

// Jobs, Time, Mileage
void MainWindow::on_actionJobs_Time_Mileage_triggered()
{

}

// Tax Summary
void MainWindow::on_actionTax_Summary_triggered()
{

}

//------------Settings------------


// Company Profile
void MainWindow::on_actionCompany_Profile_triggered()
{

}

// User Settings
void MainWindow::on_actionUser_Settings_triggered()
{

}

// Invoice Customization
void MainWindow::on_actionInvoice_Customization_triggered()
{

}

// Tax Settings
void MainWindow::on_actionTax_Settings_triggered()
{

}

//------------About Tab------------

// About Qt
void MainWindow::on_actionAbout_Qt_triggered()
{
    // This pops up a native, professionally formatted window
    // crediting Qt and explaining the LGPL license terms.
    QMessageBox::aboutQt(this, "About Qt");
}

