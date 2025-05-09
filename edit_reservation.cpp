#include "edit_reservation.h"
#include "show_user_reservations.h"
#include "show_rooms_user_version.h"

editReservation::editReservation(QWidget *parent)
    : reservationGui(parent)
    , show_user_reservations_editReservation (nullptr)
{
    //ui->setupUi(this);
}

void editReservation::setShowUserReservations(showUserReservations *gui){
    show_user_reservations_editReservation = gui;

    disconnect(ui->back, SIGNAL(clicked()), this, SLOT(on_back_clicked()));
    connect(ui->back, &QPushButton::clicked, this, &editReservation::on_back_clicked);

    disconnect(ui->reserveRoom, SIGNAL(clicked()), this, SLOT(on_reserveRoom_clicked()));
    connect(ui->reserveRoom, &QPushButton::clicked, this, &editReservation::on_reserveRoom_clicked);

    ui->selectedRoomLabel->hide();
    ui->reserveRoom->setText("Edit \n reservation");
    if(QTime::currentTime() < QTime(10,0)){
        ui->startDate->setMinimumDate(QDate::currentDate().addDays(1));
        ui->endDate->setMinimumDate(QDate::currentDate().addDays(2));
    }
    else{
        ui->startDate->setMinimumDate(QDate::currentDate().addDays(2));
        ui->endDate->setMinimumDate(QDate::currentDate().addDays(3));
    }

    ui->calendarWidget->setMinimumDate(QDate::currentDate());

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
    //qDebug() << "DUPA";
    setReservedDateHighlightBeforeCommit();
    setDateRangeHighlight(ui->startDate->date(), ui->endDate->date());
}

void editReservation::setReservedDateHighlightBeforeCommit(){
    QTextCharFormat defaultFormat;
    for (const QDate &date : reservedDates) {
        ui->calendarWidget->setDateTextFormat(date, defaultFormat);
    }
    reservedDates.clear(); // wyczyść poprzednie daty
    QVector <reservation> date_details = reservationObj_gui.getStartAndEndReservationDateForEditReservation(show_user_reservations_editReservation->getSelectedRoomID(), show_user_reservations_editReservation->getSelectedReservationID());
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

void editReservation::setReservedDateHighlight(){
    QTextCharFormat defaultFormat;
    for (const QDate &date : reservedDates) {
        ui->calendarWidget->setDateTextFormat(date, defaultFormat);
    }
    reservedDates.clear(); // wyczyść poprzednie daty
    QVector <reservation> date_details = reservationObj_gui.getStartAndEndReservationDateForRoom(show_user_reservations_editReservation->getSelectedRoomID());
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


editReservation::~editReservation()
{
    //delete ui;
    if(show_user_reservations_editReservation != nullptr){delete show_user_reservations_editReservation; show_user_reservations_editReservation = nullptr;}
}

void editReservation::on_back_clicked(){
    show_user_reservations_editReservation = new showUserReservations;
    show_user_reservations_editReservation -> setEditReservationGui(this);
    this->close();
    show_user_reservations_editReservation -> show();
}


void editReservation::on_reserveRoom_clicked(){
    QDate startDate = ui->startDate->date();// do funkcji
    QDate endDate = ui->endDate->date();

    if(startDate>=endDate){
        QMessageBox::information(this,"Error","Improper date, \n Hint: must be at least one day long");
        return;
    }

    QVector<reservation> start_end_date_for_reservation_of_room = reservationObj_gui.getStartAndEndReservationDateForEditReservation(show_user_reservations_editReservation->getSelectedRoomID(), show_user_reservations_editReservation->getSelectedReservationID());
    for(int i=0; i<start_end_date_for_reservation_of_room.size(); i++){
        reservation date_info = start_end_date_for_reservation_of_room[i];
        QDate compared_start_date = date_info.getBeginOfReservation();
        QDate compared_end_date = date_info.getEndOfReservation();
        if (endDate >= compared_start_date && startDate <= compared_end_date) {
            QMessageBox::information(this,"Error","Room reserved, choose another date");
            return;
        }
    }
    reservationObj_gui.editReservation(show_user_reservations_editReservation->getSelectedReservationID(), startDate, endDate);
    QMessageBox::information(this,"Success","Reservation successfully edited");
    ui->startDate->setMinimumDate(QDate::currentDate());
    ui->endDate->setMinimumDate(QDate::currentDate().addDays(1));
    setReservedDateHighlight();
}
