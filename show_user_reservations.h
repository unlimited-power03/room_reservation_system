#ifndef SHOW_USER_RESERVATIONS_H
#define SHOW_USER_RESERVATIONS_H

#include <QDialog>
#include "room.h"
#include "reservation.h"
#include "userdata.h"
#include <QMessageBox>
#include "session_manager.h"
#include "show_rooms_user_version.h"

namespace Ui {
class showUserReservations;
}

class userGui;
class editReservation;

class showUserReservations : public QDialog
{
    Q_OBJECT

public:
    explicit showUserReservations(QWidget *parent = nullptr);
    void setUserGui(userGui* gui);
    void setEditReservationGui(editReservation* gui);
    void showTable();
    int getSelectedRoomID();
    int getSelectedReservationID();
    ~showUserReservations();

private slots:

    void on_back_clicked();
    void onClickedEditReservationButton(int row);
    void onClickedCancelReservationButton(int row);

    void on_submit_button_clicked();

    void on_reset_button_clicked();

private:
    Ui::showUserReservations *ui;
    userGui* user_gui_showUserReservation;
    editReservation * editReservation_showUserReservations;
    //editReservation* edit_reservation_gui;
    //room roomObj_showUserReservation;
    reservation reservationObj_showUserReservation;
    userdata userData_showUserReservation;
    session_manager sM_showUserReservation;
    int selectedRoomId;
    int selectedReservationID;
    //showRoomsUserVersion show_rooms_user_version_showUserreservations;
};

#endif // SHOW_USER_RESERVATIONS_H
