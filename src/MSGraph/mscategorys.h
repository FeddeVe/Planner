#ifndef MSCATEGORYS_H
#define MSCATEGORYS_H

#include <QObject>

class MSCategorys : public QObject
{
    Q_OBJECT
public:
    explicit MSCategorys(QString Key, QString value, QObject *parent = nullptr);

    QString Key;
    QString Value;
signals:

};

#endif // MSCATEGORYS_H
