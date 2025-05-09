#include "user_password_data.h"

void userPasswordData::hashPassword(const QString &password){
    passwordData::hashPassword(password);
    QSqlQuery query;
    query.prepare("INSERT INTO users_password(salt,hashed_password) VALUES(:salt,:hashed_password)");
    query.bindValue(":salt",salt);
    query.bindValue(":hashed_password",hashedPassword);
    bool if_ok = query.exec();
    if(!if_ok){
        qDebug() << query.lastError().text();
    }
    query.clear();
    query.finish();

}

void userPasswordData::editUserPassword(const QString &password, int user_id){
    passwordData::hashPassword(password);
    QSqlQuery query;
    query.prepare("UPDATE users_password SET salt = :salt, hashed_password = :hashed_password WHERE id = :user_id");
    query.bindValue(":salt",salt);
    query.bindValue(":hashed_password",hashedPassword);
    query.bindValue(":user_id", user_id);
    query.exec();
    query.clear();
    query.finish();
}

bool userPasswordData::checkUserPassword(/*const QString &email,*/ const QString &password, const int id_for_given_email){
    //int index_of_password_for_given_email = uD.searchForUserEmail(email).second;
    QByteArray hashedPasswordStoredInDb;
    QByteArray givenPassword;
    QSqlQuery query;
    query.prepare("SELECT salt,hashed_password FROM users_password WHERE id = :id_for_given_email");
    query.bindValue(":id_for_given_email", id_for_given_email);
    query.exec();
    if(query.next()){
        hashedPasswordStoredInDb = query.value(1).toByteArray();
        givenPassword = QCryptographicHash::hash(password.toUtf8() + query.value(0).toByteArray(),QCryptographicHash::Sha256);
    }
    query.clear();
    query.finish();
    return hashedPasswordStoredInDb==givenPassword;
}

void userPasswordData::deleteUserPassword(int user_id){
    QSqlQuery query;
    query.prepare("DELETE FROM users_password WHERE id = :user_id");
    query.bindValue(":user_id", user_id);
    query.exec();
    query.clear();
    query.finish();
}
