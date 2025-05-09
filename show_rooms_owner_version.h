#ifndef SHOW_ROOMS_OWNER_VERSION_H
#define SHOW_ROOMS_OWNER_VERSION_H

#include <QDialog>
#include "room.h"
namespace Ui {
class showRoomsOwnerVersion;
}

class ownerGui;
class editRoom;
class showRoomsOwnerVersion : public QDialog
{
    Q_OBJECT

public:
    explicit showRoomsOwnerVersion(QWidget *parent = nullptr);
    void setOwnerGui(ownerGui *gui);
    void setEditRoom(editRoom *gui);

    int getSelectedRoomId();
    ~showRoomsOwnerVersion();

private slots:
    void on_back_clicked();
    void onClickedEditButton(int row_number);
    void onClickedDeleteButton(int row_number);

    void on_submit_button_clicked();

    void on_reset_button_clicked();

private:
    Ui::showRoomsOwnerVersion *ui;
    room roomObj_showRoomsOwnerVersion;
    ownerGui *owner_gui_showRoomsOwnerVersion;
    editRoom *edit_room_gui_showRoomsOwnerVersion;
    void loadRooms();
    int selectedRoomId;
};

#endif // SHOW_ROOMS_OWNER_VERSION_H
