#include "settings.h"

Settings &Settings::getInstance()
{
	static Settings settings;
	return settings;
}

Settings::Settings(){
	readData();
}

void Settings::readData()
{
	// setting.iniをini形式で開く
	QSettings settings("setting.ini", QSettings::IniFormat);
	settings.setIniCodec("UTF-8");

	// データを読み出し
	filename_ = settings.value("settings/filename").toString();
	path_ = settings.value("settings/path").toString();
	geometry_ = settings.value("settings/geometry").toRect();
	openDialog_ = settings.value("settings/openDialog").toBool();
}

void Settings::writeData()
{
	// setting.iniをini形式で開く
	QSettings settings("setting.ini", QSettings::IniFormat);
	settings.setIniCodec("UTF-8");
	
	// データを書出し
	settings.setValue("settings/filename", filename_);
	settings.setValue("settings/path", path_);
	settings.setValue("settings/geometry", geometry_);
	settings.setValue("settings/openDialog", openDialog_);
}

Settings::~Settings(){
	writeData();
}
