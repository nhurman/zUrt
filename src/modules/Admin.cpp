#include "Admin.h"

QString Module_Admin::nom()
{
	return "Admin";
}

QStringList Module_Admin::ecoute()
{
	return QStringList() << "say";
}

void Module_Admin::evenement(QString type, Arguments args)
{
	Module_Joueur *j = dynamic_cast<Module_Joueur*>(zUrt::instance()->module("Joueur"));
	QString message = args.get(2, true);
	int id_admin = j->matchOnePlayer(args.get(1));
	if(message[0] == '!')
	{
		QString commande = args.get(2);
		commande = commande.right(commande.size() - 1);
		if(commande == "kick")
		{
			if(args.get(3) != "")
			{
				int joueur = j->matchOnePlayer(args.get(3), id_admin);
				if(joueur != -1)
				{
					zUrt::instance()->serveur()->kick(joueur);
				}
			}
			else
			{
				zUrt::instance()->serveur()->tell(id_admin, "Syntaxe : ");
				zUrt::instance()->serveur()->tell(id_admin, "kick <nom>");
				zUrt::instance()->serveur()->tell(id_admin, "kick <id>");
			}
		}
	}
}
