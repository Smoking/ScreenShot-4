#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QDialog>
#include <QMouseEvent>

class ScreenShot : public QDialog
{
	Q_OBJECT
private:
	QPixmap pixmap_; // 範囲指定開始時点での画面全体のキャプチャ
	QPoint start_;   // 指定範囲 左上
	QPoint end_;     // 指定範囲 右下
	
public:
	explicit ScreenShot(QWidget *parent = 0);
	
public slots:
	void startPartSelect();
	void takeWholeShot();
	
protected:
	void paintEvent(QPaintEvent *);
	
protected:
	void mouseMoveEvent(QMouseEvent *e);
	void mousePressEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
	
private:
	void takePartShot();
};

#endif // SCREENSHOT_H
