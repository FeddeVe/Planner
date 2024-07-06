#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QCoreApplication>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QDir>
#include <QThread>
#include <QMutex>

#include "dbrequest.h"
#include <QCryptographicHash>



class DBManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool serverError READ serverError WRITE setServerError NOTIFY serverErrorChanged);
    Q_PROPERTY(QString serverErrorText READ serverErrorText WRITE setserverErrorText NOTIFY serverErrorTextChanged);
    Q_PROPERTY(bool loginRequired READ loginRequired WRITE setloginRequired NOTIFY loginRequiredChanged);
    Q_PROPERTY(QString password READ password WRITE setpassword NOTIFY passwordChanged);
    Q_PROPERTY(QString userName READ userName WRITE setuserName NOTIFY userNameChanged);
    Q_PROPERTY(bool loginRunning READ loginRunning WRITE setloginRunning NOTIFY loginRunningChanged);
    Q_PROPERTY(int waitingList READ waitingList NOTIFY waitingListChanged);

public:
    explicit DBManager(QObject *parent = nullptr);

    struct db_info{
        QString username;
        QString token;
        int tokenIndex;
        int userID;
        QString serverID;
        QString password;
    } *DBInfo;

    void AddRequest(DBRequest *request);
    void InsertRequest(DBRequest *request);
    void Run();

    bool serverError() const;
    void setServerError(bool serverError);
    QString serverErrorText() const;
    void setserverErrorText(QString serverError);
    bool loginRequired() const;
    void setloginRequired(bool loginRequired);
    QString userName();
    void setuserName(QString username);
    QString password();
    void setpassword(QString password);
    bool loginRunning();
    void setloginRunning(bool running);
     Q_INVOKABLE void login();

    int waitingList() const;


private:
    QNetworkAccessManager *network;

    bool quit;

    QString Server;
    void LoadSession();
    void SaveSession();

    void GetState();



    QMutex request_mutex;
    QVector<DBRequest*> request_list;
    bool m_serverError;
    bool handleMessage(QByteArray data, DBRequest *request);
    QString m_serverErrorText;
    bool m_loginRequired;
    bool m_loginRunning;
    uint64_t last_msg_recieved;


public slots:
    void handleGetState(QJsonObject data);
    void handleLogin(QJsonObject data);
    void handleAfterLogin(QJsonObject data);

signals:
   void serverErrorChanged();
   void serverErrorTextChanged();
   void loginRequiredChanged();
   void serverStateChanged(bool state);
   void userNameChanged();
   void passwordChanged();
   void loginRunningChanged();

   void LoginOk();
   void JLERecieved(quint64 JLE);
   void waitingListChanged();
};

#endif // DBMANAGER_H
