#ifndef APPOINTMENTS_H
#define APPOINTMENTS_H

#include <QObject>
#include <QQmlEngine>
#include "appointmenttypes.h"
#include "appointment.h"
#include "appointmenterrormodel.h"

#include "../Database/dbmanager.h"
#include "../Jobs/jobs.h"
#include "../Agenda/agenda.h"

QT_FORWARD_DECLARE_CLASS(Appointment);
QT_FORWARD_DECLARE_CLASS(Agenda);
QT_FORWARD_DECLARE_CLASS(AppointmentErrorModel);

class Appointments : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool appointmentsLoaded READ appointmentsLoaded WRITE setAppointmentsLoaded NOTIFY appointmentsLoadedChanged);
public:

    explicit Appointments(DBManager *db, Jobs *jobs, QObject *parent = nullptr);
    Q_INVOKABLE AppointmentTypes *types();
    Q_INVOKABLE Appointment *appointment(int id);
    Q_INVOKABLE AppointmentErrorModel *errModel();
    Appointment *get(int msid);
    AppointmentType *get_type(int index);
    QVector<Appointment*>list;
    void SetAgenda(Agenda *agenda);
    void SortList();
    void AddAppointment(Appointment *app);
    void CheckErrors();
    void removeAppointment(Appointment *appointment);
    Appointment *getBucketItemAppointment(int bucketItemID);
    void getBucketAppointments(int BucketID, QVector<Appointment*> *list);

     Agenda *agenda;
    AppointmentTypes *appointmenttypes;
     bool appointmentsLoaded() const;
     void setAppointmentsLoaded(bool newAppointmentsLoaded);

 private:
    DBManager *db;
    Jobs *jobs;
    QMutex m;

    AppointmentErrorModel *m_err;
    Appointment *CreateEditAppointment();

    qint64 lastEdit;


    QVector<AppointmentType*>TypeList;


    bool m_appointmentsLoaded;

signals:
    void Update_TMPY_Agenda();


    void appointmentsLoadedChanged();

public slots:
    void LoadAppointments();
    void AfterLoadAppointments(QJsonObject data);
};

#endif // APPOINTMENTS_H
