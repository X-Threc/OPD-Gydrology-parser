#include "mainwindow.h"
#include <QApplication>
#include <locale.h>
#include <QTranslator>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"rus");
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("POGA");
    w.show();
    return a.exec();
}
