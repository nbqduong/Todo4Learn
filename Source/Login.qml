import QtQuick 2.0
import QtQuick.Controls 2.3
import com.company.view 1.0

Item {
    signal login(string username,string password)
    width: 250
    height: 200

    View {
           id: view1
    }


    Column {
        id: column
        anchors.fill: parent
        spacing: 10

        Label {
            id: label
            text: qsTr("Username")
        }

        TextField {
            id: txtUsername
            width: parent.width
            text: qsTr("")
        }

        Label {
            id: label1
            text: qsTr("Password")
        }

        TextField {
            id: txtPassword
            width: parent.width
            text: qsTr("")
            echoMode: TextInput.Password
        }

        Button {
            id: button
            width: parent.width
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Login")

        }

    }

    Connections {
        target: button
        onClicked:
        {
            view1.getUserName(txtUsername.text)
            view1.getPassWord(txtPassword.text)
            login(view1.emitUserName(),txtPassword.text)
        }
    }


}

/*##^##
Designer {
    D{i:1;anchors_height:400;anchors_width:200}
}
##^##*/
