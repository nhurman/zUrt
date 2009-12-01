#include "Admin.h"

Commande Module_Admin::m_commandes[] = {
	{	"kick", 1, "[^3nom^7|^3id^7]",
		"Force un joueur a quitter le serveur."
	},
	{	"mute", 1, "[^3nom^7|^3id^7]",
		"Empeche un joueur de parler."
	}
};

unsigned int Module_Admin::m_nombreCommandes =
	sizeof(Module_Admin::m_commandes) / sizeof(Module_Admin::m_commandes[0]);


QString Module_Admin::nom()
{
	return "Admin";
}

QStringList Module_Admin::ecoute()
{
	return QStringList() << "say";
}

void Module_Admin::evenement(QString /*type*/, Arguments args)
{
	Module_Joueur *j = dynamic_cast<Module_Joueur*>(
		zUrt::instance()->module("Joueur"));
	unsigned int id_admin = args.get(0).toInt();
	
	// Ne garder que la partie à partir du message
	args.couper(2);
	
	Commande *commande = getCommande(args);
	if(!commande)
		return;
	if(args.nombre() <= commande->minArgs)
	{
		zUrt::instance()->serveur()->tell(id_admin,
			tr("Syntaxe : !%1 %2")
			.arg(commande->nom)
			.arg(commande->syntaxe)
		);
		return;
	}
	
	if(commande->nom == "kick")
	{
		int joueur = j->matchOnePlayer(args.get(1), id_admin);
		if(joueur != -1)
			zUrt::instance()->serveur()->kick(joueur);
	}
	else if(commande->nom == "mute")
	{
		int joueur = j->matchOnePlayer(args.get(1), id_admin);
		if(joueur != -1)
			zUrt::instance()->serveur()->mute(joueur);
	}
}

Commande *Module_Admin::getCommande(Arguments args)
{
	QString nom = args.get(0);
	if(nom[0] != '!')
		return NULL;
	
	nom = nom.right(nom.size() - 1);
	Commande *commande = NULL;
	for(unsigned int i = 0; i < m_nombreCommandes; i++)
		if(m_commandes[i].nom == nom)
			commande = &m_commandes[i];
	return commande;
}