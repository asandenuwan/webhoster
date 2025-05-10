#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <QObject>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QByteArray>
#include <QVector>
#include <QFile>
#include <QTextStream>

class webserver:public QObject{
    Q_OBJECT
public:
    webserver();
    void powerup();
    void stopserver();
private:
    void respond(QString data,QTcpSocket* clientSock);
    QVector<QTcpSocket*> clients;
    QTcpServer* server;
signals:
    void reqwest(QString msg);
};

#endif // WEBSERVER_H
