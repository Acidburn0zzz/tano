/****************************************************************************
* Tano - An Open IP TV Player
* Copyright (C) 2008-2010 Tadej Novak <tadej@tano.si>
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

#include "TimersEdit.h"
#include "ui_TimersEdit.h"

#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtGui/QCloseEvent>
#include <QtGui/QMessageBox>
#include <QtXml/QXmlSimpleReader>
#include <QtXml/QXmlInputSource>

#include "core/Settings.h"
#include "xml/TimersGenerator.h"

TimersEdit::TimersEdit(const QString &playlist,
					   QWidget *parent)
	: QMainWindow(parent),
	ui(new Ui::TimersEdit),
	_channel(0),
	_closeEnabled(false)
{
	ui->setupUi(this);
	ui->timersWidget->header()->setResizeMode(QHeaderView::Stretch);

	ui->dockWidgetContents->setDisabled(true);
	ui->playlistWidget->open(playlist);

	createSettings();
	createConnections();

	_handler = new TimersHandler(ui->timersWidget);

	read();
}

TimersEdit::~TimersEdit()
{
	delete ui;
	delete _handler;
}

void TimersEdit::changeEvent(QEvent *e)
{
	QMainWindow::changeEvent(e);
	switch (e->type()) {
		case QEvent::LanguageChange:
			ui->retranslateUi(this);
			break;
		default:
			break;
	}
}

void TimersEdit::closeEvent(QCloseEvent *event)
{
	event->ignore();
	exit();
}

void TimersEdit::createSettings()
{
	Settings *settings = new Settings(this);
	ui->toolBar->setToolButtonStyle(Qt::ToolButtonStyle(settings->toolbarLook()));
	_path = settings->path();
	delete settings;
}

void TimersEdit::createConnections()
{
	connect(ui->timersWidget, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)), this, SLOT(edit(QTreeWidgetItem*)));
	connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(newItem()));
	connect(ui->actionDelete, SIGNAL(triggered()), this, SLOT(deleteItem()));
	connect(ui->buttonCreate, SIGNAL(clicked()), this, SLOT(addItem()));
	connect(ui->playlistWidget->treeWidget(), SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)), this, SLOT(playlist(QTreeWidgetItem*)));

	connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(write()));
	connect(ui->actionClose, SIGNAL(triggered()), this, SLOT(exit()));

	connect(ui->editName, SIGNAL(textChanged(QString)), this, SLOT(editName(QString)));
	connect(ui->editType, SIGNAL(currentIndexChanged(int)), this, SLOT(editType(int)));
	connect(ui->editDate, SIGNAL(dateChanged(QDate)), this, SLOT(editDate(QDate)));
	connect(ui->editStartTime, SIGNAL(timeChanged(QTime)), this, SLOT(editStartTime(QTime)));
	connect(ui->editEndTime, SIGNAL(timeChanged(QTime)), this, SLOT(editEndTime(QTime)));
	connect(ui->checkBoxDisabled, SIGNAL(clicked()), this, SLOT(validate()));
}

void TimersEdit::exit()
{
	if(_closeEnabled) {
		hide();
		return;
	}

	int c;
	c = QMessageBox::warning(this, tr("Timers Editor"),
								   tr("Do you want close the editor?\nYou changes will not be applied."),
								   QMessageBox::Save | QMessageBox::Close | QMessageBox::Cancel,
								   QMessageBox::Save);

	switch (c) {
		case QMessageBox::Save:
			ui->actionSave->trigger();
			break;
		case QMessageBox::Close:
			_closeEnabled = true;
			ui->actionClose->trigger();
			break;
		case QMessageBox::Cancel:
			break;
		default:
			break;
	}
}

void TimersEdit::newItem()
{
	ui->toolBar->setDisabled(true);
	ui->dockWidgetContents->setDisabled(true);
	ui->mainWidget->setCurrentIndex(1);
}

void TimersEdit::deleteItem()
{
	ui->dockWidgetContents->setDisabled(true);
	_handler->deleteItem(ui->timersWidget->currentItem());
}

void TimersEdit::addItem()
{
	if(_channel == 0 || ui->editNameNew->text() == "") {
		QMessageBox::warning(this, tr("Tano"),
							tr("Please enter a name and select a channel from the list."));
		return;
	} else {
		for(int i = 0; i < ui->timersWidget->topLevelItemCount(); i++) {
			if(ui->timersWidget->topLevelItem(i)->text(0) == ui->editNameNew->text()) {
				QMessageBox::warning(this, tr("Tano"),
									tr("Timer with this name already exists. Please select another name."));
				return;
			}
		}
	}

	edit(_handler->newTimer(ui->editNameNew->text(), _channel->name(), ui->playlistWidget->fileName(), _channel->number(), _channel->url()));

	ui->dockWidgetContents->setDisabled(false);
	ui->toolBar->setDisabled(false);
	ui->mainWidget->setCurrentIndex(0);
}

void TimersEdit::playlist(QTreeWidgetItem *item)
{
	_channel = ui->playlistWidget->channelRead(item);
}

void TimersEdit::edit(QTreeWidgetItem *item)
{
	if(item == 0)
		return;

	ui->dockWidgetContents->setDisabled(false);

	ui->timersWidget->setCurrentItem(item);

	ui->checkBoxDisabled->setChecked(_handler->timerRead(item)->isDisabled());
	ui->editName->setText(_handler->timerRead(item)->name());
	ui->editChannel->setText(_handler->timerRead(item)->channel());
	ui->editNum->display(_handler->timerRead(item)->num());
	ui->editPlaylist->setText(_handler->timerRead(item)->playlist());
	ui->editUrl->setText(_handler->timerRead(item)->url());
	ui->editType->setCurrentIndex(Tano::timerType(_handler->timerRead(item)->type()));
	ui->editDate->setDate(_handler->timerRead(item)->date());
	ui->editStartTime->setTime(_handler->timerRead(item)->startTime());
	ui->editEndTime->setTime(_handler->timerRead(item)->endTime());
}

void TimersEdit::editName(const QString &name)
{
	for(int i = 0; i < ui->timersWidget->topLevelItemCount(); i++)
		if(ui->timersWidget->topLevelItem(i)->text(0) == name && ui->timersWidget->topLevelItem(i) != ui->timersWidget->currentItem()) {
			QMessageBox::warning(this, tr("Tano"),
								tr("Timer with this name already exists. Please select another name."));
			ui->editName->setText(ui->timersWidget->currentItem()->text(0));
			_handler->timerRead(ui->timersWidget->currentItem())->setName(ui->timersWidget->currentItem()->text(0));
			return;
		}

	ui->timersWidget->currentItem()->setText(0, name);
	_handler->timerRead(ui->timersWidget->currentItem())->setName(name);
}

void TimersEdit::editType(const int &type)
{
	_handler->timerRead(ui->timersWidget->currentItem())->setType(Tano::timerType(type));
	ui->timersWidget->currentItem()->setText(1, Tano::timerTypeString(Tano::timerType(type)));
}

void TimersEdit::editDate(const QDate &date)
{
	_handler->timerRead(ui->timersWidget->currentItem())->setDate(date);
}

void TimersEdit::editStartTime(const QTime &time)
{
	_handler->timerRead(ui->timersWidget->currentItem())->setStartTime(time);
	validate();
}

void TimersEdit::editEndTime(const QTime &time)
{
	_handler->timerRead(ui->timersWidget->currentItem())->setEndTime(time);
	validate();
}

void TimersEdit::read()
{
	QString fileName = _path + "timers.tano.xml";

	QXmlSimpleReader reader;
	reader.setContentHandler(_handler);
	reader.setErrorHandler(_handler);

	if(!QFileInfo(fileName).exists())
		return;

	QFile file(fileName);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("Tano"),
							tr("Cannot read file %1:\n%2.")
							.arg(fileName)
							.arg(file.errorString()));
		return;
	}

	QXmlInputSource xmlInputSource(&file);
	if (!reader.parse(xmlInputSource))
		return;
}

void TimersEdit::write()
{
	QString fileName = _path + "timers.tano.xml";

	QFile file(fileName);
	if (!file.open(QFile::WriteOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("Tano"),
							tr("Cannot write file %1:\n%2.")
							.arg(fileName)
							.arg(file.errorString()));
		return;
	}

	TimersGenerator *generator = new TimersGenerator(ui->timersWidget, _handler->timersMap());
	generator->write(&file);
	delete generator;

	_closeEnabled = true;
	exit();
}

void TimersEdit::validate()
{
	if(ui->editDate->date() < QDate::currentDate() ||
	   (ui->editDate->date() == QDate::currentDate() && ui->editEndTime->time() < QTime::currentTime()) ||
	   ui->checkBoxDisabled->isChecked())
	{
		_handler->timerRead(ui->timersWidget->currentItem())->setDisabled(true);
		ui->timersWidget->currentItem()->setText(2, tr("Disabled or expired"));
		ui->checkBoxDisabled->setChecked(true);
	} else {
		_handler->timerRead(ui->timersWidget->currentItem())->setDisabled(false);
		ui->timersWidget->currentItem()->setText(2, tr("Active"));
	}
}
