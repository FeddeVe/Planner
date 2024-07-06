#include "graphbufferitem.h"

GraphBufferItem::GraphBufferItem(GraphBufferType type, QString URL, QJsonObject data, QString CalendarID, QObject *parent)
    : QObject{parent}
{
    this->type = type;
    this->URL = URL;
    this->data = data;
    this->CalendarID = CalendarID;
}
