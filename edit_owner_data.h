#ifndef EDIT_OWNER_DATA_H
#define EDIT_OWNER_DATA_H

#include <QDialog>
#include "sign_in.h"
#include "ui_sign_in.h"
#include "ownerdata.h"
#include "owner_password_data.h"
#include "session_manager.h"

namespace Ui {
class editOwnerData;
}

class ownerGui;

class editOwnerData : public sign_in
{
    Q_OBJECT

public:
    explicit editOwnerData(QWidget *parent = nullptr);
    void setOwnerGui_editOwnerData(ownerGui* gui);
    ~editOwnerData();

private slots:
    void on_edit_clicked();
    void on_back_clicked();

private:
    ownerGui* ownerGui_editOwnerData;
    ownerData oD_editOwnerData;
    ownerPasswordData oPD_editOwnerData;
    session_manager sM_editOwnerData;
};

#endif // EDIT_OWNER_DATA_H
