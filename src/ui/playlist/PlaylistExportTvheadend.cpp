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

#include "PlaylistExportTvheadend.h"
#include "ui_PlaylistExportTvheadend.h"

PlaylistExportTvheadend::PlaylistExportTvheadend(QWidget *parent)
	: QDialog(parent),
	ui(new Ui::PlaylistExportTvheadend),
	_proceed(false)
{
	ui->setupUi(this);

	connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton *)), this, SLOT(action(QAbstractButton *)));
}

PlaylistExportTvheadend::~PlaylistExportTvheadend()
{
	delete ui;
}

void PlaylistExportTvheadend::changeEvent(QEvent *e)
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

void PlaylistExportTvheadend::action(QAbstractButton *button)
{
	switch(ui->buttonBox->standardButton(button)) {
		case QDialogButtonBox::Ok:
			_proceed = true;
			close();
			break;
		case QDialogButtonBox::Cancel:
			close();
			break;
		default:
			break;
	}
}

QString PlaylistExportTvheadend::interface() const
{
	return ui->editInterface->text();
}

QString PlaylistExportTvheadend::location() const
{
	return ui->editLocation->text();
}

QString PlaylistExportTvheadend::xmltv() const
{
	return ui->editXmltv->text();
}