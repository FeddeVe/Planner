import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item {
    id:root
    property int lefytClmWidth: 200
    property bool editMode : false
    property var template : templateManager.get(0)
    width: 600
    height: Constants.height

    Rectangle{
        id:mainRect
        x:0
        y:0
        height: root.height
        width: root.width
        color:Style.gray
        border.color: Style.amber
        radius: 10

        Text{
            id:bucketName
            x:10
            y:10
            text: "Planner Templates"
            font:Style.fLargeBold
            color: Style.clrText
            width: root.width - 20
            height: 32
        }

        SpacerLine{
            id:spacer1
            x:10
            y:bucketName.y+bucketName.height
            width: root.width - x*2
        }

        Text{
            id:categoryTitle
            x:10
            y:spacer1.y + spacer1.height
            text: "Template"
            font:Style.fLargeBold
            color: Style.clrText
            width: root.width - 20
            height: 32
        }

        MyComboBox{
            id:templateSelect
            x:10
            y:categoryTitle.y + categoryTitle.height
            width: root.width - x*2
            label: "Template:"
            editMode: true
            model: templateManager
            currentIndex: 0
            textRole: "Name"
            onCurrentIndexChanged: {
                console.log(currentIndex);
                root.template = templateManager.get(currentIndex);

            }
        }

        MyTextField{
            id: templateName
            x:10
            y:templateSelect.y+ templateSelect.height
            width: root.width - x*2
            label: "Name:"
            value: template.name
            editMode: true
            onValueChanged: template.name = value
        }

        MyMenuButton{
            id:btnAdd
            x:10
            y:templateName.y+templateName.height + 5
            width: root.width - x*2
            height:42
            label: "Add Category"
            onClick: function(){
                template.addCatagory()
            }
        }

        MyMenuButton{
            id:btnSave
            x:10
            y:btnAdd.y+btnAdd.height + 10
            width: root.width - x*2
            height:42
            label: "Save Template"
        }

        SpacerLine{
            id:spacer5
            x:10
            y:btnSave.y+btnSave.height + 5
            width: root.width - x*2
        }




    ListView{
       // visible: !agendaManager.plannerRunning
        id:  lstCategories
        x:2
        y: spacer5.y + spacer5.height
        width: root.width - x*2
        height: root.height - y - 2
        clip: true
        boundsMovement: Flickable.StopAtBounds
        flickableDirection: Flickable.AutoFlickDirection
        interactive: true
        model: template
        delegate: PlannerTemplateItem{
            plannerItem: template.get(index);

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
