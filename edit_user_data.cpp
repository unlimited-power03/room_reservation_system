#include "edit_user_data.h"
#include "usergui.h"

editUserData::editUserData(QWidget *parent)
    : sign_in(parent)
    , userGui_editUserData(nullptr)
{
    ui->setupUi(this);

    disconnect(ui->sign_to_db, SIGNAL(clicked()), this, SLOT(on_sign_to_db_clicked()));
    connect(ui->sign_to_db, &QPushButton::clicked, this, &editUserData::on_edit_clicked);

    disconnect(ui->back_button, SIGNAL(clicked()), this, SLOT(on_back_button_clicked()));
    connect(ui->back_button, &QPushButton::clicked, this, &editUserData::on_back_clicked);

    QVector <userdata> user_name = uD_editUserData.getUserNameFromDb(sM_editUSerData.getIdOfCurrentlyLoggedUser());

    ui->first_name->setText(user_name.at(0).getFirstName());
    ui->surname->setText(user_name.at(0).getSurname());
    ui->email->setText(user_name.at(0).getEmail());
    ui->telephone_number->setText(user_name.at(0).getTelephoneNumber());


    ui->first_name->setDisabled(true);
    ui->surname->setDisabled(true);

    ui->sign_to_db->setText("Edit data");
}

void editUserData::setUserGui_editUserData(userGui *gui){
    userGui_editUserData = gui;
}

editUserData::~editUserData()
{
    delete ui;
    if(userGui_editUserData != nullptr){delete userGui_editUserData; userGui_editUserData = nullptr;}
}

void editUserData::on_back_clicked(){
    userGui_editUserData = new userGui;
    userGui_editUserData->setEditUserData(this);
    this->close();
    userGui_editUserData->show();

}

void editUserData::on_edit_clicked(){

    QVector <userdata> user_data_compare = uD_editUserData.getUserNameFromDb(sM_editUSerData.getIdOfCurrentlyLoggedUser());

    QString old_email = user_data_compare.at(0).getEmail();
    QString old_telephone_number = user_data_compare.at(0).getTelephoneNumber();

    QString new_email = ui->email->text();
    QString new_password = ui->password->text();
    QString new_telephone = ui->telephone_number->text();

    validateEmail(new_email);
    if(!(ui->password->text().isEmpty())){
        validatePassword(new_password);
    }
    validateTelephoneNumber(new_telephone);

    if(new_email != old_email){
        if(validateEmail(new_email)){
            if(pD_signIn.doesEmailExists(new_email)){
                QMessageBox::information(this, "Error","E-mail address occurs in database. Please change it");
                return;
            }
        }
    }
    if(new_telephone != old_telephone_number){
        if(validateTelephoneNumber(new_telephone)){
            if(pD_signIn.doesTelephoneNumberExists(new_telephone)){
                QMessageBox::information(this, "Error","Telephone number occurs in database. Please change it");
                return;
            }
        }
    }
    uD_editUserData.editUserData(sM_editUSerData.getIdOfCurrentlyLoggedUser(), new_email, new_telephone);
    if(!(ui->password->text().isEmpty())){
        if(validatePassword(new_password)){
            uPD_editUserData.editUserPassword(new_password, sM_editUSerData.getIdOfCurrentlyLoggedUser());
        }
        else{
            return;
        }
    }
    QMessageBox::information(this, "Success","Your data have been edited");
    on_back_clicked();
}
