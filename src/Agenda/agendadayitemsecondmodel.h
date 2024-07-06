#ifndef AGENDADAYITEMSECONDMODEL_H
#define AGENDADAYITEMSECONDMODEL_H

#include <QObject>
#include <QAbstractListModel>

#include "agendablock.h"


class AgendaDayItemSecondModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit AgendaDayItemSecondModel(QObject *parent = nullptr);


signals:

};

#endif // AGENDADAYITEMSECONDMODEL_H
