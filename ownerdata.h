#ifndef OWNERDATA_H
#define OWNERDATA_H
#include "persondata.h"
class ownerData : public personData
{
public:
    std::pair<bool,int> searchForOwnerEmail(QString email);
    void insertPersonToDb(const QString &firstName, const QString &surname, const QString &email, const QString &telephoneNumber);
    QVector<ownerData> getOwnerNameFromDb(const int id);
    void editOwnerData(const int id, const QString &email, const QString &telephoneNumber);
    void deleteOwner(const int id);
};

#endif // OWNERDATA_H
