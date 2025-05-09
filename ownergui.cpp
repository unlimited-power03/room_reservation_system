#include "ownergui.h"
#include "ui_ownergui.h"
#include "login.h"
#include "addroom.h"
#include "show_rooms_owner_version.h"
#include "owner_sign_in.h"
#include "show_all_reservations.h"
#include "edit_owner_data.h"

ownerGui::ownerGui(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ownerGui),
    log_in(nullptr), add_room_gui(nullptr),
    show_rooms_owner_version(nullptr),
    owner_sign_in(nullptr),
    show_all_reservations_gui(nullptr),
    showEditOwnerData_ownerGui(nullptr)
{
    ui->setupUi(this);
    setWindowFlag(Qt::WindowCloseButtonHint, false);
    setWindowFlag(Qt::WindowMaximizeButtonHint, false);
    QVector <ownerData> owner_name = oD_gui.getOwnerNameFromDb(sM_ownergui.getIdOfCurrentlyLoggedUser());
    ui->greeting->setText("Hello " + owner_name.at(0).getFirstName());

    if(sM_ownergui.getIdOfCurrentlyLoggedUser() == 1){
        ui->deleteOwnerAccount->hide();
    }
}

void ownerGui::setAddRoomGui(addroom *gui)
{
    add_room_gui = gui;
}

void ownerGui::setShowRoomsOwnerVersionGui(showRoomsOwnerVersion *gui){
    show_rooms_owner_version = gui;
}

void ownerGui::setOwnerSignInGui(ownerSignIn *gui){
    owner_sign_in = gui;
}

void ownerGui::setShowAllReservations(showAllReservations *gui){
    show_all_reservations_gui = gui;
}

void ownerGui::setEditOwnerData(editOwnerData *gui){
    showEditOwnerData_ownerGui = gui;
}

ownerGui::~ownerGui()
{
    delete ui;
    if(log_in != nullptr){delete log_in; log_in = nullptr;}
    if(add_room_gui!=nullptr){delete add_room_gui; add_room_gui = nullptr;}
    if(show_rooms_owner_version!=nullptr){delete show_rooms_owner_version; show_rooms_owner_version = nullptr;}
    if(owner_sign_in!=nullptr){delete owner_sign_in; owner_sign_in = nullptr;}
    if(show_all_reservations_gui!=nullptr){delete show_all_reservations_gui; show_all_reservations_gui = nullptr;}
    if(showEditOwnerData_ownerGui!=nullptr){delete showEditOwnerData_ownerGui; showEditOwnerData_ownerGui = nullptr;}
}

void ownerGui::setLogin(login *log_in)
{
    this->log_in = log_in;

}


void ownerGui::on_signOut_clicked()
{
    log_in = new login;
    log_in->setOwnerGui(this);
    this->close();
    log_in->show();
    sM_ownergui.setIdOfCurrentlyLoggedUser(-1);
}


void ownerGui::on_addRoom_clicked()
{
    add_room_gui = new addroom;
    add_room_gui->setOwnerGui(this);
    this->close();
    add_room_gui->show();
}


void ownerGui::on_showEditRoom_clicked()
{
    show_rooms_owner_version = new showRoomsOwnerVersion;
    show_rooms_owner_version->setOwnerGui(this);
    this->close();
    show_rooms_owner_version->show();
}


void ownerGui::on_addOwner_clicked()
{
    owner_sign_in = new ownerSignIn;
    owner_sign_in->setOwnerGui(this);
    this->close();
    owner_sign_in->show();
}


void ownerGui::on_showAllReservations_clicked()
{
    show_all_reservations_gui = new showAllReservations;
    show_all_reservations_gui->setOwnerGui(this);
    this->close();
    show_all_reservations_gui->show();
}

void ownerGui::on_deleteOwnerAccount_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this,"Delete account", "Are you sure you want to delete your account?", QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes){
        oD_gui.deleteOwner(sM_ownergui.getIdOfCurrentlyLoggedUser());
        oPD_ownerGui.deleteOwnerPassword(sM_ownergui.getIdOfCurrentlyLoggedUser());
        on_signOut_clicked();
    }
}


void ownerGui::on_editAccountData_clicked()
{
    showEditOwnerData_ownerGui = new editOwnerData;
    showEditOwnerData_ownerGui->setOwnerGui_editOwnerData(this);
    this->close();
    showEditOwnerData_ownerGui->show();
}

