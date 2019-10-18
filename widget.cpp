#include "widget.h"
#include "ui_widget.h"
#include <QFile>
#include <QTextStream>
#include <QDial>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    QFile inputFile("/sys/class/backlight/panel-backlight/max_brightness");
    int max_brightness;
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       max_brightness = in.readLine().toInt();
       inputFile.close();
    }
    ui->dial->setMaximum(max_brightness);
    ui->dial->setMinimum(0);



    QFile brightnessFile("/sys/class/backlight/panel-backlight/brightness");
    int brightness;
    if (brightnessFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&brightnessFile);
       brightness = in.readLine().toInt();
       ui->dial->setValue(brightness);
       brightnessFile.close();
    }

    connect(ui->dial, &QDial::valueChanged, this, &Widget::update_brightness);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::update_brightness(int value)
{
    QFile inputFile("/sys/class/backlight/panel-backlight/brightness");
    if (inputFile.open(QIODevice::ReadWrite))
    {
       QTextStream out(&inputFile);
       out << value << endl;
       inputFile.close();
    }
}
