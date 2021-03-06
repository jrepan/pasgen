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
            check.text = "Checksum: " + hash.Do(password.text, "check", true)
            hash.Do(password.text, page.text, false)

            if (result.text != "Click here to show password") {
                result.text = "Result: " + hash.Do(password.text, page.text, false)
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
            id: listItem
            text: modelData

            MouseArea {
                anchors.fill: parent
                property int origin: -1

                onClicked: {
                    page.text = parent.text
                    page.onAccepted()
                }

                onMouseXChanged: {
                    if (origin != -1) {
                        parent.x = mouseX - origin
                    }
                }

                onPressed: {
                    origin = mouseX
                }

                onReleased: {
                    if (Math.abs(parent.x) > parent.width / 2) {
                        hash.Remove(parent.text)
                    } else {
                        onCanceled()
                    }
                }

                onCanceled: {
                    parent.x = 0
                    origin = -1
                }
            }
        }
    }

    Text {
        id: result
        font.family: "serif"
        anchors.bottom: parent.bottom
        text: qsTr("Click here to show password")
        MouseArea {
            anchors.fill: parent
            onClicked: {
                if (result.text == "Click here to show password") {
                    result.text = "Result: " + hash.Do(password.text, page.text, false)
                }
                else {
                    result.text = "Click here to show password"
                }
            }
        }
    }
    Text {
        id: check
        font.family: "serif"
        anchors.bottom: result.top
        text: qsTr("Checksum: -")
    }
}
