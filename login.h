#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "userdata.h"
#include "ownerdata.h"
#include "user_password_data.h"
#include "owner_password_data.h"
#include "session_manager.h"
#include "connection_do_db.h"

namespace Ui {
class login;
}

class userGui;
class ownerGui;
class sign_in;

class login : public QMainWindow
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    bool checkEmail();
    bool checkPassword();
    bool isRatioCheched();
    void setUserGui(userGui* gui);
    void setOwnerGui(ownerGui* gui);
    void setSignInGui(sign_in* gui);
    ~login();

private slots:
    void on_login_to_account_clicked();

    void on_sign_in_clicked();

    void on_exit_clicked();
private:
    Ui::login *ui;
    userdata uD;
    ownerData oD;
    userPasswordData uPD;
    ownerPasswordData oPD;
    session_manager sM;
    userGui* user_gui;
    ownerGui* owner_gui;
    sign_in *signInGui;
    connection_do_db conn_to_db;

};

#endif // LOGIN_H
