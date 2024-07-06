import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item {
    id:root

    property bool expanded : true
    property bool completed : false
    property bool isTemplate: true
    property bool isActive : false
    property bool isNodig: true
    property string title: "Title"
    property string template : "template"
    property string dueDate: "Not Set"
    property string timeLeft: "99:99"
    property int type : 1

    width: 400
    height: mainRect.height


    Rectangle{
        id: mainRect
        x:10
        y:0
        width: root.width - x*2
        height: expanded ? lstLog.y + lstLog.height : expButtton.y+expButtton.height + 10
        onHeightChanged: line.requestPaint()
        color: completed ? Style.grey : "#88888888"
        clip:true
       // border.color: Style.grey
       // radius: 10

        MouseArea{
            anchors.fill: parent
            onClicked: root.expanded = !root.expanded
        }

        Image{
            visible: false
            id:statusImage
            width:32
            height: 32
            source: "../images/warning.png"
            fillMode: Image.PreserveAspectFit
            x:5
            y:5
        }

        Text{
            id: title
            x:statusImage.x + statusImage.width + 20
            y: 5
            font: Style.fLargeBold
            width: root.width - x
            wrapMode: Text.WordWrap
            text: root.title
            color: Style.clrText
        }


        MyTextField{
            //visible: root.isTemplate
            id: txtDuration
            x: root.width-width
            y: title.y
            width: 100
            label: "Duration:"
            value: "88:88"
        }


        MyTextField{
            id: txtDurationLeft
            x: root.width - width
            y: txtDuration.y + txtDuration.height
            width: 100
            label: "Duration Left:"
            value: root.timeLeft
        }

        MyTextField{
            id: txtDueDate
            x: title.x
            y: txtDuration.y + txtDuration.height
            label: root.isNodig ? "Due Date" : ""
            value: root.isNodig ? root.dueDate : "Not Needed"
            mask: "99-99-9999 99:99"
            width: title.width
        }

        ExpandButton{
            id: expButtton
            x:5
            y:txtDurationLeft.y
            expanded: root.expanded
            onExpandedChanged: root.expanded = expanded
        }

        Rectangle{
            visible: !isNodig
            x:0
            y:0
            width: root.width
            height: mainRect.height
            color: "#88000000"
        }

        SpacerLine{
            id: spacer1
            x:0
            y:txtDueDate.y+txtDueDate.height
            width: mainRect.width
        }


        ListView{
            visible: !agendaManager.plannerRunning
            id:  lstLog
            x:20
            y: spacer1.y + spacer1.height
            width: mainRect.width - 40
            height: contentHeight
            clip: true
            boundsMovement: Flickable.StopAtBounds
            flickableDirection: Flickable.AutoFlickDirection
            interactive: true
            model: jobs
            //model: appointment.appPlanner()
            delegate:
                    Rectangle{
                      height: plannedRemarks.height
                      width: lstLog.width
                      color:Completed ? Style.clrDark : IsFromTMPY ? Style.amber : Style.clrTransparant

                      DeleteButton{
                          visible: IsPast
                          x:0
                          y:0
                          width:16
                          height: plannedRemarks.height;
                          onClick: function(){
                              appointment.deleteTimeFrame(index);
                          }
                      }

                      MyTextField{
                          x:25
                          id: plannedOn
                          label: "Date:"
                          value: Datum
                          textColor: Style.clrText
                          width: (lstLog.width - 25) / 4
                          textOffset: 0
                      }
                      MyTextField{
                          x: (lstLog.width / 4) + 40
                          id: plannedDuration
                          label: "Duration:"
                          value: Duration
                          textColor: Style.clrText
                          width: (lstLog.width - 25) / 4
                      }
                      MyTextField{
                          x: (lstLog.width / 4 * 2) + 20
                          id: plannedStatus
                          label: "Status:"
                          value: Status
                          textColor: Style.clrText
                          width: (lstLog.width - 25) / 4
                      }

                      MyMenuButton{
                          id: plannedRemarks
                          visible: IsPast && !Completed
                           x: lstLog.width / 4 * 3
                           width: (lstLog.width - 25) / 4
                           label: "Change status to Worked On"
                           height:plannedStatus.height
                      }

                      /*
                      MyTextField{
                          x: lstPlanning.width / 4 * 3
                          id: plannedRemarks
                          label: "Remarks:"
                          value: Remarks
                          textColor: Style.clrText
                          width: (lstPlanning.width - 25) / 4
                      }
                      */
                    }
            ScrollIndicator.vertical: ScrollIndicator {visible: true}
            ScrollBar.vertical: ScrollBar {visible: true}

            header:Rectangle{
                x:0
                y:0
                width: lstLog.width;
                height: btnhdrStart.y + btnhdrStart.height
                color: Style.clrTransparant

                MyMenuButton{
                    id: btnhdrStart
                    x:0
                    y:0
                    width: lstLog.width/3
                    label: "Start working on"
                }
                MyMenuButton{
                    id: btnhdrPauze
                    x:btnhdrStart.width
                    y:0
                    width: lstLog.width/3
                    label: "Pauze"
                }
                MyMenuButton{
                    id: btnhdrComplete
                    x:btnhdrStart.width * 2
                    y:0
                    width: lstLog.width/3
                    label: "Complete and Close task"
                }


            }
            footer: Rectangle{
                id:ftrRect
                x:0
                y:0
                color: Style.gray
                width: lstPlanning.width;
                height: ftrCloseButton.y + ftrCloseButton.height + 20
                Text{
                    id:ftrLabel
                    x:5
                    y:5
                    color:Style.amber
                    text: "Manual Entry:"
                    font: Style.fLarge
                    MyTextField{
                        id:ftrDatum
                        x:10
                        y:ftrLabel.y+ftrLabel.height
                        label: "StartDate"
                        mask: "99/99/9999 99:99"
                        value: ""
                        editMode: true
                        width: ftrRect.width - x*2
                    }
                    /*
                    MyTextField{
                        id:ftrDuration
                        x:10
                        y:ftrDatum.y+ftrDatum.height
                        label: "Duration"
                        mask: "99:99"
                        value: ""
                        editMode: true
                        width: ftrRect.width - x*2
                    }
                    */
                    MyTextField{
                        id:ftrDuration
                        x:10
                        y:ftrDatum.y+ftrDatum.height
                        label: "EndDate"
                        mask: "99/99/9999 99:99"
                        value: ""
                        editMode: true
                        width: ftrRect.width - x*2
                    }

                    MyMenuButton{
                        id: ftrSaveButton
                        x: 10
                        y: ftrDuration.y + ftrDuration.height + 20
                        width: ftrDuration.width
                        warning: true
                        label: "Save";
                        height:35

                    }

                    MyMenuButton{
                        id: ftrCloseButton
                        x: 10
                        y: ftrSaveButton.y + ftrSaveButton.height + 20
                        width: ftrDuration.width
                        warning: true
                        label: "Close Appointment";
                        height:35

                    }
                }
            }
        }





        Canvas {
            id: line
                width: root.width; height: root.height
                property color lineColor : Style.grey
                onLineColorChanged: requestPaint()

                onPaint: {
                    var ctx = getContext("2d")
                    ctx.lineWidth = 2
                    ctx.strokeStyle = lineColor
                    ctx.beginPath()
                    ctx.moveTo(10, mainRect.height - 1)
                    ctx.lineTo(root.width, mainRect.height+2)
                    ctx.closePath()
                    //ctx.fill()
                    ctx.stroke()
                }
            }
    }

    ListModel{
        id:jobs
        ListElement{d_title: "Venue 2D"; d_template: "Tekening Opstarten"; d_dueDate: "Not Set"; d_durationLeft: "01:00"; d_completed: true; d_isNodig: true; d_type:1}
        ListElement{d_title: "Venue 3D"; d_template: "Venue 2D"; d_dueDate: "Not Set"; d_durationLeft: "04:00"; d_completed: false; d_isNodig: true;d_type:1}


    }


}
