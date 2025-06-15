import QtQuick 2.0
import QtQuick.Controls 2.15

Item {
    id: id_root

    property int value: 0
    property real animatedBatteryLevel: value // Giá tr? du?c animating

    Item {
        id: batteryIcon
        width: parent.height * 0.2 // Kích thu?c nh? g?n
        height: parent.height * 0.2
        anchors {
            right: id_fuel.left
            verticalCenter: id_fuel.verticalCenter
            rightMargin: parent.width * 0.02 // G?n sát v?i thanh pin
        }

        Rectangle {
            anchors.fill: parent
            color: "transparent"

            Canvas {
                anchors.fill: parent
                contextType: "2d"
                onPaint: {
                    var ctx = getContext("2d");
                    ctx.clearRect(0, 0, width, height);
                    ctx.fillStyle = "yellow";

                    // V? tia sét (g?p khúc m?t l?n)
                    ctx.beginPath();
                    ctx.moveTo(width * 0.5, 0);              // Ð?nh
                    ctx.lineTo(width * 0.2, height * 0.55);   // Ði?m g?p khúc xu?ng
                    ctx.lineTo(width * 0.55, height * 0.55);   // Ðáy
                    ctx.lineTo(width * 0.4, height);         // Chân tia sét
                    ctx.lineTo(width * 0.8, height * 0.4);   // Kéo lên
                    ctx.lineTo(width * 0.4, height * 0.4);   // Kéo lên
                    ctx.lineTo(width * 0.5, 0);              // Quay v? d?nh
                    ctx.closePath();
                    ctx.fill();

                }
            }
        }
    }

    //Thanh pin
    Rectangle {
        id: id_fuel

        width: parent.width * 0.8
        height: parent.height * 0.4
        radius: 5
        border.color: "white"
        border.width: 2
        anchors.centerIn: parent
        color: "black"
        // M?c pin hi?n t?i
        Rectangle {
            id: batteryLevel
            width: id_fuel.width * (id_root.animatedBatteryLevel / 100)
            height: id_fuel.height - id_fuel.border.width * 2
            anchors.left: id_fuel.left
            anchors.verticalCenter: id_fuel.verticalCenter
            color: id_root.animatedBatteryLevel > 20 ? "green" : "red"
            radius: id_fuel.radius - id_fuel.border.width
        }
    }

    // Ph?n d?u c?a pin
        Rectangle {
            id: batteryHead
            width: id_fuel.width * 0.05
            height: id_fuel.height * 0.3
            color: "white"
            anchors {
                left: id_fuel.right
                verticalCenter: id_fuel.verticalCenter
            }
            radius: 2
        }

        // Hi?n th? ph?n tram pin
        Text {
            id: batteryText
            text: Math.round(id_root.animatedBatteryLevel) + "%"
            anchors.centerIn: parent
            font.pixelSize: id_fuel.height * 0.4
            font.family: "Arial"
            color: id_root.animatedBatteryLevel > 20 ? "white" : "red"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            clip: true
        }

        // Animation d? thay d?i giá tr? mu?t mà
        Behavior on animatedBatteryLevel {
            SmoothedAnimation { velocity: 50 }
        }
}

    // Rectangle {
    //         id: id_fuel
    //         width: id_root.width * 0.8
    //         height: width
    //         anchors.centerIn: parent
    //         color: "green"
    //         radius: width / 2

    //         // Xoay vô lăng dựa trên góc value
    //         rotation: id_root.value
    //         Behavior on rotation {
    //             SmoothedAnimation { velocity: 60 }
    //         }

    //         // Đường viền bên ngoài cho vô lăng
    //         border.color: "grey"
    //         border.width: 6

    //         // Vẽ chi tiết của vô lăng
    //         Canvas {
    //             id: canvas
    //             anchors.fill: parent
    //             contextType: "2d"
    //             antialiasing: true

    //             onPaint: {
    //                 var context = canvas.getContext("2d");
    //                 var centerX = id_fuel.width / 2;
    //                 var centerY = id_fuel.height / 2;
    //                 var radius = id_fuel.width / 2 * 0.8;

    //                 // Vẽ vòng tròn vô lăng
    //                 context.beginPath();
    //                 context.arc(centerX, centerY, radius, 0, 2 * Math.PI);
    //                 context.lineWidth = 10;
    //                 context.strokeStyle = "black";
    //                 context.stroke();

    //                 // Vẽ thanh ngang giữa vô lăng
    //                 context.beginPath();
    //                 context.moveTo(centerX - radius , centerY);
    //                 context.lineTo(centerX + radius , centerY);
    //                 context.lineWidth = 6;
    //                 context.strokeStyle = "black";
    //                 context.stroke();

    //                 // Vẽ các thanh dọc của vô lăng
    //                 context.beginPath();
    //                 context.moveTo(centerX, centerY);  // Bắt đầu từ giữa vô lăng
    //                 context.lineTo(centerX, centerY + radius );
    //                 context.lineWidth = 6;
    //                 context.strokeStyle = "black";
    //                 context.stroke();
    //             }
    //         }
    //     }
    // Text {
    //         text: "Steering"
    //         color: "light green"
    //         font.pixelSize: id_fuel.height * 0.15
    //         anchors.top: id_fuel.bottom  // Đặt trên dưới của vô lăng
    //         anchors.horizontalCenter: id_fuel.horizontalCenter
    //         //anchors.topMargin:   // Khoảng cách nhỏ từ vô lăng
    //         font.family: "Comic Sans MS"
    //     }
    // }
