import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item {
    id:root
    property bool expanded : false
    property bool editMode : false
    property var bucketItem
    property int maxNotesHeight: 300

    //Debug
    property bool bucketisClosed : false

    width: 500
    height: mainRect.height

    Rectangle{
        id: mainRect
        x:0
        y:0
        width: root.width
        height: expanded ? logRect.y + logRect.height :bucketisClosed ? title.y + title.height + 5 : startWorking.y+ startWorking.height + 5
        onHeightChanged: line.requestPaint()
        color: bucketisClosed ? Style.gray : Style.clrNormal
        clip:true
        gradient:
             Gradient {
                     orientation: Gradient.Vertical
                    GradientStop { position: 0.0; color: bucketisClosed ? Style.grey :  bucketItem.planColor}
                    GradientStop { position: bucketisClosed ? 1 : 0.5; color: bucketItem.isActive ? Style.amber : Style.background}
                }

        MouseArea{
            anchors.fill: parent
            onClicked: expanded = !expanded
        }

        Image{
            visible: true
            id:statusImage
            width:32
            height: 32
            source: "../images/warning.png"
            fillMode: Image.PreserveAspectFit
            x:5
            y:expButtton.y + expButtton.height
        }

        MyTextField{
            id: title
            x:statusImage.x + statusImage.width + 20
            y: 5
            showLabel: false
            textFont: Style.fHugeBold
            height: 40
            textColor: Style.gray
            value: bucketItem.title
            width: root.width - x*2
            editModeSelected: function(){title.editMode = true};
            editModeDeselected: function(){title.editMode = false};
            onNewValueChanged: bucketItem.title = newValue
        }

        MyTextField{
            id: durationLeft
            editMode: false
            x: root.width - width - 10
            y: 50
            width: 125
            //textColor: Style.gray
            label: "Duration Left:"
            value: bucketItem.durationLeft
            textAlign: Text.AlignRight
            enabled: false
        }

        MyTextField{
            id: durationPlanned
            x: root.width - width - 10
            y: durationLeft.y + durationLeft.height
            width: 125
            //textColor: Style.gray
            label: "Duration:"
            value: bucketItem.duration
            mask: "99:99"
            textAlign: Text.AlignRight
            enabled: true
            editMode: root.editMode
            editModeDeselected: function(){root.editMode = false};
            editModeSelected: function(){root.editMode = true};
            onNewValueChanged: bucketItem.duration = newValue
        }

        MyTextField{
            id: dueDate
            editMode: root.editMode
            x: title.x
            y: title.y + title.height
            //textColor: Style.gray
            label: "Due Date:"
            value: bucketItem.dueDate
            mask: "99-99-9999 99:99"
            width: root.width - x - durationLeft.width - 10
            enabled: true
            editModeDeselected: function(){root.editMode = false};
            editModeSelected: function(){root.editMode = true};
            onNewValueChanged: bucketItem.dueDate = newValue

        }

        MyComboBox{
            id:planAss
            editMode: root.editMode
            x: title.x
            y: dueDate.y + dueDate.height
            label: "Plan Ass:"
            currentIndex: bucketItem.planAssIndex
            model: appManager.types()
            textRole: "label"
            width: title.width/2
            onCurrentIndexChanged: bucketItem.planAssIndex = currentIndex
            editModeSelected: function(){root.editMode = true};
            editModeDeselected:  function(){root.editMode = false};
        }



        MyMenuButton{
            id:startWorking
            visible: !isActive
            x:title.x
            y:planAss.y + planAss.height
            label: "Start Working On"
            width: (root.width - x * 2)
            height: 40
            onClick: function(){
                root.isActive = true
                root.expanded = true
            };
        }

        MyMenuButton{
            id: breakBtn
            visible: isActive
            x:title.x
            y:planAss.y + planAss.height
            label: "Pauze"
            width: (root.width - x * 2) / 2
            height: 40
            onClick: function(){
                root.isActive = false
                root.expanded = false;
            };
        }

        MyMenuButton{
            id: closeBtn
            visible: isActive
            x:breakBtn.x + breakBtn.width + 5
            y:planAss.y + planAss.height
            label: "Stop and close item"
            width: breakBtn.width
            height: 40
            onClick: function(){
                root.isActive = false
                root.expanded = false
            };
        }











        /*


        MyTextField{
            id: txtDuration
            x: root.width - width
            y: title.y
            width: 100
            label: "Duration Left:"
            value: root.timeLeft
        }
        */

        ExpandButton{
            id: expButtton
            x:5
            y:title.y
            expanded: root.expanded
            darkMode: true
            onExpandedChanged: root.expanded = expanded
        }

        DeleteButton{
            visible: !root.editMode
            id: editButton
            x:root.width - width - 5
            y:title.y
            dark: true
            onClick: function(){root.editMode = true}

        }


        Rectangle{
            id:notesRect
            x:20
            y: startWorking.y + startWorking.height + 10
            width: root.width - (x*2)
            height: lstNotes.height
            radius: 10
            color: "#99FFFFFF"

        ListView{
           // visible: !agendaManager.plannerRunning
            id: lstNotes
            x:0
            y: 0
            width: notesRect.width
           // height: contentHeight > maxNotesHeight ? maxNotesHeight : contentHeight
           height: contentHeight
                  clip: true
            boundsMovement: Flickable.StopAtBounds
            flickableDirection: Flickable.AutoFlickDirection
            interactive: true
            model: 10
            delegate:  MyCheckBox{
                text: "Note Item"
               txtclr: Style.gray
               clr:Style.clrDark
            }


            ScrollIndicator.vertical: ScrollIndicator {visible: true}
            ScrollBar.vertical: ScrollBar {visible: true}


            header:Rectangle{
                x:0
                y:0
                width: lstNotes.width;
                height: lstNotesHdr.y + lstNotesHdr.height
                color: Style.clrTransparant

               Text{
                   id:lstNotesHdr
                   x:0
                   y:0
                   width: lstNotes.width
                   text: "Notes"
                   horizontalAlignment: Text.AlignHCenter
                   font:Style.fLargeBold


               }
            }
            /*
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
                    text: "Worked On:"
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
                        onClick: function(){
                           var returnmsg = appointment.appPlanner().saveWorkedOn(ftrDatum.value, ftrDuration.value)
                            if(returnmsg == ""){
                                ftrDatum.value = ""
                                ftrDuration.value = ""
                            }else{
                                savePopup.msg = returnmsg
                                savePopup.open()
                            }
                        };
                    }

                    MyMenuButton{
                        visible: appointment.isPast
                        id: ftrCloseButton
                        x: 10
                        y: ftrSaveButton.y + ftrSaveButton.height + 20
                        width: ftrDuration.width
                        warning: true
                        label: "Close Appointment";
                        height:35
                        onClick: function(){
                           var returnmsg = appointment.closeApp();
                        };
                    }
                }

            }
            */
        }
          }

        Rectangle{
            id:logRect
            x:20
            y: notesRect.y + notesRect.height + 10
            width: root.width - (x*2)
            height: lstLog.height
            radius: 10
            color: "#55000000"

        ListView{
           // visible: !agendaManager.plannerRunning
            id: lstLog
            x:0
            y: 0
            width: logRect.width
           // height: contentHeight > maxNotesHeight ? maxNotesHeight : contentHeight
            height: contentHeight
            clip: true
            boundsMovement: Flickable.StopAtBounds
            flickableDirection: Flickable.AutoFlickDirection
            interactive: true
            model: 10
            delegate:  LogItem{
                width: lstLog.width
                height: 105
            }


            ScrollIndicator.vertical: ScrollIndicator {visible: true}
            ScrollBar.vertical: ScrollBar {visible: true}


            header:Rectangle{
                x:0
                y:0
                width: lstNotes.width;
                height: lstLogHeader.y + lstLogHeader.height
                color: Style.clrTransparant

               Text{
                   id:lstLogHeader
                   x:0
                   y:0
                   width: lstLog.width
                   text: "Log"
                   horizontalAlignment: Text.AlignHCenter
                   font:Style.fLargeBold


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
                    text: "Worked On:"
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
                        onClick: function(){
                           var returnmsg = appointment.appPlanner().saveWorkedOn(ftrDatum.value, ftrDuration.value)
                            if(returnmsg == ""){
                                ftrDatum.value = ""
                                ftrDuration.value = ""
                            }else{
                                savePopup.msg = returnmsg
                                savePopup.open()
                            }
                        };
                    }

                    MyMenuButton{
                        visible: appointment.isPast
                        id: ftrCloseButton
                        x: 10
                        y: ftrSaveButton.y + ftrSaveButton.height + 20
                        width: ftrDuration.width
                        warning: true
                        label: "Close Appointment";
                        height:35
                        onClick: function(){
                           var returnmsg = appointment.closeApp();
                        };
                    }
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
            ListElement{d_title: "Venue 2D"; d_template: "Venue 2D"; d_dueDate: "Not Set"; d_durationLeft: "04:00"; d_completed: false; d_isNodig: true;d_type:1}
            ListElement{d_title: "Venue 3D"; d_template: "Venue 2D"; d_dueDate: "Not Set"; d_durationLeft: "04:00"; d_completed: false; d_isNodig: true;d_type:1}


    }


}
