#include "job.h"

Job::Job(DBManager *db, int msid, QString no, QString title, QString client, QDateTime jobDate, QDateTime jobStartDate, QDateTime jobPickDate,bool isEdit, QObject *parent)
    : QObject{parent}
{
    this->db = db;
    this->m_msid = msid;
    this->m_no = no;
    this->m_title = title;
    this->m_client = client;
    this->m_jobDate = jobDate;
    this->m_jobStartDarte = jobStartDate;
    this->m_jobPickDate = jobPickDate;
    this->m_inUse = false;
    this->m_editJob = isEdit;
    this->m_statusColor = "#FFFFFF";
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

int Job::msid() const{
    return m_msid;
}

QString Job::no() const{
    return m_no;
}

QString Job::title() const{
    return m_title;
}

QString Job::client() const{
    return m_client;
}

QString Job::jobDate() const{
    return m_jobDate.toString("dd-MM-yyyy HH:mm");
}

QDateTime Job::JobDate() const{
    return m_jobDate;
}

QString Job::jobStartDate() const{
    return m_jobStartDarte.toString("dd-MM-yyyy HH:mm");
}

QDateTime Job::JobStartDate() const{
    return m_jobStartDarte;
}

QString Job::jobPickDate() const{
    QString tmp = m_jobPickDate.toString("dd-MM-yyyy HH:mm");
    return m_jobPickDate.toString("dd-MM-yyyy HH:mm");
}

QDateTime Job::JobPickDate() const{
    return m_jobPickDate;
}

bool Job::inUse() const{
    return m_inUse;
}

bool Job::isEditJob() const{
    return m_editJob;
}

void Job::setmsid(int msid){
    if(m_msid == msid){
        return;
    }
    m_msid = msid;
    emit this->msidChanged();
}

void Job::setno(QString jobNo){
    if(m_no == jobNo){
        return;
    }
    m_no = jobNo;
    emit this->noChanged();
}

void Job::settitle(QString title){
    if(m_title == title){
        return;
    }
    m_title = title;
    emit this->titleChanged();
}

void Job::setclient(QString client){
    if(m_client == client){
        return;
    }
    m_client = client;
    emit this->clientChanged();
}

void Job::setjobDate(QString date){
    QDateTime a = QDateTime::fromString(date, "dd-MM-yyyy HH:mm");
    if(!a.isValid()){
        return;
    }

    if(m_jobDate == a){
        return;
    }
    m_jobDate = a;
    emit this->jobDateChanged();

}

void Job::setjobStartDate(QString date){
    QDateTime a = QDateTime::fromString(date, "dd-MM-yyyy HH:mm");
    if(!a.isValid()){
        return;
    }
    if(m_jobStartDarte == a){
        return;
    }
    m_jobStartDarte = a;
    emit this->jobStartDateChanged();
}

void Job::setjobPickDate(QString date){
    QDateTime a = QDateTime::fromString(date, "dd-MM-yyyy HH:mm");
    if(!a.isValid()){
        return;
    }
    if(m_jobPickDate == a){
        return;
    }
    m_jobPickDate = a;
    emit this->jobPickDateChanged();
}

void Job::setjobDate(QDateTime date){


    if(m_jobDate == date){
        return;
    }
    m_jobDate = date;
    emit this->jobDateChanged();

}

void Job::setjobStartDate(QDateTime date){

    if(m_jobStartDarte == date){
        return;
    }
    m_jobStartDarte = date;
    emit this->jobStartDateChanged();
}

void Job::setjobPickDate(QDateTime date){

    if(m_jobPickDate == date){
        return;
    }
    m_jobPickDate = date;
    emit this->jobPickDateChanged();
}


void Job::setInUse(bool inUse){
    if(m_inUse == inUse){
        return;
    }
    m_inUse = inUse;
    emit this->inUseChanged();
}

void Job::setisEditJob(bool edit){
    if(m_editJob == edit){
        return;
    }
    m_editJob = edit;
    emit this->isEditJobChanged();
}

void Job::save(QString jobNo, QString title, QString client, QString jobDate, QString jobStartDate, QString jobPickDate){
    bool ischanged = false;
    if(m_no != jobNo){
        ischanged = true;
    }
    if(m_title != title){
        ischanged = true;
    }
    if(m_client != client){
        ischanged = true;
    }
    QDateTime a = QDateTime::fromString(jobDate, "dd-MM-yyyy HH:mm");
    if(m_jobDate != a){
        ischanged = true;
    }
    a = QDateTime::fromString(jobStartDate, "dd-MM-yyyy HH:mm");
    if(m_jobStartDarte != a){
        ischanged = true;
    }
    a = QDateTime::fromString(jobPickDate, "dd-MM-yyyy HH:mm");
    if(m_jobPickDate != a){
        ischanged = true;
    }

    this->setno(jobNo);
    this->settitle(title);
    this->setclient(client);
    this->setjobDate(jobDate);
    this->setjobStartDate(jobStartDate);
    this->setjobPickDate(jobPickDate);

    if(ischanged){
        QJsonObject data;
        data.insert("msid", m_msid);
        data.insert("jobNo", m_no);
        data.insert("jobTitle", m_title);
        data.insert("jobClient", m_client);
        data.insert("jobDate", m_jobDate.toSecsSinceEpoch());
        data.insert("jobStartDate", m_jobStartDarte.toSecsSinceEpoch());
        data.insert("jobPickDate", m_jobPickDate.toSecsSinceEpoch());
        data.insert("lastEdit", QDateTime::currentSecsSinceEpoch());
        DBRequest *request = new DBRequest(RequestTypes::UpdateJob, data, this);
        connect(request, SIGNAL(finished(QJsonObject)), this, SLOT(AfterUpdate(QJsonObject)));
        this->db->AddRequest(request);
    }
}

void Job::AfterUpdate(QJsonObject data){
    int msid = data.value("id").toInt();
    if(msid != 0){
        this->setmsid(msid);
    }
    int bp = 0;
    bp++;
}

QString Job::statusColor() const
{
    return m_statusColor;
}

void Job::setStatusColor(const QString &newStatusColor)
{
    if (m_statusColor == newStatusColor)
        return;
    m_statusColor = newStatusColor;
    emit statusColorChanged();
}

int Job::secDiff() const
{
    return m_secDiff;
}

void Job::setSecDiff(int newSecDiff)
{
    if (m_secDiff == newSecDiff)
        return;
    m_secDiff = newSecDiff;
    emit secDiffChanged();
}
