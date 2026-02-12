QT += core widgets
CONFIG += c++17
TEMPLATE = app
TARGET = PhoneBook

SOURCES += \
    filters/phonebook_proxy.cpp \
    main.cpp \
    ui/mainwindow.cpp \
    model/phonebookmodel.cpp \
    ui/phonebooktableview.cpp

HEADERS += \
    filters/phonebook_proxy.h \
    ui/mainwindow.h \
    model/phonebookmodel.h \
    model/phonebookentry.h \
    ui/phonebooktableview.h
