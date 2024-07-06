#ifndef AGENDALOADERITEM_H
#define AGENDALOADERITEM_H

#include <QObject>
#include "../Appointments/appointment.h"



class AgendaLoaderItem : public QObject
{
    Q_OBJECT
public:
    explicit AgendaLoaderItem(LoaderType type, Appointment *appointment = nullptr, QDateTime starttime = QDateTime::currentDateTime(), QDateTime endtime = QDateTime::currentDateTime(), bool isClosed = false, QObject *parent = nullptr);

    LoaderType type;
    Appointment *app;
    QDateTime starttime;
    QDateTime endtime;
    bool isClosed;


signals:

};

#endif // AGENDALOADERITEM_H
