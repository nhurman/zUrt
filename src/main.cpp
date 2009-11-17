#include <cstdlib>
#include <QCoreApplication>
#include <QSettings>
#include "coeur/zUrt.h"
#include "modules/Bonjour.h"
#include <iostream>

int main(int argc, char *argv[])
{
	zUrt *bot = NULL;	
	QCoreApplication app(argc, argv);
	
	Log::instance("coeur")->information("---------- Démarrage ----------");	
	Log::instance("coeur")->donnees("\n\n\n");
	
	bot = zUrt::instance();
	bot->charger(new Module_Bonjour);
	bot->demarrer();
	return app.exec();
}
