#include "agendablockitem.h"

AgendaBlockItem::AgendaBlockItem(qint64 msid, AgendaTypes type, Appointment *appointment, bool isClosed, QObject *parent)
    : QObject{parent}
{
      QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
    this->Type = type;
    this->appointment = appointment;
    this->isClosed = isClosed;
    this->isSaved = false;
    this->isDisplayd = false;

}
