#include <cstdlib>
#include <QCoreApplication>
#include <QSettings>
#include "coeur/zUrt.h"
#include <iostream>

#include "modules/Admin.h"

int main(int argc, char *argv[])
{
	int retour = 0;
	zUrt *bot = NULL;
	QCoreApplication app(argc, argv);
	Log::instance("coeur")->information("---------- Démarrage ----------");
	
	bot = zUrt::instance();
	bot->charger(new Module_Admin);
	
	if(bot->serveur()->connecte())
		retour = app.exec();
	
	Log::instance("coeur")->information("---------- Arrêt ----------\n\n\n");
	return retour;
}
