#include "login.h"
#include "ui_login.h"
#include "usergui.h"
#include "ownergui.h"
#include <QMessageBox>
#include "sign_in.h"

login::login(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::login), user_gui(nullptr), owner_gui(nullptr), signInGui(nullptr)
{
    ui->setupUi(this);
    setWindowFlag(Qt::WindowCloseButtonHint, false);
    setWindowFlag(Qt::WindowMaximizeButtonHint, false);

}

void login::setUserGui(userGui *gui)
{
    user_gui = gui;
}

void login::setOwnerGui(ownerGui *gui)
{
    owner_gui = gui;
}

void login::setSignInGui(sign_in *gui){
    signInGui = gui;
}

login::~login()
{
    if(ui!= nullptr){delete ui;}
    if(user_gui!=nullptr){delete user_gui; user_gui = nullptr;}
    if(owner_gui!=nullptr){delete owner_gui; owner_gui = nullptr;}
    if(signInGui!=nullptr){delete signInGui; signInGui = nullptr;}

}
bool login::checkEmail(){
    bool status = false;
    if(ui->set_email->text().isEmpty()){
        ui->error_on_email->setText("Set your email");
    }
    else{
        ui->error_on_email->setText("");
        status=true;
    }
    return status;
}

bool login::checkPassword()
{
    bool status = false;
    if(ui->set_password->text().isEmpty()){
        ui->error_on_password->setText("Set your email");
    }
    else{
        ui->error_on_password->setText("");
        status=true;
    }
    return status;
}

bool login::isRatioCheched(){
    bool status = false;
    if(ui->user_radio->isChecked() || ui->admin_ratio->isChecked()){
        ui->error_on_ratio->setText("");
        status=true;
    }
    else{
        ui->error_on_ratio->setText("Set your role");

    }
    return status;
}

void login::on_login_to_account_clicked()
{
    QString email = ui->set_email->text();
    QString password = ui->set_password->text();

    checkEmail();
    checkPassword();
    isRatioCheched();
    if(checkEmail() && checkPassword() && isRatioCheched()){
        if(ui->user_radio->isChecked()){
            std::pair<bool,int> result = uD.searchForUserEmail(email);
            if(result.first && uPD.checkUserPassword(password,result.second)){
                sM.setIdOfCurrentlyLoggedUser(result.second);
                //if(user_gui!=nullptr){/*user_gui -> deleteLater();*/ user_gui = nullptr;}
                user_gui = new userGui;
                user_gui->setLogin(this);
                this->hide();
                user_gui->show();

            }
            else{
                QMessageBox::information(this, "Error","User not found");
            }
        }
        else if (ui->admin_ratio->isChecked()) {
            std::pair<bool,int> result = oD.searchForOwnerEmail(email);
            if(result.first && oPD.checkOwnerPassword(password,result.second)){
                //indexOfCurrentlyLoggedUser = oD.getEmail().indexOf(email);
                sM.setIdOfCurrentlyLoggedUser(result.second);
                //if(owner_gui!=nullptr){/*owner_gui -> deleteLater();*/ owner_gui = nullptr;}
                owner_gui = new ownerGui;
                owner_gui->setLogin(this);
                this->hide();
                owner_gui->show();
            }
            else{
                QMessageBox::information(this, "Error","User not found");
            }
        }
    }
}


void login::on_sign_in_clicked()
{
    /*sign_in *signIn = nullptr;
    if(signIn != nullptr){
        delete signIn;
    }
    this->hide();
    signIn = new sign_in;
    signIn -> show();*/
    //if(signInGui!=nullptr){/*signInGui -> deleteLater();*/ signInGui = nullptr;}
    signInGui = new sign_in;
    signInGui->setLoginGui(this);
    this->hide();
    signInGui->show();
    ui->set_email->setText("");
    ui->set_password->setText("");
}

void login::on_exit_clicked()
{
    //conn_to_db.closeConnectionToDb();
    this->close();
}

