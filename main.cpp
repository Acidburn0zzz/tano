#include <QApplication>
#include <QCoreApplication>
#include <QTranslator>
#include <QSettings>
#include <QSplashScreen>
#include <QLocale>
#include <QtDebug>

#include "MainWindow.h"
#include "Common.h"
#include "ui/FirstRun.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("Tano Player");

    QPixmap pixmap(Common::locateResource("splash.png"));
    QSplashScreen *splash = new QSplashScreen(pixmap);
    splash->show();
    splash->showMessage("Initializing Tano Player " + Common::version(), Qt::AlignCenter | Qt::AlignBottom);

    //Settings
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, "Tano", "Settings");
    QString locale = settings.value("locale", QString(QLocale::system().name()).replace(2, 3, "")).toString();

    QTranslator translator;
	QString langPath = Common::locateLang("tano_" + locale + ".qm");
	translator.load(QString("tano_" + locale), langPath);
	app.installTranslator(&translator);

	if(!settings.value("registered",false).toBool()) {
		FirstRun wizard;
		wizard.exec();
	}

    MainWindow mainWindow;

    mainWindow.show();
    splash->close();

    return app.exec();
}
