#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

#if defined(PLATFORM_X86)
    // PC test
    w.show();
    w.setGeometry(200, 100, 800, 600);
#elif defined(PLATFORM_ARM)
    w.showFullScreen();
#endif

    return a.exec();
}
