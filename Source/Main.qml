import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.3

import com.company.view 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    View {
           id: view
    }

    property string displayedUsr: "Initial Text"
    property string displayedPass: "Initial Text"

    // Main component
    Column {
        anchors.centerIn: parent
        spacing: 10

        Login {
            id: login
            width: 250
            height: 200
            anchors.centerIn: parent
            onLogin: {
                console.log("Username: ", username, " Password: ", password)
            }
        }


    }
}
