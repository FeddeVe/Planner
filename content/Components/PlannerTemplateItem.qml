import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item {
    id: root
    property color clr : Style.clrLight
    property bool isFirst : false
    property bool isLast : false
    property var plannerItem
    width: 600
    height: mainRect.height

    Rectangle{
        id:mainRect
        x:0
        y:0
        width: root.width
        height: lstItems.height + lstItems.y
        color: clr
        gradient: Gradient {
                orientation: Gradient.Horizontal
                GradientStop { position: 0.0; color: plannerItem.clr}
                GradientStop { position: 0.25; color: Style.clrDark}
        }

   Image {
       visible: !isFirst
       id: btnUp
       x:10
       source: "../images/up-arrow-light.png"
       fillMode: Image.PreserveAspectFit
       width:32
       height: 64
       MouseArea{
           anchors.fill: parent
           onClicked: plannerItem.moveUp();
       }
   }

   Image {
       visible: !isLast
       id: btnDown
       x:btnUp.x + btnUp.width + 20
       source: "../images/down-arrow-light.png"
       fillMode: Image.PreserveAspectFit
       width:32
       height: 64
       MouseArea{
           anchors.fill: parent
           onClicked: plannerItem.moveDown();
       }
   }

   DeleteButton{
       id: deleteBtn
       x: btnDown.x + btnDown.width + 20
       height: 64
   }

   MyTextField{
       id: title
       x: deleteBtn.x + deleteBtn.width + 20
       y:5
       editMode: true
       width: mainRect.width - x - 20
       label: "Label:"
       value: plannerItem.label
       onNewValueChanged: plannerItem.label = newValue
   }

   MyComboBox{
       id:colorInput
       x: title.x
       y: title.y + title.height
       editMode: true
       width: title.width
       label: "Plan As:"
       model: appManager.types()
       currentIndex: plannerItem.planAss
       textRole: "label"
       onCurrentIndexChanged: {
           plannerItem.planAss = currentIndex;
       }
   }

   MyComboBox{
       id:planMode
       x: colorInput.x
       y: colorInput.y + colorInput.height
       editMode: true
       width: title.width
       label: "Plan Mode:"
       model: appManager.types()
       currentIndex: plannerItem.planAss
       textRole: "label"
       onCurrentIndexChanged: {
           plannerItem.planAss = currentIndex;
       }
   }

   MyComboBox{
       id:defDeadLine
       x: planMode.x
       y: planMode.y + planMode.height
       editMode: true
       width: title.width
       label: "Default Deadline:"
       model: deadLines
       currentIndex: plannerItem.planAss
       textRole: "d_title"
       onCurrentIndexChanged: {
           plannerItem.planAss = currentIndex;
       }
   }

   MyTextArea{
       id: remarks
       x: defDeadLine.x
       y:defDeadLine.y + defDeadLine.height
       editMode: true
       width: mainRect.width - x - 20
       label: "Default Remarks:"
       value: plannerItem.label
       onValueChanged: plannerItem.label = value
       height: 200
   }

   MyTextField{
       id: calcDuration
       x: planMode.x
       y:remarks.y + remarks.height
       editMode: false
       width: mainRect.width - x - 20
       label: "Average Duration:"
       value: plannerItem.label
       onNewValueChanged: plannerItem.label = newValue
   }

   /*

   MyMenuButton{
       id: addItem
       x: title.x
       y: calcDuration.y + calcDuration.height
       width: colorInput.width
       height: 40
       label: "Add Item"
       onClick: function(){root.plannerItem.addItem()}
   }

   */


   SpacerLine{
       id:spacer1
       x:10
       y:calcDuration.y + calcDuration.height
       width: root.width - x*2
       height: 20
   }



   ListView{
      // visible: !agendaManager.plannerRunning
       id:  lstItems
       x:2
       y: spacer1.y + spacer1.height
       width: mainRect.width
       height: contentHeight
       clip: true
       boundsMovement: Flickable.StopAtBounds
       flickableDirection: Flickable.AutoFlickDirection
       interactive: true
       model: plannerItem
       delegate: PlannerTemplateSubItem{
            x:30
            width: lstItems.width-x
            subItem: plannerItem.get(index)
       }


       ScrollIndicator.vertical: ScrollIndicator {visible: true}
       ScrollBar.vertical: ScrollBar {visible: true}
   }







    }


    ListModel{
        id:jobs
        ListElement{d_title: "Tekening opstarten"; d_template: "Tekening Opstarten"; d_dueDate: "Not Set"; d_durationLeft: "01:00"; d_completed: true; d_isNodig: true; d_type:1}
        ListElement{d_title: "Venue"; d_template: "Venue 2D"; d_dueDate: "Not Set"; d_durationLeft: "04:00"; d_completed: false; d_isNodig: true;d_type:1}
         ListElement{d_title: "Set Design"; d_template: "Set Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:1}
        ListElement{d_title: "Production Floorplan"; d_template: "Production Floorplan"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:1}
        ListElement{d_title: "Production 3D"; d_template: "Production 3D"; d_dueDate: "Not Set"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:1}
        ListElement{d_title: "Lighting Design"; d_template: "Lighting Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:1}
        ListElement{d_title: "Rigging Design"; d_template: "Rigging Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:1}
        ListElement{d_title: "Offerte Hardware Inboeken"; d_template: "Offerte Hardware Inboeken"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:1}
        ListElement{d_title: "Inschatting Crew"; d_template: "Rigging Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:1}
        ListElement{d_title: "Renders of Screenshots"; d_template: "Rigging Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:1}
        ListElement{d_title: "Einde van SALES"; d_template: "Rigging Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : false;d_type:1}
        ListElement{d_title: "Tekening Opschonen"; d_template: "Rigging Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:2}
        ListElement{d_title: "Items skipped in offerte stadium"; d_template: "Rigging Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:2}
        ListElement{d_title: "First Requests"; d_template: "Rigging Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:2}
        ListElement{d_title: "Planning & Crew"; d_template: "Rigging Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:2}
        ListElement{d_title: "Licht Prep"; d_template: "Rigging Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:2}
        ListElement{d_title: "Revisie Power"; d_template: "Rigging Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:2}
        ListElement{d_title: "Revisie Weights"; d_template: "Rigging Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:2}
        ListElement{d_title: "Revisie Materialen"; d_template: "Rigging Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:2}
        ListElement{d_title: "Revisie Design"; d_template: "Rigging Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:2}
        ListElement{d_title: "Operator Informeren"; d_template: "Rigging Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:2}
        ListElement{d_title: "Patchlijsten"; d_template: "Rigging Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:2}
        ListElement{d_title: "Check reacties Power & Rigging"; d_template: "Rigging Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:2}
        ListElement{d_title: "Printen & Final Checks"; d_template: "Rigging Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:2}


    }

    ListModel{
        id:deadLines
        ListElement{d_title: "Not Set"; d_template: "Tekening Opstarten"; d_dueDate: "Not Set"; d_durationLeft: "01:00"; d_completed: true; d_isNodig: true; d_type:1}
        ListElement{d_title: "JobDate"; d_template: "Tekening Opstarten"; d_dueDate: "Not Set"; d_durationLeft: "01:00"; d_completed: true; d_isNodig: true; d_type:1}
        ListElement{d_title: "JobStartDate"; d_template: "Venue 2D"; d_dueDate: "Not Set"; d_durationLeft: "04:00"; d_completed: false; d_isNodig: true;d_type:1}
        ListElement{d_title: "JobPickDate"; d_template: "Set Design"; d_dueDate: "01-06-2024 18:00"; d_durationLeft: "04:00"; d_completed: false; d_isNodig : true;d_type:1}

    }


}
