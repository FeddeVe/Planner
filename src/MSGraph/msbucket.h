#ifndef MSBUCKET_H
#define MSBUCKET_H

#include <QObject>

#include "solidgraph.h"
#include "mstask.h"

QT_FORWARD_DECLARE_CLASS(SolidGraph);

class MSBucket : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged);
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged);
public:
    explicit MSBucket(QString ID, SolidGraph *srGraph, QObject *parent = nullptr);

    QString id() const;
    void setId(const QString &newId);

    QString title() const;
    void setTitle(const QString &newTitle);

    void addTask(MSTask *task);

signals:

    void idChanged();

    void titleChanged();

public slots:
    void AfterLoad(QJsonObject data);

private:
    SolidGraph *srGraph;
    void loadData();

    QVector<MSTask*>tasks;
    QString m_id;
    QString m_title;
};

#endif // MSBUCKET_H
