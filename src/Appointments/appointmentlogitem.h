#ifndef APPOINTMENTLOGITEM_H
#define APPOINTMENTLOGITEM_H

#include <QObject>
#include <QDateTime>

#include "../Defines.h"
#include "../Database/dbmanager.h"

class AppointmentLogItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int msid READ msid WRITE setMsid NOTIFY msidChanged);
    Q_PROPERTY(QString startDate READ startDate WRITE setStartDate NOTIFY startDateChanged);
    Q_PROPERTY(QString duration READ duration WRITE setDuration NOTIFY durationChanged);
    Q_PROPERTY(QString endDate READ endDate WRITE setEndDate NOTIFY endDateChanged);
    Q_PROPERTY(int startBlock READ startBlock WRITE setStartBlock NOTIFY startBlockChanged);
    Q_PROPERTY(int endBlock READ endBlock WRITE setEndBlock NOTIFY endBlockChanged);
    Q_PROPERTY(int status READ status WRITE setStatus NOTIFY statusChanged);
    Q_PROPERTY(QString statusString READ statusString NOTIFY statusStringChanged);
    Q_PROPERTY(bool locked READ locked WRITE setLocked NOTIFY lockedChanged);
    Q_PROPERTY(bool saveRequired READ saveRequired WRITE setSaveRequired NOTIFY saveRequiredChanged);
    Q_PROPERTY(bool isPublished READ isPublished WRITE setIsPublished NOTIFY isPublishedChanged);
    Q_PROPERTY(bool isSaved READ isSaved WRITE setIsSaved NOTIFY isSavedChanged);

public:
    explicit AppointmentLogItem(int msid, QDateTime startDate,int Duration, QDateTime endDate, qint64 startBlockID, qint64 endBlockID, int status, DBManager *db, QObject *parent = nullptr);

    void save(int appointmentID);

    int msid() const;
    void setMsid(int newMsid);

    QString startDate() const;
    QDateTime StartDate() const;
    void setStartDate(const QString &newStartDate);
    void setStartDate(const QDateTime &newStartDate);

    QString duration() const;
    int Duration() const;
    void setDuration(const QString &newDuration);
    void setDuration(const int &newDuration);

    QString endDate() const;
    QDateTime EndDate() const;
    void setEndDate(const QString &newEndDate);
    void setEndDate(const QDateTime &newEndDate);

    int startBlock() const;
    void setStartBlock(int newStartBlock);

    int endBlock() const;
    void setEndBlock(int newEndBlock);

    int status() const;
    void setStatus(int newStatus);

    QString statusString() const;


    bool locked() const;
    void setLocked(bool newLocked);

    bool saveRequired() const;
    void setSaveRequired(bool newSaveRequired);

    bool isPublished() const;
    void setIsPublished(bool newIsPublished);

    bool isSaved() const;
    void setIsSaved(bool newIsSaved);

signals:

    void msidChanged();
    void startDateChanged();
    void durationChanged();
    void endDateChanged();
    void startBlockChanged();
    void endBlockChanged();
    void statusChanged();
    void statusStringChanged();
    void lockedChanged();
    void saveRequiredChanged();
    void isPublishedChanged();

    void isSavedChanged();

private:

    DBManager *m_db;

    int m_msid;
    QDateTime m_startDate;
    int m_duration;
    QDateTime m_endDate;
    int m_startBlock;
    int m_endBlock;
    int m_status;
    bool m_locked;
    bool m_saveRequired;
    bool m_isPublished;
    bool m_isSaved;

public slots:
    void afterSave(QJsonObject data);
};

#endif // APPOINTMENTLOGITEM_H
