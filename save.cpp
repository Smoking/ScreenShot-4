#include "save.h"

#include <qpixmap.h>
#include <QDesktopServices>
#include "settings.h"

Save::Save()
{
}

void Save::save(QPixmap pixmap)
{
	QString filepath = Settings::getInstance().path();
	QString filename = QDateTime::currentDateTime().toString(
				Settings::getInstance().filename());
	
	filepath += "/";
	filepath += filename;
	filepath += ".png";
	
	pixmap.save(filepath);
	
	if(Settings::getInstance().openDialog()){
		open(Settings::getInstance().path());
	}
}

void Save::open(QString filepath)
{
	QDesktopServices::openUrl(QUrl(filepath, QUrl::TolerantMode));
}
