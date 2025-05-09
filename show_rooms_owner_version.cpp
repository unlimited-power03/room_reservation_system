#include "show_rooms_owner_version.h"
#include "ui_show_rooms_owner_version.h"
#include "ownergui.h"
#include "edit_room.h"
#include <QDebug>
showRoomsOwnerVersion::showRoomsOwnerVersion(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::showRoomsOwnerVersion), owner_gui_showRoomsOwnerVersion(nullptr), edit_room_gui_showRoomsOwnerVersion(nullptr)
{

    ui->setupUi(this);
    setWindowFlag(Qt::WindowCloseButtonHint, false);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->name_filter->addItem("");
    for(QString &room_name : roomObj_showRoomsOwnerVersion.getFilteredRoomName()){
        ui->name_filter->addItem(room_name);
    }

    ui->number_of_beds_filter->addItem("");
    for(QString &number_of_beds : roomObj_showRoomsOwnerVersion.getFilteredRoomNumberOfBeds()){
        ui->number_of_beds_filter->addItem(number_of_beds);
    }

    ui->status_filter->addItem("");
    for(QString &status : roomObj_showRoomsOwnerVersion.getFilteredRoomStatus()){
        ui->status_filter->addItem(status);
    }

    loadRooms();

}
void showRoomsOwnerVersion::loadRooms(){

    QVector <room> allRooms = roomObj_showRoomsOwnerVersion.getAllRoomsFromDb();
    int storedRooms = allRooms.size();
    ui->tableWidget->setRowCount(storedRooms);


    for(int i=0; i<storedRooms; i++){
        room roomData = allRooms[i];
        QTableWidgetItem *room_id = new QTableWidgetItem();
        room_id -> setData(Qt::UserRole, roomData.getRoomID());
        QTableWidgetItem *room_name = new QTableWidgetItem(roomData.getRoomName());
        QTableWidgetItem *room_capacity = new QTableWidgetItem(QString::number(roomData.getRoomCapacity()));
        QTableWidgetItem *room_description = new QTableWidgetItem(roomData.getRoomDescription());
        QTableWidgetItem *room_status = new QTableWidgetItem(roomData.getRoomStatus());

        room_description->setToolTip(roomData.getRoomDescription());

        ui->tableWidget->setItem(i, 0, room_id);
        ui->tableWidget->setColumnHidden(0, true);
        ui->tableWidget->setItem(i, 1, room_name);
        ui->tableWidget->setItem(i, 2, room_capacity);
        ui->tableWidget->setItem(i, 3, room_description);
        ui->tableWidget->setItem(i, 4, room_status);
        QPushButton *editRoomButton = new QPushButton("Edit",this);
        connect(editRoomButton, &QPushButton::clicked, this, [=](){onClickedEditButton(i);});
        ui->tableWidget->setCellWidget(i,5, editRoomButton);
        QPushButton *deleteRoomButton = new QPushButton("Delete",this);
        connect(deleteRoomButton, &QPushButton::clicked, this, [=](){onClickedDeleteButton(i);});
        ui->tableWidget->setCellWidget(i,6, deleteRoomButton);
    }
}

void showRoomsOwnerVersion::setEditRoom(editRoom *gui){
    edit_room_gui_showRoomsOwnerVersion = gui;
}


void showRoomsOwnerVersion::setOwnerGui(ownerGui *gui){
    owner_gui_showRoomsOwnerVersion = gui;
}

int showRoomsOwnerVersion::getSelectedRoomId(){
    return selectedRoomId;
}



void showRoomsOwnerVersion::on_back_clicked()
{
    owner_gui_showRoomsOwnerVersion = new ownerGui;
    owner_gui_showRoomsOwnerVersion->setShowRoomsOwnerVersionGui(this);
    this->close();
    owner_gui_showRoomsOwnerVersion->show();
}

void showRoomsOwnerVersion::onClickedEditButton(int row_number){
    selectedRoomId = ui->tableWidget->item(row_number, 0)->data(Qt::UserRole).toInt();
    edit_room_gui_showRoomsOwnerVersion = new editRoom;
    edit_room_gui_showRoomsOwnerVersion->setShowRoomsOwnerVersionGui(this);
    this->hide();
    edit_room_gui_showRoomsOwnerVersion->show();
}

void showRoomsOwnerVersion::onClickedDeleteButton(int row_number){
    QMessageBox::StandardButton reply = QMessageBox::question(this,"Delete room", "Are you sure you want to delete this room?", QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes){
        selectedRoomId = ui->tableWidget->item(row_number, 0)->data(Qt::UserRole).toInt();
        roomObj_showRoomsOwnerVersion.deleteRoomFromDb(selectedRoomId);
        loadRooms();
    }
}

showRoomsOwnerVersion::~showRoomsOwnerVersion()
{
    delete ui;
    if(owner_gui_showRoomsOwnerVersion != nullptr){delete owner_gui_showRoomsOwnerVersion; owner_gui_showRoomsOwnerVersion=nullptr;}
    if(edit_room_gui_showRoomsOwnerVersion != nullptr){delete edit_room_gui_showRoomsOwnerVersion; edit_room_gui_showRoomsOwnerVersion=nullptr;}
}

void showRoomsOwnerVersion::on_submit_button_clicked()
{
    QString room_name = ui->name_filter->currentText();
    QString number_of_beds = ui->number_of_beds_filter->currentText();
    QString status = ui->status_filter->currentText();

    QVector <room> filteredRooms = roomObj_showRoomsOwnerVersion.getFilteredRoomsFromDb(room_name, number_of_beds, status);
    int storedRooms = filteredRooms.size();
    ui->tableWidget->setRowCount(storedRooms);

    for(int i=0; i<storedRooms; i++){
        room roomData = filteredRooms[i];
        QTableWidgetItem *room_id = new QTableWidgetItem();
        room_id -> setData(Qt::UserRole, roomData.getRoomID());
        QTableWidgetItem *room_name = new QTableWidgetItem(roomData.getRoomName());
        QTableWidgetItem *room_capacity = new QTableWidgetItem(QString::number(roomData.getRoomCapacity()));
        QTableWidgetItem *room_description = new QTableWidgetItem(roomData.getRoomDescription());
        QTableWidgetItem *room_status = new QTableWidgetItem(roomData.getRoomStatus());

        room_description->setToolTip(roomData.getRoomDescription());

        ui->tableWidget->setItem(i, 0, room_id);
        ui->tableWidget->setColumnHidden(0, true);
        ui->tableWidget->setItem(i, 1, room_name);
        ui->tableWidget->setItem(i, 2, room_capacity);
        ui->tableWidget->setItem(i, 3, room_description);
        ui->tableWidget->setItem(i, 4, room_status);
        QPushButton *editRoomButton = new QPushButton("Edit",this);
        connect(editRoomButton, &QPushButton::clicked, this, [=](){onClickedEditButton(i);});
        ui->tableWidget->setCellWidget(i,5, editRoomButton);
        QPushButton *deleteRoomButton = new QPushButton("Delete",this);
        connect(deleteRoomButton, &QPushButton::clicked, this, [=](){onClickedDeleteButton(i);});
        ui->tableWidget->setCellWidget(i,6, deleteRoomButton);
    }
}


void showRoomsOwnerVersion::on_reset_button_clicked()
{
    ui->name_filter->setCurrentIndex(0);
    ui->number_of_beds_filter->setCurrentIndex(0);
    ui->status_filter->setCurrentIndex(0);
    loadRooms();
}

