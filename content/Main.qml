import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0
import "Components/"

Rectangle {
    property bool taskIsActive : false
    property int todayIndex : 8
    property bool taskVisible : true
    property int mainWidth : Constants.width
    property int itemRectWidht: jobs.width
    property int itemIndex: 1
    id: main
   // width: mainWidth
    height: Constants.height
    color: Style.background


    onItemRectWidhtChanged: {
        itemRect.width = itemRectWidht
        agenda.x = itemRect.x + itemRectWidht
        agenda.width = main.width-agenda.x

    }


    /*
    Rectangle{
        id:quickButtons
        x:2
        y:2
        width: 300-4
        height:60
        color:Style.background
        border.color: Style.clrText
        border.width: 2
        radius:10
    }

    TaskListItem{
        visible: taskIsActive
        id:activeTask
        x:0
        y:60
        width: 300
    }

    ListView {
                id: listView
                x:0
                y:taskIsActive ? 60+ activeTask.height + 20 : 60
                clip: true
                height: parent.height -y
                model: jobs
                width: 300
                spacing: 0

                delegate: ItemDelegate {
                    width: listView.width
                    height: 90
                    padding: 0
                    contentItem:
                        JobBtn{
                        id:jobbtn
                            //x:0
                            //y:0
                            width: 300
                            height: 90
                            jobNumber : jobNo
                            expandRight: false
                            jobPercentComplete: 01
                            isActive: listView.currentIndex == index
                            clip:true
                           // property string jobName : "Job Naam"
                          //  property real jobPercentComplete : 0.01
                           // property bool hover : false
                           // property bool isActive : false
                           // property bool expandRight: true
                           // property bool expandDown : false
                        }
                    MouseArea{
                        anchors.fill: jobbtn
                        hoverEnabled: true
                        onEntered: jobbtn.hover = true
                        onExited: jobbtn.hover = false
                        onClicked: {
                            listView.currentIndex = index
                            main.taskVisible = true
                        }
                    }


                 //   background: Rectangle{
                 //       id: listItem
                      //  property bool hovered : false
                        //x:1
                        //y:1
                //        x:0
                 //       y:0
                //        width: 300
                 //       height: 80
                //        color: Style.cyan
                //    }
                }
                //currentIndex: listView.highlightedIndex
                ScrollIndicator.vertical: ScrollIndicator {visible: false}
                ScrollBar.vertical: ScrollBar {visible: false}
onCurrentIndexChanged: {
    console.log("Current index = " + currentIndex);
            }
    }

   // Rectangle{
   //     x:listView.width
   //     y:0
   //     height: parent.height
   //     width: parent.width - listView.width
   //     color: Style.grey
   //     radius: 10




   // }



        Rectangle{
            id:dayViewContainer
             x: taskVisible ? 20 + tasks.width + tasks.x : 20 +listView.width
             y:0
             height : main.height
             width: agenda.isMinWidth ? agenda.minWidth : agenda.maxWidth
             color: Style.background
             border.color: Style.clrLight
             border.width: 2
             radius: 10
             onWidthChanged: {
               //  mainWidth : Constants.width
               //  main.width = mainWidth
             }

             Agenda{
                id: agenda
                x:0
                y:0
                minWidth: 300
                maxWidth: main.width - dayViewContainer.x
                isMinWidth: false
                height: dayViewContainer.height
                width: dayViewContainer.width
             }
        }





    Rectangle{
        id:tasks
        visible: taskVisible
        x: 0
        y:0
        height: main.height
        width: main.width
        color: Style.grey

        JobLists{
            id: taskView
            x:0
            y:0
            clip: true
            height: tasks.height - y
            width:tasks.width
            onClose: function(){main.taskVisible = false}
        }



        /*
    ListView {
                visible:taskVisible
                id: taskView
                x:10
                y:60
                clip: true
                height: tasks.height - y
                model: jobs
                width: 250
                spacing: 0
                delegate: ItemDelegate {
                    width: taskView.width
                    height: taskListItem.height
                    padding: 0
                    contentItem:
                        TaskListItem{
                            id:taskListItem

                    }

                    MouseArea{
                        anchors.fill: taskListItem
                        hoverEnabled: true
                        onEntered: taskListItem.hover = true
                        onExited: taskListItem.hover = false
                        onClicked: taskView.currentIndex = index
                    }


                 //   background: Rectangle{
                 //       id: listItem
                      //  property bool hovered : false
                        //x:1
                        //y:1
                //        x:0
                 //       y:0
                //        width: 300
                 //       height: 80
                //        color: Style.cyan
                //    }
                }
                //currentIndex: listView.highlightedIndex
                ScrollIndicator.vertical: ScrollIndicator {visible: true}
                ScrollBar.vertical: ScrollBar {visible: true}
onCurrentIndexChanged: {
    console.log("Current index = " + currentIndex);
            }
    }

    }


    Rectangle{
        visible: false
        id:criticalContainer
        x:taskVisible ? 20 + tasks.width + tasks.x : 20 +listView.width
        y:650
        height:main.height-y
        width: main.width-x
        color:Style.background
        border.color: Style.clrLight
        border.width: 2
        radius: 10



        ListView {
                    id: critView
                    x:10
                    y:10
                    orientation: ListView.Horizontal
                    clip: true
                    height: criticalContainer.height - y
                    model: jobs
                    width: criticalContainer.width - x
                    spacing: 0
                    delegate: ItemDelegate {
                        width: 255
                        height: critView.height
                        padding: 0
                        contentItem:
                            TaskListItem{
                                id:critTaskItem

                        }

                        MouseArea{
                            anchors.fill: taskListItem
                            hoverEnabled: true
                            onEntered: taskListItem.hover = true
                            onExited: taskListItem.hover = false
                            onClicked: critView.currentIndex = index
                        }


                     //   background: Rectangle{
                     //       id: listItem
                          //  property bool hovered : false
                            //x:1
                            //y:1
                    //        x:0
                     //       y:0
                    //        width: 300
                     //       height: 80
                    //        color: Style.cyan
                    //    }
                    }
                    //currentIndex: listView.highlightedIndex
                    ScrollIndicator.vertical: ScrollIndicator {visible: true}
                    ScrollBar.vertical: ScrollBar {visible: true}
    onCurrentIndexChanged: {
        console.log("Current index = " + currentIndex);
                }
        }

    }



    ListModel{
        id:capacitymodel

        ListElement{descrription: "JAN"; capacity: 0.1; current: false}
        ListElement{descrription: "FEB"; capacity: 0.2; current: false}
        ListElement{descrription: "MRT"; capacity: 0.3; current: false}
        ListElement{descrription: "APR"; capacity: 0.4; current: false}
        ListElement{descrription: "MEI"; capacity: 0.5; current: false}
        ListElement{descrription: "JUN"; capacity: 0.6; current: false}
        ListElement{descrription: "JUL"; capacity: 0.7; current: true}
        ListElement{descrription: "AUG"; capacity: 0.8; current: false}
        ListElement{descrription: "SEP"; capacity: 0.9; current: false}
        ListElement{descrription: "OKT"; capacity: 0.8; current: false}
        ListElement{descrription: "NOV"; capacity: 0.7; current: false}
        ListElement{descrription: "DEC"; capacity: 0.6; current: false}
        ListElement{descrription: "DEC"; capacity: 0.5; current: false}
        ListElement{descrription: "DEC"; capacity: 0.4; current: false}

    }

    Component.onCompleted: {
      //  mainWidth = dayViewContainer.x + dayViewContainer.width
    }
    */

    LeftMenu{
        id:menuBar
        x:0
        y:0
        width: 75
        height: main.height
        onClickIndexChanged: {
            if(clickIndex == 1){
                itemIndex = 1
                itemRectWidht = 310
                jobs.editMode = false
                jobs.addMode = false

            }else if(clickIndex == 3){
                //New Appointment
                itemIndex = 3
                appointmentItem.appointment = appManager.appointment(-1);
                appointmentItem.editMode = true;
                itemRectWidht = appointmentItem.width + 10
            }else{
                itemIndex = 0
                itemRectWidht = 500
            }
        }

    }

    Rectangle{
        id:itemRect
        x:menuBar.x + menuBar.width
        y:0
        height: main.height - capModel.height - 10
        width:main.itemRectWidht
        gradient:
            Gradient {
                    orientation: Gradient.Horizontal
                    GradientStop { position: 0.0; color: Style.gray}
                    GradientStop { position: 1.0; color: Style.background}
               }

        Behavior on width {
                    NumberAnimation {
                        duration: 500 //ms
                    }

                }




        Canvas {
                width: itemRect.width; height: itemRect.height
                property color lineColor : Style.amber
                onLineColorChanged: requestPaint()
                onPaint: {
                    var ctx = getContext("2d")
                    ctx.lineWidth = 1
                    ctx.strokeStyle = lineColor
                    ctx.beginPath()
                    ctx.moveTo(itemRect.width - 1, 20)
                    ctx.lineTo(itemRect.width - 1, itemRect.height-20)
                    ctx.closePath()
                    //ctx.fill()
                    ctx.stroke()
                }
            }

        Jobs{
            id:jobs
            visible: main.itemIndex == 1
            width:300
            height: itemRect.height
            maxWidth: main.width - itemRect.x
            onWidthChanged: {
               // agenda.x = jobs.x + jobs.width
               // agenda.width = main.width - agenda.x
                itemRectWidht = jobs.width
            }
        }

        /*
        PlannerTemplate{
            id:plannerBucket
        }
        */

        Appointment_Large{
            id: appointmentItem
            visible: main.itemIndex == 3
            height: itemRect.height
            width: 600
            closeWindow: function(){
                itemIndex = 0
                itemRectWidht = 5
            }
        }

    }

    Agenda{
        id: agenda
        //visible: !jobs.expanded
        x:itemRect.x + itemRect.width
        y:0
        height: main.height - capModel.height
        width: main.width - x

        onItemClick: function(type, id){
            if(type == 0){
                itemIndex = 3
                appointmentItem.appointment = appManager.appointment(id);
                appointmentItem.editMode = false;
                itemRectWidht = appointmentItem.width + 10
            }
        }
    }

    CapacityModel{
        id: capModel
        x:menuBar.x + menuBar.width
        y:main.height - height
        width: main.width - x
        height: 200
    }



    /*
    Appointment_Page{
        height: main.height
        width: main.width
       // z:50
    }
    */




    ServerLoadingDialog{
        x:0
        y:0
        height: main.height
        width: main.width
        //visible: false
        visible: !jobsManager.jobsLoaded || !appManager.appointmentsLoaded || !bucketManager.bucketsLoaded
    }

    ServerLoginDialog{
        x:0
        y:0
        height: main.height
        width: main.width
        // visible: false
        visible: dbManager.loginRequired
    }

    ServerErrorDialog{
        x:0
        y:0
        height: main.height
        width: main.width
        // visible: false
        visible: dbManager.serverError
    }


    PlannerRunningDialog{
        x:0
        y:0
        height: main.height
        width: main.width
        visible: false
       // visible: agendaManager.plannerRunning
    }



/*
    ListModel{
        id:jobs
        ListElement{jobID: 1222; jobNo: "24-0001"; isActive: false}
        ListElement{jobNo: "24-0002"}
        ListElement{jobNo: "24-0003"}
        ListElement{jobID: 1222; jobNo: "24-0001"}
        ListElement{jobNo: "24-0002"}
        ListElement{jobNo: "24-0003"}
        ListElement{jobID: 1222; jobNo: "24-0001"}
        ListElement{jobNo: "24-0002"}
        ListElement{jobNo: "24-0003"}
        ListElement{jobID: 1222; jobNo: "24-0001"}
        ListElement{jobNo: "24-0002"}
        ListElement{jobNo: "24-0003"}
        ListElement{jobID: 1222; jobNo: "24-0001"}
        ListElement{jobNo: "24-0002"}
        ListElement{jobNo: "24-0003"}
        ListElement{jobID: 1222; jobNo: "24-0001"}
        ListElement{jobNo: "24-0002"}
        ListElement{jobNo: "24-0003"}
        ListElement{jobID: 1222; jobNo: "24-0001"}
        ListElement{jobNo: "24-0002"}
        ListElement{jobNo: "24-0003"}
        ListElement{jobID: 1222; jobNo: "24-0001"}
        ListElement{jobNo: "24-0002"}
        ListElement{jobNo: "24-0003"}
    }
    */


}
