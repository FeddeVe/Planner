import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item {
    id:root
    property int lefytClmWidth: 200
    property bool editMode : false
    property bool jobVisible :false
    property var bucket



    width: 500
    height: 500

    Rectangle{
        id:mainRect
        x:0
        y:0
        height: root.height
        width: root.width
      //  color:Style.clrTransparant
        color: Style.gray

        MyTextField{
            id:bucketName
            editMode: root.editMode
            x:10
            y:10
            width: root.width - x - timeLeft.width - 15
            height: 40
           showLabel: false
            textFont: Style.fHugeBold
            label: "LABEL"
            value: bucket.title
            onNewValueChanged: bucket.title = newValue
            editModeSelected: function(){root.editMode = true};
            editModeDeselected: function(){root.editMode = false};
        }

        MyTextField{
            id:timeLeft
            editMode: false
            enabled: false
            x:root.width - width - 10
            y:10
            width: 100
            height: 40
            textFont: Style.fLargeBold
            label: "Time Left:"
            value: bucket.timeLeft
            textAlign: Text.AlignRight
        }

        /*
        Text{
            id:bucketName
            visible: !editMode
            x:10
            y:10
            text: bucket.title == "" ? "Title" : bucket.title
            font:Style.fLargeBold
            color: Style.clrText
            width: root.width - editBtn.width - 20
            height: 42
        }
        */
/*
        TextField{
            id:bucketNameInput
            visible: editMode
            x:10
            y:10
            text: bucket.title
            placeholderText: "Bucket Title"
            font:Style.fLargeBold
            color: Style.clrText
            width: root.width - editBtn.width - 20
            height: 42
            Material.accent: Style.amber
            onFocusChanged:
                if(!focus){
                    bucket.title = text
                }
        }
        */

        /*
        EditButton{
            id:editBtn
            x:root.width-10-width
            y:5
            onClick: function(){root.editMode = !root.editMode}
        }
        */

        SpacerLine{
            id:spacer1
            x:10
            y:bucketName.y+bucketName.height
            width: root.width - x*2
        }

        Rectangle{
            id: jobRect
            visible: root.jobVisible
            x:10
            y:spacer1.y + spacer1.height
            height: jobSpacer.y + jobSpacer.height
            width: root.width - x*2
            color:Style.clrTransparant
            MyTextField{
                id: jobNo
                x:0
                y:0
                width: jobRect.width
                label: "Job:"
                value: bucket.jobNo
            }
            MyTextField{
                id: jobTitle
                x:0
                y:jobNo.y + jobNo.height
                width: jobRect.width
                label: "Title:"
                value: bucket.jobTitle
            }
            MyTextField{
                id: jobClient
                x:0
                y:jobTitle.y + jobTitle.height
                width: jobRect.width
                label: "Client:"
                value: bucket.jobClient
            }
            SpacerLine{
                id: jobSpacer
                x:0
                y: jobClient.y + jobClient.height
                width: jobRect.width
            }

        }



        Text{
            x:5
            y:root.jobVisible ? jobRect.y + jobRect.height : spacer1.y + spacer1.height
            id:critHdr
            text: "Critiria"
            horizontalAlignment: Text.AlignHCenter
            font:Style.fMedium
            width: root.width
            color: Style.amber
        }

        MyTextField{
            id:crit1
            x: 5
            y: critHdr.y + critHdr.height
            label: "Number of Fixtures:"
            value: bucket.crit1
            width: root.width/3 - x
            editMode: root.editMode
            onNewValueChanged: bucket.crit1 = newValue
            editModeSelected: function(){root.editMode = true};
            editModeDeselected: function(){root.editMode = false};

        }

        MyTextField{
            id:crit2
            x: root.width / 3
            y: crit1.y
            label: "Meters Truss:"
            value: bucket.crit2
             width: root.width / 3
             editMode: root.editMode
             onNewValueChanged: bucket.crit2 = newValue
             editModeSelected: function(){root.editMode = true};
             editModeDeselected: function(){root.editMode = false};
        }

        MyTextField{
            id:crit3
            x: root.width / 3 *2
            y: crit2.y
            label: "Hoist en Staanders:"
            value: bucket.crit3
            width: root.width / 3 - 5
            editMode: root.editMode
            onNewValueChanged: bucket.crit3 = newValue
            editModeSelected: function(){root.editMode = true};
            editModeDeselected: function(){root.editMode = false};
        }

        MyComboBox{
            id:crit4
            x: 5
            y: crit3.y + crit3.height
            label: "Prep Fideilty:"
            currentIndex: bucket.crit4
            width: root.width/3 * 2
            editMode: root.editMode
            model: fidelity
            textRole: "d_text"
            onCurrentIndexChanged: bucket.crit4 = currentIndex
            editModeSelected: function(){root.editMode = true};
            editModeDeselected: function(){root.editMode = false};

        }

        /*
        MyTextField{
            id:crit4
            x: 5
            y: crit3.y + crit3.height
            label: "Prep Fideilty:"
            value: bucket.crit4
            width: root.width / 3
            editMode: root.editMode
            onNewValueChanged: bucket.crit4 = newValue
        }
        */

        MyTextField{
            id:crit5
            x: root.width / 3 * 2
            y: crit4.y
            label: "Ciriria Factor:"
            value: bucket.critFactor
            width: root.width / 3
            enabled: false

        }

        /*
        MyTextField{
            id:crit6
            x: root.width / 3 *2
            y: crit4.y
            label: "Time Left:"
            value: bucket.timeLeft
            width: root.width / 3
        }
        */

        SpacerLine{
            id:spacer2
            x:10
            y:crit4.y + crit4.height
            width: root.width - x*2
        }

        MyTextField{
            id:status
            x:10
            y:  spacer2.y + spacer2.height
            label: "Status:"
            value: "OK - Planned 88:88 from 88:88"
            textColor: Style.green
            width: root.width-x*2
            enabled: false
        }



        Rectangle{
            id: addRect
            property bool expanded : true
            x:10
            y:status.y + status.height
            width: root.width-x*2
            height: expanded ? addBtn.y + addBtn.height + 5 : expandBtn.y + expandBtn.height + expandBtn.y
            color: Style.clrTransparant
            border.color: Style.clrText
            radius: 5
            clip:true
            ExpandButton{
                id: expandBtn
                x:5
                y:5
                expanded: addRect.expanded
                onExpandedChanged: addRect.expanded = expanded
            }

            Text {
                id: addLabel
                x: expandBtn.x + expandBtn.width + 10
                y: 5
                text: "Add"
                color: Style.clrText
                font: Style.fLargeBold
            }

            MyComboBox{
                id:addInput
                x:10
                y:expandBtn.y + expandBtn.height + expandBtn.y
                label: "Add:"
                currentIndex: 1
                width: addRect.width - x*2
                editMode: true
                model: addMode
                textRole: "d_text"
                showLabel: false
            }

            MyTextField{
                id:addCustomTitle
                 visible:  addInput.currentIndex == 1
                x: 10
                y:addInput.y + addInput.height
                width: addRect.width - x*2
                label: "Title"
                value: ""
                editMode: true
            }

            MyComboBox{
                id: addCustomPlanAss
                x: 10
                y: addCustomTitle.y + addCustomTitle.height
                label: "Plan Ass:"
                currentIndex: 0
                width: addRect.width - x*2
                editMode: true
                model: appManager.types()
                textRole: "label"
            }

            MyTextField{
                id:addCustomDuration
                 visible:  addInput.currentIndex == 1
                x: 10
                y:addCustomPlanAss.y + addCustomPlanAss.height
                width: addRect.width - x*2
                label: "Duration"
                value: ""
                mask: "99:99"
                editMode: true
            }

            MyTextField{
                id:addCustomDueDate
                visible:  addInput.currentIndex == 1
                x: 10
                y:addCustomDuration.y + addCustomDuration.height
                width: addRect.width - x*2
                label: "DueDate"
                value: ""
                mask: "99-99-9999 99:99"
                editMode: true
            }




            MyMenuButton{
                id: addBtn
                x: 10
                y: addInput.currentIndex < 1 ? addInput.y + addInput.height + 5 : addCustomDueDate.y + addCustomDueDate.height + 5
                height: 45
                width: addRect.width - x * 2
                label: "Add Item"
                onClick: function(){
                    if(addInput.currentIndex == 0){

                    }else if(addInput.currentIndex == 1){
                        bucket.addItem(addCustomTitle.quickNewValue, addCustomDuration.quickNewValue, addCustomDueDate.quickNewValue, addCustomPlanAss.currentIndex);
                        addCustomTitle.value = "";
                        addCustomDuration.value = "";
                        addCustomDueDate.value = "";
                    }
                }

            }

        }



        MyCheckBox{
            id:showCompleted
            x:20
            y:addRect.y + addRect.height
            height:32
            width: root.width - x*2
            text: "Show completed items"
            checked: false
        }

        SpacerLine{
            id:spacer5
            x:10
            y:showCompleted.y + showCompleted.height + 5
            width: root.width - x*2
        }


    ListView{
       // visible: !agendaManager.plannerRunning
        id:  lstBucket
        x:2
        y: spacer5.y + spacer5.height
        width: root.width - x*2
        height: root.height - y - 2
        clip: true
        boundsMovement: Flickable.StopAtBounds
        flickableDirection: Flickable.AutoFlickDirection
        interactive: true
        model: bucket
        delegate: PlannerBucketItem{
            expanded: false
            bucketItem: bucket.get(index)
        }

        ScrollIndicator.vertical: ScrollIndicator {visible: true}
        ScrollBar.vertical: ScrollBar {visible: true}

        /*
        header:Rectangle{
            x:0
            y:0
            width: lstPlanning.width;
            height: hdrAgendaErrorText.y + hdrAgendaErrorText.height
          //  color: Style.clrTransparant
            gradient:
                 Gradient {
                         orientation: Gradient.Horizontal
                        GradientStop { position: 0.0; color:(appointment.appPlanner().completePlanned) && (!appointment.appPlanner().agendaErrors) ? Style.green : Style.red}
                        GradientStop { position: 1.0; color: Style.clrTransparant}
                    }
            MyTextField{
                x:10
                y:10
                id: hdrTotalDuration
                label: "Total Duration:"
                value: appointment.appPlanner().totalDuration
                textColor: Style.clrText
                width: (lstPlanning.width - 25) / 4
            }
            MyTextField{
                x: lstPlanning.width / 4
                y:10
                id: hdrWorkedDuration
                label: "Worked:"
                value: appointment.appPlanner().workedDuration
                textColor: Style.clrText
                width: (lstPlanning.width - 25) / 4
            }
            MyTextField{
                x: lstPlanning.width / 4 * 2
                y:10
                id: hdrPlannedDuration
                label: "Planned:"
                value: appointment.appPlanner().plannedDuration
                textColor: Style.clrText
                width: (lstPlanning.width - 25) / 4
            }
            MyTextField{
                x: lstPlanning.width / 4 * 3
                y:10
                id: hdrDurationError
                label: "To plan:"
                value: appointment.appPlanner().durationLeft
                textColor: Style.clrText
                width: (lstPlanning.width - 25) / 4
            }
            Text{
                visible: appointment.appPlanner().agendaErrors
                id: hdrAgendaErrorText
                x: 20;
                y:hdrDurationError.y + hdrDurationError.height
                width: lstPlanning.width - x*2
                font: Style.fLargeBold;
                text:  appointment.appPlanner().agendaErrorsText
                color:Style.clrText
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
    Canvas {
        id: splitLine
            width: mainRect.width; height: mainRect.height
            property color lineColor : Style.grey
            onLineColorChanged: requestPaint()

            onPaint: {
                var ctx = getContext("2d")
                ctx.lineWidth = 2
                ctx.strokeStyle = lineColor
                ctx.beginPath()
                ctx.moveTo(mainRect.width-2, 20)
                ctx.lineTo(mainRect.width + 2, mainRect.height - 20)
                ctx.closePath()
                //ctx.fill()
                ctx.stroke()
            }
        }
  }

    ListModel{
        id: addMode
        ListElement{d_text: "Template Item"}
        ListElement{d_text: "Custom Item"}
    }

    ListModel{
        id: fidelity
        ListElement{d_text: "100% Alles Compleet"}
        ListElement{d_text: "75% Naar inzicht versnellen"}
        ListElement{d_text: "50% Alleen als ik zelf naar klus ga"}
        ListElement{d_text: "25% Alleen kleine schets, grove easyjob"}
    }

    ListModel{
        id:jobs
        ListElement{d_title: "Tekening opstarten"; d_template: "Tekening Opstarten"; d_dueDate: "Not Set"; d_durationLeft: "01:00"; d_completed: true; d_isNodig: true; d_type:1}
        ListElement{d_title: "Venue"; d_template: "Venue 2D"; d_dueDate: "Not Set"; d_durationLeft: "04:00"; d_completed: false; d_isNodig: true;d_type:1}
         ListElement{d_title: "Set Design"; d_template: "Set Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:1}
        ListElement{d_title: "Production Floorplan"; d_template: "Production Floorplan"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:1}
        ListElement{d_title: "Production 3D"; d_template: "Production 3D"; d_dueDate: "Not Set"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:1}
        ListElement{d_title: "Lighting Design"; d_template: "Lighting Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:1}
        ListElement{d_title: "Rigging Design"; d_template: "Rigging Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:1}
        ListElement{d_title: "Offerte Hardware Inboeken"; d_template: "Offerte Hardware Inboeken"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:1}
        ListElement{d_title: "Inschatting Crew"; d_template: "Rigging Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:1}
        ListElement{d_title: "Renders of Screenshots"; d_template: "Rigging Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:1}
        ListElement{d_title: "Einde van SALES"; d_template: "Rigging Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : false;d_type:1}
        ListElement{d_title: "Tekening Opschonen"; d_template: "Rigging Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:2}
        ListElement{d_title: "Items skipped in offerte stadium"; d_template: "Rigging Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:2}
        ListElement{d_title: "First Requests"; d_template: "Rigging Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:2}
        ListElement{d_title: "Planning & Crew"; d_template: "Rigging Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:2}
        ListElement{d_title: "Licht Prep"; d_template: "Rigging Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:2}
        ListElement{d_title: "Revisie Power"; d_template: "Rigging Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:2}
        ListElement{d_title: "Revisie Weights"; d_template: "Rigging Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:2}
        ListElement{d_title: "Revisie Materialen"; d_template: "Rigging Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:2}
        ListElement{d_title: "Revisie Design"; d_template: "Rigging Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:2}
        ListElement{d_title: "Operator Informeren"; d_template: "Rigging Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:2}
        ListElement{d_title: "Patchlijsten"; d_template: "Rigging Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:2}
        ListElement{d_title: "Check reacties Power & Rigging"; d_template: "Rigging Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:2}
        ListElement{d_title: "Printen & Final Checks"; d_template: "Rigging Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:2}


    }

}
