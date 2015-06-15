#include "screenshot.h"

#include <QApplication>
#include <QDesktopWidget>

#include <QGuiApplication>
#include <QScreen>


#include <QPainter>
#include <QDebug>
#include "save.h"

ScreenShot::ScreenShot(QWidget *parent) :
	QDialog(parent)
{
}

void ScreenShot::startPartSelect()
{
	// スクリーン切り出し範囲を初期化
	start_ = QPoint(0, 0);
	end_ = QPoint(0, 0);
	qDebug() << parentWidget();
	// フルスクリーンでウィンドウを表示
	setGeometry(QApplication::desktop()->screenGeometry());
	showFullScreen();
}

void ScreenShot::takeWholeShot()
{
	// 現在のスクリーンショットを撮影
	pixmap_ = QGuiApplication::screens().at(0)->grabWindow(QApplication::desktop()->winId());
}

void ScreenShot::paintEvent(QPaintEvent *)
{
	// 線なしペインタを生成
	QPainter painter(this);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(Qt::NoPen);
	
	// スクリーンの大きさを取得
	QRect screenRect = QApplication::desktop()->screen(0)->rect();
	
	// 全体スクリーンショット画像を自身に描画
	painter.drawPixmap(screenRect,pixmap_);
	
	// 選択した範囲以外を塗りつぶすパスを作成(ちょっと角丸)
	QPainterPath path;
	path.addRect(screenRect);
	path.addRoundedRect(QRect(start_, end_), 8, 8);
	
	// 選択した範囲以外を塗りつぶすパスを描画
	painter.setBrush(QBrush(QColor(0,0,0,100)));
	painter.drawPath(path);
}

void ScreenShot::mouseMoveEvent(QMouseEvent *e)
{
	// マウスが動くたびに再描画かける必要あり
	end_ = e->pos();
	repaint();
}

void ScreenShot::mousePressEvent(QMouseEvent *e)
{
	// クリックされたら範囲指定開始。始点を設定する
	start_ = e->pos();
}

void ScreenShot::mouseReleaseEvent(QMouseEvent *e)
{
	// マウスがドラッグを終了したら範囲指定終了。
	end_ = e->pos();
	takePartShot();
}

void ScreenShot::takePartShot()
{
	// startがendよりも原点から遠ければ入れ替える
	if(start_.manhattanLength() > end_.manhattanLength()){
		qSwap(start_, end_);
	}
	
	// 全体スクリーンショットから指定範囲をコピーする
	QPixmap pixmap = pixmap_.copy(QRect(start_, end_));
	
	// 保存する
	Save::save(pixmap);
	
	// windowを閉じる。
	this->close();
}
