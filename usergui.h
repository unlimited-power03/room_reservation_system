#ifndef USERGUI_H
#define USERGUI_H

#include <QWidget>
#include "userdata.h"
#include "session_manager.h"
#include "user_password_data.h"
#include "reservation.h"
namespace Ui {
class userGui;
}

class login;
class showRoomsUserVersion;
class showUserReservations;
class editUserData;


class userGui : public QWidget
{
    Q_OBJECT

public:
    explicit userGui(QWidget *parent = nullptr);
    void setLogin(login* log_in);
    void setShowRoomsUserVersion(showRoomsUserVersion* gui);
    void setShowUserReservations(showUserReservations * gui);
    void setEditUserData(editUserData* gui);
    ~userGui();

private slots:
    void on_signOut_clicked();
    void on_showroomsAndMakeReservation_clicked();
    void on_reservationHistory_clicked();

    void on_deleteAccount_clicked();

    void on_editAccount_clicked();

private:
    Ui::userGui *ui;
    userdata uD_gui;
    session_manager sM_gui;
    showRoomsUserVersion* showRoomsUserVersionGui;
    showUserReservations * showUserReservationsGui;
    editUserData* showEditUserData_usergui;
    userPasswordData userpasswordData_usergui;
    reservation reservation_userGui;
    login* log_in;
};

#endif // USERGUI_H
