import QtQuick 2.0
import QtQuick.Layouts 1.0

Rectangle {
    width: 700
    height: 100

    GridLayout {
        id: grid
        columns: 2
        anchors.left: parent.left
        anchors.right: parent.right

        Text {
            id: passwordText
            Layout.fillHeight: true
            Layout.preferredWidth: passwordText.width
            text: qsTr("Password: ")
        }
        TextInput {
            id: password
            Layout.fillHeight: true
            Layout.fillWidth: true
            echoMode: TextInput.Password
            focus: true

            onAccepted: {
                result.text = "Result: " + hash.Do(password.text, page.text)
                page.focus = true
            }
        }

        Text {
            id: pageText
            Layout.fillHeight: true
            Layout.preferredWidth: passwordText.width
            text: qsTr("Page: ")
        }
        TextInput {
            id: page
            Layout.fillHeight: true
            Layout.fillWidth: true

            onAccepted: {
                result.text = "Result: " + hash.Do(password.text, page.text)
            }
        }
    }

    ListView {
        anchors.top: grid.bottom
        anchors.bottom: result.top
        anchors.left: parent.left
        anchors.right: parent.right
        clip: true
        model: myModel

        delegate: Text {
            text: modelData

            MouseArea {
                anchors.fill: parent

                onClicked: {
                    page.text = parent.text
                    page.onAccepted()
                }

                onPressAndHold: {
                    hash.Remove(parent.text)
                }
            }
        }
    }

    Text {
        id: result
        anchors.bottom: parent.bottom
        text: qsTr("Result: -")
    }
}
