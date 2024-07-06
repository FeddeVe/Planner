#ifndef BUCKETITEM_H
#define BUCKETITEM_H

#include <QObject>
#include <QAbstractListModel>
#include <QMutex>
#include <QQmlEngine>
#include <QDateTime>

#include "bucketsubitem.h"
#include "bucket.h"
#include "../Defines.h"
#include "../Database/dbmanager.h"
#include "../Appointments/appointmenttypes.h"

QT_FORWARD_DECLARE_CLASS(Bucket);
QT_FORWARD_DECLARE_CLASS(Appointment);

class BucketItem : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int msid READ msid WRITE setMsid NOTIFY msidChanged);
    Q_PROPERTY(int index READ index WRITE setIndex NOTIFY indexChanged);
    Q_PROPERTY(int templateID READ templateID WRITE setTemplateID NOTIFY templateIDChanged);
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged);
    Q_PROPERTY(QString dueDate READ dueDate WRITE setDueDate NOTIFY dueDateChanged);
    Q_PROPERTY(QString duration READ duration WRITE setDuration NOTIFY durationChanged);
    Q_PROPERTY(QString durationLeft READ durationLeft WRITE setDurationLeft NOTIFY durationLeftChanged);
    Q_PROPERTY(bool isClosed READ isClosed WRITE setIsClosed NOTIFY isClosedChanged);
    Q_PROPERTY(bool isFromTemplate READ isFromTemplate WRITE setIsFromTemplate NOTIFY isFromTemplateChanged);
    Q_PROPERTY(QString msPlannerID READ msPlannerID WRITE setMsPlannerID NOTIFY msPlannerIDChanged);
    Q_PROPERTY(bool isLoaded READ isLoaded WRITE setIsLoaded NOTIFY isLoadedChanged);
    Q_PROPERTY(int planAss READ planAss WRITE setPlanAss NOTIFY planAssChanged);
    Q_PROPERTY(QString planColor READ planColor  NOTIFY planColorChanged);
    Q_PROPERTY(int planAssIndex READ planAssIndex WRITE setPlanAssIndex NOTIFY planAssIndexChanged);
    Q_PROPERTY(bool isActive READ isActive NOTIFY isActiveChanged);

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

    explicit BucketItem(int msid, int templateID,int index, QString title, QDateTime dueDate, int duration, bool isClosed, QString msPlannerID, int planAss, QDateTime startWorkingOn, Bucket *bucket, DBManager *db, QObject *parent = nullptr);

    Q_INVOKABLE void loadModel();
    Q_INVOKABLE BucketSubItem *get(int row) const;
    Q_INVOKABLE void save();

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

    int msid() const;
    void setMsid(int newMsid);

    int index() const;
    void setIndex(int newIndex);

    QString title() const;
    void setTitle(const QString &newTitle);

    QString dueDate() const;
    QDateTime DueDate() const;
    void setDueDate(const QString &newDueDate);
    void SetDueDate(const QDateTime &newDueDate);

    QString duration() const;
    int Duration() const;
    void setDuration(const QString &newDuration);
    void SetDuration(const int &newDuration);

    QString durationLeft() const;
    int DurationLeft() const;
    void setDurationLeft(const QString &newDurationLeft);
    void SetDurationLeft(const int &newDurationLeft);

    bool isClosed() const;
    void setIsClosed(bool newIsClosed);

    int templateID() const;
    void setTemplateID(int newTemplateID);

    bool isFromTemplate() const;
    void setIsFromTemplate(bool newIsFromTemplate);

    QString msPlannerID() const;
    void setMsPlannerID(const QString &newMsPlannerID);

    bool isLoaded() const;
    void setIsLoaded(bool newIsLoaded);

    int planAss() const;
    void setPlanAss(int newPlanAss);

    QString planColor() const;

    int planAssIndex() const;
    void setPlanAssIndex(int newPlanAssIndex);

    bool isActive() const;

protected:
    // return the roles mapping to be used by QML
    virtual QHash<int, QByteArray> roleNames() const override;
private:

    QMutex m;
    QVector<BucketSubItem*>m_data;
    QHash<int, QByteArray> m_roleNames;

    void SortList();
    void calcDurationLeft();
    void loadData();


    int m_msid;
    Bucket *m_bucket;
    DBManager *m_db;
    AppointmentType *planType;
    int m_templateID;
    int m_index;
    QString m_title;
    QDateTime m_dueDate;
    int m_duration;
    int m_durationLeft;
    bool m_isClosed;
    QDateTime m_startWorkingOn;

    bool m_isFromTemplate;

    QString m_msPlannerID;

    bool m_isLoaded;

    int m_planAss;


    int m_planAssIndex;

    Appointment *m_appointment;


signals:


    void msidChanged();

    void indexChanged();

    void titleChanged();

    void dueDateChanged();

    void durationChanged();

    void durationLeftChanged();

    void isClosedChanged();

    void templateIDChanged();

    void isFromTemplateChanged();

    void msPlannerIDChanged();

    void isLoadedChanged();

    void planAssChanged();

    void planColorChanged();

    void planAssIndexChanged();

    void isActiveChanged();

public slots:
    void AfterSave(QJsonObject data);
    void AfterLoad(QJsonObject data);
};


#endif // BUCKETITEM_H
