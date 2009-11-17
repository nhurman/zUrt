#include "Bonjour.h"

QStringList Module_Bonjour::ecoute()
{
	return QStringList() << "say";
}

void Module_Bonjour::evenement(QString type, Arguments args)
{
	zUrt::instance()->serveur()->say(
		tr("Hey %1 ! Tu as dit '%2' :D")
		.arg(args.get(1))
		.arg(args.get(2, true))
	);
}

QString Module_Bonjour::nom()
{
	return "Bonjour";
}
