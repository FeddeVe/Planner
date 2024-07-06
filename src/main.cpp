// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR GPL-3.0-only

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "app_environment.h"
#include "import_qml_components_plugins.h"
#include "import_qml_plugins.h"

#include "Database/dbmanager.h"
#include "Jobs/jobs.h"
#include "Appointments/appointments.h"
#include "Agenda/agenda.h"
#include "usersettings.h"
#include "MSGraph/msgraph.h"
#include "MSGraph/solidgraph.h"
#include "Planner/plannertemplates.h"
#include "Planner/buckets.h"


int main(int argc, char *argv[])
{
    set_qt_environment();


    QGuiApplication app(argc, argv);


    DBManager *database = new DBManager();
    Jobs *jobs = new Jobs(database);
    Appointments *appointments = new Appointments(database, jobs);
    UserSettings *settings = new UserSettings();
    MSGraph *graph = new MSGraph(database);
    SolidGraph *srgraph = new SolidGraph(database);
    PlannerTemplates *plannerTemplates = new PlannerTemplates(appointments);
    Buckets *buckets = new Buckets(database, jobs, appointments);

    Agenda *agenda = new Agenda(settings, appointments, buckets, database, graph);

    appointments->SetAgenda(agenda);
    buckets->SetAgenda(agenda);

    database->Run();

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/qt/qml/Main/main.qml"_qs);
    engine.rootContext()->setContextProperty("dbManager", database);
    engine.rootContext()->setContextProperty("jobsManager", jobs);
    engine.rootContext()->setContextProperty("appManager", appointments);
    engine.rootContext()->setContextProperty("agendaManager", agenda);
    engine.rootContext()->setContextProperty("microsoftManager", graph);
    engine.rootContext()->setContextProperty("solidManager", srgraph);
    engine.rootContext()->setContextProperty("templateManager", plannerTemplates);
    engine.rootContext()->setContextProperty("bucketManager", buckets);


    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);

    engine.addImportPath(QCoreApplication::applicationDirPath() + "/qml");
    engine.addImportPath(":/");

    engine.load(url);



    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
};
