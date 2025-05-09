#include "ownerdata.h"

std::pair<bool,int> ownerData::searchForOwnerEmail(QString email){
    bool result = false;
    QSqlQuery query;
    query.prepare("SELECT id,email FROM owner WHERE email = :given_email");
    query.bindValue(":given_email", email);
    query.exec();
    while(query.next()){
        result=true;
        id=query.value(0).toInt();
    }
    query.clear();
    query.finish();
    return std::make_pair(result, id);
}

void ownerData::insertPersonToDb(const QString &firstName, const QString &surname, const QString &email, const QString &telephoneNumber){
    QSqlQuery query;
    query.prepare("INSERT INTO owner(firstname,surname,email,telephonenumber) VALUES (:firstName, :surname, :email, :telephoneNumber)");
    query.bindValue(":firstName", firstName);
    query.bindValue(":surname", surname);
    query.bindValue(":email", email);
    query.bindValue(":telephoneNumber", telephoneNumber);
    query.exec();
    query.clear();
    query.finish();
}

QVector<ownerData> ownerData::getOwnerNameFromDb(const int id){
    QVector <ownerData> name;
    QSqlQuery query;
    query.prepare("SELECT firstname, surname, email, telephonenumber FROM owner WHERE id = :id");
    query.bindValue(":id",id);
    query.exec();
    while(query.next()){
        ownerData tmp;
        tmp.firstName = query.value(0).toString();
        tmp.surname = query.value(1).toString();
        tmp.email = query.value(2).toString();
        tmp.telephoneNumber = query.value(3).toString();
        name.append(tmp);
    }
    query.clear();
    query.finish();
    return name;
}

void ownerData::editOwnerData(const int id, const QString &email, const QString &telephoneNumber){
    QSqlQuery query;
    query.prepare("UPDATE owner SET email=:email, telephonenumber = :telephoneNumber WHERE id = :id");
    query.bindValue(":email",email);
    query.bindValue(":telephoneNumber",telephoneNumber);
    query.bindValue(":id",id);
    query.exec();
    query.clear();
    query.finish();
}

void ownerData::deleteOwner(const int id){
    QSqlQuery query;
    query.prepare("DELETE FROM owner WHERE id = :id");
    query.bindValue(":id",id);
    query.exec();
    query.clear();
    query.finish();
}
