import QtQuick 2.0

Rectangle {
    width: 300
    height: 500

    Text {
        id: passwordText
        text: qsTr("Password: ")
    }
    TextInput {
        id: password
        anchors.left: passwordText.right
        anchors.right: parent.right
        echoMode: TextInput.Password
        focus: true

        onAccepted: {
            page.focus = true
            page.onAccepted()
        }
    }

    Text {
        id: pageText
        anchors.top: passwordText.bottom
        text: qsTr("Page: ")
    }
    TextInput {
        id: page
        anchors.left: passwordText.right
        anchors.right: parent.right
        anchors.top: password.bottom

        onAccepted: {
            check.text = "Checksum: " + hash.Do(password.text, "check", false)
            hash.Do(password.text, page.text, true)

            if (result.text != "Click here to show password") {
                result.text = "Result: " + hash.Do(password.text, page.text, true)
            }
        }
    }

    ListView {
        anchors.top: pageText.bottom
        anchors.bottom: check.top
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
        text: qsTr("Click here to show password")
        MouseArea {
            anchors.top: parent.bottom
            anchors.bottom: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            onClicked: {
                if (result.text == "Click here to show password") {
                    result.text = "Result: " + hash.Do(password.text, page.text, true)
                }
                else {
                    result.text = "Click here to show password"
                }
            }
        }
    }
    Text {
        id: check
        anchors.bottom: result.top
        text: qsTr("Checksum: -")
    }
}
