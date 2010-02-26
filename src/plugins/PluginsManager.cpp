/****************************************************************************
* PluginsManager.cpp: A dialog that lists all available plugins
*****************************************************************************
* Copyright (C) 2008-2010 Tadej Novak
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*
* This file may be used under the terms of the
* GNU General Public License version 3.0 as published by the
* Free Software Foundation and appearing in the file LICENSE.GPL
* included in the packaging of this file.
*****************************************************************************/

#include "PluginsLoader.h"
#include "PluginsManager.h"

PluginsManager::PluginsManager(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	_interfaceIcon.addPixmap(style()->standardPixmap(QStyle::SP_DirOpenIcon), QIcon::Normal, QIcon::On);
	_interfaceIcon.addPixmap(style()->standardPixmap(QStyle::SP_DirClosedIcon), QIcon::Normal, QIcon::Off);
	_featureIcon.addPixmap(style()->standardPixmap(QStyle::SP_FileIcon));

	_epg = new QTreeWidgetItem(ui.pluginsWidget);
	_epg->setText(0, tr("EPG Plugins"));
	_recorder = new QTreeWidgetItem(ui.pluginsWidget);
	_recorder->setText(0, tr("Recorder Plugins"));
	ui.pluginsWidget->setItemExpanded(_epg, true);
	ui.pluginsWidget->setItemExpanded(_recorder, true);

	QFont font = _epg->font(0);
	font.setBold(true);
	_epg->setFont(0, font);
	_recorder->setFont(0, font);

	PluginsLoader *loader = new PluginsLoader();

	for(int i=0; i < loader->recorderPlugin().size(); i++)
		populateTreeWidget(loader->recorderFile()[i], loader->recorderName()[i], "Recorder");
	for(int i=0; i < loader->epgPlugin().size(); i++)
		populateTreeWidget(loader->epgFile()[i], loader->epgName()[i], "EPG");

	delete loader;
}

PluginsManager::~PluginsManager()
{
	ui.pluginsWidget->clear();
}

void PluginsManager::populateTreeWidget(const QString &file, const QString &name, const QString &type)
{
	QTreeWidgetItem *pluginItem;
	if(type == "EPG")
		pluginItem = new QTreeWidgetItem(_epg);
	else if(type == "Recorder")
		pluginItem = new QTreeWidgetItem(_recorder);
	pluginItem->setText(0, file);
	pluginItem->setIcon(0, _interfaceIcon);

	QTreeWidgetItem *featureItem = new QTreeWidgetItem(pluginItem);
	featureItem->setText(0, name);
	featureItem->setIcon(0, _featureIcon);
}
