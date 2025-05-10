#include "reservation.h"



int reservation::getReservationID() {
    return id;
}

room reservation::getRoom() {
    return roomObj_reservation;  // Zwracamy shared_ptr
}

 userdata reservation::getUserData() {
    return userdataObj_reservation;
}

 QDate reservation::getBeginOfReservation() {
    return begin_date;
}

 QDate reservation::getEndOfReservation() {
    return end_date;
}

void reservation::setReservationID(int reservation_id){
    id = reservation_id;
}
QVector<reservation> reservation::getAllReservationData(){
    QVector<reservation> general_data;
    QSqlQuery query;
    query.prepare("SELECT reservation.id, room.name, users.first_name, users.surname, users.email, begin_date, end_date FROM reservation LEFT JOIN room ON room.id = reservation.room_id LEFT JOIN users ON reservation.user_id = users.id");
    query.exec();
    while(query.next()){
        reservation tmp;
        tmp.id = query.value(0).toInt();
        QString room_name = query.value(1).toString();
        tmp.roomObj_reservation.setRoomName(room_name.isEmpty() ? "deleted" : room_name);
        QString user_first_name = query.value(2).toString();
        tmp.userdataObj_reservation.setFirstName(user_first_name.isEmpty() ? "deleted" : user_first_name);
        QString user_surname = query.value(3).toString();
        tmp.userdataObj_reservation.setSurname(user_surname.isEmpty() ? "deleted" : user_surname);
        QString user_email = query.value(4).toString();
        tmp.userdataObj_reservation.setEmail(user_email.isEmpty() ? "deleted" : user_email);
        tmp.begin_date = query.value(5).toDate();
        tmp.end_date = query.value(6).toDate();
        general_data.append(tmp);
    }
    query.clear();
    query.finish();
    return general_data;
}

QVector<QString> reservation::getFilterForRoomName(){
    QVector<QString> filter;
    QSqlQuery query;
    query.prepare("SELECT DISTINCT room.name FROM reservation INNER JOIN room ON room.id = reservation.room_id");
    query.exec();
    while(query.next()){
        filter.append(query.value(0).toString());
    }
    query.clear();
    query.finish();
    return filter;
}

QVector<QString> reservation::getUserVersionFilterForRoomName(int user_id){
    QVector<QString> filter;
    QSqlQuery query;
    query.prepare("SELECT DISTINCT room.name FROM reservation INNER JOIN room ON room.id = reservation.room_id WHERE user_id = :user_id");
    query.bindValue(":user_id", user_id);
    query.exec();
    while(query.next()){
        filter.append(query.value(0).toString());
    }
    query.clear();
    query.finish();
    return filter;
}

QVector<QString> reservation::getFilterForUserName(){
    QVector<QString> filter;
    QSqlQuery query;
    query.prepare("SELECT DISTINCT users.first_name FROM reservation INNER JOIN users ON reservation.user_id = users.id");
    query.exec();
    while(query.next()){
        filter.append(query.value(0).toString());
    }
    query.clear();
    query.finish();
    return filter;
}
QVector<QString> reservation::getFilterForUserSurnmae(){
    QVector<QString> filter;
    QSqlQuery query;
    query.prepare("SELECT DISTINCT users.surname FROM reservation INNER JOIN users ON reservation.user_id = users.id");
    query.exec();
    while(query.next()){
        filter.append(query.value(0).toString());
    }
    query.clear();
    query.finish();
    return filter;
}
QVector<QString> reservation::getFilterForUserEmail(){
    QVector<QString> filter;
    QSqlQuery query;
    query.prepare("SELECT DISTINCT users.email FROM reservation INNER JOIN users ON reservation.user_id = users.id");
    query.exec();
    while(query.next()){
        filter.append(query.value(0).toString());
    }
    query.clear();
    query.finish();
    return filter;
}

QVector<reservation> reservation::getFilteredReservationDate(QString &room_name, QString &first_name, QString &surname, QString &email, QDate start_date, QDate end_date){
    QVector<reservation> filtered_reservations;
    QString base_query = "SELECT reservation.id, room.name, users.first_name, users.surname, users.email, begin_date, end_date FROM reservation INNER JOIN room ON room.id = reservation.room_id INNER JOIN users ON reservation.user_id = users.id";

    QStringList where_clauses;
    QMap<QString, QVariant> parametres;
    if(!room_name.isEmpty()){
        where_clauses << "room.name = :room_name";
        parametres[":room_name"] = room_name;
    }
    if(!first_name.isEmpty()){
        where_clauses << "users.first_name = :first_name";
        parametres[":first_name"] = first_name;
    }
    if(!surname.isEmpty()){
        where_clauses << "users.surname = :surname";
        parametres[":surname"] = surname;
    }
    if(!email.isEmpty()){
        where_clauses << "users.email = :email";
        parametres[":email"] = email;
    }
    if(start_date.isValid()){
        where_clauses << "begin_date = :start_date";
        parametres[":start_date"] = start_date;
    }
    if(end_date.isValid()){
        where_clauses << "end_date = :end_date";
        parametres[":end_date"] = end_date;
    }

    if(!where_clauses.isEmpty()){
        base_query += " WHERE " + where_clauses.join(" AND ");
    }
    QSqlQuery query;
    query.prepare(base_query);
    for(auto i = parametres.begin(); i != parametres.end(); i++){
        query.bindValue(i.key(), i.value());
    }
    query.exec();
    while(query.next()){
        reservation tmp;
        tmp.id = query.value(0).toInt();
        tmp.roomObj_reservation.setRoomName(query.value(1).toString());
        tmp.userdataObj_reservation.setFirstName(query.value(2).toString());
        tmp.userdataObj_reservation.setSurname(query.value(3).toString());
        tmp.userdataObj_reservation.setEmail(query.value(4).toString());
        tmp.begin_date = query.value(5).toDate();
        tmp.end_date = query.value(6).toDate();
        filtered_reservations.append(tmp);
    }
    query.clear();
    query.finish();
    return filtered_reservations;
}


QVector<reservation> reservation::getUserVersionFilteredReservationDate(int user_id, QString &room_name, QDate start_date, QDate end_date){
    QVector<reservation> filtered_reservations;
    QString base_query = "SELECT reservation.id, room.name, begin_date, end_date FROM reservation INNER JOIN room ON room.id = reservation.room_id";

    QStringList where_clauses;
    QMap<QString, QVariant> parametres;

    where_clauses << "user_id = :user_id";
    parametres[":user_id"] = user_id;

    if(!room_name.isEmpty()){
        where_clauses << "room.name = :room_name";
        parametres[":room_name"] = room_name;
    }
    if(start_date.isValid()){
        where_clauses << "begin_date = :start_date";
        parametres[":start_date"] = start_date;
    }
    if(end_date.isValid()){
        where_clauses << "end_date = :end_date";
        parametres[":end_date"] = end_date;
    }

    if(!where_clauses.isEmpty()){
        base_query += " WHERE " + where_clauses.join(" AND ");
    }
    QSqlQuery query;
    query.prepare(base_query);
    for(auto i = parametres.begin(); i != parametres.end(); i++){
        query.bindValue(i.key(), i.value());
    }
    query.exec();
    while(query.next()){
        reservation tmp;
        tmp.id = query.value(0).toInt();
        tmp.roomObj_reservation.setRoomName(query.value(1).toString());
        tmp.begin_date = query.value(2).toDate();
        tmp.end_date = query.value(3).toDate();
        filtered_reservations.append(tmp);
    }
    query.clear();
    query.finish();
    return filtered_reservations;
}


QVector<reservation> reservation::getUserReservation(int user_id){
    QVector<reservation> user_data;
    QSqlQuery query;
    query.prepare("SELECT reservation.id, room.name, begin_date, end_date FROM reservation "
                  "LEFT JOIN room ON room.id = reservation.room_id WHERE reservation.user_id = :user_id");
    query.bindValue(":user_id",user_id);
    query.exec();
    while(query.next()){
        reservation tmp;
        tmp.id = query.value(0).toInt();
        QString room_name = query.value(1).toString();
        tmp.roomObj_reservation.setRoomName(room_name.isEmpty() ? "deleted" : room_name);
        tmp.begin_date = query.value(2).toDate();
        tmp.end_date = query.value(3).toDate();
        user_data.append(tmp);
    }
    query.clear();
    query.finish();
    return user_data;
}

int reservation::checkActualReservations(int user_id){
    int messageIdToDisplay=0;
    QSqlQuery query;
    query.prepare("SELECT begin_date, end_date FROM reservation WHERE reservation.user_id = :user_id");
    query.bindValue(":user_id",user_id);
    query.exec();
    while(query.next()){
        if(query.value(0).toDate() <= QDate::currentDate() && query.value(1).toDate() >= QDate::currentDate()){
            messageIdToDisplay = 1;
            break;
        }
        if(query.value(0).toDate() > QDate::currentDate()){
            messageIdToDisplay = 2;
            break;
        }
    }
    query.clear();
    query.finish();
    return messageIdToDisplay;
}

void reservation::insertReservationToDB(int room_id, int user_id, QDate begin_of_reservation, QDate end_of_reservation){
    QSqlQuery query;
    query.prepare("INSERT INTO reservation(room_id,user_id,begin_date,end_date) VALUES(:room_id, :user_id, :begin_of_reservation, :end_of_reservation)");
    query.bindValue(":room_id",room_id);
    query.bindValue(":user_id",user_id);
    query.bindValue(":begin_of_reservation",begin_of_reservation);
    query.bindValue(":end_of_reservation",end_of_reservation);
    query.exec();
    query.clear();
    query.finish();
}

void reservation::deleteReservation(int reservation_id){
    QSqlQuery query;
    query.prepare("DELETE FROM reservation WHERE id = :reservation_id");
    query.bindValue(":reservation_id",reservation_id);
    query.exec();
    query.clear();
    query.finish();
}

void reservation::editReservation(int reservation_id, QDate reservation_begin_date, QDate reservation_end_date){
    QSqlQuery query;
    query.prepare("UPDATE reservation SET begin_date = :reservation_begin_date, end_date = :reservation_end_date WHERE id = :reservation_id");
    query.bindValue(":reservation_begin_date", reservation_begin_date);
    query.bindValue(":reservation_end_date", reservation_end_date);
    query.bindValue(":reservation_id", reservation_id);
    query.exec();
    query.clear();
    query.finish();
}

bool reservation::doesReservationExist(int reservation_room_ID){
    bool result=false;
    QSqlQuery query;
    query.prepare("SELECT id FROM reservation WHERE room_id = :reservation_room_ID");
    query.bindValue(":reservation_room_ID",reservation_room_ID);
    query.exec();
    while(query.next()){
        result=true;
        break;
    }
    query.clear();
    query.finish();
    return result;
}

QVector<reservation> reservation::getStartAndEndReservationDateForRoom(int room_id){
    QVector <reservation> date_info;
    QSqlQuery query;
    query.prepare("SELECT begin_date, end_date FROM reservation WHERE room_id = :room_id");
    query.bindValue(":room_id", room_id);
    query.exec();
    while(query.next()){
        reservation tmp;
        tmp.begin_date = query.value(0).toDate();
        tmp.end_date = query.value(1).toDate();
        date_info.append(tmp);
    }
    query.clear();
    query.finish();
    return date_info;
}

QVector<reservation>  reservation::getStartAndEndReservationDateForEditReservation(int room_id, int reservation_id){
    QVector <reservation> date_info;
    QSqlQuery query;
    query.prepare("SELECT begin_date, end_date FROM reservation WHERE room_id = :room_id AND id != :reservation_id");
    query.bindValue(":room_id", room_id);
    query.bindValue(":reservation_id", reservation_id);
    query.exec();
    while(query.next()){
        reservation tmp;
        tmp.begin_date = query.value(0).toDate();
        tmp.end_date = query.value(1).toDate();
        date_info.append(tmp);
    }
    query.clear();
    query.finish();
    return date_info;
}
