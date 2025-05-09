#include "password_data.h"

int passwordData::getId() const{
    return id;
}

const QByteArray &passwordData::getSalt() const{
    return salt;
}

const QByteArray &passwordData::getHashedPassword() const{
    return hashedPassword;
}

void passwordData::hashPassword(const QString &password){
    salt.clear();
    hashedPassword.clear();
    QDataStream text(&salt, QIODevice::WriteOnly);
    QDateTime current_time = QDateTime::currentDateTime();
    qint64 timestamp = current_time.toMSecsSinceEpoch();

    qint64 counter = current_time.time().msecsSinceStartOfDay();
    text << timestamp << counter;

    QByteArray prepare_to_hash = password.toUtf8() + salt;
    hashedPassword = QCryptographicHash::hash(prepare_to_hash,QCryptographicHash::Sha256);
    qDebug() << salt;
    qDebug() << hashedPassword;
}
