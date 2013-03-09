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

#include "core/Common.h"

#include "common/Backend.h"

#include "AboutDialog.h"
#include "ui_AboutDialog.h"

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    ui->labelTitle->setText(ui->labelTitle->text().arg(Tano::version(), Tano::changeset()));
    ui->labelBuild->setText(ui->labelBuild->text().arg(QString("%1 %2 %3").arg(Tano::version(), Tano::is64bit() ? "64-bit" : "32-bit", Tano::changeset()), qVersion(), Tano::Backend::versionLibrary()));
    ui->labelCopyright->setText(ui->labelCopyright->text().arg(QDate::currentDate().toString("yyyy")));
    ui->labelBackendInfo->setText(ui->labelBackendInfo->text().arg(Tano::Backend::versionCore()));
    ui->labelBackendVersion->setText(ui->labelBackendVersion->text().arg(Tano::Backend::versionLibrary()));

    QFile file(":/info/AUTHORS");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    ui->authors->setPlainText(QString::fromUtf8(file.readAll()));
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