QT       += core gui network serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14 no_batch

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
        ./3dParty/spdlog-1.9.2/spdlog-1.9.2/include \
        ./3dParty/tinyxml2-9.0.0/tinyxml2-9.0.0 \
        ./3dParty/MVS/Development/Includes \
        ./3dParty/Halcon/include/halconcpp \
        ./3dParty/Halcon/include


CONFIG(debug, debug|release) {
    LIBS += \
        ./3dParty/spdlog-1.9.2/spdlog-1.9.2/bin/Debug/spdlogd.lib \
        ./3dParty/tinyxml2-9.0.0/tinyxml2-9.0.0/bin/Debug/tinyxml2.lib \
        ./3dParty/MVS/Development/Libraries/win64/MvCameraControl.lib \
        ./3dParty/Halcon/lib/x64-win64/halconcpp.lib


}else{
    LIBS += \
        ./3dParty/spdlog-1.9.2/spdlog-1.9.2/bin/Release/spdlog.lib \
        ./3dParty/tinyxml2-9.0.0/tinyxml2-9.0.0/bin/Release/tinyxml2.lib \
        ./3dParty/MVS/Development/Libraries/win64/MvCameraControl.lib \
        ./3dParty/Halcon/lib/x64-win64/halconcpp.lib
}

SOURCES += \
    DataStructure/Camera/MCameraBase.cpp \
    DataStructure/Camera/MCameraHik.cpp \
    DataStructure/Camera/MCameraSimulator.cpp \
    DataStructure/Communication/MCommunicationBase.cpp \
    DataStructure/Communication/MCommunicationSerialPort.cpp \
    DataStructure/Communication/MCommunicationTcpClient.cpp \
    DataStructure/Communication/MCommunicationTcpServer.cpp \
    DataStructure/Configuration/MConfiguration.cpp \
    DataStructure/Configuration/MBasicSettings.cpp \
    DataStructure/Configuration/MAdvancedSettings.cpp \
    DataStructure/Configuration/MAuthoritySettings.cpp \
    DataStructure/Configuration/MSysInfo.cpp \
    DataStructure/Log/MLog.cpp \
    DataStructure/Thread/MThreadTask.cpp \
    Dialog/CameraWidget.cpp \
    Dialog/CommunicationWidget.cpp \
    Dialog/SettingsWidget.cpp \
    Dialog/StatisticsWidget.cpp \
    Dialog/mainwindow.cpp \
    main.cpp

HEADERS += \
    DataStructure/Camera/MCameraBase.h \
    DataStructure/Camera/MCameraHik.h \
    DataStructure/Camera/MCameraSimulator.h \
    DataStructure/Communication/MCommunicationBase.h \
    DataStructure/Communication/MCommunicationSerialPort.h \
    DataStructure/Communication/MCommunicationTcpClient.h \
    DataStructure/Communication/MCommunicationTcpServer.h \
    DataStructure/Configuration/MConfiguration.h \
    DataStructure/Configuration/MBasicSettings.h \
    DataStructure/Configuration/MAdvancedSettings.h \
    DataStructure/Configuration/MAuthoritySettings.h \
    DataStructure/Log/MLog.h \
    DataStructure/Configuration/MSysInfo.h \
    DataStructure/Thread/MThreadTask.h \
    Dialog/CameraWidget.h \
    Dialog/CommunicationWidget.h \
    Dialog/SettingsWidget.h \
    Dialog/StatisticsWidget.h \
    Dialog/mainwindow.h

FORMS += \
    Dialog/camerawidget.ui \
    Dialog/communicationwidget.ui \
    Dialog/settingswidget.ui \
    Dialog/statisticswidget.ui \
    Dialog/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
