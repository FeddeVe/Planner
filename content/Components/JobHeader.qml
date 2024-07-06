import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item {
    property bool editMode : false
    property int offset : 20
    property int jobId : 0
    property var job : jobsManager.job(jobId)
    id:root
    width: 200
    height: Constants.height

    onEditModeChanged: {
        if(editMode == false){
            var jobNo = autoCompleteJob.value;
            if(jobNo == ""){
                jobNo = autoCompleteJob.textValue;
            }

            job.save(jobNo, inputjobName.text, inputClient.text, inputJobDate.text, inputStartDate.text, inputJobPickDate.text);
        }
    }

    Rectangle{
    id:headerRect
        x:0
        y:0
        width: 200
        height: root.height
        z:2
        color:Style.clrDark

        CloseButton{
            x:5
            y:5
            onClick: function(){onClose()}
        }

        EditButton{
            x:headerRect.width - width - 5
            y:5
            onClick: function(){root.editMode = !root.editMode}
        }

        Text{
            id:jobTitle
            x: offset
            y: 40
            height: 15
            font: Style.fStandard
            text:"Job:"
            color: Style.clrText
        }

        AutoCompleteJob{
            id:autoCompleteJob
            visible: editMode
            x: 5
            y: jobNo.y
            width: root.width - x * 2
            z:2
            value: job.no
            //onValueChanged: job.no = value
            onJobIDChanged:{
                root.jobId = autoCompleteJob.jobID
               // root.job = jobsManager.job(root.jobId)
            }
        }

        Text{
            visible: !editMode
            id:jobNo
            x: offset
            y: jobTitle.y + jobTitle.height
            width: root.width/2-10
            height: 35
            font: Style.fMedium
            text:job.no
            color: Style.clrText
        }

        Text{
            id:jobNameTitle
            x: offset
            y: jobNo.y + jobNo.height
            height: 15
            font: Style.fStandard
            text:"Title:"
            color: Style.clrText
        }

        Text{
            visible: !editMode
            id:jobName
            x: offset
            y: jobNameTitle.y + jobNameTitle.height
            width: root.width/2-10
            height:35
            font: Style.fMedium
            text:job.title
            color: Style.clrText
        }

        TextField{
            visible: editMode
            id:inputjobName
            x: 6
            y: jobNameTitle.y + jobNameTitle.height
            width: root.width - x * 2
            height:35
            font: Style.fMedium
            text:job.title
            color: Style.clrText
            Keys.onReturnPressed: editMode = false
        }

        Text{
            id:jobClientTitle
            x: offset
            y: jobName.y + jobName.height
            height: 15
            font: Style.fStandard
            text:"Client:"
            color: Style.clrText
        }

        Text{
            id:client
            visible: !editMode
            x: offset
            y: jobClientTitle.y + jobClientTitle.height
            width: root.width/2-10
            height: 35
            font: Style.fMedium
            text:job.client
            color: Style.clrText
        }

        TextField{
            visible: editMode
            id:inputClient
            x: 6
            y: jobClientTitle.y + jobClientTitle.height
            width: root.width - x * 2
            height:35
            font: Style.fMedium
            text:job.client
            color: Style.clrText
            Keys.onReturnPressed: editMode = false
        }



        Text{
            id:durTitle
            x: offset
            y: client.y + client.height
            height: 15
            font: Style.fStandard
            text:"Job Date:"
            color: Style.clrText
        }
        Text{
            visible: !editMode
            id:totalDuration
            x: offset
            y: durTitle.y + durTitle.height
            width: root.width/2-10
            height: 35
            font: Style.fMedium
            text: job.jobDate
            color: Style.clrText
        }

        TextField{
            id:inputJobDate
            visible: editMode
            x:6
            y:totalDuration.y
            width: root.width - x *2
            height: totalDuration.height
            text: job.jobDate
            inputMask: "99.99.9999 99:99"
            font: Style.fMedium
            color: Style.amber
            Keys.onReturnPressed: editMode = false
        }



        Text{
            id:statustitle
            x: offset
            y: totalDuration.y + totalDuration.height
            height: 15
            font: Style.fStandard
            text:"Job Bouw Datum:"
            color: Style.clrText
        }
        Text{
            id:status
            x: offset
            y: statustitle.y + statustitle.height
            width: root.width/2-10
            height: 35
            font: Style.fMedium
            color: Style.clrText
            text: job.jobStartDate
        }

        TextField{
            visible: editMode
            id: inputStartDate
            x:6
            y:status.y
            width: root.width - x *2
            height: totalDuration.height
            text: job.jobStartDate
            inputMask: "99.99.9999 99:99"
            font: Style.fMedium
            color: Style.amber
            Keys.onReturnPressed: editMode = false
        }

        Text{
            id:jobP
            x: offset
            y: status.y + status.height
            height: 15
            font: Style.fStandard
            text:"Job Pick Date:"
            color: Style.clrText
        }
        Text{
            id:jobPickDate
            x: offset
            y: jobP.y + jobP.height
            width: root.width/2-10
            height: 35
            font: Style.fMedium
            text: job.jobPickDate
            color: Style.clrText
        }

        TextField{
            id:inputJobPickDate
            visible: editMode
            x:6
            y:jobPickDate.y
            width: root.width - x *2
            height: jobPickDate.height
            text: job.jobPickDate
            inputMask: "99.99.9999 99:99"
            font: Style.fMedium
            color: Style.amber
            Keys.onReturnPressed: editMode = false
        }
        Text{
            id:jobS
            x: offset
            y: jobPickDate.y + jobPickDate.height
            height: 15
            font: Style.fStandard
            text:"Status:"
            color: Style.clrText
        }
        Text{
            id:jobStatus
            x: offset
            y: jobS.y + jobS.height
            width: root.width/2-10
            font: Style.fMedium
            text:"OK // In Progress"
            color: Style.green
        }
        MyCheckBox{
            id:chDisplay
            x: offset
            y: jobStatus.y + jobStatus.height
            text: "Display Complete"
            checked: false
            clr: Style.clrText
            txtclr: Style.clrText
        }
        Button{
            x:offset
            y:chDisplay.y + chDisplay.height
            width: headerRect.width - x * 2
            text: "Add List"
            onClicked: edit.visible = true

        }

        Canvas {
                width: headerRect.width; height: headerRect.height
                //x:dayPartHeight * index + dayPartHeight
                //property color fillColor : disabled ? "#ababab" : "#ffffff"
                //onFillColorChanged: requestPaint()
                onPaint: {
                    var ctx = getContext("2d")
                    ctx.lineWidth = 1
                    ctx.fillStyle = Style.background
                    ctx.strokeStyle = Style.amber
                    ctx.beginPath()
                    ctx.moveTo(headerRect.width - 2, 20)
                    ctx.lineTo(headerRect.width - 2, headerRect.height-20)
                    ctx.closePath()
                    //ctx.fill()
                    ctx.stroke()
                }
            }

    }




}
