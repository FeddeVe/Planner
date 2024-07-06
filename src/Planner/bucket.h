#ifndef BUCKET_H
#define BUCKET_H

#include <QObject>
#include <QAbstractListModel>
#include <QQmlEngine>
#include <QMutex>

#include "bucketitem.h"
#include "../Jobs/job.h"
#include "../Appointments/appointments.h"
#include "../Defines.h"


QT_FORWARD_DECLARE_CLASS(BucketItem);
QT_FORWARD_DECLARE_CLASS(Appointments);

class Bucket : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int msid READ msid WRITE setMsid NOTIFY msidChanged);
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged);
    Q_PROPERTY(QString jobNo READ jobNo NOTIFY jobNoChanged);
    Q_PROPERTY(QString jobTitle READ jobTitle NOTIFY jobTitleChanged);
    Q_PROPERTY(QString jobClient READ jobClient NOTIFY jobClientChanged);
    Q_PROPERTY(QString crit1 READ crit1 WRITE setCrit1 NOTIFY crit1Changed);
    Q_PROPERTY(QString crit2 READ crit2 WRITE setCrit2 NOTIFY crit2Changed);
    Q_PROPERTY(QString crit3 READ crit3 WRITE setCrit3 NOTIFY crit3Changed);
    Q_PROPERTY(QString crit4 READ crit4 WRITE setCrit4 NOTIFY crit4Changed);
    Q_PROPERTY(QString critFactor READ critFactor NOTIFY critFactorChanged);
    Q_PROPERTY(QString timeLeft READ timeLeft NOTIFY timeLeftChanged);
    Q_PROPERTY(QString statusColor READ statusColor WRITE setStatusColor NOTIFY statusColorChanged);
    Q_PROPERTY(QString statusText READ statusText WRITE setStatusText NOTIFY statusTextChanged);
    Q_PROPERTY(bool showCompleted READ showCompleted WRITE setShowCompleted NOTIFY showCompletedChanged);
    Q_PROPERTY(int status READ status WRITE setStatus NOTIFY statusChanged);
    Q_PROPERTY(bool isLoaded READ isLoaded WRITE setIsLoaded NOTIFY isLoadedChanged);

public:

    enum RoleNames {
        JobNoRole = Qt::UserRole,
        JobTitleRole = Qt::UserRole+2,
        JobClientRole = Qt::UserRole+3,
        IDRole = Qt::UserRole + 4,
        DateRole = Qt::UserRole + 5,
        StartDateRole = Qt::UserRole + 6,
        PickDateRole = Qt::UserRole + 7,
        StatusColorRole = Qt::UserRole + 8,
    };

    explicit Bucket(int msid,QString title, float crit1, float crit2, float crit3, float crit4, bool showCompleted, Job *job, DBManager *db, Appointments *appointments, Jobs *jobs,  QObject *parent = nullptr);

    Q_INVOKABLE void loadModel(const QString SearchValue);
    Q_INVOKABLE BucketItem *get(int row) const;
    Q_INVOKABLE void save();
    Q_INVOKABLE void addItem(QString title, QString duration, QString dueDate, int planAss);
    Q_INVOKABLE void plan();

    int count() const;



    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    QString title() const;
    void setTitle(const QString &newTitle);

    QString jobNo() const;

    QString jobTitle() const;

    QString jobClient() const;

    QString crit1() const;
    void setCrit1(const QString &newCrit1);

    QString crit2() const;
    void setCrit2(const QString &newCrit2);

    QString crit3() const;
    void setCrit3(const QString &newCrit3);

    QString crit4() const;
    void setCrit4(const QString &newCrit4);

    QString critFactor() const;

    QString timeLeft() const;

    QString statusColor() const;
    void setStatusColor(const QString &newStatusColor);

    QString statusText() const;
    void setStatusText(const QString &newStatusText);

    bool showCompleted() const;
    void setShowCompleted(bool newShowCompleted);

    int msid() const;
    void setMsid(int newMsid);

    int status() const;
    void setStatus(int newStatus);

    Job *job();
    QVector<BucketItem*>m_data;
    Appointments *m_appointments;
    Jobs *m_jobs;


    bool isLoaded() const;
    void setIsLoaded(bool newIsLoaded);


protected:
    // return the roles mapping to be used by QML
    virtual QHash<int, QByteArray> roleNames() const override;
private:

    QMutex m;

    QHash<int, QByteArray> m_roleNames;

    void SortList();
    void LoadData();
    int m_msid;
    QString m_title;
    Job *m_job;

    DBManager *m_db;
    float m_crit1;
    float m_crit2;
    float m_crit3;
    float m_crit4;
    float m_critFactor;
    int m_timeLeft;
    QString m_statusColor;
    QString m_statusText;
    bool m_showCompleted;
    int m_status;
    qint64 lastEdit;
    void calcCritFactor();
    bool m_isLoaded;

    QVector<Appointment*>appointments;

signals:
    void countChanged();
    void titleChanged();
    void jobNoChanged();
    void jobTitleChanged();
    void jobClientChanged();
    void crit1Changed();
    void crit2Changed();
    void crit3Changed();
    void crit4Changed();
    void critFactorChanged();
    void timeLeftChanged();
    void statusColorChanged();
    void statusTextChanged();
    void showCompletedChanged();
    void msidChanged();
    void statusChanged();

    void isLoadedChanged();

public slots:
    void AfterSave(QJsonObject data);
    void AfterLoad(QJsonObject data);
    void childDurationLeftChanged();

};


#endif // BUCKET_H
