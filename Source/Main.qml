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

    // Main component
    Column {
        anchors.centerIn: parent
        spacing: 10

        // Text field with placeholder text
        TextField {
            id: textField
            width: 200
            placeholderText: "Enter text here..."
        }

        // Display the text entered in the TextField
        Text {
            id: displayText
            text: "Entered text: "
        }

        // Button to display text
        Button {
            text: "Copy"
            onClicked: {
                displayText.text = "Copied"
                view.get(textField.text)
                // view.start()
            }
        }

        // Button to display text
        Button {
            text: "Display Text"
            onClicked: {
                displayText.text = "Entered text: " + view.emitUserName()
                // view.start()
            }
        }
    }
}
