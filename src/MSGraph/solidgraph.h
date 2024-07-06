#ifndef SRGRAPH_H
#define SRGRAPH_H

#include <QObject>
#include <QCryptographicHash>
#include <QDesktopServices>
#include <QOAuthHttpServerReplyHandler>
#include <QUrlQuery>
#include <QOAuth2AuthorizationCodeFlow>
#include <QObject>
#include <QTimer>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QBuffer>



#include "../Agenda/agenda.h"
#include "graphbufferitem.h"
#include "../Database/dbmanager.h"
#include "msplanner.h"

QT_FORWARD_DECLARE_CLASS(MSPlanner);

class SolidGraph : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int itemsLeft READ itemsLeft WRITE setItemsLeft NOTIFY itemsLeftChanged);
    Q_PROPERTY(bool authenticated READ authenticated WRITE setAuthenticated NOTIFY authenticatedChanged);

public:
    explicit SolidGraph(DBManager *db, QObject *parent = nullptr);
    bool authenticated() const { return m_authenticated; }
    QString token() const { return m_token; }

    void SaveAgenda(Agenda *agenda);

    int itemsLeft() const;
    void setItemsLeft(int newItemsLeft);

    void setAuthenticated(bool newAuthenticated);

    Q_INVOKABLE void authenticate();

     void AddBuffer(GraphBufferItem *item);


signals:
    void authenticatedChanged();
    void tokenChanged();
    void itemsLeftChanged();

public slots:

    void process();
    void saveAgenda2(QJsonObject data);
    void newAgenda(QJsonObject data);
    void AfterDelete(QJsonObject data);
    void AfterLoadTasks(QJsonObject data);
    void authorizationCallbackReceived(const QVariantMap &data);

private:
    QMutex m;
    QStringList knownIDs;
    QOAuth2AuthorizationCodeFlow *m_authFlow;
    bool m_authenticated{false};

    QString m_token;
    QTimer m_refreshTokenTimer;


    QVector<GraphBufferItem*> graphBuffer;

    DBManager *db;
    Agenda *agenda;
    int m_itemsLeft;
    QVector<MSPlanner*>planners;
    MSPlanner *getPlanner(QString plannerID);
    void loadTasks();
};

#endif // SRGRAPH_H
