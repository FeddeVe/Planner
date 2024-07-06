#include "bucketitem.h"

int CalcTimeLeft(const BucketItem *item){
    int duration = item->Duration();

    if(duration < 0){
        duration = 0;
    }
    return duration;
}

BucketItem::BucketItem(int msid, int templateID,int index, QString title, QDateTime dueDate, int duration, bool isClosed, QString msPlannerID,int planAss,QDateTime startWorkingOn, Bucket *bucket, DBManager *db, QObject *parent)
    : QAbstractListModel{parent}
{
    m_msid = msid;
    m_templateID = templateID;
    m_index = index;
    m_title = title;
    m_dueDate = dueDate;
    m_duration = duration;
    m_isClosed = isClosed;
    m_msPlannerID = msPlannerID;
    m_bucket = bucket;
    m_db = db;
    m_planAss = planAss;
    planType = m_bucket->m_appointments->types()->getByID(m_planAss);
    m_planAssIndex = m_bucket->m_appointments->types()->GetIndex(planType);
    m_startWorkingOn = startWorkingOn;
    this->m_appointment = this->m_bucket->m_appointments->getBucketItemAppointment(m_msid);
    if(this->m_appointment == NULL){
        //time to create an appointment for this
        Appointment *app = new Appointment(this->m_bucket->m_appointments, this->m_bucket->m_jobs, this->m_db, -1, m_title, m_bucket->job()->msid(), QDateTime::currentDateTime(), 0, m_bucket->job()->JobDate(), true, false,false, m_planAss, true, "DESCRIPTION MOET NOG", PlanModes::Fixed, m_bucket->msid(), m_msid, m_bucket->job()->JobDate());
        app->save(0,0);
        m_bucket->m_appointments->AddAppointment(app);
        int bp = 0;
        bp++;
    }

    this->loadData();
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

void BucketItem::loadData(){
    /*
    QJsonObject data;
    data.insert("bucketItemID", m_msid);
    data.insert("bucketID", m_bucket->msid());
    data.insert("bucketItemTemplateID", m_templateID);
    data.insert("bucketItemIndex", m_index);
    data.insert("bucketItemTitle", m_title);
    data.insert("bucketItemDueDate", m_dueDate.toSecsSinceEpoch());
    data.insert("bucketItemDuration", m_duration);
    data.insert("bucketItemIsClosed", (int)m_isClosed);
    data.insert("bucketItemMSPlannerID", m_msPlannerID);
    data.insert("bucketItemLastEdit", QDateTime::currentSecsSinceEpoch());
    DBRequest *request = new DBRequest(RequestTypes::SaveBucketItem, data);
    connect(request, SIGNAL(finished(QJsonObject)), this, SLOT(AfterSave(QJsonObject)));
    this->m_db->AddRequest(request);
*/
}

void BucketItem::AfterLoad(QJsonObject data){
    int bp = 0;
    bp++;
}


int BucketItem::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.count();
}

QVariant BucketItem::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row < 0 || row >= m_data.count()) {
        return QVariant();
    }
    /*
    const Job  *job = m_data.at(row);
    switch(role) {
    case IDRole:
        return job->msid();
    case JobNoRole:
        return job->no();
    case TitleRole:
        return job->title();
    case ClientRole:
        return job->client();
    case DateRole:
        return job->jobDate();
    case StartDateRole:
        return job->jobStartDate();
    case PickDateRole:
        return job->jobPickDate();
    case StatusColorRole:
        return job->statusColor();
    }
*/
    return QVariant();
}

QHash<int, QByteArray> BucketItem::roleNames() const
{
    auto roles = QAbstractListModel::roleNames();
    /*
    roles[IDRole] = "ID";
    roles[JobNoRole] = "JobNo";
    roles[TitleRole] = "Title";
    roles[ClientRole] = "Client";
    roles[DateRole] = "Date";
    roles[StartDateRole] = "StartDate";
    roles[PickDateRole] = "PickDate";
    roles[StatusColorRole] = "StatusColor";
*/
    return roles;
}

void BucketItem::loadModel(){
    // m.lock();
    m.lock();
    /*
    QString sval = searchValue.toUpper();

    beginResetModel();
    this->m_data.clear();
    this->m_data.shrink_to_fit();

    //this->m_data.push_back(jobs->editJob);
    this->SortList();
    endResetModel();
*/
    m.unlock();
}

BucketSubItem *BucketItem::get(int row) const{
    //QMutexLocker lock( &m);
    if((row < 0) || (row >= m_data.count())){
        return NULL;
    }
    return m_data[row];
}


void BucketItem::SortList(){
    // std::sort(m_data.begin(), m_data.end(), [](const BucketItem *a, const BucketItem *b) { return a->secDiff() < b->secDiff(); });
}

void BucketItem::save(){
    QJsonObject data;
    data.insert("bucketItemID", m_msid);
    data.insert("bucketID", m_bucket->msid());
    data.insert("bucketItemTemplateID", m_templateID);
    data.insert("bucketItemIndex", m_index);
    data.insert("bucketItemTitle", m_title);
    data.insert("bucketItemDueDate", m_dueDate.toSecsSinceEpoch());
    data.insert("bucketItemDuration", m_duration);
    data.insert("bucketItemIsClosed", (int)m_isClosed);
    data.insert("bucketItemMSPlannerID", m_msPlannerID);
    data.insert("bucketItemPlanAss", m_planAss);
    data.insert("bucketItemStartWorkingOn", m_startWorkingOn.toSecsSinceEpoch());
    data.insert("bucketItemLastEdit", QDateTime::currentSecsSinceEpoch());
    DBRequest *request = new DBRequest(RequestTypes::SaveBucketItem, data);
    connect(request, SIGNAL(finished(QJsonObject)), this, SLOT(AfterSave(QJsonObject)));
    this->m_db->AddRequest(request);
}

void BucketItem::AfterSave(QJsonObject data){
    int msid = data.value("id").toInt();
    if(msid != 0){
        this->setMsid(msid);
    }
    int bp = 0;
    bp++;
}



int BucketItem::msid() const
{
    return m_msid;
}

void BucketItem::setMsid(int newMsid)
{
    if (m_msid == newMsid)
        return;
    m_msid = newMsid;
    emit msidChanged();
}

int BucketItem::index() const
{
    return m_index;
}

void BucketItem::setIndex(int newIndex)
{
    if (m_index == newIndex)
        return;
    m_index = newIndex;
    emit indexChanged();
}

QString BucketItem::title() const
{
    return m_title;
}

void BucketItem::setTitle(const QString &newTitle)
{
    if (m_title == newTitle)
        return;
    m_title = newTitle;
    this->save();
    emit titleChanged();
}

QString BucketItem::dueDate() const
{
    if(m_dueDate.toSecsSinceEpoch() == 0){
        return "Not Set";
    }

    return m_dueDate.toString("dd-MM-yyyy HH:mm");
}

QDateTime BucketItem::DueDate() const{
    if(m_dueDate == NullDate()){
        return m_bucket->job()->JobDate();
    }
    return m_dueDate;
}



void BucketItem::setDueDate(const QString &newDueDate)
{
    QDateTime a = QDateTime::fromString(newDueDate, "dd-MM-yyyy HH:mm");
    if(!a.isValid()){
        a = QDateTime::fromSecsSinceEpoch(0);
    }

    if (m_dueDate == a)
        return;
    m_dueDate = a;
    this->save();
    emit dueDateChanged();
}

void BucketItem::SetDueDate(const QDateTime &a){

    if (m_dueDate == a)
        return;
    m_dueDate = a;
    this->save();
    emit dueDateChanged();
}

QString BucketItem::duration() const
{

    return durationToString(m_duration);
}

int BucketItem::Duration() const
{
    return m_duration;
}

void BucketItem::setDuration(const QString &newDuration)
{
    int dur = durationFromString(newDuration);
    if(dur == 0){
        int bp = 0;
        bp++;
        // code hier om duration van template te halen
    }
    if (m_duration == dur)
        return;
    m_duration = dur;
    this->save();
    emit durationChanged();
    emit durationLeftChanged();
}

void BucketItem::SetDuration(const int &duration){
    if(duration == 0){
        int bp = 0;
        bp++;
        // code hier om duration van template te halen
    }
    if (m_duration == duration)
        return;
    m_duration = duration;
    this->save();
    emit durationChanged();
}

QString BucketItem::durationLeft() const
{
    return durationToString(CalcTimeLeft(this));
}

int BucketItem::DurationLeft() const
{
    return CalcTimeLeft(this);
}

void BucketItem::setDurationLeft(const QString &newDurationLeft)
{
    int dur = durationFromString(newDurationLeft);
    if (m_durationLeft == dur)
        return;
    m_durationLeft = dur;
    emit durationLeftChanged();
}

void BucketItem::SetDurationLeft(const int &newDurationLeft){
    if (m_durationLeft == newDurationLeft)
        return;
    m_durationLeft = newDurationLeft;
    emit durationLeftChanged();
}

bool BucketItem::isClosed() const
{
    return m_isClosed;
}

void BucketItem::setIsClosed(bool newIsClosed)
{
    if (m_isClosed == newIsClosed)
        return;
    m_isClosed = newIsClosed;
    this->save();
    emit isClosedChanged();
}

int BucketItem::templateID() const
{
    return m_templateID;
}

void BucketItem::setTemplateID(int newTemplateID)
{
    if (m_templateID == newTemplateID)
        return;
    m_templateID = newTemplateID;
    emit templateIDChanged();
}

bool BucketItem::isFromTemplate() const
{
    return m_isFromTemplate;
}

void BucketItem::setIsFromTemplate(bool newIsFromTemplate)
{
    if (m_isFromTemplate == newIsFromTemplate)
        return;
    m_isFromTemplate = newIsFromTemplate;
    emit isFromTemplateChanged();
}

QString BucketItem::msPlannerID() const
{
    return m_msPlannerID;
}

void BucketItem::setMsPlannerID(const QString &newMsPlannerID)
{
    if (m_msPlannerID == newMsPlannerID)
        return;
    m_msPlannerID = newMsPlannerID;
    emit msPlannerIDChanged();
}

bool BucketItem::isLoaded() const
{
    return m_isLoaded;
}

void BucketItem::setIsLoaded(bool newIsLoaded)
{
    if (m_isLoaded == newIsLoaded)
        return;
    m_isLoaded = newIsLoaded;
    emit isLoadedChanged();
}

int BucketItem::planAss() const
{
    return m_planAss;
}

void BucketItem::setPlanAss(int newPlanAss)
{
    if (m_planAss == newPlanAss)
        return;
    m_planAss = newPlanAss;
    this->save();
    emit planColorChanged();
    emit planAssChanged();
}

QString BucketItem::planColor() const
{
    if(planType == NULL){
        return "#FFFFFF";
    }
    return planType->clr();
}

int BucketItem::planAssIndex() const
{
    return m_planAssIndex;
}

void BucketItem::setPlanAssIndex(int newPlanAssIndex)
{
    if (m_planAssIndex == newPlanAssIndex)
        return;
    m_planAssIndex = newPlanAssIndex;
    planType = m_bucket->m_appointments->appointmenttypes->get(m_planAssIndex);
    this->setPlanAss(planType->index());

    emit planAssIndexChanged();
}

bool BucketItem::isActive() const
{
    if(m_startWorkingOn.toSecsSinceEpoch() == 0){
        return false;
    }

    return true;
}
