#include "show_rooms_user_version.h"
#include "ui_show_rooms_user_version.h"
#include "usergui.h"
#include "reservation_gui.h"
#include <QDebug>

showRoomsUserVersion::showRoomsUserVersion(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::showRoomsUserVersion), user_gui_showRoomsUserVersion(nullptr), reservation_gui_showRoomsUserVersion(nullptr)
{
    ui->setupUi(this);
    setWindowFlag(Qt::WindowCloseButtonHint, false);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->name_filter->addItem("");
    for(QString &room_name : roomObj_showRoomsUserVersion.getUserVersionFilteredRoomName()){
        ui->name_filter->addItem(room_name);
    }

    ui->number_of_beds_filter->addItem("");
    for(QString &number_of_beds : roomObj_showRoomsUserVersion.getUserVersionFilteredRoomNumberOfBeds()){
        ui->number_of_beds_filter->addItem(number_of_beds);
    }
    showTable();

}

void showRoomsUserVersion::showTable(){
    QVector<room> availableRooms = roomObj_showRoomsUserVersion.getAvailableRoomsFromDb();
    int storedRooms=availableRooms.size();
    ui->tableWidget->setRowCount(storedRooms);

    for(int i=0; i<storedRooms; i++){
        room roomData = availableRooms[i];
        QTableWidgetItem *room_id = new QTableWidgetItem();
        room_id -> setData(Qt::UserRole, roomData.getRoomID());
        QTableWidgetItem *room_name = new QTableWidgetItem(roomData.getRoomName());
        QTableWidgetItem *room_capacity = new QTableWidgetItem(QString::number(roomData.getRoomCapacity()));
        QTableWidgetItem *room_description = new QTableWidgetItem(roomData.getRoomDescription());

        room_description->setToolTip(roomData.getRoomDescription());

        ui->tableWidget->setItem(i, 0, room_id);
        ui->tableWidget->setColumnHidden(0, true);
        ui->tableWidget->setItem(i, 1, room_name);
        ui->tableWidget->setItem(i, 2, room_capacity);
        ui->tableWidget->setItem(i, 3, room_description);
        QPushButton *reserveRoomButton = new QPushButton("Reserve",this);
        connect(reserveRoomButton, &QPushButton::clicked, this, [this, i](){onClickedReserveButton(i);});
        ui->tableWidget->setCellWidget(i,4, reserveRoomButton);
    }
}

int showRoomsUserVersion::getSelectedRoomID(){
    return selectedRoomId;
}

void showRoomsUserVersion::setReservationGui(reservationGui *gui){
    reservation_gui_showRoomsUserVersion = gui;
}

void showRoomsUserVersion::setUserGui(userGui *gui){
    user_gui_showRoomsUserVersion = gui;
}

void showRoomsUserVersion::onClickedReserveButton(int row_number){
    selectedRoomId = ui->tableWidget->item(row_number, 0)->data(Qt::UserRole).toInt();

    reservation_gui_showRoomsUserVersion = new reservationGui;
    reservation_gui_showRoomsUserVersion->setShowRoomsUserVersionGui(this);
    this->close();
    reservation_gui_showRoomsUserVersion->show();
}


showRoomsUserVersion::~showRoomsUserVersion()
{
    delete ui;
    if(user_gui_showRoomsUserVersion != nullptr){delete user_gui_showRoomsUserVersion; user_gui_showRoomsUserVersion = nullptr;}
    if(reservation_gui_showRoomsUserVersion != nullptr){delete reservation_gui_showRoomsUserVersion; reservation_gui_showRoomsUserVersion=nullptr;}
}


void showRoomsUserVersion::on_back_clicked()
{
    //if(user_gui != nullptr){/*user_gui -> deleteLater(); */user_gui = nullptr;}
    user_gui_showRoomsUserVersion = new userGui;
    user_gui_showRoomsUserVersion->setShowRoomsUserVersion(this);
    this->close();
    user_gui_showRoomsUserVersion->show();
}


void showRoomsUserVersion::on_submit_button_clicked()
{
    QString room_name = ui->name_filter->currentText();
    QString number_of_beds = ui->number_of_beds_filter->currentText();

    QVector<room> filteredRooms = roomObj_showRoomsUserVersion.getUserVersionFilteredRoomsFromDb(room_name, number_of_beds);
    int storedRooms=filteredRooms.size();
    ui->tableWidget->setRowCount(storedRooms);

    for(int i=0; i<storedRooms; i++){
        room roomData = filteredRooms[i];
        QTableWidgetItem *room_id = new QTableWidgetItem();
        room_id -> setData(Qt::UserRole, roomData.getRoomID());
        QTableWidgetItem *room_name = new QTableWidgetItem(roomData.getRoomName());
        QTableWidgetItem *room_capacity = new QTableWidgetItem(QString::number(roomData.getRoomCapacity()));
        QTableWidgetItem *room_description = new QTableWidgetItem(roomData.getRoomDescription());

        room_description->setToolTip(roomData.getRoomDescription());

        ui->tableWidget->setItem(i, 0, room_id);
        ui->tableWidget->setColumnHidden(0, true);
        ui->tableWidget->setItem(i, 1, room_name);
        ui->tableWidget->setItem(i, 2, room_capacity);
        ui->tableWidget->setItem(i, 3, room_description);
        QPushButton *reserveRoomButton = new QPushButton("Reserve",this);
        connect(reserveRoomButton, &QPushButton::clicked, this, [this, i](){onClickedReserveButton(i);});
        ui->tableWidget->setCellWidget(i,4, reserveRoomButton);
    }
}

