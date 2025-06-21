import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Window {
    width: 320
    height: 240
    visible: true
    color: "darkgrey"
    title: qsTr("temp_calculator")

    ColumnLayout {
        anchors.centerIn: parent
        anchors.margins: 10
        spacing: 10

        Rectangle {
            Layout.alignment: Qt.AlignCenter
            Layout.preferredHeight: 20
            RowLayout {
                anchors.centerIn: parent
                spacing: 10

                Rectangle {
                    Layout.fillWidth: true
                    Layout.minimumWidth: 50
                    Layout.preferredWidth: 100

                    Text {
                        anchors.centerIn: parent
                        text: "Celsius"
                        color: "black"
                    }
                }

                Rectangle {
                    Layout.fillWidth: true
                    Layout.minimumWidth: 50
                    Layout.preferredWidth: 100

                    TextField {
                        anchors.centerIn: parent
                        id: field_Celsius
                        validator: RegularExpressionValidator { regularExpression: /^(-[0-9]|-1[0-9][0-9]|-2[0-9]|-2[0-6][0-9]|-27[0-3]|\d*)$/ }
                        onTextEdited: {
                            controller.set_field_Celsius(field_Celsius.text)
                        }
                    }
                }
            }
        }


        Rectangle {
            Layout.alignment: Qt.AlignCenter
            Layout.preferredHeight: 20
            RowLayout {
                anchors.centerIn: parent
                spacing: 10

                Rectangle {
                    Layout.fillWidth: true
                    Layout.minimumWidth: 50
                    Layout.preferredWidth: 100

                    Text {
                        anchors.centerIn: parent
                        text: "Fahrenheit"
                        color: "black"
                    }
                }

                Rectangle {
                    Layout.fillWidth: true
                    Layout.minimumWidth: 50
                    Layout.preferredWidth: 100

                    TextField {
                        anchors.centerIn: parent
                        id: field_Fahrenheit
                        validator: RegularExpressionValidator { regularExpression: /^(-[0-9]|-1[0-9][0-9]|-2[0-9][0-9]|-3[0-9][0-9]|-4[0-9]|-4[0-4][0-9]|-45[0-9]|\d*)$/ }
                        onTextEdited: {
                            controller.set_field_Fahrenheit(field_Fahrenheit.text)
                        }
                    }
                }
            }
        }


        Rectangle {
            Layout.alignment: Qt.AlignCenter
            Layout.preferredHeight: 20
            RowLayout {
                anchors.centerIn: parent
                spacing: 10

                Rectangle {
                    Layout.fillWidth: true
                    Layout.minimumWidth: 50
                    Layout.preferredWidth: 100

                    Text {
                        anchors.centerIn: parent
                        text: "Kelvin"
                        color: "black"
                    }
                }

                Rectangle {
                    Layout.fillWidth: true
                    Layout.minimumWidth: 50
                    Layout.preferredWidth: 100

                    TextField {
                        anchors.centerIn: parent
                        id: field_Kelvin
                        validator: RegularExpressionValidator { regularExpression: /^(\d*)$/ }
                        onTextEdited: {
                            controller.set_field_Kelvin(field_Kelvin.text)
                        }
                    }
                }
            }
        }
    }

    Connections {
        target: model
        function onField_Celsius_changed(Celsius_val) {
            field_Celsius.text = Celsius_val
        }

        function onField_Fahrenheit_changed(Fahrenheit_val) {
            field_Fahrenheit.text = Fahrenheit_val
        }

        function onField_Kelvin_changed(Kelvin_val) {
            field_Kelvin.text = Kelvin_val
        }
    }
}
