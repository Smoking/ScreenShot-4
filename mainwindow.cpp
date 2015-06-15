#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	settingDialog_(new SettingDialog(this)),
	screenShot_(new ScreenShot(this)),
	shadow_(new QGraphicsDropShadowEffect(this))
{
	ui->setupUi(this);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::initialize()
{
	settingDialog_->initialize();
	
	// 枠なし・ドロップシャドウ
	setAttribute(Qt::WA_TranslucentBackground);
	setWindowFlags(Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint);
	shadow_->setBlurRadius(20);
	shadow_->setColor(Qt::black);
	shadow_->setOffset(0);
	ui->widget->setGraphicsEffect(shadow_);
	
	// screenshot buttonのイベントフィルタ設定
	ui->b_screenshot->installEventFilter(this);
	
	connect(ui->b_screenshot, SIGNAL(clicked()),
			screenShot_, SLOT(startPartSelect()));
	connect(ui->b_setting, SIGNAL(clicked()),
			this->settingDialog_, SLOT(showDialog()));
	connect(ui->b_exit, SIGNAL(clicked()),
			this, SLOT(close()));
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
	if(obj == ui->b_screenshot){
		if(event->type() == QEvent::HoverEnter){
			screenShot_->takeWholeShot();
		}
	}
	return ui->b_screenshot->eventFilter(obj, event);
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
	clickedPos_ = e->pos();
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
	move(e->globalPos() - clickedPos_);
}
