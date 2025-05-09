#ifndef EDIT_ROOM_H
#define EDIT_ROOM_H

#include <QDialog>
#include "room.h"
#include "addroom.h"
#include <QMessageBox>
#include "reservation.h"
#include "sign_in.h"
#include <QDate>
namespace Ui {
class editRoom;
}

class showRoomsOwnerVersion;

class editRoom : public QDialog
{
    Q_OBJECT

public:
    explicit editRoom(QWidget *parent = nullptr);
    void setShowRoomsOwnerVersionGui(showRoomsOwnerVersion *gui);
    ~editRoom();

private slots:

    void on_back_clicked();

    void on_edit_room_clicked();

private:
    Ui::editRoom *ui;
    showRoomsOwnerVersion *show_rooms_owner_version_gui_editRoom;
    room roomObj_editRoom;
    addroom addRoom_editRoom;
    sign_in signIn_editRoom;
    reservation reservationObj_editRoom;
};

#endif // EDIT_ROOM_H
