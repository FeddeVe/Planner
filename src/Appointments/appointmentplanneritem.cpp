#include "appointmentplanneritem.h"

AppointmentPlannerItem::AppointmentPlannerItem(QDateTime starttime,  bool completed, bool fromtmpy, QObject *parent)
    : QObject{parent}
{
    this->m_datum = starttime;
    this->m_duration = 0;
    this->m_completed = completed;
    this->m_fromTMPY = fromtmpy;
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);

}

QString AppointmentPlannerItem::datum() const
{
    return m_datum.toString("dd/MM/yyyy HH:mm");
}

QDateTime AppointmentPlannerItem::Datum() const{
    return m_datum;
}

void AppointmentPlannerItem::setDatum(const QString &newDatum)
{
    QDateTime a = QDateTime::fromString("dd/MM/yyyy HH:mm");
    if(!a.isValid()){
        return;
    }

    if (m_datum == a)
        return;
    m_datum = a;
    QDateTime endDate = m_datum.addSecs(m_duration);
    if(endDate < QDateTime::currentDateTime()){
        this->setIsPast(true);
    }else{
        this->setIsPast(false);
    }
    emit datumChanged();
}

QString AppointmentPlannerItem::duration() const
{
    return durationToString(m_duration);
}

int AppointmentPlannerItem::Duration() const{
    return m_duration;
}

void AppointmentPlannerItem::setDuration(const QString &newDuration)
{
    int duration = durationFromString(newDuration);
    if (m_duration == duration)
        return;
    m_duration = duration;
    QDateTime endDate = m_datum.addSecs(m_duration);
    if(endDate < QDateTime::currentDateTime()){
        this->setIsPast(true);
    }else{
        this->setIsPast(false);
    }
    emit durationChanged();
}

QString AppointmentPlannerItem::status() const
{
    if(m_completed){
        return "Worked on";
    }else{
        return "Planned";
    }
    return m_status;
}

void AppointmentPlannerItem::setStatus(const QString &newStatus)
{
    if (m_status == newStatus)
        return;
    m_status = newStatus;
    emit statusChanged();
}

QString AppointmentPlannerItem::remarks() const
{
    return m_remarks;
}

void AppointmentPlannerItem::setRemarks(const QString &newRemarks)
{
    if (m_remarks == newRemarks)
        return;
    m_remarks = newRemarks;
    emit remarksChanged();
}

bool AppointmentPlannerItem::completed() const
{
    return m_completed;
}


void AppointmentPlannerItem::setCompleted(bool newCompleted)
{
    if (m_completed == newCompleted)
        return;
    m_completed = newCompleted;
    emit completedChanged();
}

bool AppointmentPlannerItem::fromTMPY() const{
    return m_fromTMPY;
}

void AppointmentPlannerItem::addDuration(int duration){
    this->m_duration = this->m_duration + duration;
    QDateTime endDate = m_datum.addSecs(m_duration);
    if(endDate < QDateTime::currentDateTime()){
        this->setIsPast(true);
    }else{
        this->setIsPast(false);
    }
}

bool AppointmentPlannerItem::isPast() const
{
    return m_isPast;
}

void AppointmentPlannerItem::setIsPast(bool newIsPast)
{
    if (m_isPast == newIsPast)
        return;
    m_isPast = newIsPast;
    emit isPastChanged();
}


