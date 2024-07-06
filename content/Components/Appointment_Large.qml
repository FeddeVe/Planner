import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item {
    property bool editMode : false
    property color backgroundColor : Style.background
    property int maxLength: 2048
    property var appointment
    property var closeWindow
    property bool jobVisible : true


    onAppointmentChanged: {

        repeatInput.currentIndex = 0;
        repeatCountInput.value = 0;
        //if()
        //agendaManager.dayModel().setIndexAt(appointment.startDate);
        /*
        titleInput.text = appointment.title
        title.text = appointment.title
        if(root.jobVisible){
        jobno.text = appointment.jobNo
        jobnoinput.value = appointment.jobNo
        jobnoinput.jobID = appointment.jobID
        jobtitleinput.text = appointment.jobTitle

        jobtitle.text = appointment.jobTitle
        jobclient.text = appointment.jobClient
        jobclientinput.text = appointment.jobClient;
        }
        typeInput.currentIndex = appointment.typeIndex;
        planModeInput.currentIndex = appointment.planMode;
        startDateInput.value = appointment.startDate;
        startDateInput.newValue = appointment.startDate;
        durationInput.value = appointment.duration;
        durationInput.newValue = appointment.duration;
        inpEndDate.value = appointment.endDate;
        inpEndDate.newValue = appointment.endDate;
        chBlock.checked = appointment.blockRest;
        chBlockRest.checked = appointment.planRest;
        chBlockCalc.checked = appointment.calcTime;
        txtDescription.value = appointment.description;
        lstPlanning.model = appointment.appPlanner();
        */
    }


    onEditModeChanged: appointment.inEditMode = editMode
    onVisibleChanged: {
        if(visible){
            agendaManager.dayModel().setIndexAt(appointment.startDate);
            maxLength = 1024
        }
    }

    id:root
    width: 600
    height: 600

        Rectangle{
            id: mainRect
            x:0
            y:0
            width: scrl.width
            height: spacer10.y + spacer10.height + 20
            color: Style.clrTransparant

    Text{
        visible: !editMode
        id:title
        font:Style.fHugeBold
        x:10
        y:10
        width: root.width - 2*x
        text:  appointment.title === "" ? "New Appointment" : appointment.title
        height: titleInput.height
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        color: Style.clrText
    }

    EditButton{
        visible: !editMode
        id: editimg
        x:root.width -width - 20
        y:10
        onClick: function(){ root.editMode = true}
    }

    DeleteButton{
        visible: editMode;
        id: deleteimg
        x: 20
        y: 10
        onClick: function(){
            appointment.del();
            root.closeWindow();
        }
    }



    TextField{
        visible: editMode
        id:titleInput
        font:Style.fHugeBold
        x:deleteimg.width + deleteimg.x + 10
        y:10
        width: mainRect.width - 2*x - editimg.width - 20
        text: appointment.title
        placeholderText: "Appointment Title"
        placeholderTextColor: Style.clrNormal
        color: Style.clrText
        horizontalAlignment: Text.AlignHCenter
        Material.accent: Style.amber
        onTextChanged: appointment.title = text
    }

    SpacerLine{
        id:spacer1
        x: 0
        y:title.y + title.height
        width: root.width - x*2
    }

    ScrollView{
        id:scrl
        x:0
        y: spacer1.y + spacer1.height
        height: root.height - y - saveBox.height
        width: root.width
        contentHeight: spacer10.y + spacer10.height + 20


        Rectangle{
            id:jobRect
            visible: root.jobVisible
            x:0
            y:0
            width: root.width
            height: spacer2.y + spacer2.height
            color: Style.clrTransparant


    Text{
        id:jobnotitle

        font:Style.fStandard
        x:0
        y: 0
        text: "JobNo:"
        horizontalAlignment: Text.AlignRight
        width: root.width/4
        height:35
        color: Style.clrText
    }

    Text{
        visible: !editMode
        id:jobno
        font:Style.fMediumBold
        x:root.width - width - 20
        y: 0
        text: "24-0001" //app.jobNo
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        width: root.width/4 * 3 -60
        height: 35
        color: Style.clrText
    }

    AutoCompleteJob{
        visible: editMode
        id:jobnoinput
        x:root.width - width - 20
        y:jobnotitle.y
        width: root.width/4 * 3 -40
        value: app.jobNo
        onJobIDChanged:{
            console.log(jobnoinput.jobID)
            appointment.jobID = jobID;
            appointment.jobNo = value
        }
    }

    Text{
        id:jobtitletitle
        font:Style.fStandard
        x:0
        y: jobnotitle.y + jobnotitle.height
        text: "Title:"
        horizontalAlignment: Text.AlignRight
        width: root.width/4
        color: Style.clrText
    }

    Text{
        visible: (!editMode || appointment.jobID != -1)
        id:jobtitle
        font:Style.fMediumBold
        x:root.width - width - 20
        y: jobtitletitle.y
        text: appointment.jobTitle
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        width: root.width/4 * 3 -60
        height: 35
         color: Style.clrText
    }

    TextField{
        visible: (editMode) && (appointment.jobID == -1)
        id:jobtitleinput
        x:root.width - width - 20
        y:jobtitle.y
        width: root.width/4 * 3 -40
        height: 35
        font: Style.fMedium
        text: appointment.jobTitle
        onTextChanged: appointment.jobTitle = text
    }
    Text{
        id:jobclientitle
        font:Style.fStandard
        x:0
        y: jobtitleinput.y + jobtitleinput.height
        text: "Client:"
        horizontalAlignment: Text.AlignRight
        width: root.width/4
        color: Style.clrText

    }

    Text{
        visible: (!editMode) || (appointment.jobID != -1)
        id:jobclient
        font:Style.fMediumBold
        x:root.width - width - 20
        y: jobclientitle.y
        text: appointment.jobClient
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        width: root.width/4 * 3 -60
        height: 35
         color: Style.clrText
    }

    TextField{
        visible: (editMode) && (appointment.jobID == -1)
        id:jobclientinput
        x:root.width - width - 20
        y:jobclient.y
        width: root.width/4 * 3 -40
        height: 35
        font: Style.fMedium
        text: appointment.jobClient
        onTextChanged: appointment.jobClient = text
    }


    SpacerLine{
        id:spacer2
        x:0
        y: jobclientinput.y + jobclientinput.height
        width: root.width
    }

     }

    Text{
        id:planModeTitle
        font:Style.fStandard
        x:20
        y: root.jobVisible ?  jobRect.y + jobRect.height : 0
        text: "Plan Mode:"
        width: root.width/3 - 20
        color:Style.clrText
    }



    ComboBox{
        enabled: editMode
        id:planModeInput
        x:planModeTitle.x
        y:planModeTitle.y + planModeTitle.height
        width: planModeTitle.width
        model: planModeModel
        textRole: "text"
        height: 40
        currentIndex: appointment.planMode
        activeFocusOnTab: true
       // displayText: select
        background: Rectangle{
            color:"white"
            border.width: parent && parent.activeFocus ? 2 : 1
            border.color: parent && parent.activeFocus ? Style.amber : Style.gray

        }
        onActivated: {
            console.log("Selected index = " + currentIndex);
            appointment.planMode = currentIndex;
             console.log("Selected index = " + currentIndex);
        }

    }

    Text{
        id:typeTitle
        font:Style.fStandard
        x:root.width / 5 * 2
        y: planModeTitle.y
        text: "Type:"
        width: root.width/3 - 20
        color:Style.clrText
    }



    ComboBox{
        enabled: editMode
        id:typeInput
        x:typeTitle.x
        y:typeTitle.y + typeTitle.height
        width: planModeTitle.width
        model: appManager.types()
        textRole: "label"
        currentIndex: appointment.typeIndex
        height: 40
        background: Rectangle{
            color:"white"
            border.width: parent && parent.activeFocus ? 2 : 1
            border.color: parent && parent.activeFocus ? comboBoxCustom.palette.highlight : comboBoxCustom.palette.button
       }
       // displayText: "text"
        displayText: currentText
        //model: appManager.types()
        //model:jobs
       // textRole: "label"
        delegate: Rectangle {
            property bool hover: false
               id:cRect
               x:0
               y:0
               height:40
               width: typeInput.width
               color: cRect.hover ? Style.clrText : Style.gray
               border.width: 0
               clip:true
               Rectangle{
                   x:10
                   y:5
                   width: 10
                   height: 20
                   radius:10
                   color: clr
                   border.color: Style.clrLight
                   border.width: 1
               }

               Text{
                   x:30
                   y:5
                   text: label
                   font: Style.fMedium
                   color:cRect.hover ? Style.gray : Style.clrText
               }

               SpacerLine{
                   x:0
                   y:cRect.height - 5
                   width: cRect.width

               }

               MouseArea{
                   anchors.fill: parent
                   hoverEnabled: true
                   onEntered: cRect.hover = true
                   onExited: cRect.hover = false
                   onClicked: {
                       typeInput.displayText = label
                       typeInput.popup.close()
                       typeInput.currentIndex = index
                       appointment.typeIndex = index;
                       console.log(typeInput.currentIndex);
                   }

               }

        }
    }

    Text{
        id:colorTitle
        font:Style.fStandard
        x:root.width / 5 * 4
        y: planModeTitle.y
        text: "Color:"
        width: root.width/3 - 20
        color:Style.clrText
    }

    Rectangle{
        id:colorRect
        x:colorTitle.x + 10
        y:colorTitle.y + colorTitle.height
        height: 40
        width: root.width/5 - 30
        border.color: Style.clrText
        radius: 10
        color: appointment.clr
    }

    MyTextField{
        id: startDateInput
        x: planModeTitle.x
        y: colorRect.y + colorRect.height
        textColor: Style.clrText
        value: appointment.startDate
        label: "Start Date:"
        mask: "99-99-9999 99:99"
        editMode: (root.editMode) && (appointment.planMode == 0)
        width: root.width / 5 * 2 - 20
        onNewValueChanged: {
            appointment.startDate = newValue
        }
        onFocusChanged: {
             agendaManager.dayModel().setIndexAt(appointment.startDate);
        }
    }

    MyTextField{
        id: durationInput
        x: root.width/5 * 2
        y: planModeInput.y + planModeInput.height
        textColor: Style.clrText
        value: appointment.duration
        label: "Duration:"
        mask: "999:99"
        editMode: root.editMode
        width: root.width / 5 - 20
        onQuickNewValueChanged: appointment.duration = quickNewValue
    }

    MyTextField{

        id: inpEndDate
        x: root.width/5 * 3
        y: planModeInput.y + planModeInput.height
        textColor: Style.clrText
        value: appointment.endDate
        label: "End Date:"
        mask: "99-99-9999 99:99"
        editMode: (root.editMode && planModeInput.currentIndex != 0)
        width: root.width / 5 * 2 - 20
        onNewValueChanged: appointment.endDate = newValue
    }

    Text{
        id:dateWarnings
        x:20
        y:inpEndDate.y + inpEndDate.height
        color:Style.red
        text: appointment.dateErrors
    }

    Text{
        visible: editMode
        id:repeatTitle
        font:Style.fStandard
        x:20
        y: dateWarnings.y + dateWarnings.height
        text: "Repeat:"
        width: root.width/3 - 20
        color:Style.clrText
    }

    ComboBox{
        visible: editMode
        enabled: editMode
        id:repeatInput
        x:repeatTitle.x
        y:repeatTitle.y + repeatTitle.height
        width: repeatTitle.width
        model: repeatModel
        textRole: "text"
        height: 40
        currentIndex: 0
        activeFocusOnTab: true
       // displayText: select
        background: Rectangle{
            color:"white"
            border.width: parent && parent.activeFocus ? 2 : 1
            border.color: parent && parent.activeFocus ? Style.amber : Style.gray

        }


    }

    MyTextField{
        visible: editMode
        id: repeatCountInput
        x: root.width/5 * 2
        y: dateWarnings.y + dateWarnings.height
        textColor: Style.clrText
        value: "0"
        label: "Repeat Count:"
        mask: "99"
        editMode: root.editMode
        width: root.width / 5 - 20
    }



    MyCheckBox{
        id:chBlock
        x:10
        y:repeatInput.y + repeatInput.height
        width: root.width / 3
        text: "Block rest of the day(s)"
        enabled: appointment.planMode == 0
        checked: appointment.blockRest
        onCheckedChanged:{

            appointment.blockRest = checked
        }
    }

    MyCheckBox{
        id:chBlockRest
        x:root.width/3
        y:repeatInput.y + repeatInput.height
        width: root.width / 3
        text: "Block rest after"
        enabled: appointment.planMode == 0
        checked: appointment.planRest
        onCheckedChanged: appointment.planRest = checked
    }

    MyCheckBox{
        id:chBlockCalc
        x:root.width/3 * 2
        y:repeatInput.y + repeatInput.height
        width: root.width / 3
        checked: appointment.calcTime
        text: "Calculate working hours"
        onCheckStateChanged: appointment.calcTime = checkState
    }

    MyTextArea{
        id: txtDescription
        x:10
        y:chBlockRest.y + chBlockRest.height
        width: root.width - x * 2
        height: 150
        label: "Description:"
        value: appointment.description
        editMode: root.editMode
        onValueChanged: appointment.description = value

    }

    MyMenuButton{
        id:btnReplan
        x: 20;
        y: txtDescription.y + txtDescription.height + 5
        width: root.width - x*2
        height:planningHeader.height * 2
        warning: appointment.rePlanningNeeded
        label: "Check Planning";
        onClick: function(){
            appointment.plan();
        }
    }

    SpacerLine{
        id: spacer3
        y: btnReplan.y + btnReplan.height + 5
        width: root.width
    }

    Text{
        id: planningHeader
        color: Style.amber
        font:Style.fLarge
        text: "Planning"
        x: 20;
        y: spacer3.y + spacer3.height
    }



    Rectangle{
        id:  rectPlannerLoading
        visible: agendaManager.plannerRunning
        x:20
        y: planningHeader.y + planningHeader.height
        height: plannerLoadingTitle.y + plannerLoadingTitle.height
        width: root.width
        color: Style.clrTransparant
        MyBusyIndicator{
            x: 20
            y: 20
            width: 32
            height: 32
        }

        Text{
            id:plannerLoadingTitle
            x: 80
            y: 20
            color: Style.clrText
            font: Style.fLarge
            text: "Planner loading"
        }
    }


    ListView{
        visible: !agendaManager.plannerRunning
        id:  lstPlanning
        x:20
        y: planningHeader.y + planningHeader.height
        width: mainRect.width - 40
        height: contentHeight
        clip: true
        boundsMovement: Flickable.StopAtBounds
        flickableDirection: Flickable.AutoFlickDirection
        interactive: true
        //model: jobs
        model: appointment.appPlanner()
        delegate:
                Rectangle{
                  height: plannedRemarks.height
                  width: lstPlanning.width
                  color:Completed ? Style.clrDark : IsFromTMPY ? Style.amber : Style.clrTransparant

                  DeleteButton{
                    //  visible: IsPast
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
                      width: (lstPlanning.width - 25) / 4
                      textOffset: 0
                  }
                  MyTextField{
                      x: (lstPlanning.width / 4) + 40
                      id: plannedDuration
                      label: "Duration:"
                      value: Duration
                      textColor: Style.clrText
                      width: (lstPlanning.width - 25) / 4
                  }
                  MyTextField{
                      x: (lstPlanning.width / 4 * 2) + 20
                      id: plannedStatus
                      label: "Status:"
                      value: Status
                      textColor: Style.clrText
                      width: (lstPlanning.width - 25) / 4
                  }

                  MyMenuButton{
                      id: plannedRemarks
                      visible: IsPast && !Completed
                       x: lstPlanning.width / 4 * 3
                       width: (lstPlanning.width - 25) / 4
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
                       var returnmsg = root.appointment.appPlanner().saveWorkedOn(ftrDatum.newValue, ftrDuration.newValue)
                        var appID = root.appointment.title;
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
                   // visible: appointment.isPast
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

    /*

    SpacerLine{
        id:spacer4
        x:0
        y:lstPlanning.y + lstPlanning.height
        width: root.width
    }

    Text{
        id: workedOnHeader
        color: Style.amber
        font:Style.fLarge
        text: "Worked On"
        x: 20;
        y: spacer4.y + spacer4.height

    }


    ListView{
        id:lstWorkedOn
        x:20
        y: workedOnHeader.y + workedOnHeader.height
        width: mainRect.width - 40
        height: contentHeight
        clip: true
        boundsMovement: Flickable.StopAtBounds
        flickableDirection: Flickable.AutoFlickDirection
        interactive: true
        model: jobs
        delegate:
                Rectangle{
                  height: workerTo.height
                  width: lstPlanning.width
                  color:Style.clrTransparant
                  MyTextField{
                      x:20
                      //id: workedOn
                      label: "Planned on:"
                      value: "99/99/9999 99:99"
                      textColor: Style.clrText
                      width: lstPlanning.width / 5 * 2 - 40
                  }
                  MyTextField{
                      x: lstPlanning.width / 5 * 2
                     // id: plannedDuration
                      label: "Duration:"
                      value: "99:99"
                      textColor: Style.clrText
                      width: lstPlanning.width / 5
                  }
                  MyTextField{
                      x: lstPlanning.width / 5 * 3
                      id: workerTo
                      label: "Planned:"
                      value: "Block rest of day(s)"
                      textColor: Style.clrText
                      width: lstPlanning.width / 5 * 2
                  }
                }
        ScrollIndicator.vertical: ScrollIndicator {visible: true}
        ScrollBar.vertical: ScrollBar {visible: true}
    }

    SpacerLine{
        id:spacer5
        x:0
        y:lstWorkedOn.y + lstWorkedOn.height
        width: root.width
    }
    */




    SpacerLine{
        id:spacer10
        x:0
        y:lstPlanning.y + lstPlanning.height + 20
        width: root.width
    }



 }

    Rectangle{
        id:saveBox
        x: 10
        y: root.height - height
        width: root.width - x*2
        height: 100
        color: Style.clrTransparant
        SpacerLine{
            width:saveBox.width
        }
        Rectangle{
            visible: false
            id:  rectSavePlannerLoading
            x:20
            y: 0
            height: plannerSaveLoadingTitle.y + plannerSaveLoadingTitle.height
            width: root.width
            color: Style.clrTransparant
            MyBusyIndicator{
                x: 20
                y: 20
                width: 32
                height: 32
            }

            Text{
                id:plannerSaveLoadingTitle
                x: 80
                y: 20
                color: Style.clrText
                font: Style.fLarge
                text: "Planner loading"

            }
        }

        MyMenuButton{
            visible: editMode;
            id: btnCheck
            x: 0
            y: 10
            width: saveBox.width/5
            label: "Cancel"
             onClick: function(){
                 appointment.cancelEdit();
                 root.editMode = false;
                 root.closeWindow();
             };
        }



        MyMenuButton{
            visible: editMode
            x: saveBox.width - width - 20
            y: 10
            width: saveBox.width/5
            label: "Save"
             onClick: function(){
                appointment.save(repeatInput.currentIndex, repeatCountInput.value)
                root.editMode = false;
                 root.closeWindow()
             };

        }

    }

    Popup {
        property string msg : "HALLO"
           id: savePopup
           x: 100
           y: 100
           width: 200
           height: 300
           modal: true
           focus: true
           closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent
            Text{
                text: savePopup.msg
            }
    }

}



    ListModel{
        id: planModeModel
        ListElement{text:"Fixed Date Time"}
        ListElement{text:"Plan as block before end date"}
        ListElement{text:"Plan as task before end date"}
    }

    ListModel{
        id: repeatModel
        ListElement{text:"None"}
        ListElement{text:"Every Day"}
        ListElement{text:"Every Week"}
        ListElement{text:"Every Month"}
    }


    ListModel{
        id:jobs
        ListElement{jobID: 1222; jobNo: "24-0001"; jobName: "Naam";jobClient: "Client"; isSubItem: true}
        ListElement{jobNo: "24-0002"; isSubItem: true}
        ListElement{jobNo: "24-0003"}
        ListElement{jobID: 1222; jobNo: "24-0001"; isSubItem: true}
        ListElement{jobNo: "24-0002"; isSubItem: true}
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







}
