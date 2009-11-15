#include "Bonjour.h"

QStringList Module_Bonjour::ecoute()
{
	return QStringList() << "ClientConnect";
}

void Module_Bonjour::evenement(QString type, QString parametres)
{
	zUrt::instance()->serveur()->rcon(
		tr("say Hey Client ! Type %1, params %2")
		.arg(type)
		.arg(parametres)
	);
}

QString Module_Bonjour::nom()
{
	return "Bonjour";
}