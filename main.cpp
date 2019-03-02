#include "dialog.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
        try {
                QApplication a(argc, argv);
                Dialog w;
                w.setWindowTitle("simple side scroller");
                w.show();
                return a.exec();
        } catch (char const* e) {
                std::cout << e << std::endl;
        }
        return 0;
}
