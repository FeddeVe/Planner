#ifndef AGENDA_H
#define AGENDA_H

#include <QObject>
#include <QThread>
#include <QCoreApplication>

#include "agendadayitemmodel.h"
#include "agendaplanner.h"
#include "agendaitem.h"
#include "agendaloader.h"
#include "../usersettings.h"
#include "capacitymodel.h"
#include "capacityloader.h"
#include "../Database/dbmanager.h"
#include "agendaerrormodel.h"
#include "../MSGraph/msgraph.h"
#include "../Planner/buckets.h"
#include "agendablocks.h"
#include "agendawta.h"


QT_FORWARD_DECLARE_CLASS(AgendaPlanner);
QT_FORWARD_DECLARE_CLASS(AgendaLoader);
QT_FORWARD_DECLARE_CLASS(AgendaDayItemModel);
QT_FORWARD_DECLARE_CLASS(AgendaItem);
QT_FORWARD_DECLARE_CLASS(CapacityModel);
QT_FORWARD_DECLARE_CLASS(CapacityLoader);
QT_FORWARD_DECLARE_CLASS(AgendaErrorModel);
QT_FORWARD_DECLARE_CLASS(MSGraph);
QT_FORWARD_DECLARE_CLASS(AgendaBlocks);
QT_FORWARD_DECLARE_CLASS(AgendaWTA);

class Agenda : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool tmpyActive READ tmpyActive WRITE setTmpyActive NOTIFY tmpyActiveChanged);
    Q_PROPERTY(bool plannerRunning READ plannerRunning WRITE setPlannerRunning NOTIFY plannerRunningChanged);
    Q_PROPERTY(bool agendaLoading READ agendaLoading WRITE setAgendaLoading NOTIFY agendaLoadingChanged);
    Q_PROPERTY(int planMode READ planMode WRITE setPlanMode NOTIFY planModeChanged);

public:
    explicit Agenda(UserSettings *settings, Appointments *appointments, Buckets *buckets, DBManager *db, MSGraph *graph, QObject *parent = nullptr);

    Q_INVOKABLE AgendaDayItemModel *dayModel() const;
    Q_INVOKABLE int agendaIndex();
    Q_INVOKABLE int agendaIndexAt(QString date);
    Q_INVOKABLE CapacityModel *capModel();
    Q_INVOKABLE AgendaErrorModel *errModel();
    Q_INVOKABLE AgendaWTA *wtaModel();
    Q_INVOKABLE void exportAgenda();

    bool tmpyActive() const;
    void setTmpyActive(bool newTmpyActive);

    void planAgenda();
    void saveAgenda();
    void loadAgenda();
    void clearTmpyAgenda();
    void appointmentDeleted(Appointment *app);
    void removeAppointmentBlock(Appointment *app, QDateTime start, QDateTime end);
    void saveAppointmentBlock(Appointment *app, QDateTime start, QDateTime end, bool isClosed);
    void closeAppointment(Appointment *app);


    bool plannerRunning() const;
    void setPlannerRunning(bool newPlannerRunning);

     QVector<AgendaItem*>agendaitems;

    bool agendaLoading() const;
    void setAgendaLoading(bool newAgendaLoading);

    void CheckErrors();

    UserSettings *settings;
    QVector<AgendaBlock*> agendaBlocks;
    QVector<AgendaBlock*> TMPYAgendaBlocks;
    QDateTime agendaStart;
    QDateTime agendaStop;
    Appointments *appointments;
    DBManager *db;
    MSGraph *graph;
    Buckets *buckets;
    AgendaWTA *wta;
    int planMode() const;
    void setPlanMode(bool newPlanMode);

    AgendaBlocks *NewAgendaBlocks;

private:
    QMutex m;
    AgendaDayItemModel *m_dayModel;

    AgendaPlanner *planner;

    AgendaLoader *loader;
    QThread *loaderThread;
    QThread *plannerThread;

    QThread *capacityThread;
    CapacityModel *m_capmodel;
    CapacityLoader *m_capLoader;
    AgendaErrorModel *m_error;



    bool m_tmpyActive;

    void LoadBlocks(QDateTime startDate, QDateTime endDate);

 //   qint64 getEndBlockID(int startIndex, AgendaTypes type, Appointment *appointment, bool isClosed);

    bool m_plannerRunning;
    bool m_agendaLoading;

    int m_planMode;


signals:
    void tmpyActiveChanged();
    void plannerRunningChanged();
    void stopPlanner();
    void agendaLoadingChanged();
    void AgendaLoaded();

    void planModeChanged();

public slots:
    void plannerFinished();
    void loaderFinished();
    void debug(QJsonObject obj);
    void loaderStatus(bool busy);

};

#endif // AGENDA_H
