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

    ListView {
        width: 5000; height: 500
        anchors.top: _background.top; anchors.left: _background.left
        anchors.topMargin: 10; anchors.leftMargin: 20
        spacing: 5
        orientation: ListView.Horizontal
        model: ContactModel {}
        delegate: Rect{}
    }

}
