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

#include "Config.h"
#include "core/Common.h"
#include "core/Enums.h"
#include "core/LocaleManager.h"
#include "SettingsGeneral.h"
#include "ui_SettingsGeneral.h"

SettingsGeneral::SettingsGeneral(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::SettingsGeneral)
{
    ui->setupUi(this);
    loadLocale();

#if EDITOR
    ui->labelVersion->setText(tr("You are using Tano Editor version:") + " <b>" + Tano::version() + "</b>");
    ui->checkWizard->hide();
    ui->groupSession->hide();
    ui->labelLogoPlayer->hide();
#else
    ui->labelVersion->setText(tr("You are using Tano version:") + " <b>" + Tano::version() + "</b>");
    ui->labelLogoEditor->hide();
#endif
}

SettingsGeneral::~SettingsGeneral()
{
    delete ui;
}

void SettingsGeneral::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type())
    {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

bool SettingsGeneral::wizard() const
{
    return ui->checkWizard->isChecked();
}

void SettingsGeneral::setWizard(const bool &enabled)
{
    ui->checkWizard->setChecked(enabled);
}

QString SettingsGeneral::language() const
{
    if (ui->radioCustom->isChecked())
        return _locale[ui->comboLanguage->currentIndex()];
    else
        return QString("");
}

void SettingsGeneral::setLanguage(const QString &language)
{
    if (!language.isEmpty()) {
        ui->radioCustom->setChecked(true);
        for (int i = 0; i < _locale.size(); i++) {
            if (language == _locale[i]) {
                ui->comboLanguage->setCurrentIndex(i);
            }
        }
    }
}

bool SettingsGeneral::sessionAutoplay() const
{
    return ui->checkAutoplay->isChecked();
}

void SettingsGeneral::setSessionAutoplay(const bool &enabled)
{
    ui->checkAutoplay->setChecked(enabled);
}

bool SettingsGeneral::sessionVolume() const
{
    return ui->checkVolume->isChecked();
}

void SettingsGeneral::setSessionVolume(const bool &enabled)
{
    ui->checkVolume->setChecked(enabled);
}

void SettingsGeneral::loadLocale()
{
    _locale = LocaleManager::loadTranslations();

    foreach (QString language, _locale)
        ui->comboLanguage->addItem(LocaleManager::language(language));
}
