#ifndef SETTINGS_H
#define SETTINGS_H

#include <QtCore>

class Settings
{
private:
	QString path_;
	QString filename_;
	QRect geometry_;
	bool openDialog_;
	
public:
	// singleton
	static Settings &getInstance(void);
	
	// getter/setter
	void setPath(const QString &path) { path_ = path; }
	void setFilename(const QString &filename) { filename_ = filename; }
	void setGeometry(const QRect &geometry) { geometry_ = geometry; }
	void setOpenDialog(const bool &openDialog) { openDialog_ = openDialog; }
	QString path(void){ return path_; }
	QString filename(void){ return filename_; }
	QRect geometry() const { return geometry_; }
	bool openDialog() const { return openDialog_; }
	
public slots:
	void writeData();
	
private:
	// singleton
	Settings();
	Settings(const Settings &){}
	Settings &operator=(const Settings &){}
	
	void readData();
	
	~Settings();
	
};

#endif // SETTINGS_H
