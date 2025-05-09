#include "sign_in.h"
#include "ui_sign_in.h"
#include "login.h"
sign_in::sign_in(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::sign_in), loginGui(nullptr)
{
    ui->setupUi(this);
    setWindowFlag(Qt::WindowCloseButtonHint, false);
    setWindowFlag(Qt::WindowMaximizeButtonHint, false);
}

sign_in::~sign_in()
{
    delete ui;
    if(loginGui != nullptr){delete loginGui; loginGui = nullptr;}
}

void sign_in::setLoginGui(login *gui){
    loginGui = gui;
}
void sign_in::on_back_button_clicked()
{
    loginGui = new login;
    loginGui->setSignInGui(this);
    this->close();
    loginGui->show();
}

bool sign_in::validateFirstName(QString name)
{
    bool firstNameValidation=false;
    static QRegularExpression regexName("^[a-zA-ZàáâäãåąčćęèéêëėįìíîïłńòóôöõøùúûüųūÿýżźñçčšžæÀÁÂÄÃÅĄĆČĖĘÈÉÊËÌÍÎÏĮŁŃÒÓÔÖÕØÙÚÛÜŲŪŸÝŻŹÑßÇŒÆČŠŽ∂ð ,.'-]+$");
    if(name.isEmpty()){
        ui->error_on_first_name->setText("Set your name");
    }
    else if(!(regexName.match(name).hasMatch())){
        ui->error_on_first_name->setText("Improper name");
    }
    else{
        ui->error_on_first_name->setText("");
        firstNameValidation=true;
    }
    return firstNameValidation;
}

bool sign_in::validateSurname(QString surname)
{
    bool surnameValidation=false;
    static QRegularExpression regexSurname("^[a-zA-ZàáâäãåąčćęèéêëėįìíîïłńòóôöõøùúûüųūÿýżźñçčšžæÀÁÂÄÃÅĄĆČĖĘÈÉÊËÌÍÎÏĮŁŃÒÓÔÖÕØÙÚÛÜŲŪŸÝŻŹÑßÇŒÆČŠŽ∂ð ,.'-]+$");
    if(surname.isEmpty()){
        ui->error_on_surname->setText("Set your surname");
    }
    else if(!(regexSurname.match(surname).hasMatch())){
        ui->error_on_surname->setText("Improper surname");
    }
    else{
        ui->error_on_surname->setText("");
        surnameValidation=true;
    }
    return surnameValidation;
}

bool sign_in::validateEmail(QString email)
{
    bool emailValidation=false;
    static QRegularExpression regexEmail("^[a-zA-Z0-9._%+-ąćęłńóśźżĄĆĘŁŃÓŚŹŻ]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,6}$");
    if(email.isEmpty()){
        ui->error_on_email->setText("Set your email");
    }
    else if(!(regexEmail.match(email).hasMatch())){
        ui->error_on_email->setText("Improper email");
    }
    else{
        ui->error_on_email->setText("");
        emailValidation=true;
    }
    return emailValidation;
}

bool sign_in::validatePassword(QString password){
    bool passwordValidation=false;
    static QRegularExpression regexPassword("^(?=(.*[A-Z]){3})(?=(.*[\\W_]){3})(?=(.*[0-9]){1})[A-Za-z\\W_0-9]{8,}$");

    if(password.isEmpty()){
        ui->error_on_password->setText("Set your password");
    }
    else if(!(regexPassword.match(password).hasMatch())){
        ui->error_on_password->setText("Improper password");
    }
    else{
        ui->error_on_password->setText("");
        passwordValidation=true;
    }
    return passwordValidation;
}

bool sign_in::validateTelephoneNumber(QString telephoneNumber){
    bool telephoneValidation=false;
    static QRegularExpression regexPassword("^[1-9][0-9]{8}$");

    if(telephoneNumber.isEmpty()){
        ui->error_on_phone_number->setText("Set your telephone number");
    }
    else if(!(regexPassword.match(telephoneNumber).hasMatch())){
        ui->error_on_phone_number->setText("Improper telephone number");
    }
    else{
        ui->error_on_phone_number->setText("");
        telephoneValidation=true;
    }
    return telephoneValidation;
}

QString sign_in::setFirstLetterCapitalize(QString text){
    text = text.toLower();
    text[0] = text[0].toUpper();
    return text;
}

void sign_in::on_sign_to_db_clicked()
{
    QString firstName = ui->first_name->text();
    QString surname = ui->surname->text();
    QString email = ui->email->text();
    QString password = ui->password->text();
    QString telephone = ui->telephone_number->text();

    validateFirstName(firstName); validateSurname(surname); validateEmail(email); validatePassword(password); validateTelephoneNumber(telephone);
    if(validateFirstName(firstName) && validateSurname(surname) && validateEmail(email) && validatePassword(password) && validateTelephoneNumber(telephone)){
        if(pD_signIn.doesEmailExists(email)){
            QMessageBox::information(this, "Error","E-mail address occurs in database. Please change it");
            return;
        }
        else if(pD_signIn.doesTelephoneNumberExists(telephone)){
            QMessageBox::information(this, "Error","Telephone number occurs in database. Please change it");
            return;
        }
        else{
            uD_signIn.insertPersonToDb(setFirstLetterCapitalize(firstName),setFirstLetterCapitalize(surname),email,telephone);
            uPD_signIn.hashPassword(password);
            QMessageBox::information(this, "Success","You have been added to databse");
            ui->first_name->setText("");
            ui->surname->setText("");
            ui->email->setText("");
            ui->password->setText("");
            ui->telephone_number->setText("");
        }
    }
}


