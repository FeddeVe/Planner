#ifndef JOB_H
#define JOB_H

#include <QObject>
#include <QDateTime>
#include <QQmlEngine>
#include "../Database/dbmanager.h"

class Job : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int msid READ msid WRITE setmsid NOTIFY msidChanged);
    Q_PROPERTY(QString no READ no WRITE setno NOTIFY noChanged);
    Q_PROPERTY(QString title READ title WRITE settitle NOTIFY titleChanged);
    Q_PROPERTY(QString client READ client WRITE setclient NOTIFY clientChanged);
    Q_PROPERTY(QString jobDate READ jobDate WRITE setjobDate NOTIFY jobDateChanged);
    Q_PROPERTY(QString jobStartDate READ jobStartDate WRITE setjobStartDate NOTIFY jobStartDateChanged);
    Q_PROPERTY(QString jobPickDate READ jobPickDate WRITE setjobPickDate NOTIFY jobPickDateChanged);
    Q_PROPERTY(bool inUse READ inUse WRITE setInUse NOTIFY inUseChanged);
    Q_PROPERTY(bool isEditJob READ isEditJob WRITE setisEditJob NOTIFY isEditJobChanged);
    Q_PROPERTY(QString statusColor READ statusColor WRITE setStatusColor NOTIFY statusColorChanged);
    Q_PROPERTY(int secDiff READ secDiff WRITE setSecDiff NOTIFY secDiffChanged);




public:
    explicit Job(DBManager *db, int msid, QString no, QString title, QString client, QDateTime jobDate, QDateTime jobStartDate, QDateTime jobPickDate,bool isEdit = false, QObject *parent = nullptr);

    int msid() const;
    QString no() const;
    QString title() const;
    QString client() const;
    QString jobDate() const;
    QDateTime JobDate() const;
    QString jobStartDate() const;
    QDateTime JobStartDate() const;
    QString jobPickDate() const;
    QDateTime JobPickDate() const;
    bool inUse() const;
    bool isEditJob() const;

    void setmsid(int msid);
    void setno(QString jobNo);
    void settitle(QString title);
    void setclient(QString client);
    void setjobDate(QString date);
    void setjobStartDate(QString date);
    void setjobPickDate(QString date);
    void setjobDate(QDateTime date);
    void setjobStartDate(QDateTime date);
    void setjobPickDate(QDateTime date);
    void setInUse(bool inUse);
    void setisEditJob(bool editJob);

    Q_INVOKABLE void save(QString jobNo, QString title, QString client, QString jobDate, QString jobStartDate, QString jobPickDate);


    QString statusColor() const;
    void setStatusColor(const QString &newStatusColor);

    int secDiff() const;
    void setSecDiff(int newSecDiff);

private:
    DBManager *db;
    int m_msid;
    QString m_no;
    QString m_title;
    QString m_client;
    QDateTime m_jobDate;
    QDateTime m_jobStartDarte;
    QDateTime m_jobPickDate;
    bool m_inUse;
    bool m_editJob;


    int GetState();


    QString m_statusColor;

    int m_secDiff;

signals:
    void msidChanged();
    void noChanged();
    void titleChanged();
    void clientChanged();
    void jobDateChanged();
    void jobStartDateChanged();
    void jobPickDateChanged();
    void inUseChanged();
    void isEditJobChanged();

    void statusColorChanged();

    void secDiffChanged();

public slots:
    void AfterUpdate(QJsonObject data);
};

#endif // JOB_H
