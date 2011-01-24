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

#include <QtCore/QFile>
#include <QtGui/QMessageBox>

#include "PlaylistWidget.h"
#include "ui_PlaylistWidget.h"

#include "container/Channel.h"
#include "playlist/M3UGenerator.h"

PlaylistWidget::PlaylistWidget(QWidget *parent)
	: QWidget(parent),
	ui(new Ui::PlaylistWidget)
{
	ui->setupUi(this);
	ui->treeWidget->header()->setResizeMode(QHeaderView::ResizeToContents);

	_handler = new M3UHandler(ui->treeWidget);

	connect(ui->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SIGNAL(itemClicked(QTreeWidgetItem*, int)));
	connect(ui->categoryBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(processPlaylist()));
	connect(ui->languageBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(processPlaylist()));
	connect(ui->searchEdit, SIGNAL(textChanged(QString)), this, SLOT(processPlaylist()));
}

PlaylistWidget::~PlaylistWidget()
{
	delete ui;
	delete _handler;
}

void PlaylistWidget::changeEvent(QEvent *e)
{
	QWidget::changeEvent(e);
	switch (e->type()) {
		case QEvent::LanguageChange:
			ui->retranslateUi(this);
			ui->categoryBox->setItemText(0, tr("All categories"));
			ui->languageBox->setItemText(0, tr("All languages"));
			break;
		default:
			break;
	}
}

void PlaylistWidget::clear()
{
	_handler->clear();
}

void PlaylistWidget::open(const QString &file)
{
	_handler->clear();

	if (file.isEmpty())
		return;

	_fileName = file;

	QFile f(_fileName);
	if (!f.open(QFile::ReadOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("Tano"),
							tr("Cannot read file %1:\n%2.")
							.arg(_fileName)
							.arg(f.errorString()));
		return;
	}

	_handler->processFile(_fileName);

	ui->categoryBox->clear();
	ui->categoryBox->insertItem(0,tr("All categories"));
	ui->categoryBox->insertItems(1,_handler->categories());

	ui->languageBox->clear();
	ui->languageBox->insertItem(0,tr("All languages"));
	ui->languageBox->insertItems(1,_handler->languages());

	ui->treeWidget->sortByColumn(0, Qt::AscendingOrder);
}

void PlaylistWidget::save(const QString &name,
						  const QString &file)
{
	QFile f(file);
	if (!f.open(QFile::WriteOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("Tano"),
							tr("Cannot write file %1:\n%2.")
							.arg(file)
							.arg(f.errorString()));
		return;
	}

	M3UGenerator *generator = new M3UGenerator(ui->treeWidget, name, _handler->channelMap());
	generator->write(&f);
	delete generator;
}

void PlaylistWidget::processPlaylist()
{
	for(int i=0; i<ui->treeWidget->topLevelItemCount(); i++)
		ui->treeWidget->topLevelItem(i)->setHidden(false);

	if(ui->categoryBox->currentText() != tr("All categories"))
		for(int i=0; i<ui->treeWidget->topLevelItemCount(); i++)
			if(!ui->treeWidget->topLevelItem(i)->text(2).contains(ui->categoryBox->currentText(), Qt::CaseInsensitive))
				ui->treeWidget->topLevelItem(i)->setHidden(true);

	if(ui->languageBox->currentText() != tr("All languages"))
		for(int i=0; i<ui->treeWidget->topLevelItemCount(); i++)
			if(!ui->treeWidget->topLevelItem(i)->text(3).contains(ui->languageBox->currentText(), Qt::CaseInsensitive))
				ui->treeWidget->topLevelItem(i)->setHidden(true);

	if(ui->searchEdit->text() != "")
			for(int i=0; i<ui->treeWidget->topLevelItemCount(); i++)
				if(!ui->treeWidget->topLevelItem(i)->text(1).contains(ui->searchEdit->text(), Qt::CaseInsensitive))
					ui->treeWidget->topLevelItem(i)->setHidden(true);

}

QTreeWidgetItem *PlaylistWidget::createItem(const QString &name,
											const QString &url)
{
	QTreeWidgetItem *newI = _handler->createChannel(name, url);
	ui->treeWidget->sortByColumn(0, Qt::AscendingOrder);
	return newI;
}

void PlaylistWidget::deleteItem()
{
	_handler->deleteChannel(ui->treeWidget->currentItem());
	ui->treeWidget->sortByColumn(0, Qt::AscendingOrder);
}

void PlaylistWidget::import(const QString &file)
{
	_handler->clear();
	_handler->importOldFormat(file);
}

void PlaylistWidget::editMode()
{
	ui->labelCategory->hide();
	ui->categoryBox->hide();
	ui->labelLanguage->hide();
	ui->languageBox->hide();
}

QTreeWidget *PlaylistWidget::treeWidget()
{
	return ui->treeWidget;
}
