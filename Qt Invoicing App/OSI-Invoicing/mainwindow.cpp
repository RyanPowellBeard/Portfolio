#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "DatabaseManager.h"
#include "contacts_customer.h"
#include "contacts_invoices.h"
#include "companyprofile.h"
#include "salestaxreport.h"
#include "recordpaymentdialog.h"
#include "invoicedao.h"
#include "taxsettings.h"

#include <QMdiSubWindow>
#include <QMessageBox>
#include <QInputDialog>
#include <QLineEdit>
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

void MainWindow::openReceivePaymentFlow() // Called in ReceivePayment_Button and Received_Payments_triggered()
{
    bool ok = false;
    QString invoiceNumber = QInputDialog::getText(this, "Receive Payment", "Invoice Number:",
                                                  QLineEdit::Normal, QString(), &ok);
    if (!ok || invoiceNumber.trimmed().isEmpty()) {
        return;
    }

    InvoiceDao invoiceDao(m_dbManager);
    int invoiceId = invoiceDao.getInvoiceIdByNumber(invoiceNumber.trimmed());
    if (invoiceId == 0) {
        QMessageBox::warning(this, "Not Found", QString("No invoice found with number \"%1\".").arg(invoiceNumber.trimmed()));
        return;
    }

    RecordPaymentDialog dialog(m_dbManager, invoiceId, this);
    dialog.exec();
}


//------------------------------------------------Top Frame Buttons------------------------------------------------

// Create Invoice Button
void MainWindow::on_CreateInvoice_Button_clicked()
{
    // Allocate the Window on the Heap so it persists after this function
    Contacts_Invoices *invoiceWindow = new Contacts_Invoices(m_dbManager, this);

    // Add sub-window inside the MDI Area
    // This locks it to the boundaries of the MDI Area
    QMdiSubWindow *subInvoiceWindow = ui->mdiArea->addSubWindow(invoiceWindow);

    // Deletes the memory automactically when the window is closed
    subInvoiceWindow->setAttribute(Qt::WA_DeleteOnClose);

    // Opens Window
    subInvoiceWindow->showMaximized();
}

// Recieve Payment Button
void MainWindow::on_ReceivePayment_Button_clicked()
{
    openReceivePaymentFlow();
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
    // Same entry point as the Create Invoice button, just reached via the menu
    Contacts_Invoices *invoiceWindow = new Contacts_Invoices(m_dbManager, this);

    QMdiSubWindow *subInvoiceWindow = ui->mdiArea->addSubWindow(invoiceWindow);
    subInvoiceWindow->setAttribute(Qt::WA_DeleteOnClose);
    subInvoiceWindow->showMaximized();
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
    openReceivePaymentFlow();
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
    // Embedded in mdiArea, same pattern as CompanyProfile.
    SalesTaxReport *reportWindow = new SalesTaxReport(m_dbManager, this);

    // If this has stripping issues... Follow Company Profile...
    QMdiSubWindow *subReportWindow = ui->mdiArea->addSubWindow(reportWindow);
    subReportWindow->setAttribute(Qt::WA_DeleteOnClose);
    subReportWindow->showMaximized();
}

//------------Settings------------


// Company Profile
void MainWindow::on_actionCompany_Profile_triggered()
{
    // Embedded in mdiArea, same pattern as Contacts_Customer/Contacts_Invoices.
    // CompanyProfile itself is a plain QWidget with no self-set window flags;
    // this subwindow is what owns it and deletes it on close. (Do NOT switch
    // this back to profileWindow->show()/raise()/activateWindow() -- that
    // pattern requires CompanyProfile to set Qt::Window + WA_DeleteOnClose on
    // itself, which it deliberately does not do anymore.)
    CompanyProfile *profileWindow = new CompanyProfile(m_dbManager, this);

    QMdiSubWindow *subProfileWindow = ui->mdiArea->addSubWindow(profileWindow);
    subProfileWindow->setAttribute(Qt::WA_DeleteOnClose);
    subProfileWindow->showMaximized();
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
    // Embedded in mdiArea, same pattern as CompanyProfile/SalesTaxReport.
    TaxSettings *taxSettingsWindow = new TaxSettings(m_dbManager, this);

    QMdiSubWindow *subTaxSettingsWindow = ui->mdiArea->addSubWindow(taxSettingsWindow);
    subTaxSettingsWindow->setAttribute(Qt::WA_DeleteOnClose);
    subTaxSettingsWindow->showMaximized();
}

//------------About Tab------------

// About Qt
void MainWindow::on_actionAbout_Qt_triggered()
{
    // This pops up a native, professionally formatted window
    // crediting Qt and explaining the LGPL license terms.
    QMessageBox::aboutQt(this, "About Qt");
}
