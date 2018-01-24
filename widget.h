#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_openButton_clicked();

    void on_codeButton_clicked();

    void on_decodeButton_clicked();

private:
    Ui::Widget *ui;
    QString _fileName;
};

#endif // WIDGET_H
