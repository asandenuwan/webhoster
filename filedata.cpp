#include "filedata.h"
#include "ui_filedata.h"

#include <QDebug>

fileData::fileData(QWidget *parent): QWidget(parent), ui(new Ui::fileData){
    ui->setupUi(this);
}

void fileData::setupWindow(){
    QFile f(filename);
    if(!f.open(QIODevice::ReadOnly | QIODevice::Text)){
    }
    QTextStream text(&f);
    while (!text.atEnd()) {
        ui->dataPianText->appendPlainText(text.readLine());
    }
    f.close();
    this->show();
}
fileData::~fileData()
{
    delete ui;
}

void fileData::on_deleteBtn_clicked()
{
    QFile f(this->filename);
    if(!f.exists()){
        return;
    }
    qDebug()<<"run1";
    f.remove();
    qDebug()<<"run2";
    if(!f.exists()){
        emit deleter();
        this->close();
    }
}


void fileData::on_saveBtn_clicked()
{
    QFile f(this->filename);
    if(f.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream text(&f);
        text<<ui->dataPianText->toPlainText();
        f.close();
        this->close();
    }else{
        qDebug()<<"file open error";
    }
}

