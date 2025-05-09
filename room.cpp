#include "room.h"

//int room::id = -1;

int room::getRoomID(){
    return id;
}

void room::setRoomID(int room_id){
    id = room_id;
}

QString room::getRoomName(){
    return name;
}

void room::setRoomName(QString room_name){
    name = room_name;
}

int room::getRoomCapacity(){
    return bed_number;
}

QString room::getRoomDescription(){
    return description;
}

QString room::getRoomStatus(){
    return status;
}

void room::insertRoomToDb(QString room_name, int room_bed_number, QString room_description){
    QSqlQuery query;
    query.prepare("INSERT INTO room(name,bed_number,description,status) VALUES (:room_name, :room_bed_number, :room_description, 'available')");
    query.bindValue(":room_name", room_name);
    query.bindValue(":room_bed_number", room_bed_number);
    query.bindValue(":room_description", room_description);
    query.exec();
    query.clear();
    query.finish();
}

void room::editRoomInDb(QString room_name, int room_bed_number, QString room_description, QString room_status, int room_id){
    QSqlQuery query;
    query.prepare("UPDATE room SET name = :room_name, bed_number = :room_bed_number, description = :room_description, status = :room_status WHERE id = :room_id");
    query.bindValue(":room_name", room_name);
    query.bindValue(":room_bed_number", room_bed_number);
    query.bindValue(":room_description", room_description);
    query.bindValue(":room_status", room_status);
    query.bindValue(":room_id", room_id);
    query.exec();
    query.clear();
    query.finish();
}

void room::deleteRoomFromDb(int room_id){
    QSqlQuery query;
    query.prepare("DELETE FROM room WHERE id=:room_id");
    query.bindValue(":room_id", room_id);
    query.exec();
    query.clear();
    query.finish();
}

const QVector<room> room::getAllRoomsFromDb(){
    QVector<room> vektorOfAllRooms;
    QSqlQuery query;
    query.prepare("SELECT id, name, bed_number, description, status FROM room");
    query.exec();
    while(query.next()){
        room roomTmp;
        roomTmp.id = query.value(0).toInt();
        roomTmp.name = query.value(1).toString();
        roomTmp.bed_number = query.value(2).toInt();
        roomTmp.description = query.value(3).toString();
        roomTmp.status = query.value(4).toString();
        vektorOfAllRooms.append(roomTmp);
    }
    query.clear();
    query.finish();
    return vektorOfAllRooms;
}

const room room::getRoomFromTb(int room_id) {
    room roomForGivenId;
    QSqlQuery query;
    query.prepare("SELECT id, name, bed_number, description, status FROM room WHERE id = :room_id");
    query.bindValue(":room_id",room_id);
    query.exec();
    while(query.next()){
        roomForGivenId.id = query.value(0).toInt();
        roomForGivenId.name = query.value(1).toString();
        roomForGivenId.bed_number = query.value(2).toInt();
        roomForGivenId.description = query.value(3).toString();
        roomForGivenId.status = query.value(4).toString();
    }
    query.clear();
    query.finish();
    return roomForGivenId;
}

bool room::checkIfNameOccursInDb(QString room_name, int current_room_id){
    bool result = false;
    QSqlQuery query;
    query.prepare("SELECT name FROM room WHERE id != :current_room_id");
    //query.bindValue(":room_name", room_name);
    query.bindValue(":current_room_id", current_room_id);
    query.exec();
    while(query.next()){
        if(room_name.compare(query.value(0).toString(),Qt::CaseInsensitive)==0){
            result = true;
            break;
        }
    }
    query.clear();
    query.finish();
    return result;
}

const QVector<room> room::getAvailableRoomsFromDb(){
    QVector<room> vektorOfAvailableRooms;
    QSqlQuery query;
    query.prepare("SELECT id, name, bed_number, description FROM room WHERE status = 'available'");
    query.exec();
    while(query.next()){
        room roomTmp;
        roomTmp.id = query.value(0).toInt();
        roomTmp.name = query.value(1).toString();
        roomTmp.bed_number = query.value(2).toInt();
        roomTmp.description = query.value(3).toString();
        vektorOfAvailableRooms.append(roomTmp);
    }
    query.clear();
    query.finish();
    return vektorOfAvailableRooms;
}

int room::getRoomIdForName(QString room_name){
    int tmp_id = -1;
    QSqlQuery query;
    query.prepare("SELECT id FROM room WHERE name = :room_name");
    query.bindValue(":room_name", room_name);
    query.exec();
    while(query.next()){
        tmp_id = query.value(0).toInt();
    }
    query.clear();
    query.finish();
    return tmp_id;
}

QVector<QString> room::getFilteredRoomName(){
    QVector<QString> names;
    QSqlQuery query;
    query.prepare("SELECT DISTINCT name FROM room");
    query.exec();
    while(query.next()){
        names.append(query.value(0).toString());
    }
    query.clear();
    query.finish();
    return names;
}

QVector<QString> room::getUserVersionFilteredRoomName(){
    QVector<QString> names;
    QSqlQuery query;
    query.prepare("SELECT DISTINCT name FROM room WHERE status = 'available'");
    query.exec();
    while(query.next()){
        names.append(query.value(0).toString());
    }
    query.clear();
    query.finish();
    return names;
}

QVector<QString> room::getFilteredRoomNumberOfBeds(){
    QVector<QString> number_of_beds;
    QSqlQuery query;
    query.prepare("SELECT DISTINCT bed_number FROM room");
    query.exec();
    while(query.next()){
        number_of_beds.append(query.value(0).toString());
    }
    query.clear();
    query.finish();
    return number_of_beds;
}

QVector<QString> room::getUserVersionFilteredRoomNumberOfBeds(){
    QVector<QString> number_of_beds;
    QSqlQuery query;
    query.prepare("SELECT DISTINCT bed_number FROM room WHERE status = 'available'");
    query.exec();
    while(query.next()){
        number_of_beds.append(query.value(0).toString());
    }
    query.clear();
    query.finish();
    return number_of_beds;
}

QVector<QString> room::getFilteredRoomStatus(){
    QVector<QString> status;
    QSqlQuery query;
    query.prepare("SELECT DISTINCT status FROM room");
    query.exec();
    while(query.next()){
        status.append(query.value(0).toString());
    }
    query.clear();
    query.finish();
    return status;
}

QVector<room> room::getFilteredRoomsFromDb(QString room_name, QString number_of_beds, QString status){
    QVector<room> vektorOfFilteredRooms;

    QString base_query = "SELECT id, name, bed_number, description, status FROM room";

    QStringList where_clauses;
    QMap<QString, QVariant> parametres;

    if(!room_name.isEmpty()){
        where_clauses << "name = :room_name";
        parametres[":room_name"] = room_name;
    }
    if(!number_of_beds.isEmpty()){
        where_clauses << "bed_number = :number_of_beds";
        parametres[":number_of_beds"] = number_of_beds;
    }
    if(!status.isEmpty()){
        where_clauses << "status = :status";
        parametres[":status"] = status;
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
        room roomTmp;
        roomTmp.id = query.value(0).toInt();
        roomTmp.name = query.value(1).toString();
        roomTmp.bed_number = query.value(2).toInt();
        roomTmp.description = query.value(3).toString();
        roomTmp.status = query.value(4).toString();
        vektorOfFilteredRooms.append(roomTmp);
    }
    query.clear();
    query.finish();
    return vektorOfFilteredRooms;
}

QVector<room> room::getUserVersionFilteredRoomsFromDb(QString room_name, QString number_of_beds){
    QVector<room> vektorOfFilteredRooms;

    QString base_query = "SELECT id, name, bed_number, description FROM room";

    QStringList where_clauses;
    QMap<QString, QVariant> parametres;

    where_clauses << "status = 'available'";

    if(!room_name.isEmpty()){
        where_clauses << "name = :room_name";
        parametres[":room_name"] = room_name;
    }
    if(!number_of_beds.isEmpty()){
        where_clauses << "bed_number = :number_of_beds";
        parametres[":number_of_beds"] = number_of_beds;
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
        room roomTmp;
        roomTmp.id = query.value(0).toInt();
        roomTmp.name = query.value(1).toString();
        roomTmp.bed_number = query.value(2).toInt();
        roomTmp.description = query.value(3).toString();
        vektorOfFilteredRooms.append(roomTmp);
    }
    query.clear();
    query.finish();
    return vektorOfFilteredRooms;
}


