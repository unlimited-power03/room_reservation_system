#include "usergui.h"
#include "login.h"
#include "ui_usergui.h"
#include "show_rooms_user_version.h"
#include "show_user_reservations.h"
#include "edit_user_data.h"
#include <QDebug>

userGui::userGui(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::userGui)
    , showRoomsUserVersionGui(nullptr)
    , showUserReservationsGui(nullptr)
    , showEditUserData_usergui(nullptr)
    , log_in(nullptr)
{
    ui->setupUi(this);
    setWindowFlag(Qt::WindowCloseButtonHint, false);
    setWindowFlag(Qt::WindowMaximizeButtonHint, false);
    QVector <userdata> user_name = uD_gui.getUserNameFromDb(sM_gui.getIdOfCurrentlyLoggedUser());
    ui->greeting->setText("Hello " + user_name.at(0).getFirstName());
}

void userGui::setLogin(login *log_in)
{
    this->log_in = log_in;

}

void userGui::setShowRoomsUserVersion(showRoomsUserVersion *gui){
    showRoomsUserVersionGui = gui;
}

void userGui::setShowUserReservations(showUserReservations *gui){
    showUserReservationsGui = gui;
}

void userGui::setEditUserData(editUserData *gui){
    showEditUserData_usergui = gui;
}
userGui::~userGui()
{
    delete ui;
    if(showRoomsUserVersionGui!=nullptr){delete showRoomsUserVersionGui;showRoomsUserVersionGui= nullptr;}
    if(showUserReservationsGui!=nullptr){delete showUserReservationsGui;showUserReservationsGui= nullptr;}
    if(showEditUserData_usergui!=nullptr){delete showEditUserData_usergui; showEditUserData_usergui = nullptr;}
    if(log_in!=nullptr){delete log_in;log_in= nullptr;}
}

void userGui::on_signOut_clicked()
{

    //if(log_in != nullptr){/*log_in -> deleteLater();*/ log_in = nullptr;}
    log_in = new login;
    log_in->setUserGui(this);
    this->close();
    log_in->show();
    //log_in->setIndexOfCurrentlyLoggedUser(-1);
    sM_gui.setIdOfCurrentlyLoggedUser(-1);
}


void userGui::on_showroomsAndMakeReservation_clicked()
{
    //if(showRoomsUserVersionGui!=nullptr){/*showRoomsUserVersionGui -> deleteLater(); */showRoomsUserVersionGui= nullptr;}
    showRoomsUserVersionGui = new showRoomsUserVersion;
    showRoomsUserVersionGui->setUserGui(this);
    this->close();
    showRoomsUserVersionGui->show();
}


void userGui::on_reservationHistory_clicked()
{
   // if(showUserReservationsGui!=nullptr){/*showUserReservationsGui -> deleteLater();*/ showUserReservationsGui= nullptr;}
    showUserReservationsGui = new showUserReservations;
    showUserReservationsGui->setUserGui(this);
    this->close();
    showUserReservationsGui->show();
}


void userGui::on_deleteAccount_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this,"Delete account", "Are you sure you want to delete your account?", QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes){
        int messageID = reservation_userGui.checkActualReservations(sM_gui.getIdOfCurrentlyLoggedUser());
        if(messageID == 1){
            QMessageBox::information(this,"Warnig", "Wait for the current reservation to end");
        }
        else if(messageID == 2){
            QMessageBox::information(this,"Warnig", "Cancel pending reservations");
        }
        else{
            uD_gui.deleteUser(sM_gui.getIdOfCurrentlyLoggedUser());
            userpasswordData_usergui.deleteUserPassword(sM_gui.getIdOfCurrentlyLoggedUser());
            on_signOut_clicked();
        }
    }
}


void userGui::on_editAccount_clicked()
{
    showEditUserData_usergui = new editUserData;
    showEditUserData_usergui->setUserGui_editUserData(this);
    this->close();
    showEditUserData_usergui->show();
}

