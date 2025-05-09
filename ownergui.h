#ifndef OWNERGUI_H
#define OWNERGUI_H

#include <QWidget>
#include "ownerdata.h"
#include "session_manager.h"
#include "owner_password_data.h"
namespace Ui {
class ownerGui;
}

class login;
class addroom;
class showRoomsOwnerVersion;
class ownerSignIn;
class showAllReservations;
class editOwnerData;
class ownerGui : public QWidget
{
    Q_OBJECT

public:
    explicit ownerGui(QWidget *parent = nullptr);
    void setLogin(login* log_in);
    void setAddRoomGui(addroom *gui);
    void setOwnerSignInGui(ownerSignIn* gui);
    void setShowRoomsOwnerVersionGui(showRoomsOwnerVersion *gui);
    void setShowAllReservations(showAllReservations *gui);
    void setEditOwnerData(editOwnerData *gui);
    ~ownerGui();

private slots:
    void on_signOut_clicked();

    void on_addRoom_clicked();

    void on_showEditRoom_clicked();

    void on_addOwner_clicked();

    void on_showAllReservations_clicked();

    void on_deleteOwnerAccount_clicked();

    void on_editAccountData_clicked();

private:
    Ui::ownerGui *ui;
    ownerData oD_gui;
    session_manager sM_ownergui;
    login* log_in;
    addroom* add_room_gui;
    showRoomsOwnerVersion* show_rooms_owner_version;
    ownerSignIn* owner_sign_in;
    showAllReservations* show_all_reservations_gui;
    editOwnerData* showEditOwnerData_ownerGui;
    ownerPasswordData oPD_ownerGui;
};

#endif // OWNERGUI_H
