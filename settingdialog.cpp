#include "settingdialog.h"
#include "ui_settingdialog.h"

#include <QFileDialog>
#include "settings.h"

SettingDialog::SettingDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::SettingDialog)
{
	ui->setupUi(this);
}

SettingDialog::~SettingDialog()
{
	delete ui;
}

void SettingDialog::initialize()
{
	// 確定ボタンで設定を確定する
	connect(ui->b_finish, SIGNAL(clicked()),
			this, SLOT(finish()));
	
	// キャンセルボタンで設定を破棄して画面を閉じる
	connect(ui->b_cancel, SIGNAL(clicked()),
			this, SLOT(close()));
	
	// フォルダ選択ボタンがクリックされたらselectFolderを呼び出す
	connect(ui->b_folder, SIGNAL(clicked()),
			this, SLOT(selectFolder()));
	
	// ファイル名が編集されたらサンプルを更新する
	connect(ui->le_filename, SIGNAL(textChanged(QString)),
			this, SLOT(updateSample(QString)));
	
	// settingsクラスから設定を読み込む
	loadSettings();

	// ファイル名サンプル更新
	updateSample(ui->le_filename->text());
}

void SettingDialog::showDialog()
{
	// 設定を読み込んでから表示する
	loadSettings();
	show();
}

void SettingDialog::selectFolder()
{
	// QFileDialogによってユーザにフォルダを選択させる
	QString folder = QFileDialog::getExistingDirectory(this,"screenshot save folder");
	
	// pathラベルのテキストに、ユーザが選択したフォルダへのパスを設定する
	ui->l_path->setText(folder);
}

void SettingDialog::finish()
{
	// Settingsクラスに設定を反映する
	Settings::getInstance().setFilename(ui->le_filename->text());
	Settings::getInstance().setPath(ui->l_path->text());
	Settings::getInstance().setOpenDialog(ui->cb_openDialog->isChecked());
	this->close();
}

void SettingDialog::updateSample(QString format)
{
	QString sampleName = QDateTime::currentDateTime().toString(format);
	ui->lb_filenameSample->setText(sampleName + ".png");
}

void SettingDialog::loadSettings()
{
	// Settingsクラスから設定を読み込み、初期状態とする
	ui->l_path->setText(Settings::getInstance().path());
	ui->le_filename->setText(Settings::getInstance().filename());
	ui->cb_openDialog->setChecked(Settings::getInstance().openDialog());
	
}
