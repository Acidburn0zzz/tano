#include "Shortcuts.h"
#include "../Common.h"

Shortcuts::Shortcuts(QList<QAction*> list) {
	actions = list;

	defaultList << "Space"
				<< "S"
				<< "N"
				<< "P"
				<< "F"
				<< "M"
				<< "Ctrl+Up"
				<< "Ctrl+Down"
				<< "Ctrl+O"
				<< "Ctrl+U"
				<< "Ctrl+P"
				<< "Ctrl+B"
				<< "Ctrl+E"
				<< "Ctrl+S"
				<< "Ctrl+T"
				<< "Ctrl+L"
				<< "F1"
				<< "Ctrl+F1";

	settings = new SettingsShortcuts(Common::settingsFile("shortcuts"), defaultList);

	apply();
}

Shortcuts::~Shortcuts() {

}

void Shortcuts::apply()
{
	read();
	for (int i=0; i < actions.size(); i++) {
		actions.at(i)->setShortcut(QKeySequence(keys.at(i)));
		actions.at(i)->setShortcutContext(Qt::ApplicationShortcut);
	}
}

void Shortcuts::read()
{
	keys = settings->read();
}

QStringList Shortcuts::defaultKeys()
{
	return defaultList;
}
