#include "solidgraph.h"

SolidGraph::SolidGraph(DBManager *db, QObject *parent)
    : QObject{parent}
{
    this->db = db;

    m_authFlow = new QOAuth2AuthorizationCodeFlow(this);
    m_authFlow->setReplyHandler(new QOAuthHttpServerReplyHandler{1338, m_authFlow});
    m_authFlow->setAuthorizationUrl(QStringLiteral("https://login.microsoftonline.com/common/oauth2/v2.0/authorize"));
    m_authFlow->setAccessTokenUrl(QStringLiteral("https://login.microsoftonline.com/common/oauth2/v2.0/token"));
    //m_authFlow->setScope(QStringLiteral("user.read Calendars.ReadBasic Calendars.Read Calendars.ReadWrite"));
    m_authFlow->setScope(QStringLiteral("user.read Tasks.Read"));
    m_authFlow->setClientIdentifier(QStringLiteral("4f7130db-9220-4760-a397-4471a4e05450"));
    // m_authFlow->setState(QByteArrayLiteral("basically random"));
    m_authFlow->setContentType(QAbstractOAuth::ContentType::Json);

    connect(m_authFlow, &QOAuth2AuthorizationCodeFlow::statusChanged, this, [this](QAbstractOAuth::Status s) {
        if (s == QAbstractOAuth::Status::Granted)
        {
            qDebug("authed");
            m_authenticated = true;
            emit authenticatedChanged();

            m_token = m_authFlow->token();
            emit tokenChanged();

            m_refreshTokenTimer.start();
            this->loadTasks();

        }
    });

    connect(m_authFlow, SIGNAL(authorizationCallbackReceived(const QVariantMap)), this, SLOT(authorizationCallbackReceived(const QVariantMap)));


    connect(m_authFlow, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser, &QDesktopServices::openUrl);

    // Graph API tokens expire every 60-90 minutes; since Qt doesn't provide a way to find the expiration time, we'll just
    // make sure we keep the access token up-to-date all the time
    m_refreshTokenTimer.setInterval(1000 * 60 * 50);
    m_refreshTokenTimer.setSingleShot(false);
    m_refreshTokenTimer.callOnTimeout(m_authFlow, &QOAuth2AuthorizationCodeFlow::refreshAccessToken);

    // this->authenticate();
    this->process();
}

void SolidGraph::authorizationCallbackReceived(const QVariantMap &data){
    int bp = 0;
    bp++;
}


void SolidGraph::authenticate()
{

    m_authFlow->grant();
}

void SolidGraph::SaveAgenda(Agenda *agenda){

    this->agenda = agenda;
    DBRequest *request = new DBRequest(RequestTypes::GetCalendarIDs, QJsonObject());
    connect(request, SIGNAL(finished(QJsonObject)), this, SLOT(saveAgenda2(QJsonObject)));
    this->db->InsertRequest(request);

    /*
    QNetworkReply *reply = m_authFlow->get(QUrl("https://graph.microsoft.com/v1.0/me/calendar/events"));
    bool exit = false;
    while(exit == false){

    while(reply->isFinished() == false){
        qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
        QThread::msleep(1);
    }

    if(reply->error()){
        qDebug() << reply->readAll();
        exit = true;
    }else{
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        QJsonObject obj = doc.object();
        QJsonArray items = obj.value("value").toArray();
        for(int i = 0; i < items.size(); i++){
            QJsonObject item = items[i].toObject();
            QString description = item.value("bodyPreview").toString();
            if(description.contains("Created by Planner.FV")){
                QJsonObject enddate = item.value("end").toObject();
                QStringList tmp = enddate.value("dateTime").toString().split(".");
                QDateTime endDate = QDateTime::fromString(tmp[0], "yyyy-MM-ddTHH:mm:ss");
                if(endDate > agenda->agendaStart){
                    QString eventID = item.value("id").toString();
                    GraphBufferItem *item = new GraphBufferItem(GraphBufferType::DELETE, "https://graph.microsoft.com/v1.0/me/events/"+ eventID, QJsonObject());
                    this->AddBuffer(item);
                }
            }
            int bp = 0;
            bp++;
        }
        QString next = obj.value("@odata.nextLink").toString();
        if(next == ""){
            exit = true;
        }else{
            reply = m_authFlow->get(QUrl(next));
        }
        int bp= 0;
        bp++;
    }
    }

    for(int i = 0; i < agenda->dayModel()->m_data.size(); i++){
        AgendaDayItem *item = agenda->dayModel()->m_data[i];
        for(int y = 0; y < item->m_data.size(); y++){
            AgendaDisplayItem *disItem = item->m_data[y];
            QJsonObject obj;
            if(disItem->type == appointmentType){
                obj.insert("subject", disItem->m_appointment->title() + " // " + disItem->m_appointment->jobNo() + " // " + disItem->m_appointment->jobTitle());
                QJsonObject body;
                body.insert("contentType", "HTML");
                body.insert("content", disItem->m_appointment->description() + " // Created by Planner.FV");
                obj.insert("body", body);
                QJsonObject start;
                start.insert("timeZone", "UTC");
                QString dateString = disItem->m_planDate.toUTC().toString("yyyy-MM-ddTHH:mm:ss");
                start.insert("dateTime", dateString);
                obj.insert("start", start);
                QJsonObject end;
                end.insert("timeZone", "UTC");
                QString enddateString = disItem->m_endplanDate.toUTC().toString("yyyy-MM-ddTHH:mm:ss");
                end.insert("dateTime", enddateString);
                obj.insert("end", end);
                obj.insert("isReminderOn", false);
                GraphBufferItem *item = new GraphBufferItem(GraphBufferType::POST, "https://graph.microsoft.com/v1.0/me/events/", obj);
                this->AddBuffer(item);
            }
        }



    }

        /*

        "subject": "Let's go for lunch",
                    "body": {
                        "contentType": "HTML",
                        "content": "Does noon work for you?"
                    },
                             "start": {
                                 "dateTime": "2017-04-15T12:00:00",
                                 "timeZone": "Pacific Standard Time"
                             },
                                       "end": {
                                           "dateTime": "2017-04-15T14:00:00",
                                           "timeZone": "Pacific Standard Time"
                                       },
                                               "location":{
                                                   "displayName":"Harry's Bar"
                                               },
                                                            "attendees": [
                                                                              {
                                                                                  "emailAddress": {
                                                                                      "address":"samanthab@contoso.com",
                                                                                      "name": "Samantha Booth"
                                                                                  },
                                                                                  "type": "required"
                                                                              }
        ],
                                                                          "allowNewTimeProposals": true,
                                                                                                    "transactionId":"7E163156-7762-4BEB-A1C6-729EA81755A7"
    }
*/

}

void SolidGraph::saveAgenda2(QJsonObject data){
    /*
                       QString eventID = item.value("id").toString();
                    GraphBufferItem *item = new GraphBufferItem(GraphBufferType::DELETE, "https://graph.microsoft.com/v1.0/me/events/"+ eventID, QJsonObject());
                    this->AddBuffer(item);
*/
    this->knownIDs.clear();

    QJsonArray arr = data.value("data").toArray();
    for(int i = 0; i < arr.size(); i++){
        QString ID = arr[i].toObject().value("CalendarID").toString();
        if(ID==""){
            //Clean up DB

        }else{
            this->knownIDs.push_back(ID);
        }
        //GraphBufferItem *item = new GraphBufferItem(GraphBufferType::DELETEAGENDAEVENT, "https://graph.microsoft.com/v1.0/me/events/"+ ID, QJsonObject(), ID);
        //connect(item, SIGNAL(finished(QJsonObject)), this, SLOT(AfterDelete(QJsonObject)));
        //this->AddBuffer(item);
    }



    for(int i = 0; i < agenda->dayModel()->m_data.size(); i++){

        AgendaDayItem *item = agenda->dayModel()->m_data[i];
        for(int y = 0; y < item->m_data.size(); y++){
            AgendaDisplayItem *disItem = item->m_data[y];
            QJsonObject obj;
            if(disItem->type == appointmentType){
                obj.insert("subject", disItem->m_appointment->title() + " // " + disItem->m_appointment->jobNo() + " // " + disItem->m_appointment->jobTitle());
                QJsonObject body;
                body.insert("contentType", "HTML");
                body.insert("content", disItem->m_appointment->description() + " // Created by Planner.FV");
                obj.insert("body", body);
                QJsonObject start;
                start.insert("timeZone", "UTC");
                QString dateString = disItem->m_planDate.toUTC().toString("yyyy-MM-ddTHH:mm:ss");
                start.insert("dateTime", dateString);
                obj.insert("start", start);
                QJsonObject end;
                end.insert("timeZone", "UTC");
                QString enddateString = disItem->m_endplanDate.toUTC().toString("yyyy-MM-ddTHH:mm:ss");
                end.insert("dateTime", enddateString);
                obj.insert("end", end);
                obj.insert("isReminderOn", false);
                QJsonArray attandees;
                QJsonObject Attandee;
                QJsonObject AttandeeEmail;
                AttandeeEmail.insert("address", "fedde.venekamp@solidrental.nl");
                AttandeeEmail.insert("name", "Fedde Venekamp");
                Attandee.insert("type", "required");
                Attandee.insert("emailAddress", AttandeeEmail);
                attandees.push_back(Attandee);
                obj.insert("attendees", attandees);
                obj.insert("responseRequested", false);

                if(knownIDs.size() > 0){
                    GraphBufferItem *item = new GraphBufferItem(GraphBufferType::PATCH, "https://graph.microsoft.com/v1.0/me/events/"+ knownIDs[0], obj);
                    connect(item, SIGNAL(finished(QJsonObject)), this, SLOT(newAgenda(QJsonObject)));
                    this->AddBuffer(item);
                    knownIDs.erase(knownIDs.begin());
                }else{
                    GraphBufferItem *item = new GraphBufferItem(GraphBufferType::POST, "https://graph.microsoft.com/v1.0/me/events/", obj);
                    connect(item, SIGNAL(finished(QJsonObject)), this, SLOT(newAgenda(QJsonObject)));
                    this->AddBuffer(item);
                }
            }
        }

    }

    for(int i = 0; i < knownIDs.size(); i++){
        GraphBufferItem *item = new GraphBufferItem(GraphBufferType::DELETEAGENDAEVENT, "https://graph.microsoft.com/v1.0/me/events/"+ knownIDs[i], QJsonObject(), knownIDs[i]);
        connect(item, SIGNAL(finished(QJsonObject)), this, SLOT(AfterDelete(QJsonObject)));
        this->AddBuffer(item);
    }


}

void SolidGraph::newAgenda(QJsonObject data){
    QString agendaID = data.value("id").toString();
    QJsonObject obj;
    obj.insert("MSCalendarID", agendaID);
    DBRequest *request = new DBRequest(RequestTypes::InsertCalendarID, obj);
    this->db->AddRequest(request);
    int bp = 0;
    bp++;



}

void SolidGraph::AfterDelete(QJsonObject data){

}

void SolidGraph::AddBuffer(GraphBufferItem *item){
    m.lock();
    this->graphBuffer.push_back(item);
    this->setItemsLeft(this->graphBuffer.size());
    m.unlock();
}

void SolidGraph::process(){
    QThread *thread = QThread::create([this]{



        while(1){

            if(this->authenticated()){

                /*
            QNetworkReply *reply = m_authFlow->get(QUrl("https://graph.microsoft.com/v1.0/me/planner/tasks"));
            while(reply->isFinished() == false){
                qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
                QThread::msleep(1);
            }
            //  qDebug() << reply->readAll();
            QJsonDocument docret = QJsonDocument::fromJson(reply->readAll());
            QJsonObject obj = docret.object();
          //  emit item->finished(docret.object());
            int bp = 0;
            bp++;
*/



                GraphBufferItem *item = NULL;
                m.lock();
                if(this->graphBuffer.size() > 0){
                    item = this->graphBuffer[0];
                }
                m.unlock();
                if(item != NULL){
                    if(item->type == GraphBufferType::POST){
                        QJsonDocument doc(item->data);
                        QByteArray postData = doc.toJson();
                        QNetworkReply *reply = m_authFlow->post(QUrl(item->URL), postData);
                        qDebug() << postData;
                        QString Dbg = doc.toJson(QJsonDocument::Compact);
                        qDebug() << Dbg;
                        while(reply->isFinished() == false){
                            qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
                            QThread::msleep(1);
                        }
                        //  qDebug() << reply->readAll();
                        QJsonDocument docret = QJsonDocument::fromJson(reply->readAll());
                        QJsonObject obj = docret.object();
                        emit item->finished(docret.object());
                        int bp = 0;
                        bp++;
                    }else if(item->type == GraphBufferType::DELETEAGENDAEVENT){
                        QNetworkReply *reply = m_authFlow->deleteResource(QUrl(item->URL));
                        while(reply->isFinished() == false){
                            qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
                            QThread::msleep(1);
                        }
                        // qDebug() << reply->readAll();
                        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());

                        QJsonObject err = doc.object().value("error").toObject();
                        QString msg = err.value("code").toString();
                        if(msg == "ErrorItemNotFound"){
                            QJsonObject obj;
                            obj.insert("MSCalendarID", item->CalendarID);
                            DBRequest *request = new DBRequest(RequestTypes::DeleteCalendarID, obj);
                            this->db->AddRequest(request);
                        }


                        int bp = 0;
                        bp++;
                    }else if(item->type == GraphBufferType::PATCH){
                        QNetworkRequest request;
                        request.setUrl(QUrl(item->URL));
                        request.setRawHeader(QByteArray{ "Authorization" }, QString{ "Bearer %1" }.arg(m_authFlow->token()).toUtf8() );
                        request.setHeader(QNetworkRequest::ContentTypeHeader, QString{ "application/json; charset=UTF-8" }.toUtf8());
                        // request.setHeader(QNetworkRequest::ContentLengthHeader, QString{ "19" }.toUtf8());

                        QJsonDocument doc(item->data);
                        QByteArray postData = doc.toJson();


                        QNetworkReply *reply = m_authFlow->networkAccessManager()->sendCustomRequest(request, "PATCH", postData);
                        //QNetworkReply *reply = m_authFlow->deleteResource(QUrl(item->URL));
                        while(reply->isFinished() == false){
                            qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
                            QThread::msleep(1);
                        }
                        // qDebug() << reply->readAll();
                        QJsonDocument doc2 = QJsonDocument::fromJson(reply->readAll());

                        QJsonObject err = doc2.object().value("error").toObject();
                        QString msg = err.value("code").toString();
                        if(msg == "ErrorItemNotFound"){
                            QJsonObject obj;
                            obj.insert("MSCalendarID", item->CalendarID);
                            DBRequest *request = new DBRequest(RequestTypes::DeleteCalendarID, obj);
                            this->db->AddRequest(request);
                        }


                        int bp = 0;
                        bp++;

                    }else if(item->type == GraphBufferType::GET){
                        QNetworkReply *reply = m_authFlow->get(QUrl(item->URL));

                        while(reply->isFinished() == false){
                            qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
                            QThread::msleep(1);
                        }
                        //  qDebug() << reply->readAll();
                        QJsonDocument docret = QJsonDocument::fromJson(reply->readAll());
                        QJsonObject obj = docret.object();
                        emit item->finished(docret.object());
                    }
                    m.lock();
                    item->deleteLater();
                    this->graphBuffer.erase(this->graphBuffer.begin());
                    this->setItemsLeft(this->graphBuffer.size());
                    m.unlock();
                }
                QThread::msleep(1);
            }
        }
    });
    thread->start();
}






int SolidGraph::itemsLeft() const
{
    return m_itemsLeft;
}

void SolidGraph::setItemsLeft(int newItemsLeft)
{
    if (m_itemsLeft == newItemsLeft)
        return;
    m_itemsLeft = newItemsLeft;
    emit itemsLeftChanged();
}

void SolidGraph::setAuthenticated(bool newAuthenticated)
{
    if (m_authenticated == newAuthenticated)
        return;
    m_authenticated = newAuthenticated;
    emit authenticatedChanged();
}

void SolidGraph::loadTasks(){
    GraphBufferItem *item = new GraphBufferItem(GraphBufferType::GET, "https://graph.microsoft.com/v1.0/me/planner/tasks", QJsonObject());
    connect(item, SIGNAL(finished(QJsonObject)), this, SLOT(AfterLoadTasks(QJsonObject)));
    this->AddBuffer(item);
}

void SolidGraph::AfterLoadTasks(QJsonObject data){
    for(int i = 0; i < this->planners.size(); i++){
        this->planners[i]->deleteLater();
    }
    this->planners.clear();
    this->planners.shrink_to_fit();

    QJsonArray items = data.value("value").toArray();
    for(int i = 0; i < items.count(); i++){
        QJsonObject x = items[i].toObject();
        QString taskID = x.value("id").toString();
        QString bucketID = x.value("bucketId").toString();
        QString planID = x.value("planId").toString();
        QString title = x.value("title").toString();
        QDateTime endTime = QDateTime::fromString(x.value("dueDateTime").toString(), "yyyy-MM-ddTHH:mm:ssZ");
        if(endTime.isValid()){
            endTime.setTime(QTime::fromString("18:00", "HH:mm"));
        }

        MSPlanner *planner = this->getPlanner(planID);
        MSBucket *bucket = planner->getBucket(bucketID);






        int bp = 0;
        bp++;
    }


    int bp = 0;
    bp++;
}

MSPlanner *SolidGraph::getPlanner(QString plannerID){
    for(int i = 0; i < this->planners.size(); i++){
        if(this->planners[i]->id() == plannerID){
            return this->planners[i];
        }
    }

    MSPlanner *planner = new MSPlanner(plannerID, this);
    this->planners.push_back(planner);
    return planner;
}
