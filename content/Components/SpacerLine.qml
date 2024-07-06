import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item {
    property color clr: Style.clrText
    property int lineWidth: 1
    property int offset : 20

    id:root
    width: 100
    height: 5

    Canvas {
            width: root.width; height: root.height
            property color lineColor : clr
            onLineColorChanged: requestPaint()
            onPaint: {
                var ctx = getContext("2d")
                ctx.lineWidth = lineWidth
                ctx.strokeStyle = lineColor
                ctx.beginPath()
                ctx.moveTo(offset, root.height - 3)
                ctx.lineTo(root.width - offset, root.height-3)
                ctx.closePath()
                //ctx.fill()
                ctx.stroke()
            }
        }

}
