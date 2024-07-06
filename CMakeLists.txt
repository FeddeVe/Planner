cmake_minimum_required(VERSION 3.21.1)

option(LINK_INSIGHT "Link Qt Insight Tracker library" ON)
option(BUILD_QDS_COMPONENTS "Build design studio components" ON)

project(PlannerApp LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS Core Gui Qml Quick NetworkAuth)

if (Qt6_VERSION VERSION_GREATER_EQUAL 6.3)
    qt_standard_project_setup()
endif()

qt_add_executable(PlannerApp src/main.cpp
    src/Defines.h
    src/Defines.cpp
    src/MSGraph/msgraph.h src/MSGraph/msgraph.cpp
    src/MSGraph/graphbufferitem.h src/MSGraph/graphbufferitem.cpp
    src/MSGraph/solidgraph.h src/MSGraph/solidgraph.cpp
    src/MSGraph/msplanner.h src/MSGraph/msplanner.cpp
    src/MSGraph/msbucket.h src/MSGraph/msbucket.cpp
    src/MSGraph/mstask.h src/MSGraph/mstask.cpp
    src/MSGraph/mscategorys.h src/MSGraph/mscategorys.cpp

    src/Database/dbmanager.h src/Database/dbmanager.cpp
    src/Database/dbrequest.h src/Database/dbrequest.cpp
    src/Jobs/jobs.h src/Jobs/jobs.cpp
    src/Jobs/job.h src/Jobs/job.cpp
    src/Jobs/jobautocompletemodel.h src/Jobs/jobautocompletemodel.cpp
    src/Jobs/jobtaskmodel.h src/Jobs/jobtaskmodel.cpp
    src/Jobs/jobmodel.h src/Jobs/jobmodel.cpp
    src/Jobs/jobListModel.h src/Jobs/jobListModel.cpp
    src/Appointments/appointments.h src/Appointments/appointments.cpp
    src/Appointments/appointment.h src/Appointments/appointment.cpp
    src/Appointments/appointmenttypes.h src/Appointments/appointmenttypes.cpp
    src/Appointments/appointmenttype.h src/Appointments/appointmenttype.cpp
    src/Appointments/appointmentsmodel.h src/Appointments/appointmentsmodel.cpp
    src/Appointments/appointmentsjobmodel.h src/Appointments/appointmentsjobmodel.cpp
    src/Appointments/appointmentplanner.h src/Appointments/appointmentplanner.cpp
    src/Appointments/appointmentplanneritem.h src/Appointments/appointmentplanneritem.cpp
    src/Appointments/appointmenterrormodel.h src/Appointments/appointmenterrormodel.cpp
    src/Appointments/appointmenterroritem.h src/Appointments/appointmenterroritem.cpp

    src/Agenda/agenda.h src/Agenda/agenda.cpp
    src/Agenda/agendaitem.h src/Agenda/agendaitem.cpp
    src/Agenda/agendamodel.h src/Agenda/agendamodel.cpp
    src/Agenda/agendaitemmodel.h src/Agenda/agendaitemmodel.cpp
    src/Agenda/agendadayitem.h src/Agenda/agendadayitem.cpp
    src/Agenda/agendadayitemmodel.h src/Agenda/agendadayitemmodel.cpp
    src/Agenda/agendablock.h src/Agenda/agendablock.cpp
    src/Agenda/agendaplanner.h src/Agenda/agendaplanner.cpp
    src/Agenda/agendaloader.h src/Agenda/agendaloader.cpp
    src/Agenda/agendablockitem.h src/Agenda/agendablockitem.cpp
    src/Agenda/agendadayitemsecondmodel.h src/Agenda/agendadayitemsecondmodel.cpp
    src/Agenda/agendadayitemblock.h src/Agenda/agendadayitemblock.cpp
    src/Agenda/agendadisplayitem.h src/Agenda/agendadisplayitem.cpp
    src/Agenda/capacitymodel.h src/Agenda/capacitymodel.cpp
    src/Agenda/capacityitem.h src/Agenda/capacityitem.cpp
    src/Agenda/capacityloader.h src/Agenda/capacityloader.cpp
    src/Agenda/agendaerrormodel.h src/Agenda/agendaerrormodel.cpp
    src/Agenda/agendaerroritem.h src/Agenda/agendaerroritem.cpp
    src/Agenda/agendaloaderitem.h src/Agenda/agendaloaderitem.cpp
    src/Agenda/agendapublisher.h src/Agenda/agendapublisher.cpp
    src/Agenda/agendadataitem.h src/Agenda/agendadataitem.cpp
    src/Agenda/agendawta.h src/Agenda/agendawta.cpp
    src/Agenda/agendawtaerror.h src/Agenda/agendawtaerror.cpp

    src/usersettings.h src/usersettings.cpp

    src/Planner/plannertemplates.h src/Planner/plannertemplates.cpp
    src/Planner/plannertemplate.h src/Planner/plannertemplate.cpp
    src/Planner/plannertemplateitem.h src/Planner/plannertemplateitem.cpp
    src/Planner/plannertemplatesubitem.h src/Planner/plannertemplatesubitem.cpp
    src/Planner/buckets.h src/Planner/buckets.cpp
    src/Planner/bucket.h src/Planner/bucket.cpp
    src/Planner/bucketitem.h src/Planner/bucketitem.cpp
    src/Planner/bucketmodel.h src/Planner/bucketmodel.cpp
    src/Planner/addlistmodel.h src/Planner/addlistmodel.cpp
    src/Planner/bucketsubitem.h src/Planner/bucketsubitem.cpp

)

qt_add_resources(PlannerApp "configuration"
    PREFIX "/"
    FILES
        qtquickcontrols2.conf
)

target_link_libraries(PlannerApp PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::NetworkAuth
    Qt6::NetworkAuthPrivate
)

set(QT_QML_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/qml)
set(QML_IMPORT_PATH ${QT_QML_OUTPUT_DIRECTORY}
    CACHE STRING "Import paths for Qt Creator's code model"
    FORCE
)

if (BUILD_QDS_COMPONENTS)
    include(${CMAKE_CURRENT_SOURCE_DIR}/qmlcomponents)
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/qmlmodules)

if (LINK_INSIGHT)
    include(${CMAKE_CURRENT_SOURCE_DIR}/insight)
endif ()

include(GNUInstallDirs)
install(TARGETS PlannerApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# make IDEs aware of the QML import path
set(QML_IMPORT_PATH ${PROJECT_BINARY_DIR}/qml CACHE PATH
    "Path to the custom QML components defined by the project")
