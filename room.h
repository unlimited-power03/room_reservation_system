#ifndef ROOM_H
#define ROOM_H

#include <QVector>
#include <QSqlQuery>
class room
{
private:
    int id;
    QString name;
    int bed_number;
    QString description;
    QString status;
public:
    int getRoomID();
    void setRoomID(int room_id);
    QString getRoomName();
    void setRoomName(QString room_name);
    int getRoomCapacity();
    QString getRoomDescription();
    QString getRoomStatus();
    void insertRoomToDb(QString room_name, int room_capacity, QString room_description);
    void editRoomInDb(QString room_name, int room_bed_number, QString room_description, QString room_status, int room_id);
    void deleteRoomFromDb(int room_id);
    const QVector<room> getAllRoomsFromDb();
    const room getRoomFromTb(int room_id);
    bool checkIfNameOccursInDb(QString room_name, int current_room_id);
    const QVector<room> getAvailableRoomsFromDb();
    int getRoomIdForName(QString room_name);
    QVector<QString> getFilteredRoomName();
    QVector<QString> getUserVersionFilteredRoomName();
    QVector<QString> getFilteredRoomNumberOfBeds();
    QVector<QString> getUserVersionFilteredRoomNumberOfBeds();
    QVector<QString> getFilteredRoomStatus();
    QVector<room> getFilteredRoomsFromDb(QString room_name, QString number_of_beds, QString status);
    QVector<room> getUserVersionFilteredRoomsFromDb(QString room_name, QString number_of_beds);
};

#endif // ROOM_H
