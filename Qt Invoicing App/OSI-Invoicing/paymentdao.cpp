#include "paymentdao.h"
#include "DatabaseManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

PaymentDao::PaymentDao(DatabaseManager &dbManager)
    : m_dbManager(dbManager) {}

int PaymentDao::insertPayment(const Payment &payment) {
    QSqlDatabase db = m_dbManager.database();
    if (!db.isOpen()) {
        qCritical() << "PaymentDao::insertPayment - Database connection is not open!";
        return 0;
    }

    QSqlQuery query(db);
    query.prepare(
        "INSERT INTO payments (invoice_id, payment_date, amount, method, notes) "
        "VALUES (:invoice_id, :payment_date, :amount, :method, :notes);"
        );
    query.bindValue(":invoice_id", payment.invoiceId);
    query.bindValue(":payment_date", payment.paymentDate);
    query.bindValue(":amount", payment.amountCents);
    query.bindValue(":method", payment.method);
    query.bindValue(":notes", payment.notes);

    if (!query.exec()) {
        qCritical() << "Error inserting payment:" << query.lastError().text();
        return 0;
    }

    const QVariant paymentIdVariant = query.lastInsertId();
    if (!paymentIdVariant.isValid()) {
        qCritical() << "PaymentDao::insertPayment - Failed to retrieve inserted payment_id";
        return 0;
    }

    return paymentIdVariant.toInt();
}

QVector<Payment> PaymentDao::getPaymentsForInvoice(int invoiceId) const {
    QVector<Payment> results;

    QSqlDatabase db = m_dbManager.database();
    if (!db.isOpen()) {
        qCritical() << "PaymentDao::getPaymentsForInvoice - Database connection is not open!";
        return results;
    }

    QSqlQuery query(db);
    query.prepare(
        "SELECT payment_id, invoice_id, payment_date, amount, method, notes "
        "FROM payments "
        "WHERE invoice_id = :invoice_id "
        "ORDER BY payment_date ASC, payment_id ASC;"
        );
    query.bindValue(":invoice_id", invoiceId);

    if (!query.exec()) {
        qCritical() << "Error fetching payments for invoice:" << query.lastError().text();
        return results;
    }

    while (query.next()) {
        Payment payment;
        payment.id = query.value("payment_id").toInt();
        payment.invoiceId = query.value("invoice_id").toInt();
        payment.paymentDate = query.value("payment_date").toString();
        payment.amountCents = query.value("amount").toInt();
        payment.method = query.value("method").toString();
        payment.notes = query.value("notes").toString();
        results.append(payment);
    }

    return results;
}

int PaymentDao::getTotalPaidForInvoice(int invoiceId) const {
    QSqlDatabase db = m_dbManager.database();
    if (!db.isOpen()) {
        qCritical() << "PaymentDao::getTotalPaidForInvoice - Database connection is not open!";
        return 0;
    }

    QSqlQuery query(db);
    query.prepare("SELECT COALESCE(SUM(amount), 0) AS total FROM payments WHERE invoice_id = :invoice_id;");
    query.bindValue(":invoice_id", invoiceId);

    if (!query.exec() || !query.next()) {
        qCritical() << "Error summing payments for invoice:" << query.lastError().text();
        return 0;
    }

    return query.value("total").toInt();
}
