import QtQuick 2.0

Rectangle {
    width: 700
    height: 100

    Text {
        id: passwordText;
        text: qsTr("Password: ")
    }
    TextInput {
        id: password;
        anchors.left: passwordText.right
        echoMode: TextInput.Password;
        focus: true;
        onAccepted: {
            result.text = "Result: " + hash.Do(password.text, page.text);
            page.focus = true;
        }
    }
    Text {
        id: pageText
        anchors.top: passwordText.bottom
        text: qsTr("Page: ")
    }
    TextInput {
        id: page;
        anchors.left: pageText.right
        anchors.top: password.bottom
        onAccepted: {
            result.text = "Result: " + hash.Do(password.text, page.text);
        }
    }

    ListView {
        anchors.top: pageText.bottom
        anchors.bottom: result.top
        anchors.left: parent.left
        anchors.right: parent.right
        clip: true
        model: myModel
        delegate: Text {
            text: modelData
            MouseArea {
                anchors.fill: parent;
                onClicked: {
                    page.text = parent.text;
                    page.onAccepted()
                }
                onPressAndHold: {
                    hash.Remove(parent.text);
                }
            }
        }
    }

    Text {
        id: result;
        anchors.bottom: parent.bottom
        text: qsTr("Result: -")
    }
}
