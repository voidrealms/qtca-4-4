#include <QCoreApplication>
#include <QDebug>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QPluginLoader>
#include <QVariant>


//Selecting data from the database
// SELECT id,age,name FROM voidrealms.users where age > 40;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qInfo() << "Opening the database";
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost"); // 127.0.0.1
    db.setUserName("USERNAME");  //Change the username
    db.setPassword("PASSWORD"); //Change the password

    if(!db.open())
    {
        qInfo() << "Could not open connection!";
        qInfo() << db.lastError().text();
    }
    else
    {
        qInfo() << "Connected, lets make a query...";
        QSqlQuery query;
        QString cmd;
        cmd = "SELECT id,age,name FROM voidrealms.users where age > 40;";

        if(!query.exec(cmd))
        {
            qInfo() << db.lastError().text();
            qInfo() << query.lastError().text();
        }
        else
        {
            qInfo() << "Got query results: " << query.size();

            while (query.next())
            {
                int id = query.value(0).toInt();
                int age = query.value(1).toInt();
                QString name = query.value(2).toString();

                qInfo() << "id: " << id << " name: " << name << " is " << age;
            }
        }

        db.close();
        qInfo() << "Disconnected";

    }

    return a.exec();
}
