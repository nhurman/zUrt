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
	
	Log::instance("core")->information("---------- Starting up ----------");	
	Log::instance("core")->data("\n\n\n");
	
	bot = zUrt::instance();
	bot->load(new Module_Player);
	bot->load(new Module_Admin);
	bot->run();
	
	return app.exec();
}
