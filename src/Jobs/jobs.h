#ifndef JOBS_H
#define JOBS_H

#include <QObject>
#include <QMutex>

#include "job.h"
#include "jobautocompletemodel.h"
#include "jobListModel.h"
#include "../Database/dbmanager.h"

QT_FORWARD_DECLARE_CLASS(JobAutoCompleteModel);
QT_FORWARD_DECLARE_CLASS(JobListModel);

class Jobs : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool jobsLoaded READ jobsLoaded WRITE setjobsLoaded NOTIFY jobsLoadedChanged);


public:
    explicit Jobs(DBManager *db, QObject *parent = nullptr);

    bool jobsLoaded() const;
    void setjobsLoaded(bool loaded);
    Q_INVOKABLE Job *job(int msid);
    Q_INVOKABLE JobAutoCompleteModel *autocompletemodel();
    Q_INVOKABLE JobListModel *listModel();
    Q_INVOKABLE void loadAutoComplete(QString value);
    Q_INVOKABLE QString createJob(int msid, QString jobNo, QString jobTitle, QString jobClient, QString jobDate, QString jobStartDate, QString JobPickDate);
    Job *getJob(int rowID) const;
    Job *editJob;
    Job *CreateJob();

    void ClearEditJob();
    void removeJob(Job *j);

     DBManager *db;
private:
 QMutex m;
    JobAutoCompleteModel *m_autocompletemodel;
 JobListModel *m_listModel;
    bool m_jobsLoaded;
    quint64 last_sync;
     QVector<Job*>jobs;

public slots:
    void LoadJobs();
    void AfterLoadJObs(QJsonObject data);
    void NewJLE(quint64 JLE);

signals:
    void jobsLoadedChanged();

};

#endif // JOBS_H
