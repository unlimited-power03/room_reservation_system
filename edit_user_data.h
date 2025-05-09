#ifndef EDIT_USER_DATA_H
#define EDIT_USER_DATA_H

#include <QDialog>
#include "sign_in.h"
#include "ui_sign_in.h"
#include "userdata.h"
#include "user_password_data.h"
#include "session_manager.h"
namespace Ui {
class editUserData;
}

class userGui;

class editUserData : public sign_in
{
    Q_OBJECT

public:
    explicit editUserData(QWidget *parent = nullptr);
    void setUserGui_editUserData(userGui* gui);
    ~editUserData();

private slots:
    void on_edit_clicked();
    void on_back_clicked();

private:
    userGui *userGui_editUserData;
    userdata uD_editUserData;
    userPasswordData uPD_editUserData;
    session_manager sM_editUSerData;
};

#endif // EDIT_USER_DATA_H
