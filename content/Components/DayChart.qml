import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item {
    property int dayPartCount : 24*4
    property int rectHeight : root.height - 30
    property int dayPartHeight : (rectHeight-20) / dayPartCount
    property bool isToday : true
    property string datum : "88/88/8888"
    property string dag : "DAG"
    property bool isHighLight : true
    property bool isWorkingDay : true
    property bool isTMPY : true
    property int rowIndex : 0
    property var dataModel
    property var onItemClick


    property bool hover : false
    id: root
    width: 300
    height: 500




    Text{
        id:lblDag
        x:0
        y:0
        width: root.width
        color: isHighLight ? Style.clrTitle : Style.clrNormal
        text: isToday ? "TODAY" : dag
        horizontalAlignment: Text.AlignHCenter
        font: Style.fLarge
    }



    Text{
        id: lblDatum
        x:0
        y:lblDag.y+lblDag.height
        width: root.width
        color: isHighLight ? Style.clrTitle : Style.clrNormal
        text: datum
        horizontalAlignment: Text.AlignHCenter
        font: Style.fLarge
    }

    Rectangle{
        id: container
        x:0
        y:lblDatum.y+lblDatum.height
        width: root.width
        height: root.height - y
        color:  isTMPY ? (isWorkingDay? Style.halfAmber : Style.amber):isWorkingDay? Style.white : Style.clrLight
        border.color: isHighLight ? Style.amber : Style.clrDark
        border.width: isHighLight ? 4 : 1
        radius: 10


        Repeater{
            id: repeater
            model: dayPartCount / 4
            Rectangle{
            Text{
                visible: !index == 0
                x:0
                y:dayPartHeight * index * 4 //+ dayPartHeight - height/2
                color: Style.gray
                text: index
                width: 25
                horizontalAlignment: Text.AlignRight
            }

            Canvas {
                    width: container.width; height: container.height
                    //x:dayPartHeight * index + dayPartHeight
                    //property color fillColor : disabled ? "#ababab" : "#ffffff"
                    //onFillColorChanged: requestPaint()
                    property color strokeColor : isWorkingDay ? Style.clrLight : Style.clrText
                    onStrokeColorChanged: requestPaint()
                    onPaint: {
                        var ctx = getContext("2d")
                        ctx.lineWidth = 1
                        ctx.fillStyle = Style.background
                        ctx.strokeStyle = strokeColor
                        ctx.beginPath()
                        ctx.moveTo(container.x + 40, dayPartHeight * index * 4 + dayPartHeight)
                        ctx.lineTo(container.width - 30, dayPartHeight * index * 4 + dayPartHeight)

                        ctx.closePath()
                        //ctx.fill()
                        ctx.stroke()
                    }

                }
            }

            }

        Repeater{
            model: agendaManager.dayModel().get(rowIndex)
            //model: dayItems
            Rectangle{
                property var item: agendaManager.dayModel().get(rowIndex).get(index).appointment()
                property bool hover : false
                id: itemRect
                x: 30
                y: xPos * dayPartHeight + dayPartHeight
                height: xHeight * dayPartHeight
                width: root.width-40
                radius: 5
                color: hover ? Style.clrText : (item.isClosed ? Style.grey : item.boxclr)
                border.color: hover ? Style.clrDark : Style.clrDark
                border.width: 1
                clip: true
                Image{
                    visible: (!item.appPlanner().completePlanned) || (item.appPlanner().agendaErrors);
                    x:5
                    y:5
                    width: 32
                    height: 32
                    source: "../images/warning.png"
                    fillMode: Image.PreserveAspectFit

                }

                Text{
                    id:txtTitle
                    x: 10
                    y: 5
                    width: itemRect.width - x*2
                    font: Style.fLargeBold
                    text: item.title
                    horizontalAlignment: Text.AlignHCenter
                    wrapMode: Text.WordWrap
                    color: Style.clrDark
                }
                Text{
                    id:txtType
                    x: 10
                    y: txtTitle.y+ txtTitle.height
                    width: itemRect.width - x*2
                    font: Style.fMediumBold
                    text: item.typeName
                    horizontalAlignment: Text.AlignLeft
                    color: Style.clrDark
                }

                Text{
                    id:txtFromTitle
                    x: 0
                    y: txtType.y + txtType.height
                    width: 70
                    font: Style.fStandard
                    text: "From:"
                    horizontalAlignment: Text.AlignRight
                    color: Style.clrDark
                }
                Text{
                    x: 75
                    y: txtType.y + txtType.height
                    width: 100
                    font: Style.fStandard
                    text: xDate
                    horizontalAlignment: Text.AlignLeft
                    color: Style.clrDark
                }
                Text{
                    id:txtToTitle
                    x: 0
                    y: txtFromTitle.y + txtFromTitle.height
                    width: 70
                    font: Style.fStandard
                    text: "To:"
                    horizontalAlignment: Text.AlignRight
                    color: Style.clrDark
                }
                Text{
                    x: 100
                    y: txtFromTitle.y + txtFromTitle.height
                    width: 75
                    font: Style.fStandard
                    text: xEndDate
                    horizontalAlignment: Text.AlignLeft
                    color: Style.clrDark
                }
                Text{
                    id:dueTimeTitle
                    x: 0
                    y: txtToTitle.y+txtToTitle.height
                    width: 90
                    font: Style.fStandard
                    text: "Due Time:"
                    horizontalAlignment: Text.AlignRight
                    color: Style.clrDark
                }
                Text{
                    x: 100
                    y: txtToTitle.y+txtToTitle.height
                    width: 100
                    font: Style.fStandard
                    text: item.endDate
                    horizontalAlignment: Text.AlignLeft
                    color: Style.clrDark
                }
                Text{
                    id:txtDurationTitle
                    x: 0
                    y: dueTimeTitle.y+dueTimeTitle.height
                    width: 90
                    font: Style.fStandard
                    text: "Duration:"
                    horizontalAlignment: Text.AlignRight
                    color: Style.clrDark
                }
                Text{
                    x: 100
                    y: dueTimeTitle.y+dueTimeTitle.height
                    width: 100
                    font: Style.fStandard
                    text: item.duration
                    horizontalAlignment: Text.AlignLeft
                    color: Style.clrDark
                }
                Text{
                    id:timeLeftTitle
                    x: 0
                    y: txtDurationTitle.y+txtDurationTitle.height
                    width: 90
                    font: Style.fStandard
                    text: "Time Left:"
                    horizontalAlignment: Text.AlignRight
                    color: Style.clrDark
                }
                Text{
                    x: 100
                    y: txtDurationTitle.y+txtDurationTitle.height
                    width: 100
                    font: Style.fStandard
                    text: item.durationLeft
                    horizontalAlignment: Text.AlignLeft
                    color: Style.clrDark
                }
                Text{
                    id:jobNoTitle
                    x: 0
                    y: timeLeftTitle.y+timeLeftTitle.height
                    width: 90
                    font: Style.fStandard
                    text: "Job NO::"
                    horizontalAlignment: Text.AlignRight
                    color: Style.clrDark
                }
                Text{
                    x: 100
                    y: timeLeftTitle.y+timeLeftTitle.height
                    width: 100
                    font: Style.fStandard
                    text: item.jobNo
                    horizontalAlignment: Text.AlignLeft
                    color: Style.clrDark
                }
                Text{
                    id:jobTitleTitle
                    x: 0
                    y: jobNoTitle.y+jobNoTitle.height
                    width: 90
                    font: Style.fStandard
                    text: "Job:"
                    horizontalAlignment: Text.AlignRight
                    color: Style.clrDark
                }
                Text{
                    x: 100
                    y: jobNoTitle.y+jobNoTitle.height
                    width: 100
                    font: Style.fStandard
                    text: item.jobTitle
                    horizontalAlignment: Text.AlignLeft
                    color: Style.clrDark
                }
                Text{
                    id:descriptionTitle
                    x: 0
                    y: jobTitleTitle.y+jobTitleTitle.height
                    width: 90
                    font: Style.fStandard
                    text: "Description:"
                    horizontalAlignment: Text.AlignRight
                    color: Style.clrDark
                }
                Text{
                    x: 20
                    y: descriptionTitle.y+descriptionTitle.height
                    width: itemRect.width - x*2
                    height: itemRect.height - y;
                    font: Style.fStandard
                    text: item.description
                    horizontalAlignment: Text.AlignLeft
                    wrapMode: Text.WordWrap
                    color: Style.clrDark

                }




                MouseArea{
                    anchors.fill: parent
                    hoverEnabled: true
                    onEntered: {
                        //detailRect.x = mouseX
                        //detailRect.y = mouseY
                       // detailRect.item = itemRect.item
                       // detailRect.visible = true
                        itemRect.hover = true
                    }
                    onExited: {
                        itemRect.hover = false
                       // detailRect.visible = false;
                    }
                    onClicked: {
                        root.onItemClick(0, item.msid)
                        //onItemClick(0,item.msid);
                    }


                }
            }



        }

        Rectangle{
            visible: false
            id:detailRect
            property var item: agendaManager.dayModel().get(rowIndex).get(index).appointment()
                property bool hover : false

                x: 30
                y:xPos * dayPartHeight
                height: 500
                width: root.width-40
                radius: 5
                color: hover ? Style.clrText : (item.isClosed ? Style.gray : item.clr)
                border.color: hover ? Style.clrDark : Style.clrDark
                border.width: 1
                clip: true
                Text{
                    id:txtDetailTitle
                    x: 10
                    y: 5
                    width: itemRect.width - x*2
                    font: Style.fLargeBold
                    text: item.title
                    horizontalAlignment: Text.AlignHCenter
                    wrapMode: Text.WordWrap
                    color: Style.clrDark
                }
                Text{
                    id:txtDetailType
                    x: 10
                    y: txtTitle.y+ txtTitle.height
                    width: itemRect.width - x*2
                    font: Style.fMediumBold
                    text: item.typeName
                    horizontalAlignment: Text.AlignLeft
                    color: Style.clrDark
                }

                Text{
                    id:txtDetailFromTitle
                    x: 0
                    y: txtType.y + txtType.height
                    width: 70
                    font: Style.fStandard
                    text: "From:"
                    horizontalAlignment: Text.AlignRight
                    color: Style.clrDark
                }
                Text{
                    x: 75
                    y: txtType.y + txtType.height
                    width: 100
                    font: Style.fStandard
                    text: xDate
                    horizontalAlignment: Text.AlignLeft
                    color: Style.clrDark
                }
                Text{
                    id:txtDetailToTitle
                    x: 0
                    y: txtFromTitle.y + txtFromTitle.height
                    width: 70
                    font: Style.fStandard
                    text: "To:"
                    horizontalAlignment: Text.AlignRight
                    color: Style.clrDark
                }
                Text{
                    x: 100
                    y: txtFromTitle.y + txtFromTitle.height
                    width: 75
                    font: Style.fStandard
                    text: xEndDate
                    horizontalAlignment: Text.AlignLeft
                    color: Style.clrDark
                }
                Text{
                    id:dueDetailTimeTitle
                    x: 0
                    y: txtToTitle.y+txtToTitle.height
                    width: 90
                    font: Style.fStandard
                    text: "Due Time:"
                    horizontalAlignment: Text.AlignRight
                    color: Style.clrDark
                }
                Text{
                    x: 100
                    y: txtToTitle.y+txtToTitle.height
                    width: 100
                    font: Style.fStandard
                    text: item.endDate
                    horizontalAlignment: Text.AlignLeft
                    color: Style.clrDark
                }
                Text{
                    id:txtDetailDurationTitle
                    x: 0
                    y: dueTimeTitle.y+dueTimeTitle.height
                    width: 90
                    font: Style.fStandard
                    text: "Duration:"
                    horizontalAlignment: Text.AlignRight
                    color: Style.clrDark
                }
                Text{
                    x: 100
                    y: dueTimeTitle.y+dueTimeTitle.height
                    width: 100
                    font: Style.fStandard
                    text: item.duration
                    horizontalAlignment: Text.AlignLeft
                    color: Style.clrDark
                }
                Text{
                    id:timeDetailLeftTitle
                    x: 0
                    y: txtDurationTitle.y+txtDurationTitle.height
                    width: 90
                    font: Style.fStandard
                    text: "Time Left:"
                    horizontalAlignment: Text.AlignRight
                    color: Style.clrDark
                }
                Text{
                    x: 100
                    y: txtDurationTitle.y+txtDurationTitle.height
                    width: 100
                    font: Style.fStandard
                    text: "moet nog iets komen om dit te calculeren"
                    horizontalAlignment: Text.AlignLeft
                    color: Style.clrDark
                }
                Text{
                    id:jobDetailNoTitle
                    x: 0
                    y: timeLeftTitle.y+timeLeftTitle.height
                    width: 90
                    font: Style.fStandard
                    text: "Job NO::"
                    horizontalAlignment: Text.AlignRight
                    color: Style.clrDark
                }
                Text{
                    x: 100
                    y: timeLeftTitle.y+timeLeftTitle.height
                    width: 100
                    font: Style.fStandard
                    text: item.jobNo
                    horizontalAlignment: Text.AlignLeft
                    color: Style.clrDark
                }
                Text{
                    id:jobDetailTitleTitle
                    x: 0
                    y: jobNoTitle.y+jobNoTitle.height
                    width: 90
                    font: Style.fStandard
                    text: "Job:"
                    horizontalAlignment: Text.AlignRight
                    color: Style.clrDark
                }
                Text{
                    x: 100
                    y: jobNoTitle.y+jobNoTitle.height
                    width: 100
                    font: Style.fStandard
                    text: item.jobTitle
                    horizontalAlignment: Text.AlignLeft
                    color: Style.clrDark
                }
                Text{
                    id:descriptionDetailTitle
                    x: 0
                    y: jobTitleTitle.y+jobTitleTitle.height
                    width: 90
                    font: Style.fStandard
                    text: "Description:"
                    horizontalAlignment: Text.AlignRight
                    color: Style.clrDark
                }
                Text{
                    x: 20
                    y: descriptionTitle.y+descriptionTitle.height
                    width: itemRect.width - x*2
                    height: itemRect.height - y;
                    font: Style.fStandard
                    text: item.description
                    horizontalAlignment: Text.AlignLeft
                    wrapMode: Text.WordWrap
                    color: Style.clrDark

                }

        }

        ListModel{
            id: dayItems
            ListElement{startBlok: 3; endBlok: 8; title: "TEST"; jobno: "24-0001"; jobName:"SDSDSD"; dueTime: "88/88/8888 88:88"; duration: "88:88"; timeLeft: "88:88"}
            ListElement{startBlok: 3; endBlok: 8; title: "TEST"; jobno: "24-0001"; jobName:"SDSDSD"; dueTime: "88/88/8888 88:88"; duration: "88:88"; timeLeft: "88:88"}
            ListElement{startBlok: 3; endBlok: 8; title: "TEST"; jobno: "24-0001"; jobName:"SDSDSD"; dueTime: "88/88/8888 88:88"; duration: "88:88"; timeLeft: "88:88"}
            ListElement{startBlok: 3; endBlok: 8; title: "TEST"; jobno: "24-0001"; jobName:"SDSDSD"; dueTime: "88/88/8888 88:88"; duration: "88:88"; timeLeft: "88:88"}
            ListElement{startBlok: 3; endBlok: 8; title: "TEST"; jobno: "24-0001"; jobName:"SDSDSD"; dueTime: "88/88/8888 88:88"; duration: "88:88"; timeLeft: "88:88"}

        }






    }
}
