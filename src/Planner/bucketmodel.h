#ifndef BUCKETMODEL_H
#define BUCKETMODEL_H

#include <QObject>
#include <QAbstractListModel>

#include "buckets.h"

QT_FORWARD_DECLARE_CLASS(Buckets);
QT_FORWARD_DECLARE_CLASS(Bucket);

class BucketModel : public QAbstractListModel
{
    Q_OBJECT

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

    explicit BucketModel(Buckets *buckets, QObject *parent = nullptr);

    void loadModel();
    Q_INVOKABLE Bucket *get(int row) const;
    Q_INVOKABLE void createBucket();

    void SetJob(Job *j);

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

protected:
    // return the roles mapping to be used by QML
    virtual QHash<int, QByteArray> roleNames() const override;
private:

    QMutex m;
    QVector<Bucket*>m_data;
    QHash<int, QByteArray> m_roleNames;
    Buckets *m_buckets;
    Job *m_job;

    void SortList();



signals:

};

#endif // BUCKETMODEL_H
