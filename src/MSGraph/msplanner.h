#ifndef MSPLANNER_H
#define MSPLANNER_H

#include <QObject>

#include "solidgraph.h"
#include "mscategorys.h"
#include "msbucket.h"

QT_FORWARD_DECLARE_CLASS(SolidGraph);
QT_FORWARD_DECLARE_CLASS(MSBucket);

class MSPlanner : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString id READ id WRITE setId NOTIFY idChanged);
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged);
public:
    explicit MSPlanner(QString ID, SolidGraph *srGraph, QObject *parent = nullptr);
    ~MSPlanner();

    QString id() const;
    void setId(const QString &newId);

    QString title() const;
    void setTitle(const QString &newTitle);

    MSBucket *getBucket(QString ID);

signals:

    void idChanged();

    void titleChanged();

public slots:
    void AfterLoad(QJsonObject data);
    void AfterLoadDetails(QJsonObject data);
private:

    SolidGraph *srGraph;
    void loadPlanner();
    QVector<MSCategorys*>categories;
    QVector<MSBucket*>buckets;
    QString m_id;
    QString m_title;
};

#endif // MSPLANNER_H
