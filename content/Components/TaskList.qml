import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item {
    property string listTitle : "List TITLE"
    property var onEdit
    property var onClose

    id:root
    width: 600
    height: 600
    Rectangle{
        id:borderRect
        width: root.width
        height: root.height
        radius: 10
        color: Style.clrDark
        /*
        Text{
            x:5
            y:5
            width: root.width - x*2
            height: 35
            text: listTitle
            horizontalAlignment: Text.AlignHCenter
            font: Style.fHugeBold
            color: Style.clrDark
        }

        Text{
            id:jobTitle
            x: 8
            y: 64
            height: 15
            font: Style.fStandard
            text:"Job:"
            color: Style.background
        }
        Text{
            id:jobNo
            visible: !editMode
            x: 8
            y: jobTitle.y + jobTitle.height
            width: root.width/2-10
            font: Style.fMedium
            text:"88-8888"
            color: Style.background
        }
        Text{
            id:jobName
            visible: !editMode
            x: 8
            y: jobNo.y + jobNo.height
            width: root.width/2-10
            font: Style.fMedium
            text:"Jurgens disco party"
            color: Style.background
        }

        Text{
            id:jobD
            x: root.width - width - 8
            y: 64
            height: 15
            font: Style.fStandard
            text:"Job Date:"
            horizontalAlignment: Text.AlignRight
            color: Style.background
        }
        Text{
            id:jobDate
            x: root.width - width - 8
            y: jobD.y + jobD.height
            width: root.width/2-10
            font: Style.fMedium
            text:"88/88/8888"
            horizontalAlignment: Text.AlignRight
            color: Style.background
        }
        Text{
            id:jobS
            x: root.width - width - 8
            y: jobDate.y+jobDate.height
            height: 15
            font: Style.fStandard
            text:"Job Bouw Datum:"
            horizontalAlignment: Text.AlignRight
            color: Style.background
        }
        Text{
            id:jobStartDate
            x: root.width - width - 8
            y: jobS.y + jobS.height
            width: root.width/2-10
            font: Style.fMedium
            text:"88/88/8888"
            horizontalAlignment: Text.AlignRight
            color: Style.background
        }
        Text{
            id:jobP
            x: root.width - width - 8
            y: jobStartDate.y+jobStartDate.height
            height: 15
            font: Style.fStandard
            text:"Job Pick Date:"
            horizontalAlignment: Text.AlignRight
            color: Style.background
        }
        Text{
            id:jobPickDate
            x: root.width - width - 8
            y: jobP.y + jobP.height
            width: root.width/2-10
            font: Style.fMedium
            text:"88/88/8888"
            horizontalAlignment: Text.AlignRight
            color: Style.background
        }
        */


    ListView{
        id: taskList
        x: 10
        y: 2
        width: borderRect.width - x * 2
        height: borderRect.height - y - 2
        model: jobs
        clip:true
        delegate:
            Rectangle{
                x:0
                y:0
                width: root.width
                height: isSubItem ? taskListItem.height : taskListItem2.height
                color: Style.clrDark
            TaskListSubItem{
            visible: isSubItem ? true : false
            id:taskListItem
            height:54
            width: taskList.width -40
            editMode: edit
            x:20
            y:0
            }

            TaskListMileStone{
                visible: isSubItem ? false : true
                id:taskListItem2
                x:20
                y:0
                editMode: edit
                width: taskList.width -40
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
            Rectangle{
            id:headerRect
                property int offset : 25
                x:0
                y:0
                width: taskList.width
                height: displayComplete.y + displayComplete.height + 10
                z:2
                 color: Style.clrDark


                Text{
                    x:5
                    y:5
                    width: root.width - x*2
                    height: 35
                    text: listTitle
                    horizontalAlignment: Text.AlignHCenter
                    font: Style.fHugeBold
                    color: Style.clrText
                }

                EditButton{
                    x:headerRect.width - width - offset
                    y:5
                }



                Text{
                    id:durTitle
                    x: offset
                    y: 40
                    height: 15
                    font: Style.fStandard
                    text:"Duration:"
                    color: Style.clrText
                }
                Text{
                    id:totalDuration
                    x: offset
                    y: durTitle.y + durTitle.height
                    width: root.width/2-10
                    font: Style.fMedium
                    text:"888:88 // 888:88"
                    color: Style.clrText
                }
                Text{
                    id:statustitle
                    x: offset
                    y: totalDuration.y + totalDuration.height
                    height: 15
                    font: Style.fStandard
                    text:"Status:"
                    color: Style.clrText
                }
                Text{
                    id:status
                    x: offset
                    y: statustitle.y + statustitle.height
                    width: root.width/2-10
                    font: Style.fMedium
                    text:"Nog niet ingepland - Deadlines niet ingevuld"
                    color: Style.amber
                }



                MyCheckBox{
                   id:displayComplete
                   x: root.width/2 - width/2
                   // x:offset
                    y: status.y + status.height
                    font: Style.fMedium
                    text:"Display complete items"
                    clr: Style.clrText
                    txtclr: Style.clrText

                }
                Canvas {
                        width: root.width; height: root.height
                        //x:dayPartHeight * index + dayPartHeight
                        //property color fillColor : disabled ? "#ababab" : "#ffffff"
                        //onFillColorChanged: requestPaint()
                        onPaint: {
                            var ctx = getContext("2d")
                            ctx.lineWidth = 1
                            ctx.fillStyle = Style.background
                            ctx.strokeStyle = Style.amber
                            ctx.beginPath()
                            ctx.moveTo(20, headerRect.height - 5)
                            ctx.lineTo(headerRect.width - 20, headerRect.height-5)
                            ctx.closePath()
                            //ctx.fill()
                            ctx.stroke()
                        }
                    }
            }


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
     }

    Canvas {
            width: root.width; height: root.height
            //x:dayPartHeight * index + dayPartHeight
            //property color fillColor : disabled ? "#ababab" : "#ffffff"
            //onFillColorChanged: requestPaint()
            onPaint: {
                var ctx = getContext("2d")
                ctx.lineWidth = 1
                ctx.fillStyle = Style.background
                ctx.strokeStyle = Style.amber
                ctx.beginPath()
                ctx.moveTo(root.width - 2, 50)
                ctx.lineTo(root.width - 2, root.height-50)
                ctx.closePath()
                //ctx.fill()
                ctx.stroke()
            }
        }

    ListModel{
        id:jobs
        ListElement{jobNo: "24-0002";label: ""; isSubItem: true; edit: true}
        ListElement{jobNo: "24-0003";label: ""; edit: true}
    }



}
