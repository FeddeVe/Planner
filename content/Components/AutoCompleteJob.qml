import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item {
    property string value : ""
    property string textValue : ""
    property int jobID : -99
   // property int jobIndex : -1

    onValueChanged: {
        jobsManager.loadAutoComplete(text);
        input.text = value
    }


    function setJobIndex(jobIndex){
        if(jobIndex == -1){
            jobID = -1;
            value = textValue
        }else{
        jobID = jobsManager.autocompletemodel().get(jobIndex).msid;
        value = jobsManager.autocompletemodel().get(jobIndex).no;
             }
        input.focus = false
        input.text = value
        console.log("JOBID == " + jobID);

    }

    id: root
    width: 200
    height: 35
    z:60
    Rectangle{
        x:0
        y:0
        height: input.height
        width: input.width
        color:"#00000000"
    TextField{
        id:input
        x:0
        y:0
        width: root.width
        height: 35
        text: value
        font: Style.fMedium
        color: Style.clrText
        Material.accent: Style.amber
        onFocusChanged: {
            if(focus == false){
                if(autoList.model.count == 0){
                    dial.title = "Job Not Found"
                    dial.msg = "Job "+ text +" not found. Would you create this job?"
                    dial.open()
                    root.textValue = text
                }else{
                    setJobIndex(0);
                }
            }else{
                jobsManager.loadAutoComplete(text);
            }
        }
        onTextChanged: {
            if(focus){
                jobsManager.loadAutoComplete(text);
            }
        }
        Keys.onEnterPressed: {
            input.focus = false
            if(autoList.model.count == 0){
                dial.title = "Job Not Found"
                dial.msg = "Job "+ text +" not found. Would you create this job?"
                dial.open()
                root.textValue = text
            }else{
                 setJobIndex(0);
            }
        }
        Keys.onReturnPressed: {
            input.focus = false
            if(autoList.model.count == 0){
                dial.title = "Job Not Found"
                dial.msg = "Job "+ text +" not found. Would you create this job?"
                dial.open()
                root.textValue = text
            }else{
                 setJobIndex(0);
            }
        }
        Keys.onEscapePressed: input.focus = false
    }
    }

    ListView{
        visible: input.focus
        id: autoList
        x: input.x
        y: input.height
        width: root.width - x * 2
        height: contentHeight + 150
        model: jobsManager.autocompletemodel()
       // model: jobs
        //clip:true
        /*
        footer:
            Rectangle{
                x:0
                y:0
                width:autoList.width
                height: 150
                color: Style.gray
                Text{
                    id:newjobTitle
                    x:autoList.width / 2 - width / 2
                    y:0
                    font:Style.fLarge
                    text: "New Job"
                    color:Style.clrText
                }
                Text{
                    id:newjobNoTitle
                    x:10
                    y:newjobTitle.y + newjobTitle.height
                    font:Style.fStandard
                    text: "JobNo:"
                    color:Style.clrText
                    width: autoList.width / 2
                }
                TextField{
                    id:newjobNo
                    x:newjobNoTitle.x + newjobNoTitle.width - 40
                    y:autoList.y
                    height: 35
                    color:Style.clrText
                }
                Button{
                    x:10
                    y: newjobNo.y +newjobNo.height;
                    width: autoList.width - x * 2
                    text: "Create Job";
                }



            }
            */
        delegate:
            Rectangle{
            //visible: !isEditJob
            id:itemRect
            property bool hover : false
                x:0
                y:2
                width: autoList.width
                height: client.y+client.height + 3
                color:hover ? Style.clrNormal : Style.gray
                Text{
                    id:no
                    x: 20
                    y:0
                    font: Style.fMediumBold
                    color: Style.clrText
                    text: JobNo
                }
                Text{
                    id:name
                    x: 20
                    y:no.y+no.height
                    font: Style.fStandard
                    color: Style.clrText
                    text: Title
                }
                Text{
                    id:client
                    x: 20
                    y:name.y+name.height
                    font: Style.fStandard
                    color: Style.clrText
                    text: Client
                }

                Canvas {
                        width: itemRect.width; height: itemRect.height
                        //x:dayPartHeight * index + dayPartHeight
                        //property color fillColor : disabled ? "#ababab" : "#ffffff"
                        //onFillColorChanged: requestPaint()
                        onPaint: {
                            var ctx = getContext("2d")
                            ctx.lineWidth = 1
                            ctx.fillStyle = Style.background
                            ctx.strokeStyle = Style.amber
                            ctx.beginPath()
                            ctx.moveTo(20, client.y + client.height + 2)
                            ctx.lineTo(itemRect.width-20, client.y + client.height + 2)
                            ctx.closePath()
                            //ctx.fill()
                            ctx.stroke()
                        }
                    }

                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: hover  = true
                    onExited: hover = false
                    onClicked: {
                        console.log("ID == "+ index);
                        setJobIndex(index);
                    }



                }




        }






    }

    YesNoDialog{
        id:dial
        modal: true
        onClosed: {
            if(dial.returnCode == 0){
                root.value = input.text
                input.text = root.value
                root.jobID = -1
            }else{
                root.value = ""
                root.jobID = -2
                input.text = ""
                input.focus = true
            }
        }
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
