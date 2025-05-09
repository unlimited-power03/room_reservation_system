#ifndef USERDATA_H
#define USERDATA_H

#include <QVector>
#include <QSqlError>
#include "persondata.h"
class userdata : public personData
{
public:
    std::pair<bool,int> searchForUserEmail(QString email);
    void insertPersonToDb(const QString &firstName, const QString &surname, const QString &email, const QString &telephoneNumber);
    QVector <userdata> getUserNameFromDb(const int id);
    void editUserData(const int user_id, const QString &user_email, const QString &user_telephone_number);
    void deleteUser(int user_id);
};

#endif // USERDATA_H
