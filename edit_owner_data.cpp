#include "edit_owner_data.h"
#include "ownergui.h"

editOwnerData::editOwnerData(QWidget *parent)
    : sign_in(parent)
    , ownerGui_editOwnerData(nullptr)
{
    ui->setupUi(this);

    disconnect(ui->sign_to_db, SIGNAL(clicked()), this, SLOT(on_sign_to_db_clicked()));
    connect(ui->sign_to_db, &QPushButton::clicked, this, &editOwnerData::on_edit_clicked);

    disconnect(ui->back_button, SIGNAL(clicked()), this, SLOT(on_back_button_clicked()));
    connect(ui->back_button, &QPushButton::clicked, this, &editOwnerData::on_back_clicked);

    QVector <ownerData> owner_name = oD_editOwnerData.getOwnerNameFromDb(sM_editOwnerData.getIdOfCurrentlyLoggedUser());

    ui->first_name->setText(owner_name.at(0).getFirstName());
    ui->surname->setText(owner_name.at(0).getSurname());
    ui->email->setText(owner_name.at(0).getEmail());
    ui->telephone_number->setText(owner_name.at(0).getTelephoneNumber());


    ui->first_name->setDisabled(true);
    ui->surname->setDisabled(true);

    ui->sign_to_db->setText("Edit data");
}

void editOwnerData::setOwnerGui_editOwnerData(ownerGui *gui){
    ownerGui_editOwnerData = gui;
}

editOwnerData::~editOwnerData()
{
    delete ui;
    if(ownerGui_editOwnerData != nullptr){delete ownerGui_editOwnerData; ownerGui_editOwnerData = nullptr;}
}

void editOwnerData::on_back_clicked(){
    ownerGui_editOwnerData = new ownerGui;
    ownerGui_editOwnerData -> setEditOwnerData(this);
    this->close();
    ownerGui_editOwnerData->show();
}

void editOwnerData::on_edit_clicked(){
    QVector <ownerData> owner_data_compare = oD_editOwnerData.getOwnerNameFromDb(sM_editOwnerData.getIdOfCurrentlyLoggedUser());

    QString old_email = owner_data_compare.at(0).getEmail();
    QString old_telephone_number = owner_data_compare.at(0).getTelephoneNumber();

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
    oD_editOwnerData.editOwnerData(sM_editOwnerData.getIdOfCurrentlyLoggedUser(), new_email, new_telephone);
    if(!(ui->password->text().isEmpty())){
        if(validatePassword(new_password)){
            oPD_editOwnerData.editOwnerPassword(new_password, sM_editOwnerData.getIdOfCurrentlyLoggedUser());
        }
        else{
            return;
        }
    }
    QMessageBox::information(this, "Success","Your data have been edited");
    on_back_clicked();
}
