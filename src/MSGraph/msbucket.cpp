#include "msbucket.h"

MSBucket::MSBucket(QString ID, SolidGraph *srGrpah, QObject *parent)
    : QObject{parent}
{
    this->m_id = ID;
    this->srGraph = srGrpah;
    this->loadData();
}

void MSBucket::loadData(){
    GraphBufferItem *item = new GraphBufferItem(GraphBufferType::GET, "https://graph.microsoft.com/v1.0/planner/buckets/"+ this->m_id, QJsonObject());
    connect(item, SIGNAL(finished(QJsonObject)), this, SLOT(AfterLoad(QJsonObject)));
    this->srGraph->AddBuffer(item);
}

void MSBucket::AfterLoad(QJsonObject data){
    this->setTitle(data.value("name").toString());
    int bp = 0;
    bp++;
}

QString MSBucket::id() const
{
    return m_id;
}

void MSBucket::setId(const QString &newId)
{
    if (m_id == newId)
        return;
    m_id = newId;
    emit idChanged();
}

QString MSBucket::title() const
{
    return m_title;
}

void MSBucket::setTitle(const QString &newTitle)
{
    if (m_title == newTitle)
        return;
    m_title = newTitle;
    emit titleChanged();
}

void MSBucket::addTask(MSTask *task){
    this->tasks.push_back(task);
}
