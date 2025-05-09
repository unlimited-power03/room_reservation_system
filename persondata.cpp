#include "persondata.h"

//personData::personData() {}
int personData::getId() const{
    return id;
}

void personData::setId(int given_id){
    id = given_id;
}
const QString &personData::getFirstName() const{
    return firstName;
}

void personData::setFirstName(QString given_name){
    firstName = given_name;
}
const QString &personData::getSurname()const{
    return surname;
}

void personData::setSurname(QString given_surname){
    surname = given_surname;
}

const QString &personData::getEmail() const{
    return email;
}

void personData::setEmail(QString given_email){
    email = given_email;
}



const QString &personData::getTelephoneNumber() const{
    return telephoneNumber;
}


bool personData::doesEmailExists(QString given_email){ //for editing email and sign_in
    bool result=false;
    QSqlQuery query;
    query.prepare("SELECT email FROM users UNION SELECT email FROM owner");
    query.exec();
    while(query.next()){
        if(given_email.compare(query.value(0).toString(), Qt::CaseInsensitive) == 0){
            result=true;
            break;
        }
    }
    query.clear();
    query.finish();
    return result;
}

bool personData::doesTelephoneNumberExists(QString given_number){ //for editing email and sign_in
    bool result=false;
    QSqlQuery query;
    query.prepare("SELECT telephone_number FROM users WHERE telephone_number= :given_number UNION SELECT telephonenumber FROM owner WHERE telephonenumber = :given_number");
    query.bindValue(":given_number", given_number);
    query.exec();
    while(query.next()){
        result=true;
    }
    query.clear();
    query.finish();
    return result;
}
