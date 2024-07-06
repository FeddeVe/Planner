import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Shapes 1.15
import Planner 1.0

Item {
    antialiasing: true
    property string jobNumber : "24-0001"
    property string jobName : "Job Naam"
    property string jobClient : "Client"
    property real jobPercentComplete : 0.01
    property string timeLeft : "88:88"
    property string statusColor : "#000000"
    property bool hover : false
    property bool isActive : false
    property bool expandRight: false
    property bool expandDown : false
    property bool taskIsActive : true

    id: root
    width: 300
    height: borderRect.height



    Rectangle {
        id: borderRect
        x:0
        y:0
        height: txtJobStatus.y + txtJobStatus.height + 10
        width:  root.width
        color: root.hover ? Style.white : Style.clrTransparant
       // gradient:
       //     Gradient {
        //            orientation: Gradient.Horizontal
        //            GradientStop { position: 0.0; color:root.hover? Style.white : Style.background}
        //            GradientStop { position: 1.0; color: root.isActive? Style.grey : Style.green}
        //        }








    Rectangle{
        id:statusRect
        x:10
        y:10
        width: 20
        height: borderRect.height - 20
        radius: 5
        color: statusColor
        border.color: Style.grey
        border.width: 2
    }

    Text{
        id:txtJobNo
        x:45
        y:5
        text: root.jobNumber
        font: Style.fLargeBold
        color: root.hover ? Style.gray : Style.white
    }

    Text{
        id:txtJobName
        x:txtJobNo.x
        y:5+txtJobNo.height
        text: root.jobName
        font: Style.fMedium
        color: root.hover ? Style.gray : Style.white
    }

    Text{
        id: txtJobStatus
        x:txtJobNo.x
        y:5+txtJobNo.height + txtJobName.height
        font: Style.fStandard
        color: root.hover ? Style.gray : Style.white
        text: jobClient
    }

    Canvas {
        id: splitLine
            width: root.width; height: root.height
            property color lineColor : Style.grey
            onLineColorChanged: requestPaint()

            onPaint: {
                var ctx = getContext("2d")
                ctx.lineWidth = 2
                ctx.strokeStyle = lineColor
                ctx.beginPath()
                ctx.moveTo(10, borderRect.height - 1)
                ctx.lineTo(borderRect.width -10, borderRect.height+2)
                ctx.closePath()
                //ctx.fill()
                ctx.stroke()
            }
        }
    }


}
