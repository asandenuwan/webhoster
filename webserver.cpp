#include "webserver.h"
#include <QDebug>
webserver::webserver() {server=new QTcpServer(this);}

void webserver::powerup(){
        connect(server,QTcpServer::newConnection,this,[=](){
            QTcpSocket*c=server->nextPendingConnection();
            clients.append(c);
            connect(c,QTcpSocket::readyRead,this,[=]{
                QByteArray msg=c->readAll();
                qDebug()<<msg;
                QString data="reqwest : {"+QString::fromUtf8(msg)+"}";
                this->respond(data,c);
                emit reqwest(data);
            });
        });
        server->listen(QHostAddress::Any,80);
}

void webserver::stopserver(){
    if(server->isListening()){server->close();}
    for(QTcpSocket* s:clients){
        s->disconnectFromHost();
        s->close();

        s->deleteLater();
    }
    clients.clear();
}

void webserver::respond(QString data,QTcpSocket* clientSock){
    QString filename;
    for(int i=0;i<data.size();i++){
        if(data[i]=='/'){
            i++;
            for(int a=i;i<data.size();a++){
                if(data[a]==' ')break;
                filename.push_back(data[a]);
            }
            break;
        }
    }
    qDebug()<<"filename : !"<<filename<<"!";
    if(filename==""){
        filename="index.html";
    }
    qDebug()<<"filename : !"<<filename<<"!";

    QString fileType;

    for(int i=0;i<filename.size();i++){
        if(filename[i]=='.'){
            i++;
            for(i=i;i<filename.size();i++){
                if(filename[i]=='\n')break;
                fileType.push_back(filename[i]);
            }
            break;
        }
    }

    qDebug()<<"filetype: "<<fileType;
    QString contentType;

    if (fileType == "html" || fileType == "htm") contentType = "text/html";
    else if (fileType == "css") contentType = "text/css";
    else if (fileType == "js") contentType = "application/javascript";
    else if (fileType == "png" )contentType = "image/png";
    else if (fileType == "jpg" || fileType == "jpeg") contentType = "image/jpeg";
    else if (fileType == "gif") contentType = "image/gif";
    else if (fileType == "svg") contentType = "image/svg+xml";
    else if (fileType == "json") contentType = "application/json";
    else if (fileType == "txt") contentType = "text/plain";

    //  Video
    else if (fileType == "mp4") contentType = "video/mp4";
    else if (fileType == "webm") contentType = "video/webm";
    else if (fileType == "ogg") contentType = "video/ogg";
    else if (fileType == "mov") contentType = "video/quicktime";
    else if (fileType == "avi") contentType = "video/x-msvideo";
    else if (fileType == "mkv") contentType = "video/x-matroska";

    //  Archive
    else if (fileType == "zip")contentType = "application/zip";
    else if (fileType == "rar")contentType = "application/vnd.rar";
    else if (fileType == "7z")contentType = "application/x-7z-compressed";
    else if (fileType == "tar")contentType = "application/x-tar";

    //  Executables
    else if (fileType == "exe")
        contentType = "application/vnd.microsoft.portable-executable";

    //  Documents
    else if (fileType == "pdf")contentType = "application/pdf";
    else if (fileType == "doc")contentType = "application/msword";
    else if (fileType == "docx")contentType = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";

    else{contentType = "application/octet-stream"; }// Fallback


    QFile f(filename);
    if(fileType=="html"||fileType=="htm"||fileType=="css"||fileType=="js"){
        if(!f.open(QIODevice::ReadOnly|QIODevice::Text)){
            emit reqwest(filename+" not found");
            qDebug()<<filename<<" file not found";
            f.close();
            return;
        }
        QTextStream t(&f);
        QString fileContent=t.readAll();
        QString response = "HTTP/1.1 200 OK\r\n";
        response += "Content-Type: " + contentType + "\r\n";
        response += "Content-Length: " + QString::number(fileContent.toUtf8().size()) + "\r\n";
        response += "\r\n"; // blank line
        response += fileContent;
        clientSock->write(response.toUtf8());
        clientSock->flush();
        f.close();
        emit reqwest(filename+" file sended");
    }

    else{
        if(!f.open(QIODevice::ReadOnly)){
            emit reqwest(filename+" not found");
            qDebug()<<filename<<" file not found";
            f.close();
            return;
        }
        QByteArray fileContent=f.readAll();

        QString header = "HTTP/1.1 200 OK\r\n";
        header += "Content-Type: "+contentType+"\r\n";  // Example: For an image (adjust MIME type as needed)
        header += "Content-Length: " + QByteArray::number(fileContent.size()) + "\r\n\r\n";
        clientSock->write(header.toUtf8());
        clientSock->write(fileContent);
        clientSock->flush();
        f.close();
        emit reqwest(filename+" file sended");
    }
}
