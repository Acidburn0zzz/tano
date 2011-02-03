/****************************************************************************
* Tano - An Open IP TV Player
* Copyright (C) 2011 Tadej Novak <tadej@tano.si>
*
* The UI layout was based on the VLMC About dialog
* Copyright (C) 2008-2010 VideoLAN
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

#include <QtCore/QDate>
#include <QtCore/QFile>

#include <vlc-qt/Instance.h>

#include "AboutDialog.h"
#include "ui_AboutDialog.h"

#include "core/Common.h"
#include "core/PluginsLoader.h"

AboutDialog::AboutDialog(const QString &type,
						 QWidget *parent)
	: QDialog(parent),
	ui(new Ui::AboutDialog)
{
	ui->setupUi(this);

	ui->labelTitle->setText(ui->labelTitle->text().arg(type, Tano::version(), Tano::changeset()));
	ui->labelBuild->setText(ui->labelBuild->text().arg(Tano::buildHostname(), Tano::buildSystem(), qVersion(), VlcInstance::libVersion()));
	ui->labelCopyright->setText(ui->labelCopyright->text().arg(QDate::currentDate().toString("yyyy")));
	ui->labelBackendInfo->setText(ui->labelBackendInfo->text().arg(VlcInstance::version()));
	ui->labelBackendVersion->setText(ui->labelBackendVersion->text().arg(VlcInstance::libVersion()));

	QFile file(":/info/AUTHORS");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return;

	ui->authors->setPlainText(QString::fromUtf8(file.readAll()));

	_icon = QIcon(":/icons/24x24/plugin.png");

	_recorder = new QTreeWidgetItem(ui->pluginsWidget);
	_recorder->setText(0, tr("Recorder Plugins"));
	ui->pluginsWidget->setItemExpanded(_recorder, true);

	QFont font = _recorder->font(0);
	font.setBold(true);
	_recorder->setFont(0, font);

	PluginsLoader *loader = new PluginsLoader();
	for(int i = 0; i < loader->recorderPlugin().size(); i++)
		populatePluginsTreeWidget(loader->recorderFile()[i], loader->recorderName()[i], "Recorder");
	delete loader;
}

AboutDialog::~AboutDialog()
{
	delete ui;
}

void AboutDialog::changeEvent(QEvent *e)
{
	QDialog::changeEvent(e);
	switch (e->type()) {
		case QEvent::LanguageChange:
			ui->retranslateUi(this);
			break;
		default:
			break;
	}
}

void AboutDialog::populatePluginsTreeWidget(const QString &file,
											const QString &name,
											const QString &type)
{
	QTreeWidgetItem *pluginItem;
	if(type == "Recorder")
		pluginItem = new QTreeWidgetItem(_recorder);
	pluginItem->setText(0, name + " (" + file + ")");
	pluginItem->setIcon(0, _icon);
}
