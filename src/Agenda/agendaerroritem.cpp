#include "agendaerroritem.h"

AgendaErrorItem::AgendaErrorItem(QDateTime datum, QString errortext, bool isTMPY, QObject *parent)
    : QObject{parent}
{
    this->m_datum = datum;
    this->m_message = errortext;
    this->m_isTMPY = isTMPY;
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

QString AgendaErrorItem::datum() const
{
    return m_datum.toString("dd/MM/yyyy");
}

QDateTime AgendaErrorItem::Datum() const{
    return m_datum;
}

QString AgendaErrorItem::message() const
{
    return m_message;
}

void AgendaErrorItem::setMessage(const QString &newMessage)
{
    if (m_message == newMessage)
        return;
    m_message = newMessage;
    emit messageChanged();
}

bool AgendaErrorItem::isTMPY() const
{
    return m_isTMPY;
}
