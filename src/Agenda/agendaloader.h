#ifndef AGENDALOADER_H
#define AGENDALOADER_H

#include <QObject>

#include "../Defines.h"
#include "agenda.h"
#include "../Appointments/appointments.h"
#include "../Planner/buckets.h"
#include "agendablockitem.h"
#include "agendaplanner.h"
#include "agendaloaderitem.h"
#include "agendadataitem.h"

QT_FORWARD_DECLARE_CLASS(Agenda);
QT_FORWARD_DECLARE_CLASS(AgendaBlockItem);
QT_FORWARD_DECLARE_CLASS(AgendaPlanner);
QT_FORWARD_DECLARE_CLASS(AgendaLoaderItem);



class AgendaLoader : public QObject
{
    Q_OBJECT
public:
    explicit AgendaLoader(Agenda *agenda, Appointments*appointments, QObject *parent = nullptr);
    bool running;
    void Run();
    void AddAction(LoaderType type, Appointment *appointent = nullptr, QDateTime startTime = QDateTime::currentDateTime(), QDateTime endtime = QDateTime::currentDateTime(), bool isClosed = false);

public slots:
    void process();
    void afterLoadItems(QJsonObject msg);
    void dbgDelete(QJsonObject msg);

signals:
    void isPlannerRunning(bool running);
    void isSaverRunning(bool running);
    void isLoaderRunning(bool running);
    void finished();

private:
    QMutex m;
    QMutex vectorMutex;

    QVector<AgendaLoaderItem*>loaderItems;
    QVector<AgendaDataItem*>dataItems;

    Agenda *agenda;
    Appointments *appointments;
    AgendaPlanner *planner;
    bool wait_for_loading;

    void LoadAgenda();
    void PlanAgenda();
    void SaveAgenda();
    void RemoveAppointment(Appointment *app);
    void RemoveAppointmentTimeFrame(Appointment *app, QDateTime start, QDateTime end);
    void SaveAppointmentTimeFrame(Appointment *app, QDateTime start, QDateTime end, bool isClosed);
    void FixeDoubleItems();
    void CloseAppointment(Appointment *app);




    qint64 getEndBlockID(int startIndex, AgendaTypes type, Appointment *appointment, bool isClosed);
    AgendaBlock *getEndBlock(int startIndex, AgendaTypes type, Appointment *appointment, bool isClosed);


    void PublishResults(bool saveData);

    void CreateBlocks(QDateTime StartDate, qint64 startblockindex, QDateTime startblockDate, QDateTime lastPlannedObject);
    void addToBlock(qint64 blockID, qint64 endBlockId, AgendaBlockItem *item);




};

#endif // AGENDALOADER_H
