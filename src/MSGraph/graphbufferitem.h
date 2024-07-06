#ifndef GRAPHBUFFERITEM_H
#define GRAPHBUFFERITEM_H

#include <QObject>
#include <QJsonObject>

enum GraphBufferType{
    POST,
    DELETEAGENDAEVENT,
    PATCH,
    GET
};

class GraphBufferItem : public QObject
{
    Q_OBJECT
public:
    explicit GraphBufferItem(GraphBufferType type, QString URL, QJsonObject data,QString CalendarID = "", QObject *parent = nullptr);

    GraphBufferType type;
    QString URL;
    QJsonObject data;
    QString CalendarID;


signals:
    void finished(QJsonObject data);
};

#endif // GRAPHBUFFERITEM_H
