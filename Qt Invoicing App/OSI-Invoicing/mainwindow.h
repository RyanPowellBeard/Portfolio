#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_CreateInvoice_Button_clicked();

    void on_ReceivePayment_Button_clicked();

    void on_Statements_Button_clicked();

    void on_Customers_Button_clicked();

    void on_Reports_Button_clicked();

    void on_Dashboard_Button_clicked();

    void on_actionPrint_triggered();

    void on_actionExport_As_triggered();

    void on_actionImport_triggered();

    void on_actionSave_As_triggered();

    void on_actionSave_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionCut_triggered();

    void on_actionCopy_triggered();

    void on_actionPaste_triggered();

    void on_actionSelect_All_triggered();

    void on_actionShow_Clipboard_triggered();

    void on_actionMinimize_triggered();

    void on_actionMaximize_Restore_triggered();

    void on_actionZoom_In_triggered();

    void on_actionZoom_Out_triggered();

    void on_actionRefresh_Page_triggered();

    void on_actionDashboard_triggered();

    void on_actionTaxes_triggered();

    void on_actionNew_Invoice_triggered();

    void on_actionRecurring_Invoices_triggered();

    void on_actionEstimates_Quotes_triggered();

    void on_actionCredit_Notes_triggered();

    void on_actionProducts_Services_triggered();

    void on_actionReceipt_Upload_triggered();

    void on_actionMileage_Hour_Tracking_triggered();

    void on_actionAccounts_Payable_Bills_triggered();

    void on_actionVendor_Suppliers_triggered();

    void on_actionReceived_Payments_triggered();

    void on_actionPayments_Gateways_triggered();

    void on_actionBank_Reconciliation_triggered();

    void on_actionClients_Customers_triggered();

    void on_actionGroups_triggered();

    void on_actionA_R_Aging_Open_Invoices_triggered();

    void on_actionA_P_Aging_triggered();

    void on_actionSales_Reports_triggered();

    void on_actionJobs_Time_Mileage_triggered();

    void on_actionTax_Summary_triggered();

    void on_actionCompany_Profile_triggered();

    void on_actionUser_Settings_triggered();

    void on_actionInvoice_Customization_triggered();

    void on_actionTax_Settings_triggered();

    void on_actionCompany_Information_triggered();

    void on_actionDocumentation_triggered();

    void on_actionUpdates_triggered();

    void on_actionApp_Version_Information_triggered();

    void on_actionAbout_Qt_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
