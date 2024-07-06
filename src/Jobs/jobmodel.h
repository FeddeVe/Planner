#ifndef JOBMODEL_H
#define JOBMODEL_H

#include <QObject>

class JobModel : public QObject
{
    Q_OBJECT
public:
    explicit JobModel(QObject *parent = nullptr);

signals:

};

#endif // JOBMODEL_H
