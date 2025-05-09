#ifndef USER_PASSWORD_DATA_H
#define USER_PASSWORD_DATA_H
#include "password_data.h"
#include "session_manager.h"
#include "userdata.h"
class userPasswordData : public passwordData
{
private:
    userdata uD;
public:
    void hashPassword(const QString& password) override; //insert hashed password to db
    void editUserPassword(const QString& password, int user_id);
    bool checkUserPassword(const QString &password, const int id_for_given_email);
    void insertUserPasswordToDb(const QString &password);
    void deleteUserPassword(int user_id);

};

#endif // USER_PASSWORD_DATA_H
