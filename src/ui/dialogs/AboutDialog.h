/****************************************************************************
* AboutDialog.h: About dialog for Tano application
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

#ifndef TANO_ABOUTDIALOG_H_
#define TANO_ABOUTDIALOG_H_

#include <QtGui/QDialog>

namespace Ui
{
	class AboutDialog;
}

class AboutDialog : public QDialog
{
Q_OBJECT
public:
	AboutDialog(QWidget *parent = 0);
	~AboutDialog();

protected:
	void changeEvent(QEvent *e);

private slots:
	void license();

private:
	Ui::AboutDialog *ui;
};

#endif // TANO_ABOUTDIALOG_H
