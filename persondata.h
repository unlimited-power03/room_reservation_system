#ifndef PERSONDATA_H
#define PERSONDATA_H
#include <QVector>
#include <QSqlQuery>
class personData
{
protected:
    int id;
    QString firstName;
    QString surname;
    QString email;
    QString telephoneNumber;
public:
    int getId() const;
    void setId(int given_id);
    const QString &getFirstName() const;
    void setFirstName(QString given_name);
    const QString &getSurname() const;
    void setSurname(QString given_surname);
    const QString &getEmail() const;
    void setEmail(QString given_email);
    const QString &getTelephoneNumber() const;
    bool doesEmailExists(QString given_email);
    bool doesTelephoneNumberExists(QString given_number);
};

#endif // PERSONDATA_H
