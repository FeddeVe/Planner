#include "plannertemplateitem.h"

PlannerTemplateItem::PlannerTemplateItem(int msid, int index, QString label, int appointmentTypeID,PlannerTemplate *Template, Appointments *appointments,QObject *parent)
    : QAbstractListModel{parent}
{
    this->m_msid = msid;
    this->m_index = index;
    this->m_label = label;
    this->appointments = appointments;
    this->m_template = Template;
    this->m_planAss = this->appointments->types()->getByID(appointmentTypeID);


    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);

}

int PlannerTemplateItem::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.count();
}

int PlannerTemplateItem::count() const{
    return m_data.count();
}

QVariant PlannerTemplateItem::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row < 0 || row >= m_data.count()) {
        return QVariant();
    }
    const PlannerTemplateSubItem  *item = m_data.at(row);
    switch(role) {
    case MSIDRole:
        return item->msid();
    case IndexRole:
        return item->index();
    case TitleRole:
        return item->title();
    case DefDeadlineRole:
        return item->defaultDeadline();
    case CalcDurationRole:
        return item->CalculatedDuration();
    }


    return QVariant();
}

QHash<int, QByteArray> PlannerTemplateItem::roleNames() const
{
    auto roles = QAbstractListModel::roleNames();
    roles[MSIDRole] = "ID";
    roles[IndexRole] = "Index";
    roles[TitleRole] = "Title";
    roles[DefDeadlineRole] = "DefaultDeadline";
    roles[CalcDurationRole] = "CalculatedDuration";

    return roles;
}

void PlannerTemplateItem::LoadModel(const QString searchValue){
    // m.lock();
    m.lock();
    /*
      QString sval = searchValue.toUpper();

      beginResetModel();
      this->m_data.clear();
      this->m_data.shrink_to_fit();
      int index = 0;
      Job *j = jobs->getJob(index);
      while(j!=NULL){
          try{
              if((j->no().toUpper().contains(sval)) || (j->title().toUpper().contains(sval)) || (j->client().toUpper().contains(sval))){
                  this->m_data.push_back(j);
              }
          }catch(...){
              int bp = 0;
              bp++;
          }
          index++;
          j = jobs->getJob(index);
          // emit this->dataChanged(index(0),index(0);
      }
      //this->m_data.push_back(jobs->editJob);
      endResetModel();
*/
    m.unlock();
}

void PlannerTemplateItem::addItem(){
    m.lock();
    beginResetModel();
    PlannerTemplateSubItem *sub = new PlannerTemplateSubItem(-1, 0, "", 0, 0);
    this->m_data.push_back(sub);
    for(int i = 0; i < m_data.size(); i++){
        m_data[i]->setIndex(i);
    }
    endResetModel();
    m.unlock();
}

void PlannerTemplateItem::MoveDown(PlannerTemplateSubItem *item){
    m.lock();
    beginResetModel();
    for(int i = 0; i < m_data.size(); i++){
        if(m_data[i] == item){
            if(i< m_data.size()-1){
                m_data.move(i, i+1);
            }
        }
    }

    for(int i = 0; i < this->m_data.size(); i++){
        this->m_data[i]->setIndex(i);
    }
    endResetModel();
    m.unlock();
}

void PlannerTemplateItem::MoveUp(PlannerTemplateSubItem *item){
    m.lock();
    beginResetModel();
    for(int i = 0; i < m_data.size(); i++){
        if(m_data[i] == item){
            if(i>0){
                m_data.move(i, i-1);
            }
        }
    }

    for(int i = 0; i < this->m_data.size(); i++){
        this->m_data[i]->setIndex(i);
    }
    endResetModel();
    m.unlock();
}




PlannerTemplateSubItem *PlannerTemplateItem::get(int row) const{
    //QMutexLocker lock( &m);
    if((row < 0) || (row >= m_data.count())){
        return NULL;
    }
    return m_data[row];
}


int PlannerTemplateItem::msid() const
{
    return m_msid;
}

void PlannerTemplateItem::setMsid(int newMsid)
{
    if (m_msid == newMsid)
        return;
    m_msid = newMsid;
    emit msidChanged();
}

int PlannerTemplateItem::index() const{
    return m_index;
}

void PlannerTemplateItem::setIndex(int newIndex){
    if(this->m_index == newIndex){
        return;
    }
    this->m_index = newIndex;
    emit this->indexChanged();
}

QString PlannerTemplateItem::label() const
{
    return m_label;
}

void PlannerTemplateItem::setLabel(const QString &newLabel)
{
    if (m_label == newLabel)
        return;
    m_label = newLabel;
    emit labelChanged();
}

int PlannerTemplateItem::planAss() const
{
    if(this->m_planAss != NULL){
        return this->appointments->types()->GetIndex(this->m_planAss);
    }
    return 0;
}

void PlannerTemplateItem::setPlanAss(int newPlanAss)
{
    AppointmentType *p = this->appointments->types()->get(newPlanAss);

    if (m_planAss == p)
        return;
    m_planAss = p;
    emit planAssChanged();
    emit clrChanged();
}

QString PlannerTemplateItem::clr() const
{
    if(this->m_planAss != NULL){
        return this->m_planAss->clr();
    }
    return "#FFFFFF";
}

void PlannerTemplateItem::setClr(const QString &newClr)
{
    if (m_clr == newClr)
        return;
    m_clr = newClr;
    emit clrChanged();
}

void PlannerTemplateItem::moveUp(){
    this->m_template->moveUp(this);
}

void PlannerTemplateItem::moveDown(){
    this->m_template->moveDown(this);
}
