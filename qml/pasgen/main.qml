import QtQuick 2.0

Rectangle {
    width: 700
    height: 100

    Column {
        Row {
            Text {
                text: qsTr("Password: ")
            }
            TextInput {
                id: password;
                echoMode: TextInput.Password;
                focus: true;
                onAccepted: {
                    result.text = "Result: " + hash.Do(password.text, page.text);
                    page.focus = true;
                }
            }
        }
        Row {
            Text {
                text: qsTr("Page: ")
            }
            TextInput {
                id: page;
                onAccepted: {
                    result.text = "Result: " + hash.Do(password.text, page.text);
                }
            }
        }
        Text {
            id: result;
            text: qsTr("Result: -")
        }
    }
}
