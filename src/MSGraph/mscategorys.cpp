#include "mscategorys.h"

MSCategorys::MSCategorys(QString key, QString value, QObject *parent)
    : QObject{parent}
{
    this->Key = key;
    this->Value = value;
}
