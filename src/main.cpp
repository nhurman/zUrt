#include <QCoreApplication>
#include <QSettings>
#include "coeur/Serveur.h"

int main(int argc, char *argv[])
{
	int retour = 0;
	QCoreApplication app(argc, argv);
	QSettings reglages("zurt.cfg", QSettings::IniFormat);
	
	Log::instance("coeur.log")->information("---------- Démarrage ----------");
	
	Serveur *serveur = new Serveur(
		reglages.value("serveur/ip").toString(),
		reglages.value("serveur/port").value<quint16>(),
		reglages.value("serveur/rcon").toString()
	);
	
	if(serveur->connecte())
		retour = app.exec();
	
	Log::instance("coeur.log")->information("---------- Arrêt ----------\n\n");
	return retour;
}
