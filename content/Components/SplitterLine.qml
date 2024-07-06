import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item {
    property int startX : 10

    property int startY : 10


    id:root
    width: Constants.width
    height: Constants.height

    Canvas {
        id: line
            width: root.width; height: root.height
            property color lineColor : Style.grey
            onLineColorChanged: requestPaint()

            onPaint: {
                var ctx = getContext("2d")
                ctx.lineWidth = 2
                ctx.strokeStyle = lineColor
                ctx.beginPath()
                ctx.moveTo(startX, root.height - 1)
                ctx.lineTo(root.width - startX, root.height+2)
                ctx.closePath()
                //ctx.fill()
                ctx.stroke()
            }
        }
}
