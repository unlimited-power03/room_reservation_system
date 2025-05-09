#ifndef RESERVATION_GUI_H
#define RESERVATION_GUI_H

#include <QDialog>
#include <QDate>
#include "reservation.h"
#include "room.h"
#include "userdata.h"
#include <QTextCharFormat>
#include <QMessageBox>
#include <QVector>
#include "session_manager.h"
namespace Ui {
class reservationGui;
}

class showRoomsUserVersion;
class reservationGui : public QDialog
{
    Q_OBJECT

public:
    explicit reservationGui(QWidget *parent = nullptr);
    void setShowRoomsUserVersionGui(showRoomsUserVersion* gui);

    ~reservationGui();

protected slots:
    void setDateRangeHighlight(QDate startDate, QDate endDate);
    void on_back_clicked();

    void on_reserveRoom_clicked();

private slots:


protected:
    QVector<QDate> highlighedDates;
    QVector<QDate> reservedDates;
    Ui::reservationGui *ui;
    reservation reservationObj_gui;
    userdata userData_reservationGui;
    session_manager sM_reservationGui;

private:
    void setReservedDateHighlight();
    showRoomsUserVersion *showRoomsUserVersionGui_reservationGui;

};

#endif // RESERVATION_GUI_H
