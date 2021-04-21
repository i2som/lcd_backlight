#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QDebug>
#include <QScreen>
#include <QResizeEvent>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void update_brightness(int);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
