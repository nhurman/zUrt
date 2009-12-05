#include <cstdlib>
#include <QCoreApplication>
#include <QSettings>
#include "core/zUrt.h"

#include "modules/Admin.h"
#include "modules/Player.h"

int main(int argc, char *argv[])
{
	zUrt *bot = NULL;	
	QCoreApplication app(argc, argv);
	
	QTranslator *translator = new QTranslator;
	QSettings *settings = new QSettings("config/zurt.cfg", QSettings::IniFormat);
	translator->load("ui/" + settings->value("ui/locale").toString());
	app.installTranslator(translator);
	delete settings;
	
	Log::instance("core")->information("---------- Starting up ----------");	
	Log::instance("core")->data("\n\n\n");
	
	bot = zUrt::instance();
	bot->load(new Module_Player);
	bot->load(new Module_Admin);
	bot->run();
	
	return app.exec();
}
