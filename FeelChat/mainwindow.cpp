#include "mainwindow.h"

#include <QRegExp>
#include <string>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUi(this);
    Login->setText("Nickname");
    QString a = "Welcome to FeelChat! \n Set your Nickname and have fun! \n Double tap on UserName or on Message \n will insert UserName in message text field! \n Budkov sergey 2536";
    new QListWidgetItem(QPixmap(),a, ChatMesseges);
    QUdpSocket* tmp = new QUdpSocket(this);
    tmp->bind(QHostAddress::Any, 2500);
    sendS = tmp;
    connect(sendS, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(this->Users, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(itemDoubleClick(QListWidgetItem*)));
    connect(this->ChatMesseges, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(itemDoubleClick(QListWidgetItem*)));
}


void MainWindow::itemDoubleClick(QListWidgetItem *item)
{

    Message->clear();

    if(item->listWidget() == Users)
    {
        Message->setText(item->text() + ", ");

    }
    else
    {

        QString s = item->text();
        QString res = "";
        for(int i = 0 ; i < s.size();i++)
        {
            if(s[i] == ':')
                break;
            res+=s[i];
        }
        Message->setText(res + ", ");

    }


}


void MainWindow::readyRead()
{
    for(;;)
    {
    if(sendS->hasPendingDatagrams())
    {
        QByteArray buffer;
        buffer.resize(sendS->pendingDatagramSize());
        QHostAddress sender;
        quint16 port;
        sendS->readDatagram(buffer.data(), buffer.size(), &sender, &port);
        QString line = QString::fromUtf8(buffer).trimmed();
        QString s = line;
        QString nick = "";
        for(int i = 0 ; i < s.size();i++)
        {
            if(s[i] == ':')
                break;
            nick+=s[i];
        }
        bool toShow = true;
        for(int i = 0 ; i < Users->count();i++)
        {
            if(Users->item((i))->text() == nick)
                toShow = false;
        }
        if(toShow)
            new QListWidgetItem(QPixmap(), nick, Users );
        new QListWidgetItem(QPixmap(),line, ChatMesseges);


    }
    else
        return;
    }
}








void MainWindow::on_buttonSend_clicked()
{
    if(this->nickName == "")
    {
        Message->setText("Set nickname first!");
        return;
    }
    if(Message->toPlainText() == "")
    {
        return;
    }
    QString toSend = this->nickName + ":->"+ Message->toPlainText();
    QByteArray message;
    message.append(toSend);
    sendS->writeDatagram(message.data(), message.size(), QHostAddress::Broadcast, 2500);
    Message->setText("");
}

void MainWindow::on_buttonLogin_clicked()
{
    if(this->nickName !="")
    {
        Login->setText("Already set!");
        return;
    }
    if(Login->text()=="")
    {
        Login->setText("Insert your nickname");
    }
    this->nickName = Login->text();

    Login->setText("Have a good time!");
    Message->setText(this->nickName);
    QString toSend = this->nickName + ":-> Hey,guys, I'm now using FeelChat";
    QByteArray message;
    message.append(toSend);
    sendS->writeDatagram(message.data(), message.size(), QHostAddress::Broadcast, 2500);
}
