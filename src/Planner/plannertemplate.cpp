#include "plannertemplate.h"

PlannerTemplate::PlannerTemplate(int msid, QString name, Appointments *appointments, QObject *parent)
    : QAbstractListModel{parent}
{
    this->appointments = appointments;
    this->m_msid = msid;
    this->m_name = name;
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);

}

int PlannerTemplate::rowCount(const QModelIndex &parent) const
{
      Q_UNUSED(parent);
      return m_data.count();
}

int PlannerTemplate::count() const{
      return m_data.count();
}

QVariant PlannerTemplate::data(const QModelIndex &index, int role) const
{
      int row = index.row();
      if(row < 0 || row >= m_data.count()) {
          return QVariant();
      }
      const PlannerTemplateItem  *item = m_data.at(row);
      switch(role) {
      case MSIDRole:
          return item->msid();
      case IndexRole:
          return item->index();
      case LabelRole:
          return item->label();
      case PlanAsRole:
          return item->planAss();

      }


      return QVariant();
}

QHash<int, QByteArray> PlannerTemplate::roleNames() const
{
      auto roles = QAbstractListModel::roleNames();
      roles[MSIDRole] = "ID";
      roles[IndexRole] = "Index";
      roles[LabelRole] = "Label";
      roles[PlanAsRole] = "PlanAss";

      return roles;
}

void PlannerTemplate::LoadModel(const QString searchValue){
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

void PlannerTemplate::addCatagory(){
      this->insertItem();
}

PlannerTemplateItem *PlannerTemplate::insertItem(){
      m.lock();
      beginResetModel();
      PlannerTemplateItem *item = new PlannerTemplateItem(-1,0,"",0,this, this->appointments);
      this->m_data.push_back(item);
      for(int i = 0; i < this->m_data.size(); i++){
          this->m_data[i]->setIndex(i);
      }
      endResetModel();
      m.unlock();
      return item;
}

void PlannerTemplate::moveDown(PlannerTemplateItem *item){
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

void PlannerTemplate::moveUp(PlannerTemplateItem *item){
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


PlannerTemplateItem *PlannerTemplate::get(int row) const{
      //QMutexLocker lock( &m);
      if((row < 0) || (row >= m_data.count())){
          return NULL;
      }
      return m_data[row];
}


QString PlannerTemplate::name() const
{
      return m_name;
}

void PlannerTemplate::setName(const QString &newName)
{
      if (m_name == newName)
          return;
      m_name = newName;
      emit nameChanged();
}




int PlannerTemplate::msid() const
{
      return m_msid;
}

void PlannerTemplate::setMsid(int newMsid)
{
      if (m_msid == newMsid)
          return;
      m_msid = newMsid;
      emit msidChanged();
}
