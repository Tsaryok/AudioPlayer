#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
//#include <bass/include/bass.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    /* проверка версии BASS
        if (HIWORD(BASS_GetVersion())!=BASSVERSION) {
        return 1;
    }
    if (!BASS_Init (-1, 22050, BASS_DEVICE_3D , 0, NULL)) {
        return 1;
    }

            ... работаем со звуком ...
    */
    //BASS_Free ();
    return a.exec();

}
