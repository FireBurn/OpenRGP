#include <QApplication>
#include "MainWindow.h"
int main(int argc,char**argv){
    QApplication a(argc,argv);
    a.setApplicationName("OpenRGP");
    MainWindow w;
    if(argc>1) w.openFile(QString::fromLocal8Bit(argv[1]));
    w.show();
    // openrgp_gui <file> --screenshot <dir>: write one PNG per tab and exit (documentation and smoke tests)
    if(argc>3 && QString(argv[2])=="--screenshot"){
        for(int i=0;i<w.tabCount();i++){ w.setTab(i); QApplication::processEvents(); w.grab().save(QString("%1/tab%2.png").arg(argv[3]).arg(i)); }
        return 0;
    }
    return a.exec();
}
