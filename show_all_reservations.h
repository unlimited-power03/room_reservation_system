#ifndef SHOW_ALL_RESERVATIONS_H
#define SHOW_ALL_RESERVATIONS_H

#include <QDialog>
#include "room.h"
#include "reservation.h"
#include <QMessageBox>
namespace Ui {
class showAllReservations;
}

class ownerGui;

class showAllReservations : public QDialog
{
    Q_OBJECT

public:
    explicit showAllReservations(QWidget *parent = nullptr);
    void setOwnerGui(ownerGui *gui);
    void showAllReservationsTable();
    ~showAllReservations();

private slots:
    void on_back_clicked();
    void onClickedCancelReservationButton(int row);

    void on_submit_button_clicked();

    void on_reset_button_clicked();

    void setFilters();

private:
    Ui::showAllReservations *ui;
    ownerGui *owner_gui_showAllReservations;
    room roomObj_showAllReservations;
    reservation reservationObj_showAllReservations;
};

#endif // SHOW_ALL_RESERVATIONS_H
