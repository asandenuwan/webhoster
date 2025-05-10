#ifndef APP_H
#define APP_H

#include <QMainWindow>
#include <QPushButton>
#include <QDir>
#include <QStringList>
#include <QVector>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QUrl>
#include <QTextStream>
#include <QThread>

#include "filedata.h"
#include "webserver.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class app;
}
QT_END_NAMESPACE

class app : public QMainWindow
{
    Q_OBJECT

public:
    QVBoxLayout* VLayout;
    app(QWidget *parent = nullptr);
    ~app();

private slots:
    void on_importFilesBtn_clicked();

private:
    webserver* ws;
    bool serverOnStop=false;
    QVector <QPushButton*> fileButtonList;
    void readFiles();
    void openFile(QString name);
    Ui::app *ui;
private slots:
    void refresh();
    void on_startServerBtn_clicked();
};
#endif // APP_H
