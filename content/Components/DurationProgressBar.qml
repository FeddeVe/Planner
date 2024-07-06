import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item {
    property int max : 100
    property int value : 50


    id:root
    width: 300
    height: 15

    ProgressBar{
        x:0
        y:0
        width: root.width
        height: root.height
        value: value
        from: 0
        to: max
    }
}
