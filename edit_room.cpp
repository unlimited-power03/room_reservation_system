#include "edit_room.h"
#include "ui_edit_room.h"
#include "show_rooms_owner_version.h"

#include <QDebug>
editRoom::editRoom(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::editRoom), show_rooms_owner_version_gui_editRoom(nullptr)
{
    ui->setupUi(this);
    setWindowFlag(Qt::WindowCloseButtonHint, false);

}

void editRoom::setShowRoomsOwnerVersionGui(showRoomsOwnerVersion *gui){
    //repaint();
    show_rooms_owner_version_gui_editRoom = gui;
    room singleRoom = roomObj_editRoom.getRoomFromTb(show_rooms_owner_version_gui_editRoom->getSelectedRoomId());
    qDebug() << show_rooms_owner_version_gui_editRoom->getSelectedRoomId();
    ui->roomNewName->setText(singleRoom.getRoomName());

    int selectedRoomCapacity = singleRoom.getRoomCapacity();
    for(int i=0; i<ui->listWidget->count(); i++){
        QListWidgetItem *item = ui->listWidget->item(i);
        if(item->text() == QString::number(selectedRoomCapacity)){
            ui->listWidget->setCurrentItem(item);
            break;
        }
    }

    ui->roomNewDescription->setText(singleRoom.getRoomDescription());

    QString selectedRoomStatus = singleRoom.getRoomStatus();
    for(int i=0; i<ui->statusList->count(); i++){
        QListWidgetItem *item = ui->statusList->item(i);
        if(item->text() == selectedRoomStatus){
            ui->statusList->setCurrentItem(item);
            break;
        }
    }
}

void editRoom::on_edit_room_clicked(){
    if(!reservationObj_editRoom.doesReservationExist(show_rooms_owner_version_gui_editRoom->getSelectedRoomId())){
        QString summary;
        QString new_name = ui->roomNewName->text();
        int new_capacity = ui->listWidget->currentItem()->text().toInt();
        QString new_description = ui->roomNewDescription->toPlainText();
        QString new_status = ui->statusList->currentItem()->text();

        addRoom_editRoom.validateRoomName(new_name);    //validate data - using addroom cause of same logic of implementation
        addRoom_editRoom.validateRoomDescription(new_description);

        room compareRoom = roomObj_editRoom.getRoomFromTb(show_rooms_owner_version_gui_editRoom->getSelectedRoomId());
        QString compared_name = compareRoom.getRoomName();
        int compared_capacity = compareRoom.getRoomCapacity();
        QString compared_description = compareRoom.getRoomDescription();
        QString compared_status = compareRoom.getRoomStatus();

        if(addRoom_editRoom.validateRoomName(new_name) && addRoom_editRoom.validateRoomDescription(new_description)){
            if(roomObj_editRoom.checkIfNameOccursInDb(new_name, show_rooms_owner_version_gui_editRoom->getSelectedRoomId())){
                QMessageBox::warning(this,"Error", "Name already exists");
            }
            else{
                //qDebug() <<show_rooms_owner_version_gui_editRoom->getSelectedRoomId();
                if(new_name != compared_name){
                    summary += "Room name: " + compared_name + " to " + new_name + "\n";
                }
                if(new_capacity != compared_capacity){
                    summary += "Room capacity: " + QString::number(compared_capacity) + " to " + QString::number(new_capacity) + "\n";
                }
                if(new_description != compared_description){
                    summary += "Room description: " + compared_description + " to " + new_description + "\n";
                }
                if(new_status != compared_status){
                    summary += "Room status: " + compared_status + " to " + new_status + "\n";
                }

                if(summary.isEmpty()){
                    QMessageBox::information(this,"No changes", "No changes were made to the room");
                    on_back_clicked();
                }
                else{
                    QMessageBox::StandardButton reply = QMessageBox::question(this,"New changes", summary, QMessageBox::Yes | QMessageBox::No);

                    if(reply == QMessageBox::Yes){
                        roomObj_editRoom.editRoomInDb(signIn_editRoom.setFirstLetterCapitalize(new_name),new_capacity,signIn_editRoom.setFirstLetterCapitalize(new_description),new_status,show_rooms_owner_version_gui_editRoom->getSelectedRoomId());
                        on_back_clicked();
                    }
                    if(reply == QMessageBox::No){
                        on_back_clicked();
                    }
                }
            }
        }
    }
    else{
        QMessageBox::warning(this,"Error","Reservation occurs, can't modify");
        on_back_clicked();
    }
}

editRoom::~editRoom()
{
    delete ui;
    if(show_rooms_owner_version_gui_editRoom != nullptr){delete show_rooms_owner_version_gui_editRoom; show_rooms_owner_version_gui_editRoom = nullptr;}
}

void editRoom::on_back_clicked()
{
    //if(show_rooms_owner_version_gui != nullptr){/*show_rooms_owner_version_gui -> deleteLater();*/ show_rooms_owner_version_gui = nullptr;}
    show_rooms_owner_version_gui_editRoom = new showRoomsOwnerVersion;
    show_rooms_owner_version_gui_editRoom->setEditRoom(this);
    this->close();
    show_rooms_owner_version_gui_editRoom->show();
}

