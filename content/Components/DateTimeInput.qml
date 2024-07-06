import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item{
    id: root
    property string dateTime : ""
    property string placeHolderText : "Not Set"
    property bool submit: false
    width: 200
    height: 35

    onDateTimeChanged: textField.text = dateTime;

    TextField {
        id:textField
    x:0
    y: 0
    visible: true
    width: root.width
    height: root.height
    text : dateTime
    inputMask: "99.99.9999 99:99"
    font: Style.fMedium
    color: Style.amber
    onFocusChanged: submit = false
    Keys.onReturnPressed: submit = true
    //onFocusChanged: dateTime = text
}

}
