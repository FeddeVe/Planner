#include "dbrequest.h"

DBRequest::DBRequest(RequestTypes type, QJsonObject postData, QObject *parent)
    : QObject{parent}
{
    this->RequestType = type;
    this->postData = postData;
}
