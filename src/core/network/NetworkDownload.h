/****************************************************************************
* Tano - An Open IP TV Player
* Copyright (C) 2012 Tadej Novak <tadej@tano.si>
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

#ifndef TANO_NETWORKDOWNLOAD_H_
#define TANO_NETWORKDOWNLOAD_H_

#include <QtCore/QFile>
#include <QtCore/QPointer>

#include "CoreSharedExport.h"

class QNetworkReply;

class NetworkRequest;

class TANO_CORE_EXPORT NetworkDownload : public QObject
{
Q_OBJECT
public:
	NetworkDownload(QObject *parent = 0);
	~NetworkDownload();

	void getFile(const QString &fileUrl,
				 const QString &location = 0);

signals:
	void file(const QString &);

private slots:
    void write(const QByteArray &data,
               QNetworkReply *reply);

private:
    QPointer<QFile> _file;

    NetworkRequest *_request;
    QNetworkReply *_currentReply;
};

#endif // TANO_NETWORKDOWNLOAD_H_
