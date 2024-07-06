#include "appointmenterroritem.h"

AppointmentErrorItem::AppointmentErrorItem(QString appTitle, QString job, int appID,QString msg, QObject *parent)
    : QObject{parent}
{
    this->m_title = appTitle;
    this->m_job = job;
    this->m_id = appID;
    this->m_errMSG = msg;
}

QString AppointmentErrorItem::title() const
{
    return m_title;
}

QString AppointmentErrorItem::job() const
{
    return m_job;
}

int AppointmentErrorItem::id() const
{
    return m_id;
}

QString AppointmentErrorItem::errMSG() const
{
    return m_errMSG;
}
