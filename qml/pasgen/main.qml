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
        anchors.bottom: result.bottom
        model: myModel
        delegate: Text {
            text: modelData
            MouseArea {
                anchors.fill: parent;
                onClicked: {
                    page.text = parent.text;
                    page.onAccepted()
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
