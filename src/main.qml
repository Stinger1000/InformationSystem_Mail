import QtQuick 2.2
import QtQuick.Window 2.2

Window {
    width: 1280
    height: 720
    visible: true
    title: qsTr("Information System Mail");

    Image{
        id: _background
        source: "qrc:/image/back.png"
        anchors.fill: parent
    }
}
