#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QFileDialog>
#include <QPixmap>
#include <QBuffer>
#include <QImage>
#include <QThread>

Widget::Widget(QWidget *parent) :
    QWidget(parent)
  , ui(new Ui::Widget)
  , _fileName("")
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_openButton_clicked()
{
    _fileName = QFileDialog::getOpenFileName();
    QPixmap img (_fileName);
    ui->pictureLabel->setPixmap(img.scaled(ui->pictureLabel->width(), ui->pictureLabel->height(), Qt::KeepAspectRatio));
}

void Widget::on_codeButton_clicked()
{
    ui->plainTextEdit->clear();
    QPixmap img (_fileName);
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    img.save(&buffer, "JPG");
    QString base64string = QString::fromLatin1(byteArray.toBase64().data());
    qDebug() << base64string;
    ui->plainTextEdit->insertPlainText(base64string);
}

void Widget::on_decodeButton_clicked()
{
    ui->pictureLabel->clear();
    qApp->processEvents();
    QThread::sleep(2);
    QString strbase64 = ui->plainTextEdit->toPlainText();
    QByteArray array = QByteArray::fromBase64(QByteArray().append(strbase64));
    QImage img = QImage::fromData(array, "JPG");
    QPixmap pix = QPixmap::fromImage(img);
    ui->pictureLabel->setPixmap(pix.scaled(ui->pictureLabel->width(), ui->pictureLabel->height(), Qt::KeepAspectRatio));
}
