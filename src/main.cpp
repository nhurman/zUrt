#include <cstdlib>
#include <QCoreApplication>
#include <QSettings>

#include "core/zUrt.h"
#include "modules/Player.h"
#include "modules/Admin.h"
#include "modules/Ban.h"

int main(int argc, char *argv[])
{
	zUrt *bot = NULL;
	QCoreApplication app(argc, argv);

	QTranslator *translator = new QTranslator;
	QSettings *settings = new QSettings("config/zurt.cfg", QSettings::IniFormat);
	translator->load("locales/" + settings->value("ui/locale").toString());
	app.installTranslator(translator);

	Log::instance("core")->data("\n\n\n");
	Log::instance("core")->information(QObject::tr("---------- Starting up ----------"));

	bot = zUrt::instance();
	bot->load(new Module_Player);
	bot->load(new Module_Admin);
	bot->load(new Module_Ban);
	bot->run();

	return app.exec();
}
