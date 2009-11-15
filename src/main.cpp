#include <cstdlib>
#include <QCoreApplication>
#include <QSettings>
#include "coeur/zUrt.h"

int main(int argc, char *argv[])
{
	int retour = 0;
	QCoreApplication app(argc, argv);
	
	zUrt *bot = NULL;
	Log::instance("coeur")->information("---------- Démarrage ----------");
	
	bot = new zUrt();
	if(bot->serveur()->connecte())
		retour = app.exec();
	
	Log::instance("coeur")->information("---------- Arrêt ----------\n\n");
	return retour;
}
