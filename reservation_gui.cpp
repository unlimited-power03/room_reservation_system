#include "reservation_gui.h"
#include "ui_reservation_gui.h"
#include "show_rooms_user_version.h"
#include <QDebug>
reservationGui::reservationGui(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::reservationGui), showRoomsUserVersionGui_reservationGui(nullptr)
{
    ui->setupUi(this);
    setWindowFlag(Qt::WindowCloseButtonHint, false);

}

void reservationGui::setDateRangeHighlight(QDate startDate, QDate endDate){

    for(auto &date: highlighedDates){
        QTextCharFormat defaultFormat;
        defaultFormat.setBackground(Qt::transparent);
        ui->calendarWidget->setDateTextFormat(date, defaultFormat);
    }
    highlighedDates.clear();

    QDate currentDateToHighlight = startDate;
    while(currentDateToHighlight<=endDate){
        if(!reservedDates.contains(currentDateToHighlight)){
            QTextCharFormat greenHighlight;
            greenHighlight.setBackground(Qt::green);
            //greenHighlight.setForeground(Qt::black);
            ui->calendarWidget->setDateTextFormat(currentDateToHighlight, greenHighlight);
            highlighedDates.append(currentDateToHighlight);
        }
        else{
            QTextCharFormat orangeHighlight;
            QColor color(255,166,0);
            orangeHighlight.setBackground(color);
            ui->calendarWidget->setDateTextFormat(currentDateToHighlight, orangeHighlight);
        }
        currentDateToHighlight = currentDateToHighlight.addDays(1);
    }

}

void reservationGui::setReservedDateHighlight(){  //dodaj od wybranego pokoju
    QVector <reservation> date_details = reservationObj_gui.getStartAndEndReservationDateForRoom(showRoomsUserVersionGui_reservationGui->getSelectedRoomID());
    for(int i=0; i<date_details.size(); i++){
        reservation info = date_details[i];
        QDate startDate = info.getBeginOfReservation();
        QDate endDate = info.getEndOfReservation();
        QDate currentDate = startDate;
        while (currentDate <= endDate) {

            QTextCharFormat redHighlight;
            redHighlight.setBackground(Qt::red);


            ui->calendarWidget->setDateTextFormat(currentDate, redHighlight);
            reservedDates.append(currentDate);
            currentDate = currentDate.addDays(1);
        }
    }
}
void reservationGui::setShowRoomsUserVersionGui(showRoomsUserVersion *gui){
    showRoomsUserVersionGui_reservationGui = gui;

    if(QTime::currentTime() < QTime(10,0)){
        ui->startDate->setMinimumDate(QDate::currentDate().addDays(1));
        ui->endDate->setMinimumDate(QDate::currentDate().addDays(2));
    }
    else{
        ui->startDate->setMinimumDate(QDate::currentDate().addDays(2));
        ui->endDate->setMinimumDate(QDate::currentDate().addDays(3));
    }



    ui->calendarWidget->setMinimumDate(QDate::currentDate());
    room room_name_info = reservationObj_gui.getRoom().getRoomFromTb(showRoomsUserVersionGui_reservationGui->getSelectedRoomID());
    QString selectedRoom = room_name_info.getRoomName();
    ui->selectedRoomLabel->setText("Selected room: " + selectedRoom);
    /*connect(ui->startDate, &QDateEdit::userDateChanged, this, &reservationGui::setDateRangeHighlight);
    connect(ui->endDate, &QDateEdit::userDateChanged, this, &reservationGui::setDateRangeHighlight);*/
    connect(ui->startDate, &QDateEdit::userDateChanged, this, [this](){  //do funkcji
        QDate startDate = ui->startDate->date();  // Pobierz startDate
        QDate endDate = ui->endDate->date();      // Pobierz endDate
        setDateRangeHighlight(startDate, endDate);  // Przekaż obie daty do slotu
    });

    connect(ui->endDate, &QDateEdit::userDateChanged, this, [this](){
        QDate startDate = ui->startDate->date();  // Pobierz startDate
        QDate endDate = ui->endDate->date();      // Pobierz endDate
        setDateRangeHighlight(startDate, endDate);  // Przekaż obie daty do slotu
    });

    setReservedDateHighlight();
    setDateRangeHighlight(ui->startDate->date(), ui->endDate->date());
}

void reservationGui::on_back_clicked()
{
    //if(showRoomsUserVersionGui_reservationGui != nullptr){/*showRoomsUserVersionGui_reservationGui -> deleteLater();*/ showRoomsUserVersionGui_reservationGui = nullptr;}
    showRoomsUserVersionGui_reservationGui = new showRoomsUserVersion;
    showRoomsUserVersionGui_reservationGui->setReservationGui(this);
    this->close();
    showRoomsUserVersionGui_reservationGui->show();
}


reservationGui::~reservationGui()
{
    delete ui;
    if(showRoomsUserVersionGui_reservationGui != nullptr){delete showRoomsUserVersionGui_reservationGui; showRoomsUserVersionGui_reservationGui = nullptr;}
}


void reservationGui::on_reserveRoom_clicked()
{
    QDate startDate = ui->startDate->date();// do funkcji
    QDate endDate = ui->endDate->date();

    if(startDate>=endDate){
        QMessageBox::information(this,"Error","Improper date, \n Hint: must be at least one day long");
        return;
    }

    QVector<reservation> start_end_date_for_reservation_of_room = reservationObj_gui.getStartAndEndReservationDateForRoom(showRoomsUserVersionGui_reservationGui->getSelectedRoomID());
    for(int i=0; i<start_end_date_for_reservation_of_room.size(); i++){
        reservation date_info = start_end_date_for_reservation_of_room[i];
        QDate compared_start_date = date_info.getBeginOfReservation();
        QDate compared_end_date = date_info.getEndOfReservation();
        if (endDate >= compared_start_date && startDate <= compared_end_date) {
            QMessageBox::information(this,"Error","Room reserved, choose another date");
            return;
        }
    }
    reservationObj_gui.insertReservationToDB(showRoomsUserVersionGui_reservationGui->getSelectedRoomID(), sM_reservationGui.getIdOfCurrentlyLoggedUser(), startDate, endDate);
    QMessageBox::information(this,"Success","Room successfully reserved");
    ui->startDate->setMinimumDate(QDate::currentDate());
    ui->endDate->setMinimumDate(QDate::currentDate().addDays(1));
    setReservedDateHighlight();
}

