#include "addroom.h"
#include "ui_addroom.h"
#include "ownergui.h"
#include <QDebug>
addroom::addroom(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::addroom), owner_gui_addroom(nullptr)
{
    ui->setupUi(this);
    setWindowFlag(Qt::WindowCloseButtonHint, false);

}

void addroom::setOwnerGui(ownerGui *gui){
    owner_gui_addroom = gui;
}

bool addroom::validateRoomName(QString name)
{
    bool roomNameValidation=false;
    static QRegularExpression regexName("^[a-zA-ZàáâäãåąčćęèéêëėįìíîïłńòóôöõøùúûüųūÿýżźñçčšžæÀÁÂÄÃÅĄĆČĖĘÈÉÊËÌÍÎÏĮŁŃÒÓÔÖÕØÙÚÛÜŲŪŸÝŻŹÑßÇŒÆČŠŽ∂ð ,.'-]+$");
    if(name.isEmpty()){
        ui->errorOnRoomName->setText("Set room name");
    }
    else if(!(regexName.match(name).hasMatch())){
        ui->errorOnRoomName->setText("Improper name");
    }
    else{
        ui->errorOnRoomName->setText(" ");
        roomNameValidation=true;
    }
    return roomNameValidation;
}

bool addroom::checkBedNumberList(QListWidgetItem *itemCheck)
{
    bool checkList=false;
    //QListWidgetItem *itemCheck = ui->listWidget->currentItem();
    if(!itemCheck){
        ui->errorOnRoomCapacity->setText("Choose room capacity");
    }
    else{
        ui->errorOnRoomCapacity->setText("");
        checkList = true;
    }
    return checkList;
}

bool addroom::validateRoomDescription(QString description)
{
    bool roomDescriptionValidation=false;
    static QRegularExpression regexName("^[a-zA-ZàáâäãåąčćęèéêëėįìíîïłńòóôöõøùúûüųūÿýżźñçčšžæÀÁÂÄÃÅĄĆČĖĘÈÉÊËÌÍÎÏĮŁŃÒÓÔÖÕØÙÚÛÜŲŪŸÝŻŹÑßÇŒÆČŠŽ∂ð0-9 ,.'-]+$");
    if(description.isEmpty()){
        ui->errorOnRoomDescription->setText("Set description");
    }
    else if(!(regexName.match(description).hasMatch())){
        ui->errorOnRoomDescription->setText("Improper description");
    }
    else{
        ui->errorOnRoomDescription->setText("");
        roomDescriptionValidation=true;
    }
    return roomDescriptionValidation;
}



addroom::~addroom()
{
    delete ui;
    if(owner_gui_addroom != nullptr){delete owner_gui_addroom; owner_gui_addroom = nullptr;}
}

void addroom::on_addRoom_clicked()
{
    QString name = ui->roomName->text();
    QListWidgetItem *item = ui->listWidget->currentItem();

    QString description = ui->roomDescription->toPlainText();

    validateRoomName(name);
    checkBedNumberList(item);
    validateRoomDescription(description);

    if(roomObj.checkIfNameOccursInDb(name, -1)){
        QMessageBox::information(this, "Error","Name occurs in database. Please change it");
    }
    else{
        if(validateRoomName(name) && checkBedNumberList(item) && validateRoomDescription(description)){
            int choice = item->text().toInt();
            roomObj.insertRoomToDb(signIn_addroom.setFirstLetterCapitalize(name),choice,signIn_addroom.setFirstLetterCapitalize(description));
            QMessageBox::information(this, "Success","Room added to database");
            ui->roomName->setText("");
            ui->roomDescription->setText("");
        }
    }
}


void addroom::on_back_clicked()
{
    //if(owner_gui != nullptr){/*owner_gui -> deleteLater();*/ owner_gui = nullptr;}
    owner_gui_addroom = new ownerGui;
    owner_gui_addroom->setAddRoomGui(this);
    this->close();
    owner_gui_addroom->show();
}

