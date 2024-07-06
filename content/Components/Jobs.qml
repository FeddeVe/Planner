import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item {

    property bool addMode: false
    property bool editMode : false
    property bool expanded : true
    property int maxWidth: Constants.width
    property int defWidth: 300
    property var selectedJob



    onSelectedJobChanged: {
        if(selectedJob == undefined){
            console.log('NULL');
            addJobNr.value = "";
            addJobTitle.value = "";
            addJobClient.value = "";
            addJobDate.value = "";
            addJobStartDate.value = "";
            addJobPickDate.value = "";
            root.expanded = false;
        }else{
            addJobNr.value = selectedJob.no;
            addJobTitle.value = selectedJob.title;
            addJobClient.value = selectedJob.client;
            addJobDate.value = selectedJob.jobDate;
            addJobStartDate.value = selectedJob.jobStartDate;
            addJobPickDate.value = selectedJob.jobPickDate;
            console.log(addJobPickDate.value);
            root.expanded = true;
        }
    }

    id:root
    width: expanded ? lstBuckets.x + lstBuckets.width : defWidth
    height: Constants.height
    clip: true
    onVisibleChanged: jobsManager.listModel().loadModel("");

    Rectangle{
        visible: !addMode
        id:searchRect
        property int offset : 25
        x:0
        y:0
        width: jobList.width
        height: spacer1.y + spacer1.height + 10
        color: Style.clrTransparant

        AddButton{
            id: addBtn
            x:searchRect.width - width - searchRect.offset
            y:5
            width: 32
            onClick: function(){
                root.addMode = true
                root.editMode = true
                root.selectedJob = jobsManager.listModel().get(-1);
            };
        }

        MyTextField{
            id:searchJob
            x:searchRect.offset
            y:addBtn.y + addBtn.height
            label:"Search"
            value: ""
            editMode:true
            width: searchRect.width - x*2
            onQuickNewValueChanged: jobsManager.listModel().loadModel(quickNewValue);

        }
        SpacerLine{
            id: spacer1
            x:searchRect.offset
            y: searchJob.y+ searchJob.height + 10
            width: searchRect.width - x*2
        }
    }

    Rectangle{
        visible: addMode
        property int offset: 25
        id:addRect
        x:0
        y:0
        width:300
        height:root.height
        color: Style.clrTransparant
       //color:Style.gray

        Image {
            id: backImage
            source: "../images/left-arrow-light.png"
            fillMode: Image.PreserveAspectFit
            x:addRect.offset
            y:addRect.offset
            width:32
            height:32
            MouseArea{
                anchors.fill: parent
                onClicked:{
                    root.addMode = false
                    root.selectedJob = jobsManager.listModel().get(-1);
                    editAppointment.visible = false
                    root.expanded = false;
                    root.width = 300
                }
            }
        }

        EditButton{
            visible: !root.editMode
            x:addRect.width - addRect.offset - width
            y: addRect.offset
            onClick: function(){ root.editMode = true};
        }

        MyTextField{
            id: addJobNr
            x: addRect.offset
            y: backImage.y+ backImage.height + 32
            width: addRect.width - x*2
            editMode: root.editMode
            label: "JobNR:"
            value: ""
            onNewValueChanged: value = newValue
        }

        MyTextField{
            id: addJobTitle
            x: addRect.offset
            y: addJobNr.y + addJobNr.height
            width: addRect.width - x*2
            editMode: root.editMode
            label: "Job Title:"
            value: ""
            onNewValueChanged: value = newValue
        }

        MyTextField{
            id: addJobClient
            x: addRect.offset
            y: addJobTitle.y + addJobTitle.height
            width: addRect.width - x*2
            editMode: root.editMode
            label: "Job Client:"
            value: ""
            onNewValueChanged: value = newValue
        }

        MyTextField{
            id: addJobDate
            x: addRect.offset
            y: addJobClient.y + addJobClient.height
            width: addRect.width - x*2
            editMode: root.editMode
            label: "Job Date:"
            value: ""
            mask: "99-99-9999 99:99"
            //onNewValueChanged: value = newValue
        }


        MyTextField{
            id: addJobStartDate
            x: addRect.offset
            y: addJobDate.y + addJobDate.height
            width: addRect.width - x*2
            editMode: root.editMode
            label: "Job Start Date:"
            value: ""
            mask: "99-99-9999 99:99"
            onNewValueChanged: value = newValue
        }

        MyTextField{
            id: addJobPickDate
            x: addRect.offset
            y: addJobStartDate.y + addJobStartDate.height
            width: addRect.width - x*2
            editMode: root.editMode
            label: "Job Pick Date:"
            value: ""
            mask: "99-99-9999 99:99"
            onNewValueChanged: value = newValue
        }

        MyMenuButton{
            visible: !root.editMode
            id: btnAddBucket
            x: addRect.offset
            y: addJobPickDate.y + addJobPickDate.height + 10
            width: addRect.width - x*2
            height: 42
            label: "Add Bucket"
            onClick: function(){
                bucketManager.bucketModel().createBucket();
            }
        }

        MyMenuButton{
            visible:  root.editMode
            id: btnSave
            x: addRect.offset
            y: addJobPickDate.y + addJobPickDate.height + 10
            width: addRect.width - x*2
            height: 42
            label: "Save"
            onClick: function(){
               var msid = -1;
                if(selectedJob == undefined){

                }else{
                    msid = selectedJob.msid;
                }

               var returnmsg = jobsManager.createJob(msid, addJobNr.quickNewValue, addJobTitle.quickNewValue, addJobClient.quickNewValue, addJobDate.quickNewValue, addJobStartDate.quickNewValue, addJobPickDate.quickNewValue);
                if(returnmsg == "OK"){
                    searchJob.value = addJobNr.quickNewValue;
                    jobsManager.listModel().loadModel(searchJob.value);
                    root.editMode = false;
                    root.addMode = false;
                    root.selectedJob = jobsManager.listModel().get(-1);
                }else{
                    savePopup.msg = returnmsg
                    savePopup.open()
                }
            }
        }

        MyMenuButton{
            visible: !root.editMode
            id: btnAddAppointment
            x: addRect.offset
            y: btnSave.y + btnSave.height + 10
            width: addRect.width - x*2
            height: 42
            label: "Add Appointment"
            onClick: function(){
                editAppointment.visible = true;
                var appointment = appManager.appointment(-1);
                editAppointment.appointment = appointment
                appointment.setJobID(selectedJob.msid);
                editAppointment.editMode = true;
                editAppointment.jobVisible = false;
                root.expanded = false;
                root.width = editAppointment.x + editAppointment.width
            }
        }

        MyMenuButton{
             visible:  root.editMode
            id: btnCancel
            x: addRect.offset
            y: btnSave.y + btnSave.height + 10
            width: addRect.width - x*2
            height: 42
            label: "Cancel"
            onClick: function(){
                addJobNr.value = "";
                addJobTitle.value = "";
                addJobClient.value = "";
                addJobDate.value = "";
                addJobStartDate.value = "";
                addJobPickDate.value = "";
                root.addMode = false;
                root.editMode = false
            }
        }
    }

    ListView{
        visible: !addMode
        id: jobList
        x: 0
        y: searchRect.y + searchRect.height
        width: 300
        height: root.height - y
        model: jobsManager.listModel()
        clip:true
        delegate:
           JobBtn{
            id:jobBtn
            jobNumber: JobNo
            jobName: Title
            jobClient: Client
            statusColor: StatusColor

            MouseArea{
                anchors.fill: parent
                hoverEnabled: true
                onEntered: jobBtn.hover = true
                onExited: jobBtn.hover = false
                onClicked: {
                    root.selectedJob =  jobsManager.listModel().get(index);
                    bucketManager.setCurrentJob(selectedJob.msid);
                    root.addMode = true;
                    root.editMode = false;
                    root.expanded = true;
                }
            }
        }


        headerPositioning: ListView.OverlayHeader
        ScrollIndicator.vertical: ScrollIndicator {visible: true}
        ScrollBar.vertical: ScrollBar {visible: true}
    }

    Appointment_Large{
        id:editAppointment
        visible: false
        x:301
        y:0
        height: root.height
        closeWindow: function(){
            visible = false
            root.width = 300
        }
    }

    ListView{
        id: lstBuckets
        x: 301
        y: 0
        width: (maxWidth - x < contentWidth) ? maxWidth-x : contentWidth
        height: root.height
        visible: root.expanded
        onVisibleChanged: {
            if(visible){
                root.width = x + width
            }
        }

        onWidthChanged: {
            if(visible){
                root.width = x + width
            }
        }


        onModelChanged: {
            if(visible){
                root.width = x + width
            }
        }

        orientation: ListView.Horizontal
        clip: true;
        model: bucketManager.bucketModel()
        delegate: PlannerBucket{
            bucket: bucketManager.bucketModel().get(index)
            height: lstBuckets.height
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

    ListModel{
        id:jobs
        ListElement{jobID: 1222; jobNo: "24-0001"; isSubItem: true}
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
