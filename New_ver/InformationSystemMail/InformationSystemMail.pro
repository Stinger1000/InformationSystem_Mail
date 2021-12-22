QT       += core gui sql

QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controllers/MainController.cpp \
    main.cpp \
    mainwindow.cpp \
    models/MainTableModel.cpp \
    utils/Configs.cpp \
    utils/Logger.cpp \
    wgts/CreateDeletePostUi.cpp \
    wgts/CreateDeleteUserUi.cpp \
    wgts/CreateForwardPostUi.cpp \
    wgts/DepartureUi.cpp \
    wgts/SignInUi.cpp

HEADERS += \
    controllers/MainController.h \
    mainwindow.h \
    models/BaseModel.h \
    models/MainTableModel.h \
    utils/Configs.h \
    utils/Logger.h \
    wgts/CreateDeletePostUi.h \
    wgts/CreateDeleteUserUi.h \
    wgts/CreateForwardPostUi.h \
    wgts/DepartureUi.h \
    wgts/SignInUi.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qml.qrc
