
import QtQuick 2.0

Item {
    id: id_root

    property int value: 3  // Giá trị mặc định là 3 (D)

    Rectangle {
        id: id_gear

        anchors.centerIn: parent
        height: Math.min(id_root.width, id_root.height)
        width: height
        radius: width / 2
        color: "black"
        border.color: "light green"
        border.width: id_gear.height * 0.02

        Repeater {
            model: 3  // Chỉ cần 3 giá trị cho D, N, R

            Item {
                height: id_gear.height / 2
                transformOrigin: Item.Bottom
                rotation: index * 90 + 180  // Điều chỉnh góc
                x: id_gear.width / 2

                Rectangle {
                    height: id_gear.height * 0.12
                    width: height
                    color: (index + 1) === value ? "light green" : "grey"  // Ánh xạ từ 1, 2, 3 sang D, N, R
                    radius: width / 2
                    antialiasing: true
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.top: parent.top
                    anchors.topMargin: id_gear.height * 0.05

                    Text {
                        anchors.centerIn: parent
                        color: "black"
                        text: index === 0 ? "R" : (index === 1 ? "N" : "D")  // Thay đổi vị trí ký tự
                        font.pixelSize: parent.height * 0.5
                        font.family: "Comic Sans MS"

                        // Đảo ngược chữ để không bị ngược
                        rotation: - (index * 90 + 180) // Xoay ngược lại chữ
                    }
                }
            }
        }
    }

    Text {
        anchors.centerIn: parent
        text: "Gear\nPosition"
        color: "light green"
        font.pixelSize: id_gear.height * 0.1
        font.family: "Comic Sans MS"
    }
}

