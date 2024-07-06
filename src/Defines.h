#ifndef DEFINES_H
#define DEFINES_H

#pragma once

#include <QObject>
#include <QDateTime>

#define AGENDABLOCKDURATION 15*60

enum AgendaTypes{
    appointmentType,
    taskType
};

enum PlanModes{
    Fixed,
    AsBlock,
    AsTask
};

enum LoaderType{
    agenda_Save,
    agenda_Plan,
    agenda_Load,
    agenda_PlanAndSave,
    appointment_Delete,
    appointment_DeleteTimeFrame,
    appointment_SaveTimeFrame,
    agenda_Export,
    appointment_Close,
};

enum logStatus{
    unknown,
    Planned,
    WorkedOn,
    Block,
    ReUsable
};

QString durationToString(int duration);



    int durationFromString(QString duration);

QDateTime NullDate();

#endif // DEFINES_H
