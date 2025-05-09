#ifndef PASSWORD_DATA_H
#define PASSWORD_DATA_H
#include <QByteArray>
#include <QIODevice>
#include <QCryptographicHash>
#include <QDateTime>
#include <QDataStream>
#include <QSqlQuery>
class passwordData
{
protected:
    int id;
    QByteArray salt;
    QByteArray hashedPassword;

public:
    int getId() const;
    const QByteArray &getSalt() const;
    const QByteArray &getHashedPassword() const;
    virtual void hashPassword(const QString& password);
};

#endif // PASSWORD_DATA_H
