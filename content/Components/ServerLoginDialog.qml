import QtQuick 2.15
import QtQuick.Controls 2.15
import Planner 1.0

Item {
    id:root
    width: Constants.width
    height: Constants.height

    Rectangle{

        x:0
        y:0
        width: root.width
        height:root.height
        z:10
        color: "#00000088"
    }
    Rectangle{
        x: root.width / 2 - width/2
        y: root.height / 2 - height/2
        width: 400;
        height:300
        border.color: Style.amber
        border.width: 1
        radius:10
        Rectangle{
            x: 0
            y: 0
            width: 400;
            height:btn.y + btn.height + 20
            border.color: Style.amber
            border.width: 1
            radius:10

            Text{
                x: 80;
                y: 10;
                height: 40
                width: parent.width - x*2;
                text: "Login"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                color: Style.clrDark
                font:Style.fHugeBold
            }
        }
        Text{
            visible: !dbManager.loginRunning
            x:10
            y:115
            width: parent.width - x*2
            font: Style.fMedium;
            text: "Username:"
            wrapMode: Text.WordWrap
        }
        TextField{
            visible: !dbManager.loginRunning
             id: txtUserName
            x:10
            y:135
            width: parent.width - x*2
            font: Style.fMedium;
            text: dbManager.userName
        }

        Text{
            visible: !dbManager.loginRunning
            x:10
            y:195
            width: parent.width - x*2
            font: Style.fMedium;
            text: "Password:"
            wrapMode: Text.WordWrap
        }
        TextField{
            visible: !dbManager.loginRunning
            id:txtpassword
            x:10
            y:215
            width: parent.width - x*2
            font: Style.fMedium;
            text: dbManager.password
        }
        Button{
            visible: !dbManager.loginRunning
            id:btn
            x:10
            y:280
            width: parent.width - x*2
            text: "Login"
            onClicked: {
                dbManager.userName = txtUserName.text
                dbManager.password = txtpassword.text
                dbManager.login();
            }
        }

        BusyIndicator{
            visible: dbManager.loginRunning
            x:parent.width / 2 - width /2
            y:160
            height: 100
            width: 100
        }


    }

   // MouseArea{
   //     anchors.fill: parent
   // }


}
