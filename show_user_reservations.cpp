#include "show_user_reservations.h"
#include "ui_show_user_reservations.h"
#include "usergui.h"
#include "edit_reservation.h"
#include <QDebug>
showUserReservations::showUserReservations(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::showUserReservations), user_gui_showUserReservation(nullptr)
{
    ui->setupUi(this);
    setWindowFlag(Qt::WindowCloseButtonHint, false);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->room_filter->addItem("");
    for(QString &room : reservationObj_showUserReservation.getUserVersionFilterForRoomName(sM_showUserReservation.getIdOfCurrentlyLoggedUser())){
        ui->room_filter->addItem(room);
    }

    ui->start_day_filter->setDate(QDate::currentDate());
    ui->end_date_filter->setDate(QDate::currentDate().addDays(1));
    ui->start_day_filter->setCalendarPopup(true);
    ui->end_date_filter->setCalendarPopup(true);

    showTable();
}

void showUserReservations::showTable(){
    ui->tableWidget->clearContents(); // Czyścimy tabelę
    QVector <reservation> reservation_user_data = reservationObj_showUserReservation.getUserReservation(sM_showUserReservation.getIdOfCurrentlyLoggedUser());

    int selectedReservations = reservation_user_data.size();
    ui->tableWidget->setRowCount(selectedReservations);

    for(int i=0; i<selectedReservations; i++){
        reservation data = reservation_user_data[i];
        QTableWidgetItem *id = new QTableWidgetItem();
        id->setData(Qt::UserRole, data.getReservationID());
        QTableWidgetItem *room_name = new QTableWidgetItem(data.getRoom().getRoomName());
        QTableWidgetItem *start_date = new QTableWidgetItem(data.getBeginOfReservation().toString("yyyy-MM-dd"));
        QTableWidgetItem *end_date = new QTableWidgetItem(data.getEndOfReservation().toString("yyyy-MM-dd"));


        ui->tableWidget->setItem(i, 0, id);
        ui->tableWidget->setColumnHidden(0, true);
        ui->tableWidget->setItem(i, 1, room_name);
        ui->tableWidget->setItem(i, 2, start_date);
        ui->tableWidget->setItem(i, 3, end_date);

        if(!(data.getBeginOfReservation() <= QDate::currentDate().addDays(1) || data.getEndOfReservation() <= QDate::currentDate())){
            QPushButton *editReservationButton = new QPushButton("Edit",this);
            connect(editReservationButton, &QPushButton::clicked, this, [=](){onClickedEditReservationButton(i);});
            ui->tableWidget->setCellWidget(i,4, editReservationButton);
            QPushButton *cancelReservationButton = new QPushButton("Cancel",this);
            connect(cancelReservationButton, &QPushButton::clicked, this, [=](){onClickedCancelReservationButton(i);});
            ui->tableWidget->setCellWidget(i,5, cancelReservationButton);
        }

        if(QDate::currentDate() >= data.getBeginOfReservation() && QDate::currentDate()<= data.getEndOfReservation()){
            for(int col=0; col<ui->tableWidget->columnCount(); col++){
                QTableWidgetItem *item = ui->tableWidget->item(i,col);
                if (!item) {
                    item = new QTableWidgetItem();
                    ui->tableWidget->setItem(i, col, item);
                }
                item->setBackground(QColor(144, 238, 144));
            }
        }
    }
}


void showUserReservations::setUserGui(userGui *gui){
    user_gui_showUserReservation = gui;
}

void showUserReservations::setEditReservationGui(editReservation *gui){
    editReservation_showUserReservations = gui;
}

void showUserReservations::onClickedCancelReservationButton(int row){
    int selectedReservation = ui->tableWidget->item(row, 0)->data(Qt::UserRole).toInt();
    QMessageBox::StandardButton reply = QMessageBox::question(this,"Cancel reservation", "Are you sure you want to cancel", QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes){
        reservationObj_showUserReservation.deleteReservation(selectedReservation);
        showTable();
    }
}

int showUserReservations::getSelectedRoomID(){
    return selectedRoomId;
}

int showUserReservations::getSelectedReservationID(){
    return selectedReservationID;
}

void showUserReservations::onClickedEditReservationButton(int row){
    selectedReservationID = ui->tableWidget->item(row, 0)->data(Qt::UserRole).toInt();
    //show_rooms_user_version_showUserreservations.setSelectedRoomId(roomObj_showUserReservation.getRoomIdForName(ui->tableWidget->item(row,1)->text()));
    selectedRoomId = reservationObj_showUserReservation.getRoom().getRoomIdForName(ui->tableWidget->item(row,1)->text());
    qDebug() << selectedReservationID;
    qDebug() << selectedRoomId;
    editReservation_showUserReservations = new editReservation;
    editReservation_showUserReservations->setShowUserReservations(this);;
    this->close();
    editReservation_showUserReservations->show();
}

showUserReservations::~showUserReservations()
{
    delete ui;
    if(user_gui_showUserReservation != nullptr){delete user_gui_showUserReservation; user_gui_showUserReservation = nullptr;}
    if(editReservation_showUserReservations != nullptr){delete editReservation_showUserReservations; editReservation_showUserReservations = nullptr;}
    //if(edit_reservation_gui != nullptr){delete edit_reservation_gui; edit_reservation_gui = nullptr;}
}

void showUserReservations::on_back_clicked()
{
    //if(user_gui_showUserReservation != nullptr){/*user_gui_showUserReservation -> deleteLater();*/ user_gui_showUserReservation = nullptr;}
    user_gui_showUserReservation = new userGui;
    user_gui_showUserReservation->setShowUserReservations(this);
    this->close();
    user_gui_showUserReservation->show();
}


void showUserReservations::on_submit_button_clicked()
{
    QString selected_room = ui->room_filter->currentText();

    QDate start_date; //empty
    QDate end_date; //empty

    if(ui->checkBox_start_day->isChecked()){
        start_date = ui->start_day_filter->date();
    }

    if(ui->checkBox_end_day->isChecked()){
        end_date = ui->end_date_filter->date();
    }

    ui->tableWidget->clearContents(); // Czyścimy tabelę
    QVector <reservation> reservation_user_data = reservationObj_showUserReservation.getUserVersionFilteredReservationDate(sM_showUserReservation.getIdOfCurrentlyLoggedUser(), selected_room, start_date, end_date);

    int selectedReservations = reservation_user_data.size();
    ui->tableWidget->setRowCount(selectedReservations);

    for(int i=0; i<selectedReservations; i++){
        reservation data = reservation_user_data[i];
        QTableWidgetItem *id = new QTableWidgetItem();
        id->setData(Qt::UserRole, data.getReservationID());
        QTableWidgetItem *room_name = new QTableWidgetItem(data.getRoom().getRoomName());
        QTableWidgetItem *start_date = new QTableWidgetItem(data.getBeginOfReservation().toString("yyyy-MM-dd"));
        QTableWidgetItem *end_date = new QTableWidgetItem(data.getEndOfReservation().toString("yyyy-MM-dd"));


        ui->tableWidget->setItem(i, 0, id);
        ui->tableWidget->setColumnHidden(0, true);
        ui->tableWidget->setItem(i, 1, room_name);
        ui->tableWidget->setItem(i, 2, start_date);
        ui->tableWidget->setItem(i, 3, end_date);

        if(!(data.getBeginOfReservation() <= QDate::currentDate().addDays(1) || data.getEndOfReservation() <= QDate::currentDate())){
            QPushButton *editReservationButton = new QPushButton("Edit",this);
            connect(editReservationButton, &QPushButton::clicked, this, [=](){onClickedEditReservationButton(i);});
            ui->tableWidget->setCellWidget(i,4, editReservationButton);
            QPushButton *cancelReservationButton = new QPushButton("Cancel",this);
            connect(cancelReservationButton, &QPushButton::clicked, this, [=](){onClickedCancelReservationButton(i);});
            ui->tableWidget->setCellWidget(i,5, cancelReservationButton);
        }
    }

}


void showUserReservations::on_reset_button_clicked()
{
    ui->room_filter->setCurrentIndex(0);
    ui->checkBox_start_day->setChecked(false);
    ui->checkBox_end_day->setChecked(false);
    showTable();
}

