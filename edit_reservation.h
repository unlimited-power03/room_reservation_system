#ifndef EDIT_RESERVATION_H
#define EDIT_RESERVATION_H

#include <QDialog>
#include "reservation_gui.h"
#include "ui_reservation_gui.h"
//#include "show_user_reservations.h"

namespace Ui {
class editReservation;
}

class showUserReservations;

class editReservation : public reservationGui
{
    Q_OBJECT

public:
    explicit editReservation(QWidget *parent = nullptr);
    void setShowUserReservations(showUserReservations *gui);
    void setReservedDateHighlightBeforeCommit();
    ~editReservation();

private slots:
    void on_back_clicked();
    void on_reserveRoom_clicked();

private:
    //reservationGui *reservationGui_editReservation;
    showUserReservations *show_user_reservations_editReservation;
    void setReservedDateHighlight();

};

#endif // EDIT_RESERVATION_H
