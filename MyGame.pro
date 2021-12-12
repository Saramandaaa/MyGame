QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Sources/basic/attribute.cpp \
    Sources/basic/character.cpp \
    Sources/basic/event.cpp \
    Sources/basic/optionset.cpp \
    Sources/GUI/mainwindow.cpp \
    Sources/GUI/startmenu.cpp \
    Sources/GUI/loadsave.cpp \
    Sources/utility/textcode.cpp \
    Sources/utility/saveinfo.cpp \
    Sources/utility/randsummoner.cpp \
    Sources/controller.cpp \
    Sources/eventHeap.cpp \
    Sources/eventlist.cpp \
    Sources/main.cpp \

HEADERS += \
    Events/ConstantEvent/entranceExam.hpp \
    Events/ConstantEvent/finalTermExam.hpp \
    Events/ConstantEvent/innovateFinish.hpp \
    Events/ConstantEvent/midTermExam.hpp \
    Events/ConstantEvent/newTerm.hpp \
    Events/ConstantEvent/prpFinish.hpp \
    Events/ConstantEvent/totallyGoodBye.hpp \
    Events/DailyEvent/dailyevent.hpp \
    Events/FinalEvent/baoyan.hpp \
    Events/FinalEvent/withdraw.hpp \
    Events/FinalEvent/work.hpp \
    Events/RandomEvent/innovateProgram.hpp \
    Events/RandomEvent/joinCorporation.hpp \
    Events/RandomEvent/love.hpp \
    Events/RandomEvent/mentalDisease.hpp \
    Events/RandomEvent/physicalDisease.hpp \
    Events/RandomEvent/prp.hpp \
    Events/RandomEvent/sayGoodBye.hpp \
    Events/RandomEvent/voteStudentAssociation.hpp \
    Events/eventheader.h \
    Headers/basic/attribute.h \
    Headers/basic/character.h \
    Headers/basic/event.h \
    Headers/basic/optionset.h \
    Headers/GUI/mainwindow.h \
    Headers/GUI/startmenu.h \
    Headers/GUI/loadsave.h \
    Headers/basicheader.h \
    Headers/utility/textcode.h \
    Headers/utility/saveinfo.h \
    Headers/utility/randsummoner.h \
    Headers/controller.h \
    Headers/eventHeap.h \
    Headers/eventlist.h \

FORMS += \
    Forms/loadsave.ui \
    Forms/mainwindow.ui \
    Forms/startmenu.ui

TRANSLATIONS += \
    MyGame_zh_CN.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
