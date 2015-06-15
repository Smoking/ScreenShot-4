#ifndef SAVE_H
#define SAVE_H

#include <QtCore>

class Save
{
public:
	Save();
	static void save(QPixmap pixmap);
	static void open(QString filepath);
};

#endif // SAVE_H
