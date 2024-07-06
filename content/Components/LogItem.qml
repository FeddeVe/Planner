import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item {
    property color background : Style.gray

    id:root
    width: 400
    height: mainRect.width

    Rectangle{
        id:mainRect
        x:0
        y:0
        width: root.width
        height: status.y + status.height
        color: root.background

        DeleteButton{
            id: deleteButton
            x:5
            y:5
            height: 16
            width:16
        }

        MyTextField{
            id:from
            x:deleteButton.x + deleteButton.width
            y:deleteButton.y
            label: "From:"
            value: "88-88-8888 88:88"
            width:root.width/2 - x
            mask: "99-99-9999 99:99"
        }

        MyTextField{
            id:duration
            x:from.x + from.width
            y:from.y
            label: "Duration:"
            value: "88:88"
            width: from.width
            mask: "99:99"
            textAlign: Text.AlignRight
        }

        MyTextField{
            id:to
            x:deleteButton.x + deleteButton.width
            y:from.y + from.height
            label: "To:"
            value: "88-88-8888 88:88"
            width:root.width/2 - x
            mask: "99-99-9999 99:99"
        }

        MyTextField{
            id:status
            x:to.x + to.width
            y:to.y
            label: "Status:"
            value: "Worked On"
            width: from.width
            textAlign: Text.AlignRight
        }

        SplitterLine{
            id: splitterLine
            x:0
            y:0
            width: mainRect.width
            height: mainRect.height
        }


    }
}
