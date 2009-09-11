#include <QDir>
#include <QFileInfo>
#include <QString>
#include <QMap>
#include <QCoreApplication>
#include <QProcess>
#include <QLibraryInfo>
#include <QMessageBox>
#include <QTextStream>

#include "Common.h"
#include "ui/About.h"

QString Common::locateResource(QString fileN) {
	QString path;

	if (QFileInfo(fileN).exists())
		path = QFileInfo(fileN).absoluteFilePath();

	// Try application exe working path
	else if (QFileInfo(QDir::currentPath() + "/" + fileN).exists())
		path = QFileInfo(QDir::currentPath() + "/" + fileN).absoluteFilePath();

	// Try application exe directory
	else if (QFileInfo(QCoreApplication::applicationDirPath() + "/" + fileN).exists())
		path = QFileInfo(QCoreApplication::applicationDirPath() + "/" + fileN).absoluteFilePath();

#ifdef Q_WS_X11
		else if (QFileInfo("/usr/bin/" + fileN).exists())
			path = QFileInfo("/usr/bin/" + fileN).absoluteFilePath();
#endif

#ifdef DEFAULT_DATA_DIR
	else if (QFileInfo(QString(DEFAULT_DATA_DIR) + "/" + fileN).exists())
		path = QFileInfo(QString(DEFAULT_DATA_DIR) + "/" + fileN).absoluteFilePath();
#endif

	return path;
}

QString Common::locateLang(QString fileL) {
	QString path;

	if (QFileInfo(fileL).exists())
		path = QFileInfo(fileL).absoluteFilePath();

	// Try application exe working path
	else if (QFileInfo(QDir::currentPath() + "/lang/" + fileL).exists())
		path = QFileInfo(QDir::currentPath() + "/lang/" + fileL).absoluteFilePath();

	// Try application exe directory
	else if (QFileInfo(QCoreApplication::applicationDirPath() + "/lang/" + fileL).exists())
		path = QFileInfo(QCoreApplication::applicationDirPath() + "/lang/" + fileL).absoluteFilePath();

#ifdef DEFAULT_DATA_DIR

	else if (QFileInfo(QString(DEFAULT_DATA_DIR) + "/lang/" + fileL).exists())
		path = QFileInfo(QString(DEFAULT_DATA_DIR) + "/lang/" + fileL).absoluteFilePath();

#endif

	return path.replace(QString("/" + fileL), QString(""));
}

QString Common::version()
{
#ifdef TANO_VERSION
	return QString(TANO_VERSION);
#else
	return "Unknown version";
#endif
}

bool Common::fripExists()
{
	QString frip;
#ifdef Q_WS_X11
	frip = "friptv";
#else
	frip = QCoreApplication::applicationDirPath() + "/friptv/friptv.exe";
#endif

	if (!locateResource(frip).isEmpty())
		return true;
	else
		return false;
}

QString Common::frip()
{
#ifdef Q_WS_X11
	return "friptv";
#else
	return QCoreApplication::applicationDirPath() + "/friptv/friptv.exe";
#endif
}

void Common::about(QWidget *parent)
{

#ifdef TANO_VERSION
	QString version = QString(TANO_VERSION);
#else
	QString version = "Unknown version";
#endif

	About about(parent, version);
	about.exec();
}

QSettings* Common::settings()
{
	QSettings* settings = new QSettings(QSettings::IniFormat, QSettings::UserScope, "Tano", "Settings");
	return settings;
}
