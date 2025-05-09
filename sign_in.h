#ifndef SIGN_IN_H
#define SIGN_IN_H

#include <QDialog>
#include "user_password_data.h"
#include "ownerdata.h"
#include<QRegularExpression>
#include<QRegularExpressionMatch>
#include<QMessageBox>
#include <QDebug>
namespace Ui {
class sign_in;
}

class login;
class sign_in : public QDialog
{
    Q_OBJECT

public:
    explicit sign_in(QWidget *parent = nullptr);
    void setLoginGui(login *gui);
    bool validateFirstName(QString name);
    bool validateSurname(QString surname);
    bool validateEmail(QString email);
    bool validatePassword(QString password);
    bool validateTelephoneNumber(QString telephoneNumber);
    QString setFirstLetterCapitalize(QString text);

    ~sign_in();

protected slots:
    void on_sign_to_db_clicked();

    void on_back_button_clicked();

protected:
    Ui::sign_in *ui;
    personData pD_signIn;
private:
    userdata uD_signIn;
    userPasswordData uPD_signIn;
    login *loginGui;
};

#endif // SIGN_IN_H
