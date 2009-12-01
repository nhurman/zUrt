#include "Bonjour.h"

QStringList Module_Bonjour::ecoute()
{
	return QStringList() << "say";
}

void Module_Bonjour::evenement(QString /*type*/, Arguments args)
{
	Module_Joueur *j = dynamic_cast<Module_Joueur*>(zUrt::instance()->module("Joueur"));
	zUrt::instance()->serveur()->say(
		tr("Hey %1 ! Tu as dit '%2' ; ton guid est %3")
		.arg(args.get(1))
		.arg(args.get(2, true))
		.arg(j->get(args.get(1).toInt(), "cl_guid"))
	);
}

QString Module_Bonjour::nom()
{
	return "Bonjour";
}
