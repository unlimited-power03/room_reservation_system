#include "userdata.h"

std::pair<bool,int> userdata::searchForUserEmail(QString email){
    bool result = false;
    QSqlQuery query;
    query.prepare("SELECT id,email FROM users WHERE email = :given_email");
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

void userdata::insertPersonToDb(const QString &firstName, const QString &surname, const QString &email, const QString &telephoneNumber){
    QSqlQuery query;
    query.prepare("INSERT INTO users(first_name,surname,email,telephone_number) VALUES (:firstName, :surname, :email, :telephoneNumber)");
    query.bindValue(":firstName", firstName);
    query.bindValue(":surname", surname);
    query.bindValue(":email", email);
    query.bindValue(":telephoneNumber", telephoneNumber);
    query.exec();
    query.clear();
    query.finish();
}

QVector <userdata> userdata::getUserNameFromDb(const int id){
    QVector <userdata> name;
    QSqlQuery query;
    query.prepare("SELECT first_name, surname, email, telephone_number FROM users WHERE id = :id");
    query.bindValue(":id",id);
    query.exec();
    while(query.next()){
        userdata tmp;
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

void userdata::editUserData(const int user_id, const QString &user_email, const QString &user_telephone_number){
    QSqlQuery query;
    query.prepare("UPDATE users SET email=:user_email, telephone_number = :user_telephone_number WHERE id = :user_id");
    query.bindValue(":user_id",user_id);
    query.bindValue(":user_email",user_email);
    query.bindValue(":user_telephone_number",user_telephone_number);
    query.exec();
    query.clear();
    query.finish();
}

void userdata::deleteUser(int user_id){
    QSqlQuery query;
    query.prepare("DELETE FROM users WHERE id = :user_id");
    query.bindValue(":user_id",user_id);
    query.exec();
    query.clear();
    query.finish();
}


