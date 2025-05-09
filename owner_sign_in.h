#ifndef OWNER_SIGN_IN_H
#define OWNER_SIGN_IN_H

#include <QDialog>
#include "sign_in.h"
#include "ui_sign_in.h"
#include "ownerdata.h"
#include "owner_password_data.h"
namespace Ui {
class ownerSignIn;
}

class ownerGui;
class ownerSignIn : public sign_in
{
    Q_OBJECT

public:
    explicit ownerSignIn(QWidget *parent = nullptr);
    void setOwnerGui(ownerGui *gui);
    ~ownerSignIn();

private slots:
    void on_sign_to_db_clicked();

    void on_back_button_clicked();
private:
    sign_in *signIn;
    ownerData oD_signIn;
    ownerPasswordData oPD_signIn;
    ownerGui* owner_gui;
};

#endif // OWNER_SIGN_IN_H
