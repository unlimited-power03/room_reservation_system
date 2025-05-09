#ifndef ADDROOM_H
#define ADDROOM_H

#include <QDialog>
#include "sign_in.h"
#include "ui_addroom.h"
#include "room.h"
namespace Ui {
class addroom;
}
class ownerGui;
class addroom : public QDialog
{
    Q_OBJECT

public:
    explicit addroom(QWidget *parent = nullptr);
    void setOwnerGui(ownerGui *gui);
    bool validateRoomName(QString name);
    bool checkBedNumberList(QListWidgetItem *itemCheck);
    bool validateRoomDescription(QString description);
    ~addroom();

private slots:
    void on_addRoom_clicked();
    void on_back_clicked();

private:
    Ui::addroom *ui;
    sign_in signIn_addroom;
    ownerGui* owner_gui_addroom;
    room roomObj;
};

#endif // ADDROOM_H
