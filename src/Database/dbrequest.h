#ifndef DBREQUEST_H
#define DBREQUEST_H

#include <QObject>
#include <QJsonObject>


enum RequestTypes{
    Welcome = 0,
    CheckLogin,
    Login,
    LoadJobs,
    UpdateJob,
    DeleteJob,
    DeleteAgendaItem,
    DeleteAgendaItemsFromBlockID,
    InsertAgendaItem,
    LoadAgendaItems,
    SaveAppoinment,
    DeleteAppointment,
    LoadAppointments,
    DeleteCapacity,
    SaveCapacity,
    InsertCalendarID,
    DeleteCalendarID,
    GetCalendarIDs,
    DeleteBucket,
    SaveBucket,
    LoadBuckets,
    DeleteBucketItem,
    SaveBucketItem,
    LoadBucketItems,
    DeleteAppointmentLog,
    SaveAppointmentLog,
    LoadAppointmentLog,
};

class DBRequest : public QObject
{
    Q_OBJECT
public:
    explicit DBRequest(RequestTypes type, QJsonObject postData, QObject *parent = nullptr);
    RequestTypes RequestType;
    QJsonObject postData;
    QJsonObject data;

signals:
    void finished(QJsonObject data);

};

#endif // DBREQUEST_H
