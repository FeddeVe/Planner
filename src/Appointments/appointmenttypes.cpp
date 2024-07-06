#include "appointmenttypes.h"

AppointmentTypes::AppointmentTypes(QObject *parent)
    : QAbstractListModel{parent}
{
    this->LoadModel();
     QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

int AppointmentTypes::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.count();
}

QVariant AppointmentTypes::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row < 0 || row >= m_data.count()) {
        return QVariant();
    }
    const AppointmentType  *type = m_data.at(row);
    switch(role) {
    case AppointmentTypes::IDRole:
        return type->index();
    case AppointmentTypes::LabelRole:
        return type->label();
    case AppointmentTypes::ColorRole:
        return type->clr();
    case AppointmentTypes::CalcRole:
        return type->calcTime();
    }
    return QVariant();
}

QHash<int, QByteArray> AppointmentTypes::roleNames() const
{
    auto roles = QAbstractListModel::roleNames();
    roles[IDRole] = "Index";
    roles[LabelRole] = "label";
    roles[ColorRole] = "clr";
    roles[CalcRole] = "calcHours";
    return roles;
}

void AppointmentTypes::LoadModel(){
    beginResetModel();
    AppointmentType *t = new AppointmentType(0, "01 SR TD", "#0432ca", "#660432ca", true);
    this->m_data.push_back(t);
    t = new AppointmentType(1, "05 SR Enginering", "#bfef8a","#66bfef8a", true);
    this->m_data.push_back(t);
    t = new AppointmentType(2, "64 SR Administratie", "#b04fc8","#66b04fc8", true);
    this->m_data.push_back(t);
    t = new AppointmentType(3, "69 SR Doordeweekse Feestdagen", "#3df27d","#663df27d", true);
    this->m_data.push_back(t);
    t = new AppointmentType(4, "55 SR Logistiek", "#d27048","#66d27048", true);
    this->m_data.push_back(t);
    t = new AppointmentType(5, "50 SR Magazijn", "#5e0cec","#665e0cec", true);
    this->m_data.push_back(t);
    t = new AppointmentType(6, "60 SR Meetings en Vergaderingen", "#c2467b","#66c2467b", true);
    this->m_data.push_back(t);
    t = new AppointmentType(7, "54 SR Onderhoud", "#e91177","#66e91177", true);
    this->m_data.push_back(t);
    t = new AppointmentType(8, "58 SR R&D", "#FF3ffec6","#663ffec6", true);
    this->m_data.push_back(t);
    t = new AppointmentType(9, "52 SR Sales", "#FFb16c4a","#66b16c4a", true);
    this->m_data.push_back(t);
    t = new AppointmentType(10, "06 SR Uitvoer", "#f37836","#66f37836", true);
    this->m_data.push_back(t);
    t = new AppointmentType(11, "Block", "#FF0000","#66FF0000", false);
    this->m_data.push_back(t);
    t = new AppointmentType(12, "OuderschapsVerlof", "#00FFFF","#6600FFFF", true);
    this->m_data.push_back(t);
    t = new AppointmentType(13, "03 SI Engeniring", "#bfef8a","#66bfef8a", true);
    this->m_data.push_back(t);
    t = new AppointmentType(14, "04 SI Uitvoer", "#f37836","#66f37836", true);
    this->m_data.push_back(t);
    t = new AppointmentType(15, "Vakantie", "#00ff00","#6600ff00", true);
    this->m_data.push_back(t);
    t = new AppointmentType(16, "Compensatie", "#ffff00","#66ffff00", true);
    this->m_data.push_back(t);
    t = new AppointmentType(17, "Rust Tijd", "#008888","#66008888", false);
    this->m_data.push_back(t);

    std::sort( m_data.begin( ), m_data.end( ), [ ]( const AppointmentType *lhs, const AppointmentType *rhs )
         {
        return lhs->label() < rhs->label();
         });

    for(int i = 0; i < m_data.size(); i++){
       // m_data[i]->setIndex(i);
    }


    endResetModel();
}

AppointmentType *AppointmentTypes::get(int row){
    if((row < 0) || (row >= m_data.count())){
        return NULL;
    }
    return m_data[row];
}

AppointmentType *AppointmentTypes::getByID(int index){
    for(int i = 0; i < m_data.count(); i++){
        if(m_data[i]->index() == index){
            return m_data[i];
        }
    }
    return NULL;
}

int AppointmentTypes::GetIndex(AppointmentType *type){
    for(int i = 0; i < this->m_data.size(); i++){
        if(m_data[i] == type){
            return i;
        }
    }
    return -1;
}

int AppointmentTypes::GetBlockIndex(){
    for(int i = 0; i < m_data.size(); i++){
        if(m_data[i]->label() == "Block"){
            return m_data[i]->index();

    }
    }
        return 0;
}

