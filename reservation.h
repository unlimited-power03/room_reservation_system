#ifndef RESERVATION_H
#define RESERVATION_H


#include <QVector>
#include <QDate>
#include <QSqlQuery>
#include "room.h"
#include "userdata.h"
class reservation
{
private:
    int id;
    room roomObj_reservation;
    userdata userdataObj_reservation;
    QDate begin_date;
    QDate end_date;
public:
    int getReservationID();
    void setReservationID(int reservation_id);
    room getRoom();
    userdata getUserData();
    QDate getBeginOfReservation();
    QDate getEndOfReservation();


    QVector<reservation> getAllReservationData();
    QVector<QString> getFilterForRoomName();
    QVector<QString> getUserVersionFilterForRoomName(int user_id);
    QVector<QString> getFilterForUserName();
    QVector<QString> getFilterForUserSurnmae();
    QVector<QString> getFilterForUserEmail();
    QVector<reservation> getFilteredReservationDate(QString &room_name, QString &first_name, QString &surname, QString &email, QDate start_date, QDate end_date);
    QVector<reservation> getUserVersionFilteredReservationDate(int user_id, QString &room_name, QDate start_date, QDate end_date);
    QVector<reservation> getUserReservation(int user_id);
    int checkActualReservations(int user_id);
    void insertReservationToDB(int room_id, int user_id, QDate begin_of_reservation, QDate end_of_reservation);
    void deleteReservation(int reservation_id);
    void editReservation(int reservation_id, QDate reservation_begin_date, QDate reservation_end_date); //only for editing date
    bool doesReservationExist(int reservation_room_ID);
    QVector<reservation> getStartAndEndReservationDateForRoom(int room_id);
    QVector<reservation> getStartAndEndReservationDateForEditReservation(int room_id, int reservation_id);
};

#endif // RESERVATION_H
