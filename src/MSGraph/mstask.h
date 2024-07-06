#ifndef MSTASK_H
#define MSTASK_H

#include <QObject>

class MSTask : public QObject
{
    Q_OBJECT
public:
    explicit MSTask(QObject *parent = nullptr);

signals:

};

#endif // MSTASK_H
