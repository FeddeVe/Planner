import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item {
    property string value : "VALUE"
    id: root
    width: 200
    height: 35
    TextField{
        x:0
        y:0
        width: root.width
        height: root.height
        text: value
        font: Style.fStandard
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
