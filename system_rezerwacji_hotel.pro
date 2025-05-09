QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT +=  sql widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addroom.cpp \
    edit_owner_data.cpp \
    edit_reservation.cpp \
    edit_room.cpp \
    edit_user_data.cpp \
    login.cpp \
    main.cpp \
    owner_password_data.cpp \
    owner_sign_in.cpp \
    ownerdata.cpp \
    ownergui.cpp \
    password_data.cpp \
    persondata.cpp \
    reservation.cpp \
    reservation_gui.cpp \
    room.cpp \
    session_manager.cpp \
    show_all_reservations.cpp \
    show_rooms_owner_version.cpp \
    show_rooms_user_version.cpp \
    show_user_reservations.cpp \
    sign_in.cpp \
    user_password_data.cpp \
    userdata.cpp \
    usergui.cpp

HEADERS += \
    addroom.h \
    edit_owner_data.h \
    edit_reservation.h \
    edit_room.h \
    edit_user_data.h \
    login.h \
    owner_password_data.h \
    owner_sign_in.h \
    ownerdata.h \
    ownergui.h \
    password_data.h \
    persondata.h \
    reservation.h \
    reservation_gui.h \
    room.h \
    session_manager.h \
    show_all_reservations.h \
    show_rooms_owner_version.h \
    show_rooms_user_version.h \
    show_user_reservations.h \
    sign_in.h \
    user_password_data.h \
    userdata.h \
    usergui.h

FORMS += \
    addroom.ui \
    edit_room.ui \
    login.ui \
    owner_sign_in.ui \
    ownergui.ui \
    reservation_gui.ui \
    show_all_reservations.ui \
    show_rooms_owner_version.ui \
    show_rooms_user_version.ui \
    show_user_reservations.ui \
    sign_in.ui \
    usergui.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    build/Desktop_Qt_6_8_2_llvm_mingw_64_bit-Debug/config.env \
    build/config.env \
    config.env
