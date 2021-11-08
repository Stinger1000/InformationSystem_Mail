import QtQuick 2.2

Rectangle{
    id: _rect
    width: 150
    height: 40
    color: "#00000000"
    Image{
        id: _im
        anchors.fill: _rect
        source: "qrc:/image/Button.png"
    }
}
