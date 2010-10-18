/****************************************************************************
* M3UHandler.h: Reader and handler of modified m3u format
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

#ifndef TANO_M3UHANDLER_H_
#define TANO_M3UHANDLER_H_

#include <QtCore/QMap>
#include <QtGui/QIcon>
#include <QtGui/QTreeWidget>
#include <QtGui/QTreeWidgetItem>

#include "container/Channel.h"

class M3UHandler
{
public:
	M3UHandler(QTreeWidget *treeWidget);
	~M3UHandler();

	void processFile(const QString &m3uFile);
	void importOldFormat(const QString &tanoFile);

	QTreeWidgetItem *createChannel(const QString &name = 0,
								   const QString &url = 0);
	void deleteChannel(QTreeWidgetItem *i);
	void clear();

	Channel *channelRead(QTreeWidgetItem *item) { return _map[item]; }
	Channel *channelRead(const int &item) { return _nmap[item]; }

	QString name() const { return _name; }
	QString epgType() const { return _epgType; }
	QStringList categories() const { return _categoryList; }
	QStringList languages() const { return _languageList; }
	QStringList epg() const { return _epgList; }
	QList<int> nums() const { return _channelNums; }
	QMap<QTreeWidgetItem*, Channel*> channelMap() const { return _map; }

	int processNewNum(QTreeWidgetItem *channel,
					  const int &num);
	void moveUp(QTreeWidgetItem *channel);
	void moveDown(QTreeWidgetItem *channel);

	bool validate() const;

private:
	void processList();
	QString processNum(const QString &num);

	QTreeWidget *_treeWidget;
	QTreeWidgetItem *_item;
	Channel *_channel;

	QIcon _channelIcon;

	QString _name;
	QString _epgType;
	QStringList _m3uLineList;
	QStringList _categoryList;
	QStringList _languageList;
	QStringList _epgList;

	QList<Channel*> _channels;
	QList<int> _channelNums;

	QMap<QTreeWidgetItem*, Channel*> _map;
	QMap<int, Channel*> _nmap;
};

#endif // TANO_M3UHANDLER_H_
