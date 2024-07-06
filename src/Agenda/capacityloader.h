#ifndef CAPACITYLOADER_H
#define CAPACITYLOADER_H

#include <QObject>
#include "capacitymodel.h"

QT_FORWARD_DECLARE_CLASS(CapacityModel);

class CapacityLoader : public QObject
{
    Q_OBJECT
public:
    explicit CapacityLoader(CapacityModel *model, QObject *parent = nullptr);

    void exit();

    CapacityModel *m_model;

public slots:
    void process();
signals:
    void finished();

};

#endif // CAPACITYLOADER_H
