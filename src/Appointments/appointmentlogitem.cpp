#include "appointmentlogitem.h"

AppointmentLogItem::AppointmentLogItem(int msid, QDateTime startDate,int Duration, QDateTime endDate, qint64 startBlockID, qint64 endBlockID, int status, DBManager *db, QObject *parent)
    : QObject{parent}
{
    m_msid = msid;
    m_startDate = startDate;
    m_duration = Duration;
    m_endDate = endDate;
    m_startBlock = startBlockID;
    m_endBlock = endBlockID;
    m_status = status;
    m_db = db;
    m_isPublished = false;
}

int AppointmentLogItem::msid() const
{
    return m_msid;
}

void AppointmentLogItem::setMsid(int newMsid)
{
    if (m_msid == newMsid)
        return;
    m_msid = newMsid;
    emit msidChanged();
}

QString AppointmentLogItem::startDate() const
{
    return m_startDate.toString("dd-MM-yyyy HH:mm");
}

QDateTime AppointmentLogItem::StartDate() const{
    return m_startDate;
}

void AppointmentLogItem::setStartDate(const QString &newStartDate)
{
    QDateTime a = QDateTime::fromString(newStartDate, "dd-MM-yyyy HH:mm");
    if(!a.isValid()){
        return;
    }

    if (m_startDate == a)
        return;
    m_startDate = a;
    m_saveRequired = true;
    emit startDateChanged();
}

void AppointmentLogItem::setStartDate(const QDateTime &newStartDate){
    if (m_startDate == newStartDate)
        return;
    m_startDate = newStartDate;
    m_saveRequired = true;
    emit startDateChanged();
}

QString AppointmentLogItem::duration() const
{
    return  durationToString(m_duration);
}

int AppointmentLogItem::Duration() const{
    return m_duration;
}

void AppointmentLogItem::setDuration(const QString &newDuration)
{
    int dur = durationFromString(newDuration);


    if (m_duration == dur)
        return;
    m_duration = dur;
    m_saveRequired = true;
    emit durationChanged();
}

void AppointmentLogItem::setDuration(const int &newDuration){
    if (m_duration == newDuration)
        return;
    m_duration = newDuration;
    m_saveRequired = true;
    emit durationChanged();
}

QString AppointmentLogItem::endDate() const
{
    return m_endDate.toString("dd-MM-yyyy HH:mm");
}

QDateTime AppointmentLogItem::EndDate() const{
    return m_endDate;
}

void AppointmentLogItem::setEndDate(const QString &newEndDate)
{
    QDateTime a = QDateTime::fromString(newEndDate, "dd-MM-yyyy HH:mm");
    if(!a.isValid()){
        return;
    }
    if (m_endDate == a)
        return;
    m_endDate = a;
    m_saveRequired = true;
    emit endDateChanged();
}

void AppointmentLogItem::setEndDate(const QDateTime &newEndDate){
    if (m_endDate == newEndDate)
        return;
    m_endDate = newEndDate;
    m_saveRequired = true;
    emit endDateChanged();
}

int AppointmentLogItem::startBlock() const
{
    return m_startBlock;
}

void AppointmentLogItem::setStartBlock(int newStartBlock)
{
    if (m_startBlock == newStartBlock)
        return;
    m_startBlock = newStartBlock;
    m_saveRequired = true;
    emit startBlockChanged();
}

int AppointmentLogItem::endBlock() const
{
    return m_endBlock;
}

void AppointmentLogItem::setEndBlock(int newEndBlock)
{
    if (m_endBlock == newEndBlock)
        return;
    m_endBlock = newEndBlock;
    m_saveRequired = true;
    emit endBlockChanged();
}

int AppointmentLogItem::status() const
{
    return m_status;
}

void AppointmentLogItem::setStatus(int newStatus)
{
    if (m_status == newStatus)
        return;
    m_status = newStatus;
    m_saveRequired = true;
    emit statusChanged();
}

QString AppointmentLogItem::statusString() const
{
    switch(m_status){
    case logStatus::Planned:
        return "Planned";
    case logStatus::Block:
        return "Block";
    case logStatus::WorkedOn:
        return "Worked On";
    }
    return "Invalid Status";
}


bool AppointmentLogItem::locked() const
{
    return m_locked;
}

void AppointmentLogItem::setLocked(bool newLocked)
{
    if (m_locked == newLocked)
        return;
    m_locked = newLocked;
    emit lockedChanged();
}

bool AppointmentLogItem::saveRequired() const
{
    return m_saveRequired;
}

void AppointmentLogItem::setSaveRequired(bool newSaveRequired)
{
    if (m_saveRequired == newSaveRequired)
        return;
    m_saveRequired = newSaveRequired;
    emit saveRequiredChanged();
}

void AppointmentLogItem::save(int appointmentID){
    if(appointmentID > 0){
        QJsonObject obj;
        obj.insert("logID", msid());
        obj.insert("logAppointmentID", appointmentID);
        obj.insert("logStartDate", this->StartDate().toSecsSinceEpoch());
        obj.insert("logDuration", this->Duration());
        obj.insert("logEndDate", this->EndDate().toSecsSinceEpoch());
        obj.insert("logStartBlock", startBlock());
        obj.insert("logEndBlock", endBlock());
        obj.insert("logStatus", status());
        DBRequest *request = new DBRequest(RequestTypes::SaveAppointmentLog, obj);

            connect(request, SIGNAL(finished(QJsonObject)), this, SLOT(afterSave(QJsonObject)));
        m_db->AddRequest(request);
    }

}

void AppointmentLogItem::afterSave(QJsonObject data){

    if(data.value("msg").toString() == "OK"){
            int msid = data.value("id").toInt();
            if((this->m_msid == -1) && (msid > 0)){
                this->setMsid(msid);
            }
    }

}

bool AppointmentLogItem::isPublished() const
{
    return m_isPublished;
}

void AppointmentLogItem::setIsPublished(bool newIsPublished)
{
    if (m_isPublished == newIsPublished)
        return;
    m_isPublished = newIsPublished;
    emit isPublishedChanged();
}

bool AppointmentLogItem::isSaved() const
{
    return m_isSaved;
}

void AppointmentLogItem::setIsSaved(bool newIsSaved)
{
    if (m_isSaved == newIsSaved)
        return;
    m_isSaved = newIsSaved;
    emit isSavedChanged();
}

