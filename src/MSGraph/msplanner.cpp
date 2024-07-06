#include "msplanner.h"

MSPlanner::MSPlanner(QString ID, SolidGraph *srGraph, QObject *parent)
    : QObject{parent}
{
    this->srGraph = srGraph;
    this->m_id = ID;
    this->loadPlanner();
}

MSPlanner::~MSPlanner(){
    for(int i = 0; i < this->categories.size(); i++){
        this->categories[i]->deleteLater();
    }
}

void MSPlanner::loadPlanner(){
    GraphBufferItem *item = new GraphBufferItem(GraphBufferType::GET, "https://graph.microsoft.com/v1.0/planner/plans/"+ this->m_id, QJsonObject());
    connect(item, SIGNAL(finished(QJsonObject)), this, SLOT(AfterLoad(QJsonObject)));
    this->srGraph->AddBuffer(item);
    item = new GraphBufferItem(GraphBufferType::GET, "https://graph.microsoft.com/v1.0/planner/plans/"+ this->m_id + "/details", QJsonObject() );
    connect(item, SIGNAL(finished(QJsonObject)), this, SLOT(AfterLoadDetails(QJsonObject)));
    this->srGraph->AddBuffer(item);
}

void MSPlanner::AfterLoad(QJsonObject data){
    this->setTitle(data.value("title").toString());
    int bp = 0;
    bp++;
}

void MSPlanner::AfterLoadDetails(QJsonObject data){
    QJsonObject categories = data.value("categoryDescriptions").toObject();
    for(int i = 0; i < categories.keys().size(); i++){
        QString val = categories.value(categories.keys()[i]).toString();
        this->categories.push_back(new MSCategorys(categories.keys()[i], val));
        int bp = 0;
        bp++;
    }
    int bp = 0;
    bp++;
}

QString MSPlanner::id() const
{
    return m_id;
}

void MSPlanner::setId(const QString &newId)
{
    if (m_id == newId)
        return;
    m_id = newId;
    emit idChanged();
}


QString MSPlanner::title() const
{
    return m_title;
}

void MSPlanner::setTitle(const QString &newTitle)
{
    if (m_title == newTitle)
        return;
    m_title = newTitle;
    emit titleChanged();
}

MSBucket *MSPlanner::getBucket(QString ID){
    for(int i = 0; i < this->buckets.size(); i++){
        if(this->buckets[i]->id() == ID){
            return this->buckets[i];
        }
    }

    MSBucket *bucket = new MSBucket(ID, this->srGraph);
    this->buckets.push_back(bucket);
    return bucket;

}
