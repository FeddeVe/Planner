import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item {
    property var onClose

    id:root
    width: Constants.width
    height: Constants.height
    Rectangle{
        id:borderRect
        width: root.width
        height: root.height
        radius: 10
        border.color: Style.clrTitle
        border.width: 2
        color:Style.clrDark


    ListView{
        id: jobLists
        x: 10
        y: 2
        width: borderRect.width - x * 2
        height: borderRect.height - y - 2
        orientation: ListView.Horizontal
        model: jobs
        clip:true

        delegate:
            Rectangle{
                x:0
                y:2
                width: taskList.width + 2
                height: jobLists.height - y*2
                color:Style.clrDark
                TaskList{
                    id: taskList
                    height: jobLists.height - y*2
                    width: 450
                }
        }

            //ItemDelegate {
            //width: taskList.width
            //height: 55

           // width: taskList.width
           // implicitHeight: 55


            //contentItem:


            /*
            MouseArea{
                anchors.fill: dayChartItem
                hoverEnabled: true
                onEntered: dayChartItem.hover = true
                onExited: dayChartItem.hover = false
                onClicked: dayView.currentIndex = index
            }
            */
        //}

        headerPositioning: ListView.OverlayHeader
        header:
             JobHeader{

              }

            /*
            Rectangle{
            id:headerRect
                property int offset : 25
                x:0
                y:0
                width: 200
                height: jobLists.height
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
                Text{
                    id:jobNo
                    visible: !editMode
                    x: offset
                    y: jobTitle.y + jobTitle.height
                    width: root.width/2-10
                    font: Style.fMedium
                    text:"88-8888"
                    color: Style.clrText
                }
                Text{
                    id:jobName
                    visible: !editMode
                    x: offset
                    y: jobNo.y + jobNo.height
                    width: root.width/2-10
                    font: Style.fMedium
                    text:"Jurgens disco party"
                    color: Style.clrText
                }
                Text{
                    id:client
                    visible: !editMode
                    x: offset
                    y: jobName.y + jobName.height
                    width: root.width/2-10
                    font: Style.fMedium
                    text:"Internation Orange"
                    color: Style.clrText
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
                    id:totalDuration
                    x: offset
                    y: durTitle.y + durTitle.height
                    width: root.width/2-10
                    font: Style.fMedium
                    text:"88/88/8888"
                    color: Style.clrText
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
                    font: Style.fMedium
                    text:"88/88/8888"
                    color: Style.clrText
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
                    font: Style.fMedium
                    text:"88/88/8888"
                    color: Style.clrText
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
              */


        /*
        footer:
            Rectangle{
                x:0
                y:0
                width: taskList.width
                height: 60
                color: Style.background
            }
            */


        ScrollIndicator.vertical: ScrollIndicator {visible: true}
        ScrollBar.vertical: ScrollBar {visible: true}
    }

    JobListEdit{
        id:edit
        visible: false
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
