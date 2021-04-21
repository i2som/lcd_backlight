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

void Widget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);

    qDebug() << endl << "Window Resize:" << this->size();

    // 屏幕长宽
    QList<QScreen*> scr = QGuiApplication::screens();
    QRect rect = scr.at(0)->geometry();
    quint32 desktop_wid = rect.width();
    quint32 desktop_hei = rect.height();

    // 根据不同屏幕分辨率, 调节字体大小
    QString style_str;
    if (desktop_wid >= 1280 && desktop_hei >= 720) {
        qDebug() << "1280*720";
        style_str = QString("font: 20pt \"WenQuanYi Micro Hei Mono\";");
    } else if (desktop_wid >= 800 && desktop_hei >= 600) {
        qDebug() << "800*600";
        style_str = QString("font: 10pt \"WenQuanYi Micro Hei Mono\";");
    }

    ui->label->setStyleSheet(style_str);
    ui->exitButton->setStyleSheet(style_str);
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
