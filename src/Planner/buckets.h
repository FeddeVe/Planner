#ifndef BUCKETS_H
#define BUCKETS_H

#include <QObject>

#include "bucket.h"
#include "bucketmodel.h"
#include "../Jobs/jobs.h"
#include "../Agenda/agenda.h"
#include "../Appointments/appointments.h"

QT_FORWARD_DECLARE_CLASS(BucketModel);
QT_FORWARD_DECLARE_CLASS(Agenda);
QT_FORWARD_DECLARE_CLASS(Appointments);

class Buckets : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool bucketsLoaded READ bucketsLoaded WRITE setBucketsLoaded NOTIFY bucketsLoadedChanged);


public:
    explicit Buckets(DBManager *db, Jobs *jobs, Appointments *appointments, QObject *parent = nullptr);

    Q_INVOKABLE Bucket *bucket(int id);
    Q_INVOKABLE BucketModel *bucketModel();
    Q_INVOKABLE void setCurrentJob(int msid);

    void SetAgenda(Agenda *agenda);
    void AddBucket(Bucket *bucket);
    void CheckErrors();
    void removeBucket(Bucket *bucket);

     QVector<Bucket*> list;
    Agenda *agenda;
     DBManager *db;
      Appointments *m_appointments;
      Jobs *jobs;

    bool bucketsLoaded() const;
    void setBucketsLoaded(bool newBucketsLoaded);

private:


    QMutex m;
    qint64 lastEdit;


    BucketModel *m_bucketModel;


    bool m_bucketsLoaded;

signals:

    void bucketsLoadedChanged();

public slots:

    void loadBuckets();
    void AfterLoadBuckets(QJsonObject data);
    void childLoaded();




};

#endif // BUCKETS_H
