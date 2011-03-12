/****************************************************************************
* Tano - An Open IP TV Player
* Copyright (C) 2011 Tadej Novak <tadej@tano.si>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/

#include "Recorder.h"
#include "ui_Recorder.h"

#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>

#include "container/Channel.h"
#include "core/Enums.h"
#include "core/RecorderController.h"
#include "core/RecorderProcess.h"
#include "core/Settings.h"
#include "ui/core/TrayIcon.h"
#include "ui/recorder/TimersEdit.h"

Recorder::Recorder(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::Recorder),
	_name(""),
	_url(""),
	_actionRecord(0),
	_trayIcon(0)
{
	ui->setupUi(this);

	_controller = new RecorderController("si.tano.TanoPlayer", "/Recorder",
										 QDBusConnection::sessionBus(), this);
	_recorder = new RecorderProcess(this);

	//Init
	connect(ui->buttonBrowse, SIGNAL(clicked()), this, SLOT(fileBrowse()));
	connect(ui->buttonRecord, SIGNAL(toggled(bool)), this, SLOT(record(bool)));

	connect(ui->playlistWidget, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(playlist(QTreeWidgetItem *)));

	connect(_controller, SIGNAL(elapsed(int)), this, SLOT(time(int)));
}

Recorder::~Recorder()
{
	delete ui;
	delete _controller;
}

void Recorder::changeEvent(QEvent *e)
{
	QWidget::changeEvent(e);
	switch (e->type()) {
		case QEvent::LanguageChange:
			ui->retranslateUi(this);
			break;
		default:
			break;
	}
}

void Recorder::createSettings()
{
	Settings *settings = new Settings(this);
	ui->fileEdit->setText(settings->recorderDirectory());
	delete settings;
}

void Recorder::stop()
{
	_controller->stop();
}

void Recorder::openPlaylist(const QString &file)
{
	_playlist = file;
	ui->playlistWidget->open(_playlist);
}

void Recorder::playlist(QTreeWidgetItem *clickedChannel)
{
	Channel *channel = ui->playlistWidget->channelRead(clickedChannel);

	_name = channel->name();
	_url = channel->url();

	ui->valueSelected->setText(channel->name());
}

void Recorder::fileBrowse()
{
	QString dir;
	if(ui->fileEdit->text().isEmpty())
		dir = QDir::homePath();
	else
		dir = ui->fileEdit->text();
	QString dfile =
			QFileDialog::getExistingDirectory(this, tr("Open directory"), dir,
											  QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if(!dfile.isEmpty())
		ui->fileEdit->setText(dfile);
}

void Recorder::record(const bool &status)
{
	if(status) {
		if(ui->fileEdit->text().isEmpty()) {
			ui->buttonRecord->setChecked(false);
			return;
		} else if(!QDir(ui->fileEdit->text()).exists()) {
			ui->buttonRecord->setChecked(false);
			QMessageBox::critical(this, tr("Recorder"),
						tr("Cannot write to %1.")
						.arg(ui->fileEdit->text()));
			return;
		} else if(ui->valueSelected->text().isEmpty()) {
			ui->buttonRecord->setChecked(false);
			QMessageBox::critical(this, tr("Recorder"),
						tr("Channel is not selected!"));
			return;
		}

		_controller->record(_name, _url, ui->fileEdit->text());

		ui->valueCurrent->setText(_name);
		if(_controller->isTimer())
			ui->valueEndTime->setText(""); // TODO: Timer end time
		else
			ui->valueEndTime->setText(tr("No timer - press button to stop."));
		ui->valueFile->setText(_controller->output());

		ui->buttonRecord->setText(tr("Stop recording"));
		if(_actionRecord)
			_actionRecord->setEnabled(true);

		if(_trayIcon) {
			_trayIcon->changeToolTip(Tano::Record, _name);
			_trayIcon->message(Tano::Record, QStringList() << _name << _controller->output());
		}
	} else {
		_controller->stop();

		ui->valueCurrent->setText("");
		ui->valueTime->setText("");
		ui->valueEndTime->setText(tr(""));
		ui->valueFile->setText("");

		ui->buttonRecord->setText(tr("Record"));
		if(_actionRecord)
			_actionRecord->setEnabled(false);

		if(_trayIcon) {
			_trayIcon->changeToolTip(Tano::Record);
			_trayIcon->message(Tano::Record, QStringList());
		}
	}
}

void Recorder::recordNow(const QString &name,
						 const QString &url)
{
	_name = name;
	_url = url;

	ui->valueSelected->setText(name);

	if(!_controller->isRecording())
		ui->buttonRecord->toggle();
}

void Recorder::time(const int &time)
{
	ui->valueTime->setText(QTime().addMSecs(time).toString("hh:mm:ss"));
}

void Recorder::setAction(QAction *action)
{
	_actionRecord = action;
	connect(_actionRecord, SIGNAL(triggered()), ui->buttonRecord, SLOT(toggle()));
}

void Recorder::setTrayIcon(TrayIcon *icon)
{
	_trayIcon = icon;
}

bool Recorder::isRecording() const
{
	return _controller->isRecording();
}

void Recorder::showTimersEditor()
{
	if(_editor) {
		if(_editor->isVisible()) {
			_editor->activateWindow();
		} else {
			delete _editor;
			_editor = new TimersEdit(_playlist, this);
			connect(_editor, SIGNAL(updateTimers()), _controller, SLOT(refreshTimers()));
			_editor->show();
		}
	} else {
		_editor = new TimersEdit(_playlist, this);
		connect(_editor, SIGNAL(updateTimers()), _controller, SLOT(refreshTimers()));
		_editor->show();
	}
}
