#include <QtGui>
#include <QMessageBox>
#include <QTextEdit>
#include <QDir>
#include <QFileDialog>

#include "EditSettings.h"
#include "../Common.h"

EditSettings::EditSettings(QWidget *parent, Shortcuts *s)
	: QDialog(parent)
{
	ui.setupUi(this);
	createActions();

	ui.buttonSet->setEnabled(false);
	ui.buttonBrowse->setEnabled(false);
	ui.buttonReset->setEnabled(false);

	ui.shortcutsWidget->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
	ui.shortcutsWidget->verticalHeader()->hide();

	shortcuts = s;
	keysList = shortcuts->defaultKeys();
	actionsList = shortcuts->actionsNames();

	settings = new QSettings(QSettings::IniFormat, QSettings::UserScope, "Tano", "Settings");
	settings->sync();

	read();
	shortcutRead();
}

void EditSettings::createActions()
{
	connect(ui.buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(action(QAbstractButton*)));

	connect(ui.radioDefault, SIGNAL(clicked()), this, SLOT(toggleCustom()));
	connect(ui.radioCustom, SIGNAL(clicked()), this, SLOT(toggleCustom()));

	connect(ui.radioSiol, SIGNAL(clicked()), this, SLOT(togglePlaylist()));
	connect(ui.radioT2, SIGNAL(clicked()), this, SLOT(togglePlaylist()));
	connect(ui.radioBrowse, SIGNAL(clicked()), this, SLOT(togglePlaylist()));

	connect(ui.buttonBrowse, SIGNAL(clicked()), this, SLOT(playlistBrowse()));
	connect(ui.buttonReset, SIGNAL(clicked()), this, SLOT(playlistReset()));

	connect(ui.shortcutsWidget, SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(shortcutEdit(QTableWidgetItem*)));
	connect(ui.keyEditor, SIGNAL(keySequenceChanged(const QKeySequence)), this, SLOT(shortcutSequence(const QKeySequence)));
	connect(ui.buttonDefaults, SIGNAL(clicked()), this, SLOT(shortcutRestore()));
	connect(ui.buttonSet, SIGNAL(clicked()), this, SLOT(shortcutSet()));
	connect(ui.buttonClear, SIGNAL(clicked()), this, SLOT(shortcutClear()));
}

void EditSettings::action(QAbstractButton *button)
{
	switch(ui.buttonBox->standardButton(button)) {
	case 0x00000800:
		ok();
		break;
	case 0x00400000:
		cancel();
		break;
	default:
		break;
	}
}

void EditSettings::ok()
{
	if (ui.radioDefault->isChecked()) {
		settings->remove("locale");
	} else {
		if(ui.comboBox->currentIndex() == 1)
			settings->setValue("locale","sl");
		else if(ui.comboBox->currentIndex() == 0)
			settings->setValue("locale","en");
	}

	settings->setValue("session",ui.checkSession->isChecked());

	if(ui.radioSiol->isChecked()) {
		settings->setValue("playlist","siol.xml");
	} else if(ui.radioT2->isChecked()) {
		settings->setValue("playlist","t-2.xml");
	} else {
		settings->setValue("playlist",ui.pEdit->text());
	}

	settings->beginGroup("Shortcuts");
	for(int i=0; i < ui.shortcutsWidget->rowCount(); i++) {
		item = ui.shortcutsWidget->item(i,1);
		if(item->text() != keysList.at(i))
			settings->setValue(actionsList.at(i),item->text());
	}
	settings->endGroup();

	shortcuts->apply();
	hide();
}

void EditSettings::cancel()
{
	hide();
}

void EditSettings::read()
{
	if(settings->value("locale","Default").toString() != "Default")
	{
		ui.radioCustom->setChecked(true);
		ui.comboBox->setEnabled(true);
		bool okint;
		if(settings->value("locale").toString() == "sl")
			ui.comboBox->setCurrentIndex(1);
		else if(settings->value("locale").toString() == "en")
			ui.comboBox->setCurrentIndex(0);
	}

	ui.checkSession->setChecked(settings->value("session",true).toBool());

	if(settings->value("playlist","siol.xml").toString() == "siol.xml")
		ui.radioSiol->setChecked(true);
	else if(settings->value("playlist","siol.xml").toString() == "t-2.xml")
		ui.radioT2->setChecked(true);
	else {
		ui.radioBrowse->setChecked(true);
		ui.buttonBrowse->setEnabled(true);
		ui.buttonReset->setEnabled(true);
		ui.pEdit->setText(settings->value("playlist").toString());
	}
}

void EditSettings::toggleCustom()
{
	if (ui.radioCustom->isChecked())
	{
		ui.comboBox->setEnabled(true);
	} else
	{
		ui.comboBox->setEnabled(false);
	}
}

void EditSettings::togglePlaylist()
{
	if (ui.radioBrowse->isChecked())
	{
		ui.buttonBrowse->setEnabled(true);
		ui.buttonReset->setEnabled(true);
	} else
	{
		ui.buttonBrowse->setEnabled(false);
		ui.buttonReset->setEnabled(false);
	}
}

void EditSettings::playlistBrowse()
{
	QString dfile = QFileDialog::getOpenFileName(this, tr("Open Channel list File"),
												QDir::homePath(),
												tr("Tano TV Channel list Files(*.tano *.xml)"));
	ui.pEdit->setText(dfile);
}

void EditSettings::playlistReset()
{
	ui.pEdit->setText("");
}

void EditSettings::shortcutRead()
{
	settings->beginGroup("Shortcuts");
	for(int i=0; i < ui.shortcutsWidget->rowCount(); i++) {
		item = ui.shortcutsWidget->item(i,1);
		item->setText(settings->value(actionsList.at(i),keysList.at(i)).toString());
	}
	settings->endGroup();
}

void EditSettings::shortcutRestore()
{
	settings->beginGroup("Shortcuts");
	for(int i=0; i < actionsList.size(); i++) {
		settings->remove(actionsList.at(i));
		item = ui.shortcutsWidget->item(i,1);
		item->setText(keysList.at(i));
	}
	settings->endGroup();
}

void EditSettings::shortcutEdit(QTableWidgetItem *titem)
{
	if(titem->column() == 1) {
		ui.buttonSet->setEnabled(true);
		item = titem;
	}
}

void EditSettings::shortcutSequence(const QKeySequence &s)
{
	sequence = s;
}

void EditSettings::shortcutSet()
{
	item->setText(sequence.toString());
	shortcutClear();
}

void EditSettings::shortcutClear()
{
	ui.keyEditor->setKeySequence(QKeySequence(""));
}
