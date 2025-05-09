#include "owner_password_data.h"
#include <QSqlError>

void ownerPasswordData::hashPassword(const QString& password){
    passwordData::hashPassword(password);
    QSqlQuery query;
    query.prepare("INSERT INTO owner_password(salt,hashed_password) VALUES(:salt,:hashed_password)");
    query.bindValue(":salt",salt);
    query.bindValue(":hashed_password",hashedPassword);
    query.exec();
    query.clear();
    query.finish();
}
void ownerPasswordData::editOwnerPassword(const QString& password, int owner_id){
    passwordData::hashPassword(password);
    QSqlQuery query;
    query.prepare("UPDATE owner_password SET salt = :salt, hashed_password = :hashed_password WHERE id = :owner_id");
    query.bindValue(":salt",salt);
    query.bindValue(":hashed_password",hashedPassword);
    query.bindValue(":owner_id", owner_id);
    //query.exec();
    bool ok = query.exec();

    if (!ok)
        qDebug() << "Query error:" << query.lastError().text();
    query.clear();
    query.finish();
}
bool ownerPasswordData::checkOwnerPassword(const QString &password, const int index_for_given_email){
    QByteArray hashedPasswordStoredInDb;
    QByteArray givenPassword;

    QSqlQuery query;
    query.prepare("SELECT salt,hashed_password FROM owner_password WHERE id = :index_for_given_email");
    query.bindValue(":index_for_given_email", index_for_given_email);
    query.exec();
    if(query.next()){
        hashedPasswordStoredInDb = query.value(1).toByteArray();
        givenPassword = QCryptographicHash::hash(password.toUtf8() + query.value(0).toByteArray(),QCryptographicHash::Sha256);
    }
    query.clear();
    query.finish();
    return hashedPasswordStoredInDb==givenPassword;
}

void ownerPasswordData::deleteOwnerPassword(const int owner_id){
    QSqlQuery query;
    query.prepare("DELETE FROM owner_password WHERE id = :owner_id");
    query.bindValue(":owner_id", owner_id);
    query.exec();
    query.clear();
    query.finish();
}
