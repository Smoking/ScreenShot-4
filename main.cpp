#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.initialize();
	
	QRect screen = QApplication::desktop()->availableGeometry(&w);
	QRect wGeo = w.geometry();
	
	w.move(screen.right() - wGeo.width() - 20,
		   screen.top() + 20);
	
	w.show();
	
	return a.exec();
}
