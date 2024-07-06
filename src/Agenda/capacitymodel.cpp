#include "capacitymodel.h"

CapacityModel::CapacityModel(Agenda *agenda, QObject *parent)
    : QAbstractListModel{parent}
{
    m_agenda = agenda;
    m_isLoading = false;
    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}



int CapacityModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_data.count();
}

QVariant CapacityModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    if(row < 0 || row >= m_data.count()) {
        return QVariant();
    }
    const CapacityItem  *item = m_data.at(row);
    switch(role) {
    case MonthNameRole:
        return item->month();
    case CapPercentageRol:
        return item->capPercentage();
    case WorkableHoursRole:
        return item->workabledHours();
    case HoursFromLastMonthRole:
        return item->hoursFromLastMoth();
    case PlannedHoursRole:
        return item->plannedHours();
    case WorkedHoursRole:
        return item->workedHours();
    case ResultHoursRole:
        return item->resultHours();
    case BoxColorRole:
        return item->capColor();
    case CurMonthRole:
        return item->isCurMonth();
    case PercentRole:
        return item->percentage();
    }


    return QVariant();
}

QHash<int, QByteArray> CapacityModel::roleNames() const
{
    auto roles = QAbstractListModel::roleNames();
    roles[MonthNameRole] = "Month";
    roles[CapPercentageRol] = "CapPercentage";
    roles[WorkableHoursRole] = "WorkableHours";
    roles[HoursFromLastMonthRole] = "HoursFromLastMonth";
    roles[PlannedHoursRole] = "PlannedHours";
    roles[WorkedHoursRole] = "WorkedHours";
    roles[ResultHoursRole] = "Result";
    roles[BoxColorRole] = "BoxColor";
    roles[CurMonthRole] = "CurMonth";
    roles[PercentRole] = "Percentage";

    return roles;
}

CapacityItem *CapacityModel::get(int row){
    if((row < 0) || (row >= m_data.count())){
        //return jobs->editJob;
        int bp = 0;
        bp++;
        return NULL;
    }
    return m_data[row];
}

bool CapacityModel::tmpyActive() const
{
    return m_tmpyActive;
}

void CapacityModel::setTmpyActive(bool newTmpyActive)
{
    if(newTmpyActive == m_tmpyActive){
        return;
    }
    m_tmpyActive = newTmpyActive;
    emit this->tmpyActiveChanged();
}


bool CapacityModel::isLoading() const
{
    return m_isLoading;
}

void CapacityModel::setIsLoading(bool newIsLoading)
{
    if (m_isLoading == newIsLoading)
        return;
    m_isLoading = newIsLoading;
    emit isLoadingChanged();
}

void CapacityModel::Process(bool save){
    this->setIsLoading(true);
    this->exit = false;
    //wait for loading finished

    /*
    while(m_agenda->agendaLoading()){
        QThread::msleep(10);
       // qApp->processEvents();
    }
    while(m_agenda->plannerRunning()){
        QThread::msleep(10);
       //  qApp->processEvents();
    }
*/

    if(save){
    DBRequest *request = new DBRequest(RequestTypes::DeleteCapacity, QJsonObject());
    connect(request, SIGNAL(finished(QJsonObject)), this, SLOT(DBDebug(QJsonObject)));
    m_agenda->db->AddRequest(request);
    }



    beginResetModel();
    for(int i = 0; i < this->m_data.size(); i++){
        delete m_data[i];
    }
    m_data.clear();
    m_data.shrink_to_fit();


    int TMPYFirstBlockID = m_agenda->agendaBlocks[m_agenda->agendaBlocks.size() -1]->blockID + 100; // 100 om er zeker van te zijn dat hij niet getriggerd word
    if(m_agenda->tmpyActive()){
        TMPYFirstBlockID = m_agenda->TMPYAgendaBlocks[0]->blockID;
    }

    bool useTMPY = false;
    int workable_minutes = 0;
    int planned_minutes = 0;
    int worked_minutes = 0;
    float overuren_vorige_maand = 0;
    QDate CurDate = m_agenda->agendaBlocks[0]->m_startTime.date();
    int CurMonth = CurDate.month();
    CapacityItem *item = NULL;
    int index = 0;
    AgendaBlock *block = NULL;
    bool isCurrentMonth = false;
    while(1){
        if(this->exit){
            break;
        }



        if(useTMPY){
            if(index >= m_agenda->TMPYAgendaBlocks.size()){
                break;
            }
            block = m_agenda->TMPYAgendaBlocks[index];
        }else{
            if(index >= m_agenda->agendaBlocks.size()){
                break;
            }
            block = m_agenda->agendaBlocks[index];
            if(block->blockID == TMPYFirstBlockID){
                block = m_agenda->TMPYAgendaBlocks[0];
                index = 0;
                useTMPY = true;
            }
        }

        CurDate = block->m_startTime.date();
        if(CurDate.month() != CurMonth){


            float workable_hours = (float)workable_minutes / 60;
            QString workHours = QString::number(round(workable_hours * 100) / 100);
            float planned_hours = (float)planned_minutes / 60;
            QString planHours = QString::number(round(planned_hours * 100) / 100);
            float worked_Hours = (float)worked_minutes / 60;
            QString workedHours = QString::number(round(worked_Hours * 100) / 100);
            float result = workable_hours - planned_hours - worked_Hours;
            QString strresult = QString::number(round(result * 100) / 100);
            float percent = ((planned_hours + worked_Hours) / workable_hours) * 100;
            QString strpercent = QString::number(round(percent)) + "%";
            QString lastoveruren = QString::number(round(overuren_vorige_maand * 100) / 100);
            int red = 0;
            int green = 255;
            int blue = 0;
            if(percent > 100){
                red = 255;
                green = 0;
            }else if(percent > 75){
                red = 255;
                green = 255 - ((percent-75) * 10);
            }else if(percent > 50){
                 red = (percent - 50) * 10;
                green = 255;
            }else{
                red = 0;
                green = 255;
            }
            QColor clr(red,green, blue);
            QString hex = clr.name();


            CapacityItem *item = new CapacityItem(this->monthToString(CurMonth), strpercent, hex, workHours, lastoveruren, planHours, workedHours, strresult, isCurrentMonth, percent);
            this->m_data.push_back(item);

            if(save){
            QJsonObject obj;
            obj.insert("capUserName", m_agenda->db->DBInfo->username);
            obj.insert("capMonthStart", block->m_startTime.toSecsSinceEpoch());
            obj.insert("capText", strpercent);
            obj.insert("workableHours", workable_hours);
            obj.insert("hoursLastMonth", overuren_vorige_maand);
            obj.insert("plannedHours", planned_hours);
            obj.insert("workedHours", worked_Hours);
            obj.insert("capResult", result);
            obj.insert("boxColor", hex);
            obj.insert("capMonth", this->monthToString(CurMonth));
            obj.insert("capYear", "");

            DBRequest *request = new DBRequest(RequestTypes::SaveCapacity, obj);
            connect(request, SIGNAL(finished(QJsonObject)), this, SLOT(DBDebug(QJsonObject)));
            m_agenda->db->AddRequest(request);
            }


            workable_minutes = 0;
            planned_minutes = 0;
            worked_minutes = 0;
            overuren_vorige_maand = 0;
            isCurrentMonth = false;
            CurMonth = CurDate.month();
        }

        if((CurDate.month()  == QDate::currentDate().month()) && (CurDate.year() == QDate::currentDate().year())){
            isCurrentMonth = true;
        }
        overuren_vorige_maand = overuren_vorige_maand + block->overurenvorigemaand;
        if(block->isPlannable){
            workable_minutes = workable_minutes + 15;
        }
        for(int i = 0; i < block->items.size(); i++){
            if((block->items[i]->Type == AgendaTypes::appointmentType) && (block->items[i]->appointment != NULL)){
                if((block->items[i]->isClosed) && (block->items[i]->appointment->calcTime())){
                    worked_minutes = worked_minutes + 15;
                }else if((block->items[i]->appointment->calcTime())){
                    planned_minutes = planned_minutes + 15;
                }
            }
            //CODE FOR TASKS
        }
        index++;
    }
    if(useTMPY){
        this->setTmpyActive(true);
    }else{
        this->setTmpyActive(false);
    }

    //removing the first
    if(m_data.size() > 0){
    delete m_data[0];
        m_data.erase(m_data.begin());
    }
    endResetModel();
    this->setIsLoading(false);
}

QString CapacityModel::monthToString(int month){
    switch(month){
    case 1:
        return "JAN";
    case 2:
        return "FEB";
    case 3:
        return "MAR";
    case 4:
        return "APR";
    case 5:
        return "MAY";
    case 6:
        return "JUN";
    case 7:
        return "JUL";
    case 8:
        return "AUG";
    case 9:
        return "SEP";
    case 10:
        return "OKT";
    case 11:
        return "NOV";
    case 12:
        return "DEC";
    }

    return "Date Not Found";
}

void CapacityModel::DBDebug(QJsonObject msg){
    int bp = 0;
    bp++;
}
