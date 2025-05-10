#include "app.h"
#include "ui_main.h"

#include <QDebug>

app::app(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::app)
{
    ui->setupUi(this);
    ui->startServerBtn->setText("Start Server...");
    ui->startServerBtn->setStyleSheet("background-color: rgb(85, 85, 127);"
                                      "color: rgb(255, 255, 255);");
    VLayout=new QVBoxLayout;
    ui->fileBtnFrame->setLayout(VLayout);

    this->readFiles();
    ui->mainTabStac->setCurrentWidget(ui->filesTab);
    ws=new webserver();
    connect(ws,webserver::reqwest,ui->terminal,app::ui->terminal->appendPlainText);
}

void app::readFiles(){
    QDir dir(".\\");
    QStringList fileList=dir.entryList(QDir::Files);
    for(QString &fn:fileList){
        QPushButton* b=new QPushButton(fn,ui->fileBtnFrame);
        VLayout->addWidget(b);
        this->fileButtonList.append(b);

        b->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        b->setMinimumHeight(100);
        b->setStyleSheet("QPushButton {"
                         "border: 3px solid rgb(0, 255, 255);"
                         "border-radius: 5px;"
                         "color: rgb(0, 255, 255);"
                         "}"
                         "QPushButton:hover {"
                         "background-color: rgb(0, 255, 255);"
                         "color:black;"
                         "}"
);
        b->show();
        connect(b,&QPushButton::clicked,this,[=](){
            this->openFile(fn);
        });
    }
}

void app::refresh(){
    qDebug()<<"run3";
    for(QPushButton* b:this->fileButtonList){
        b->hide();
        b->deleteLater();
    }
    qDebug()<<"run4";
    this->fileButtonList.clear();
    qDebug()<<"run5";
    this->readFiles();
}

void app::openFile(QString name){
    fileData* f=new fileData();
    f->filename=name;
    connect(f,&fileData::deleter,this,&app::refresh);
    f->setupWindow();
}

void app::on_importFilesBtn_clicked(){
    QList<QUrl> l=QFileDialog::getOpenFileUrls(nullptr, "Select a file", QUrl(), "All Files (*.*)");
    for(QUrl a:l){
        QFile f(a.toLocalFile());

        if(a.fileName().endsWith(".html")||a.fileName().endsWith(".css")||a.fileName().endsWith(".js")){
            if(!f.open(QIODevice::ReadOnly|QIODevice::Text)){
                qDebug()<<"import file can't open";
                return;
            }
            ui->terminal->appendPlainText("server t: "+a.fileName()+" is upload to server");
            QTextStream s(&f);

            QFile lf(a.fileName());

            lf.open(QIODevice::WriteOnly|QIODevice::Text);

            QTextStream ts(&lf);
            ts<<s.readAll();

            lf.close();
        }
        else{
            if(!f.open(QIODevice::ReadOnly)){
                qDebug()<<"import file can't open";
                return;
            }
            ui->terminal->appendPlainText("server b: "+a.fileName()+" is upload to server");

            QFile lf(a.fileName());

            lf.open(QIODevice::WriteOnly);

            lf.write(f.readAll());

            lf.close();
        }
        f.close();
        this->refresh();
    }
}


app::~app(){
    delete ui;
}




void app::on_startServerBtn_clicked()
{
    this->serverOnStop=!serverOnStop;
    if(this->serverOnStop){
        ui->startServerBtn->setText("Stop Server...");
        ui->startServerBtn->setStyleSheet("        background-color: rgb(255, 0, 0);"
                                          "color: rgb(255, 255, 255);");
        ws->powerup();
        ui->terminal->appendPlainText("server : online");
    }
    else{
        ui->startServerBtn->setText("Start Server...");
        ui->startServerBtn->setStyleSheet("background-color: rgb(85, 85, 127);"
                                          "color: rgb(255, 255, 255);");
        ws->stopserver();
        ui->terminal->appendPlainText("server : offline");
    }
}

