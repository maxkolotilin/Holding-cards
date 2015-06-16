import QtQuick 1.1

Flipable {
    id: flipable
    width: width_value
    height: height_value

    property bool flipped: switcher

    front: Image { source: "image://cards_provider/" + card_back;
                   anchors.centerIn: parent }
    back: Image { source: "image://cards_provider/" + card_image;
                  anchors.centerIn: parent }

    transform: Rotation {
        id: rotation
        origin.x: flipable.width/2
        origin.y: flipable.height/2
        axis.x: 0; axis.y: 1; axis.z: 0   // set axis.y to 1 to rotate around y-axis
        angle: 0    // the default angle
    }

    states: State {
        name: "back"
        when: flipped
        PropertyChanges { target: rotation; angle: 180 }
    }

    transitions: Transition {
        NumberAnimation { target: rotation; property: "angle"; duration: 333 }
    }
}
