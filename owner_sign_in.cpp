#include "owner_sign_in.h"
#include "ownergui.h"
//#include "ui_owner_sign_in.h"


ownerSignIn::ownerSignIn(QWidget *parent)
    : /*QDialog(parent)
    , ui(new Ui::ownerSignIn)*/
    sign_in(parent), owner_gui(nullptr)
{
    //ui->setupUi(this);
    disconnect(ui->sign_to_db, SIGNAL(clicked()), this, SLOT(on_sign_to_db_clicked()));
    connect(ui->sign_to_db, &QPushButton::clicked, this, &ownerSignIn::on_sign_to_db_clicked);

    disconnect(ui->back_button, SIGNAL(clicked()), this, SLOT(on_back_button_clicked()));
    connect(ui->back_button, &QPushButton::clicked, this, &ownerSignIn::on_back_button_clicked);

}

void ownerSignIn::setOwnerGui(ownerGui *gui){
    owner_gui = gui;
}

void ownerSignIn::on_sign_to_db_clicked(){
    QString ownerFirstName = ui->first_name->text();
    QString ownerSurname = ui->surname->text();
    QString ownerEmail = ui->email->text();
    QString ownerPassword = ui->password->text();
    QString ownerTelephone = ui->telephone_number->text();

    validateFirstName(ownerFirstName); validateSurname(ownerSurname); validateEmail(ownerEmail); validatePassword(ownerPassword); validateTelephoneNumber(ownerTelephone);
    if(validateFirstName(ownerFirstName) && validateSurname(ownerSurname) && validateEmail(ownerEmail) && validatePassword(ownerPassword) && validateTelephoneNumber(ownerTelephone)){
        if(pD_signIn.doesEmailExists(ownerEmail)){
            QMessageBox::information(this, "Error","E-mail address occurs in database. Please change it");
        }
        if(pD_signIn.doesTelephoneNumberExists(ownerTelephone)){
            QMessageBox::information(this, "Error","Telephone number occurs in database. Please change it");
        }
        else{
            oD_signIn.insertPersonToDb(setFirstLetterCapitalize(ownerFirstName),setFirstLetterCapitalize(ownerSurname),ownerEmail,ownerTelephone);
            oPD_signIn.hashPassword(ownerPassword);
            QMessageBox::information(this, "Success","You have been added to databse");
            ui->first_name->setText("");
            ui->surname->setText("");
            ui->email->setText("");
            ui->password->setText("");
            ui->telephone_number->setText("");
        }
    }
}

void ownerSignIn::on_back_button_clicked(){
   // if(owner_gui != nullptr){/*owner_gui -> deleteLater();*/ owner_gui = nullptr;}
    owner_gui = new ownerGui;
    owner_gui->setOwnerSignInGui(this);
    this->close();
    owner_gui->show();
}
ownerSignIn::~ownerSignIn()
{
    if(owner_gui != nullptr){delete owner_gui; owner_gui = nullptr;}
}
