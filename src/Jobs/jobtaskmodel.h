#ifndef JOBTASKMODEL_H
#define JOBTASKMODEL_H

#include <QObject>

class JobTaskModel : public QObject
{
    Q_OBJECT
public:
    explicit JobTaskModel(QObject *parent = nullptr);

signals:

};

#endif // JOBTASKMODEL_H
