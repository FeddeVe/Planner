#ifndef AGENDAERRORMODEL_H
#define AGENDAERRORMODEL_H

#include <QObject>
#include <QAbstractListModel>

#include "agendaerroritem.h"
#include "agenda.h"

class AgendaErrorModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged);

public:

    enum RoleNames {
        DatumRole = Qt::UserRole,
        MessageRole = Qt::UserRole+2
    };

    explicit AgendaErrorModel(QObject *parent = nullptr);

    void LoadData(Agenda *agenda);


    int count() const;

    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;

protected:
    // return the roles mapping to be used by QML
    virtual QHash<int, QByteArray> roleNames() const override;
private:
    QVector<AgendaErrorItem*>m_data;

    int m_count;
    QHash<int, QByteArray> m_roleNames;

    bool alreadyExist(QDateTime datum);

signals:
    void countChanged();


};

#endif // AGENDAERRORMODEL_H
