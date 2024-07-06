#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <QObject>
#include <QDateTime>
#include <QCoreApplication>

#include "../Database/dbmanager.h"
#include "../Jobs/jobs.h"
#include "appointments.h"
#include "../Agenda/agendablock.h"
#include "appointmentplanner.h"

QT_FORWARD_DECLARE_CLASS(Appointments);
QT_FORWARD_DECLARE_CLASS(AppointmentPlanner);


class Appointment : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int msid READ msid WRITE setmsid NOTIFY msidChanged);
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged);
    Q_PROPERTY(int jobID READ jobID WRITE setJobID NOTIFY jobIDChanged);
    Q_PROPERTY(QString jobNo READ jobNo WRITE setJobNo NOTIFY jobNoChanged);
    Q_PROPERTY(QString jobTitle READ jobTitle WRITE setJobTitle NOTIFY jobTitleChanged);
    Q_PROPERTY(QString jobClient READ jobClient WRITE setJobClient NOTIFY jobClientChanged);
    Q_PROPERTY(QString startDate READ startDate WRITE setStartDate NOTIFY startDateChanged);
    Q_PROPERTY(QString duration READ duration WRITE setDuration NOTIFY durationChanged);
    Q_PROPERTY(int durationLeft READ durationLeft WRITE setDurationLeft NOTIFY durationLeftChanged);
    Q_PROPERTY(QString endDate READ endDate WRITE setEndDate NOTIFY endDateChanged);
    Q_PROPERTY(bool isPlanned READ isPlanned WRITE setIsPlanned NOTIFY isPlannedChanged);
    Q_PROPERTY(bool isPast READ isPast WRITE setIsPast NOTIFY isPastChanged)
    Q_PROPERTY(bool isClosed READ isClosed WRITE setIsClosed NOTIFY isClosedChanged);
    Q_PROPERTY(bool blockRest READ blockRest WRITE setBlockRest NOTIFY blockRestChanged);
    Q_PROPERTY(bool planRest READ planRest WRITE setPlanRest NOTIFY planRestChanged);
    Q_PROPERTY(int typeIndex READ typeIndex WRITE setTypeIndex NOTIFY typeIndexChanged);
    Q_PROPERTY(QString type READ type NOTIFY typeChanged);
    Q_PROPERTY(QString typeName READ typeName NOTIFY typeNameChanged)
    Q_PROPERTY(QString clr READ clr WRITE setClr NOTIFY clrChanged);
    Q_PROPERTY(QString boxclr READ boxclr WRITE setBoxclr NOTIFY boxclrChanged);
    Q_PROPERTY(bool calcTime READ calcTime WRITE setCalcTime NOTIFY calcTimeChanged);
    Q_PROPERTY(QString description READ description WRITE setDescription NOTIFY descriptionChanged);
    Q_PROPERTY(bool inEditMode READ inEditMode WRITE setInEditMode NOTIFY inEditModeChanged);
    Q_PROPERTY(bool deleted READ deleted WRITE setDeleted NOTIFY deletedChanged);
    Q_PROPERTY(int planMode READ planMode WRITE setPlanMode NOTIFY planModeChanged);
    Q_PROPERTY(QString dateErrors READ dateErrors WRITE setDateErrors NOTIFY dateErrorsChanged);
    Q_PROPERTY(bool isAttached READ isAttached WRITE setIsAttached NOTIFY isAttachedChanged);
    Q_PROPERTY(bool rePlanningNeeded READ rePlanningNeeded WRITE setRePlanningNeeded NOTIFY rePlanningNeededChanged);
    Q_PROPERTY(bool savingInProgress READ savingInProgress WRITE setSavingInProgress NOTIFY savingInProgressChanged);
    Q_PROPERTY(int bucketID READ bucketID WRITE setBucketID NOTIFY bucketIDChanged);
    Q_PROPERTY(int BucketItemID READ BucketItemID WRITE setBucketItemID NOTIFY BucketItemIDChanged);
    Q_PROPERTY(bool workingOn READ workingOn NOTIFY workingOnChanged);
    Q_PROPERTY(bool isBucket READ isBucket NOTIFY isBucketChanged);
    Q_PROPERTY(bool isBucketItem READ isBucketItem NOTIFY isBucketItemChanged);
    // Q_PROPERTY(QString durationLeft READ durationLeft WRITE setDurationLeft NOTIFY durationLeftChanged);
public:
    explicit Appointment(Appointments *appointments, Jobs *jobs, DBManager *db, int m_msid, QString m_title,int m_jobID, QDateTime StartDate,int Duration,
                         QDateTime endDate, bool m_isClosed, bool m_blockRest,
                         bool m_planRest,int m_typeIndex,bool m_calcTime,QString m_description, int m_planMode,
                         int BucketID, int BucketItemID, QDateTime workingOnStartDate, bool isAttached = false, bool isDeleted = false, QObject *parent = nullptr);



    int msid() const;
    void setmsid(int newMsid);

    QString title() const;
    void setTitle(const QString &newTitle);

    int jobID() const;
    Q_INVOKABLE void setJobID(int newJobID);

    QString startDate() const;
    QDateTime StartDate() const;
    void setStartDate(const QString &newStartDate);
    void SetStartDate(const QDateTime date);

    QString duration() const;
    int Duration() const;
    void setDuration(const QString &newDuration);
    void SetDuration(const int &duration);

    QString endDate() const;
    QDateTime EndDate() const;
    void setEndDate(const QString &newEndDate);
    void SetEndDate(const QDateTime date);

    bool isPast() const;
    void setIsPast(bool newIsPast);

    bool isClosed() const;
    void setIsClosed(bool newIsClosed);

    bool blockRest() const;
    void setBlockRest(bool newBlockRest);

    bool planRest() const;
    void setPlanRest(bool newPlanRest);

    int typeIndex() const;
    void setTypeIndex(int newTypeIndex);

    QString clr() const;
    void setClr(const QString &newClr);

    bool calcTime() const;
    void setCalcTime(bool newCalcTime);

    QString description() const;
    void setDescription(const QString &newDescription);

    int planMode() const;
    void setPlanMode(int newPlanMode);

    Q_INVOKABLE Job *job();
    Q_INVOKABLE void plan();
    Q_INVOKABLE AppointmentPlanner *appPlanner();
    Q_INVOKABLE void cancelEdit();
    Q_INVOKABLE void save(int repeatMode, int repeatCount, bool ispartofmulti = false);
    Q_INVOKABLE void del();
    Q_INVOKABLE void deleteTimeFrame(int plannerIndex);
    Q_INVOKABLE void closeApp();
    Q_INVOKABLE void emitAll();


    QString jobNo() const;
    void setJobNo(const QString &newJobNo);

    QString jobTitle() const;
    void setJobTitle(const QString &newJobTitle);

    QString jobClient() const;
    void setJobClient(const QString &newJobClient);

    bool inEditMode() const;
    void setInEditMode(bool newInEditMode);

    bool deleted() const;
    void setDeleted(bool newDeleted);

    bool isPlanned() const;
    void setIsPlanned(bool newIsPlanned);

    QString boxclr() const;
    void setBoxclr(const QString &newBoxclr);

    QString type() const;


    QString dateErrors() const;
    void setDateErrors(const QString &newDateErrors);

    Appointment *BeforeBlock;
    Appointment *AfterBlock;
    Appointment *RestBlock;

    bool isAttached() const;
    void setIsAttached(bool newIsAttached);

    void UpdateAttached();

    bool rePlanningNeeded() const;
    void setRePlanningNeeded(bool newRePlanningNeeded);

    QString typeName() const;



    int durationLeft() const;
    void setDurationLeft(int newDurationLeft);

    DBManager *db;
    AppointmentPlanner *planner;
    Appointments *appointments;

    bool savingInProgress() const;
    void setSavingInProgress(bool newSavingInProgress);

    int bucketID() const;
    void setBucketID(int newBucketID);

    int BucketItemID() const;
    void setBucketItemID(int newBucketItemID);

    bool workingOn() const;

    bool isBucket() const;

    bool isBucketItem() const;

signals:


    void msidChanged();

    void titleChanged();

    void jobIDChanged();

    void startDateChanged();

    void durationChanged();

    void endDateChanged();

    void isPastChanged();

    void isClosedChanged();

    void blockRestChanged();

    void planRestChanged();

    void typeIndexChanged();

    void clrChanged();

    void calcTimeChanged();
    void descriptionChanged();

    void planModeChanged();

    void jobChanged();

    void jobNoChanged();

    void jobTitleChanged();

    void jobClientChanged();

    void inEditModeChanged();

    void deletedChanged();



    void isPlannedChanged();

    void boxclrChanged();

    void typeChanged();

    void dateErrorsChanged();

    void isAttachedChanged();

    void rePlanningNeededChanged();

    void typeNameChanged();

    void durationLeftChanged();

    void savingInProgressChanged();


    void bucketIDChanged();

    void BucketItemIDChanged();

    void workingOnChanged();

    void isBucketChanged();

    void isBucketItemChanged();

private:

    QMutex m;

    Jobs *jobs;

   // Appointments *appointments;



    int m_msid;
    QString m_title;
    int m_jobID;
    Job *m_job;
    QDateTime m_startDate;
    int m_duration;
    QDateTime m_endDate;
    bool m_isPast;
    bool m_isClosed;
    bool m_blockRest;
    bool m_planRest;
    AppointmentType *m_type;
    bool m_calcTime;
    QString m_description;

    int m_planMode;
    bool m_inEditMode;
    bool m_deleted;

    void checkDateErrors();

    struct OriginValues{
        QString m_title;
        int jobID;
        QDateTime m_startDate;
        int m_duration;
        QDateTime m_endDate;
        bool m_isPast;
        bool m_isClosed;
        bool m_blockRest;
        bool m_planRest;
        AppointmentType *m_type;
        bool m_calcTime;
        QString m_description;
        int m_planMode;
        bool m_inEditMode;
        bool m_deleted;
    }originValues;


    QString m_dateErrors;
    bool m_isAttached;
    bool m_rePlanningNeeded;
    int m_durationLeft;

    bool m_savingInProgress;
    int m_repeatMode;
    int m_repeatCount;
    bool m_saveispartofmulti;

    int m_bucketID;
    int m_BucketItemID;
    QDateTime m_workingOnStartDate;



public slots:
    void afterSave(QJsonObject msg);
    void afterSaveJob(QJsonObject msg);
    void afterSaveAppointment(QJsonObject msg);
     void AfterAgendaLoaded();
};

#endif // APPOINTMENT_H
