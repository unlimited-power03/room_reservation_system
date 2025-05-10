#include "show_all_reservations.h"
#include "ui_show_all_reservations.h"
#include "ownergui.h"

showAllReservations::showAllReservations(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::showAllReservations), owner_gui_showAllReservations(nullptr)
{
    ui->setupUi(this);
    setWindowFlag(Qt::WindowCloseButtonHint, false);

    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    setFilters();
    showAllReservationsTable();


}

void showAllReservations::setFilters(){
    ui->room_filter->addItem("");
    for(QString &room : reservationObj_showAllReservations.getFilterForRoomName()){
        ui->room_filter->addItem(room);
    }
    ui->first_name_filter->addItem("");
    for(QString &first_name : reservationObj_showAllReservations.getFilterForUserName()){
        ui->first_name_filter->addItem(first_name);
    }
    ui->surname_filter->addItem("");
    for(QString &surname : reservationObj_showAllReservations.getFilterForUserSurnmae()){
        ui->surname_filter->addItem(surname);
    }
    ui->email_filter->addItem("");
    for(QString &email : reservationObj_showAllReservations.getFilterForUserEmail()){
        ui->email_filter->addItem(email);
    }

    ui->start_day_filter->setDate(QDate::currentDate());
    ui->end_date_filter->setDate(QDate::currentDate().addDays(1));
    ui->start_day_filter->setCalendarPopup(true);
    ui->end_date_filter->setCalendarPopup(true);
}

void showAllReservations::showAllReservationsTable(){
    ui->tableWidget->clearContents();
    QVector <reservation> all_Reservation_data = reservationObj_showAllReservations.getAllReservationData();
    int storedAllReservations = all_Reservation_data.size();
    ui->tableWidget->setRowCount(storedAllReservations);

    for(int i=0; i<storedAllReservations; i++){
        reservation data = all_Reservation_data[i];
        QTableWidgetItem *id = new QTableWidgetItem();
        id->setData(Qt::UserRole, data.getReservationID());
        QTableWidgetItem *room_name = new QTableWidgetItem(data.getRoom().getRoomName());
        QTableWidgetItem *user_first_name = new QTableWidgetItem(data.getUserData().getFirstName());
        QTableWidgetItem *user_surname = new QTableWidgetItem(data.getUserData().getSurname());
        QTableWidgetItem *user_email = new QTableWidgetItem(data.getUserData().getEmail());
        QTableWidgetItem *start_date = new QTableWidgetItem(data.getBeginOfReservation().toString("yyyy-MM-dd"));
        QTableWidgetItem *end_date = new QTableWidgetItem(data.getEndOfReservation().toString("yyyy-MM-dd"));

        ui->tableWidget->setItem(i, 0, id);
        ui->tableWidget->setColumnHidden(0, true);
        ui->tableWidget->setItem(i, 1, room_name);
        ui->tableWidget->setItem(i, 2, user_first_name);
        ui->tableWidget->setItem(i, 3, user_surname);
        ui->tableWidget->setItem(i, 4, user_email);
        ui->tableWidget->setItem(i, 5, start_date);
        ui->tableWidget->setItem(i, 6, end_date);
        if(!(data.getBeginOfReservation() <= QDate::currentDate().addDays(1) || data.getEndOfReservation() <= QDate::currentDate())){
                QPushButton *cancelReservationButton = new QPushButton("Cancel",this);
                connect(cancelReservationButton, &QPushButton::clicked, this, [=](){onClickedCancelReservationButton(i);});
                ui->tableWidget->setCellWidget(i,7, cancelReservationButton);
        }
    }
}


void showAllReservations::setOwnerGui(ownerGui *gui){
    owner_gui_showAllReservations = gui;
}

showAllReservations::~showAllReservations()
{
    delete ui;
    if(owner_gui_showAllReservations != nullptr){ delete owner_gui_showAllReservations; owner_gui_showAllReservations = nullptr;}
}

void showAllReservations::onClickedCancelReservationButton(int row){
    int selectedReservation = (ui->tableWidget->item(row, 0)->text().toInt());
    QMessageBox::StandardButton reply = QMessageBox::question(this,"Cancel reservation", "Are you sure you want to cancel", QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes){
        reservationObj_showAllReservations.deleteReservation(selectedReservation);
        showAllReservationsTable();

    }
}

void showAllReservations::on_back_clicked()
{
    owner_gui_showAllReservations = new ownerGui;
    owner_gui_showAllReservations->setShowAllReservations(this);
    this->close();
    owner_gui_showAllReservations->show();
}


void showAllReservations::on_submit_button_clicked()
{
    QString selected_room = ui->room_filter->currentText();
    QString selected_firt_name = ui->first_name_filter->currentText();
    QString selected_surname = ui->surname_filter->currentText();
    QString selected_email = ui->email_filter->currentText();

    QDate start_date; //empty
    QDate end_date; //empty


    if(ui->checkBox_start_day->isChecked()){
        start_date = ui->start_day_filter->date();
    }

    if(ui->checkBox_end_day->isChecked()){
        end_date = ui->end_date_filter->date();
    }

    // draw table
    ui->tableWidget->clearContents();
    QVector <reservation> filtered_Reservation_data = reservationObj_showAllReservations.getFilteredReservationDate(selected_room,selected_firt_name,selected_surname,selected_email,start_date,end_date);
    int storedFilteredReservations = filtered_Reservation_data.size();
    ui->tableWidget->setRowCount(storedFilteredReservations);

    for(int i=0; i<storedFilteredReservations; i++){
        reservation data = filtered_Reservation_data[i];
        QTableWidgetItem *id = new QTableWidgetItem();
        id->setData(Qt::UserRole, data.getReservationID());
        QTableWidgetItem *room_name = new QTableWidgetItem(data.getRoom().getRoomName());
        QTableWidgetItem *user_first_name = new QTableWidgetItem(data.getUserData().getFirstName());
        QTableWidgetItem *user_surname = new QTableWidgetItem(data.getUserData().getSurname());
        QTableWidgetItem *user_email = new QTableWidgetItem(data.getUserData().getEmail());
        QTableWidgetItem *start_date = new QTableWidgetItem(data.getBeginOfReservation().toString("yyyy-MM-dd"));
        QTableWidgetItem *end_date = new QTableWidgetItem(data.getEndOfReservation().toString("yyyy-MM-dd"));

        ui->tableWidget->setItem(i, 0, id);
        ui->tableWidget->setColumnHidden(0, true);
        ui->tableWidget->setItem(i, 1, room_name);
        ui->tableWidget->setItem(i, 2, user_first_name);
        ui->tableWidget->setItem(i, 3, user_surname);
        ui->tableWidget->setItem(i, 4, user_email);
        ui->tableWidget->setItem(i, 5, start_date);
        ui->tableWidget->setItem(i, 6, end_date);
        if(!(data.getBeginOfReservation() <= QDate::currentDate().addDays(1) || data.getEndOfReservation() <= QDate::currentDate())){
            QPushButton *cancelReservationButton = new QPushButton("Cancel",this);
            connect(cancelReservationButton, &QPushButton::clicked, this, [=](){onClickedCancelReservationButton(i);});
            ui->tableWidget->setCellWidget(i,7, cancelReservationButton);
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


void showAllReservations::on_reset_button_clicked()
{
    ui->room_filter->setCurrentIndex(0);
    ui->first_name_filter->setCurrentIndex(0);
    ui->surname_filter->setCurrentIndex(0);
    ui->email_filter->setCurrentIndex(0);
    ui->checkBox_start_day->setChecked(false);
    ui->checkBox_end_day->setChecked(false);
    showAllReservationsTable();

}

