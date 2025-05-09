#include "login.h"
#include <QApplication>
#include <QSqlDatabase>
#include <QFile>
#include <QTextStream>

bool loadEnv(const QString &filename) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Nie można otworzyć pliku .env";
        return false;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty() || line.startsWith("#")) {
            continue;
        }

        QStringList parts = line.split("=");
        if (parts.size() == 2) {
            qputenv(parts[0].toUtf8(), parts[1].toUtf8());
        }
    }
    file.close();
    return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(!loadEnv("config.env")){
        return -1;
    }

    QString db_user_name = qgetenv("DB_USER_NAME");
    QString db_host_name = qgetenv("DB_HOST_NAME");
    int db_port = qEnvironmentVariableIntValue("DB_PORT");
    QString db_password = qgetenv("DB_PASSWORD");
    QString db_name = qgetenv("DB_NAME");

    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setUserName(db_user_name);
    db.setHostName(db_host_name);
    db.setPort(db_port);
    db.setPassword(db_password);
    db.setDatabaseName(db_name);
    db.open();
    login w;
    w.show();

    int result = a.exec();

    db.close();
    return result;
}

