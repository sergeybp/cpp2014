#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QUdpSocket>
#include <QTextLayout>

#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, public Ui::MainWindow {
    Q_OBJECT
    public:
        MainWindow(QWidget *parent = 0);
    private slots:
        //Getting double click to update message field
        void itemDoubleClick(QListWidgetItem*);
        //Reading incoming message
        void readyRead();
        //Sending message
        void on_buttonSend_clicked();
        //Login
        void on_buttonLogin_clicked();

private:
        QUdpSocket *sendS;
        QString nickName = "";
};
#endif // MAINWINDOW_H
