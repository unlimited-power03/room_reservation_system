#ifndef SHOW_ROOMS_USER_VERSION_H
#define SHOW_ROOMS_USER_VERSION_H

#include <QDialog>
#include "room.h"

namespace Ui {
class showRoomsUserVersion;
}

class userGui;
class reservationGui;

class showRoomsUserVersion : public QDialog
{
    Q_OBJECT

public:
    explicit showRoomsUserVersion(QWidget *parent = nullptr);
    void setUserGui(userGui* gui);
    void setReservationGui(reservationGui* gui);
    void onClickedReserveButton(int row_number);
    ~showRoomsUserVersion();
    int getSelectedRoomID();
    void showTable();
private slots:
    void on_back_clicked();

    void on_submit_button_clicked();

private:
    Ui::showRoomsUserVersion *ui;
    userGui* user_gui_showRoomsUserVersion;
    reservationGui* reservation_gui_showRoomsUserVersion;
    room roomObj_showRoomsUserVersion;
    int selectedRoomId;

};

#endif // SHOW_ROOMS_USER_VERSION_H
