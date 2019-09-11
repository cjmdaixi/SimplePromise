import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import Qt.labs.settings 1.0
import SimplePromise 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    Settings {
        property alias script: scriptArea.text
    }

    ColumnLayout{
        id: columnLayout
        anchors.fill: parent
        anchors.margins: 10
        Rectangle{
            Layout.fillHeight: true
            Layout.fillWidth: true
            border.width: 2
            border.color: "grey"
            Layout.margins: 5
            ScrollView{
                anchors.fill: parent
                anchors.margins: 5
                TextArea{
                    id: scriptArea
                    selectByMouse: true
                }
            }
        }
        RowLayout{
            id: btnLayout
            Layout.fillWidth: true
            Item{Layout.fillWidth: true}
            Button{
                id: evaluateBtn
                text: "Evaluate"
                onClicked: {
                    var newObject = Qt.createQmlObject('import QtQuick 2.9; Item{id: root;function test(){' + scriptArea.text + '}}',
                                                       btnLayout,
                                                       "dynamicSnippet1");
                    newObject.test();
                }
            }
        }
    }
}
