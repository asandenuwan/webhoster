#ifndef FILEDATA_H
#define FILEDATA_H

#include <QWidget>
#include <QString>
#include <QFile>
#include <QTextStream>


namespace Ui {
class fileData;
}

class fileData : public QWidget
{
    Q_OBJECT

public:
    QString filename;
    void setupWindow();
    explicit fileData(QWidget *parent = nullptr);
    ~fileData();

signals:
    void deleter();

private slots:
    void on_deleteBtn_clicked();

    void on_saveBtn_clicked();

private:
    Ui::fileData *ui;
};

#endif // FILEDATA_H
