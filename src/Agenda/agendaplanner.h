#ifndef AGENDAPLANNER_H
#define AGENDAPLANNER_H

#include <QObject>
#include <QVector>

#include "../Agenda/agenda.h"
#include "../Appointments/appointments.h"
#include "../Planner/buckets.h"


QT_FORWARD_DECLARE_CLASS(Agenda)
QT_FORWARD_DECLARE_CLASS(Appointments)
QT_FORWARD_DECLARE_CLASS(AgendaBlock)
QT_FORWARD_DECLARE_CLASS(Buckets);



class AgendaPlanner : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool exit READ exit WRITE setExit NOTIFY exitChanged);
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged);
public:
    explicit AgendaPlanner(Agenda *agenda, Appointments *appointments, Buckets *buckets, QObject *parent = nullptr);





    bool exit() const;
    void setExit(bool newExit);

    bool running() const;
    void setRunning(bool newRunning);

public slots:
    void process();


signals:
    void finished();

    void exitChanged();

    void runningChanged();

private:
    Agenda *agenda;
    Appointments *appointments;
    Buckets *buckets;



    void PlanApp1();
    void PlanTask1();
    void PlanApp2();
    void PlanTask2();
    void PlanApp3();
    void PublishResults();

    AgendaBlock *getBlock(QDateTime date);
    qint64 getBlockIndex(AgendaBlock *block);




    bool m_exit;
    bool m_running;
};

#endif // AGENDAPLANNER_H
