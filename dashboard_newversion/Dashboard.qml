import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: id_dashboard

    property int count: 0
    property var gearValues: ["D", "N", "R"]
    property string receivedString: ""
    property var parts: [] // Đảm bảo khởi tạo parts là một mảng

    Connections {
        target: udpReceiver
            function onDataReceived() {
                var receivedData = udpReceiver.getReceivedData();
                console.log("Received data:", receivedData); // In ra dữ liệu nhận được

                if (typeof receivedData === "string") {
                    id_dashboard.parts = receivedData.split("_"); // Gán chuỗi đã tách vào `parts`
                } else {
                    console.error("Dữ liệu nhận không phải là chuỗi:", receivedData);
                }
            }
    }

    Timer {
        id: id_timer
        repeat: true
        interval: 500
        running: true

        onTriggered: {
            //if (id_dashboard.parts.length === 2) {  // Kiểm tra xem `parts` có đủ hai phần không
                id_speed.value = parseInt(id_dashboard.parts[0]); // Gán phần đầu tiên vào `id_speed.value`
                id_gear.value = parseInt(id_dashboard.parts[1]);  // Gán phần thứ hai vào `id_gear.value`
                id_info.fuelValue = parseInt(id_dashboard.parts[2]);
            // id_speed.value = 200; // Gán phần đầu tiên vào `id_speed.value`
            // id_gear.value = 2;  // Gán phần thứ hai vào `id_gear.value`
            // id_info.fuelValue = 69;


            // Cập nhật trạng thái đèn báo rẽ
            if (id_dashboard.count % 2 === 0) {
                id_turnLeft.isActive = true;
                id_turnRight.isActive = false;
            } else {
                id_turnLeft.isActive = false;
                id_turnRight.isActive = true;
            }
        }
    }

    Rectangle {
        id: id_speedArea
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width * 0.4 *1.1
        height: width
        color: "black"
        radius: width / 2
        z: 1

        Speed {
            id: id_speed
            anchors.fill: id_speedArea
            anchors.margins: id_speedArea.width * 0.025
        }
    }

    Rectangle {
        id: id_gearArea
        anchors.bottom: id_speedArea.bottom
        x: parent.width / 80
        width: parent.width * 0.35 * 1.1
        height: width
        color: "black"
        radius: width / 2

        Gear {
            id: id_gear
            anchors.fill: id_gearArea
            anchors.margins: id_gearArea.width * 0.025
        }
    }

    Rectangle {
        id: id_infoArea
        anchors.bottom: id_speedArea.bottom
        x: parent.width - parent.width / 2.6
        width: parent.width * 0.35*1.1
        height: width
        color: "black"
        radius: width / 2

        Info {
            id: id_info
            anchors.fill: id_infoArea
            anchors.margins: id_infoArea.width * 0.025
        }
    }

    Rectangle {
        anchors.bottom: id_speedArea.bottom
        anchors.left: id_gearArea.horizontalCenter
        anchors.right: id_infoArea.horizontalCenter
        height: id_gearArea.width / 2
        color: "black"
        z: -1
    }

    Turn {
            id: id_turnLeft
            anchors {
                right: id_gearArea.right
                rightMargin: id_gearArea.height * 0.04
                bottom: id_gearArea.bottom
                bottomMargin: id_gearArea.height * 0.01
            }
            width: id_gearArea.width / 5.5
            height: id_gearArea.height / 8.2
            isActive: false
        }

    Turn {
         id: id_turnRight
         anchors {
            left: id_infoArea.left
            leftMargin: id_infoArea.height * 0.04
            bottom: id_infoArea.bottom
            bottomMargin: id_infoArea.height * 0.01
        }
        width: id_infoArea.width / 5.5
        height: id_infoArea.height / 8.2
        transformOrigin: Item.Center
        rotation: 180
        isActive: true
    }
}
