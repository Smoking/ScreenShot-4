#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsDropShadowEffect>
#include "screenshot.h"
#include "settingdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT
private:
	Ui::MainWindow *ui;
	SettingDialog *settingDialog_;
	ScreenShot *screenShot_;
	QPoint clickedPos_;
	QGraphicsDropShadowEffect *shadow_;
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	void initialize();
	
protected:
	bool eventFilter(QObject *obj, QEvent *event);
	void mousePressEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
};

#endif // MAINWINDOW_H
