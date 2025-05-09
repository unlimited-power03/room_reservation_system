#ifndef OWNER_PASSWORD_DATA_H
#define OWNER_PASSWORD_DATA_H
#include "password_data.h"
#include "session_manager.h"
#include "ownerdata.h"
class ownerPasswordData : public passwordData
{
private:
    ownerData oD;
public:
    void hashPassword(const QString& password) override;
    void editOwnerPassword(const QString& password, int owner_id);
    bool checkOwnerPassword(const QString &password, const int index_for_given_email);
    void deleteOwnerPassword(const int owner_id);
};

#endif // OWNER_PASSWORD_DATA_H
