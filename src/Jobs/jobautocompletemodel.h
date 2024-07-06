#ifndef JOBAUTOCOMPLETEMODEL_H
#define JOBAUTOCOMPLETEMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QMutex>

#include "jobs.h"

QT_FORWARD_DECLARE_CLASS(Jobs);

class JobAutoCompleteModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)

public:
    enum RoleNames {
        JobNoRole = Qt::UserRole,
        TitleRole = Qt::UserRole+2,
        ClientRole = Qt::UserRole+3,
        IDRole = Qt::UserRole + 4
    };

    explicit JobAutoCompleteModel(Jobs *jobs, QObject *parent = nullptr);

    void LoadModel(const QString SearchValue);
    Q_INVOKABLE Job *get(int row) const;

    int count() const;


    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

protected:
    // return the roles mapping to be used by QML
    virtual QHash<int, QByteArray> roleNames() const override;
private:
    Jobs *jobs;
    QMutex m;
    QVector<Job*>m_data;
    QHash<int, QByteArray> m_roleNames;

signals:
    void countChanged();
};

#endif // JOBAUTOCOMPLETEMODEL_H
