#include "Admin.h"

// Liste des commandes, voir Admin.h pour la syntaxe.
Admin_Commande Module_Admin::m_commandes[] = {
	{	"admintest", 0, "",
		"Affiche votre niveau d'admin."
	},
	{	"kick", 1, "[^3nom^7|^3id^7]",
		"Force un joueur a quitter le serveur."
	},
	{	"mute", 1, "[^3nom^7|^3id^7]",
		"Empeche un joueur de parler."
	},
	{	"readconfig", 0, "",
		"Recharger les administrateurs et les niveaux."
	}
};

unsigned int Module_Admin::m_nombreCommandes =
	sizeof(Module_Admin::m_commandes) / sizeof(Admin_Commande);

Module_Admin::Module_Admin()
{
	cmd_readconfig(-1);
}

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
	
	Admin_Commande *commande = getCommande(args);
	if(!commande)
		return;
	
	// Le joueur a-t-il le droit d'utiliser cette commande ?
	unsigned int niveau = getNiveau(j, id_admin);
	if(!m_niveaux[niveau].commandes.contains(commande))
	{
		zUrt::instance()->serveur()->tell(id_admin,
			tr("^3!%1^7 : Acces refuse.")
			.arg(commande->nom)
		);
		return;
	}
	
	// Y a-t-il assez d'arguments ?
	if(args.nombre() <= commande->minArgs)
	{
		zUrt::instance()->serveur()->tell(id_admin,
			tr("Syntaxe : ^3!%1^7 %2")
			.arg(commande->nom)
			.arg(commande->syntaxe)
		);
		return;
	}
	
	// Exécution de la commande
	if(commande->nom == "admintest")
		cmd_admintest(j, id_admin);
	else if(commande->nom == "kick")
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
	else if(commande->nom == "readconfig")
		cmd_readconfig(id_admin);
}

Admin_Commande *Module_Admin::getCommande(Arguments args)
{
	QString nom = args.get(0);
	if(nom[0] != '!')
		return NULL;
	
	nom = nom.right(nom.size() - 1);
	Admin_Commande *commande = NULL;
	for(unsigned int i = 0; i < m_nombreCommandes; i++)
		if(m_commandes[i].nom == nom)
			commande = &m_commandes[i];
	return commande;
}

unsigned int Module_Admin::getNiveau(Module_Joueur *j, int joueur)
{
	unsigned int niveau = 0;
	QString guid = j->get(joueur, "cl_guid");
	if(m_admins.contains(guid))
		niveau = m_admins[guid].niveau;
	return niveau;
}

///////////////
// COMMANDES //
///////////////

void Module_Admin::cmd_admintest(Module_Joueur *j, int joueur)
{
	unsigned int niveau = getNiveau(j, joueur);
	
	zUrt::instance()->serveur()->say(
		tr("^3!admintest^7 : %1^7 est un %2^7 (niveau %3).")
		.arg(j->get(joueur, "name"))
		.arg(m_niveaux[niveau].nom)
		.arg(niveau)
	);
}

void Module_Admin::cmd_readconfig(int joueur)
{
	QSettings *config = NULL;
	
	// Chargement des niveaux d'admin
	{
		config = new QSettings("config/niveaux.cfg", QSettings::IniFormat);
		QStringList niveaux = config->childGroups();
		m_niveaux = QHash<unsigned int, Admin_Niveau>();
		
		for(unsigned int i = 0, j = niveaux.size(); i < j; i++)
		{
			config->beginGroup(niveaux[i]);
			unsigned int niveau = niveaux[i].toInt();
			m_niveaux[niveau].nom = config->value("nom").toString();
	
			QStringList commandes = config->value("commandes").toString()
				.replace(" ", "").split("|");
			bool tout = commandes.contains("*");
			for(unsigned int k = 0; k < m_nombreCommandes; k++)
				if(tout || commandes.contains(m_commandes[k].nom))
					m_niveaux[niveau].commandes.append(&m_commandes[k]);
			config->endGroup();
		}
		delete config;
	}
	
	// Chargement des admins
	{
		config = new QSettings("config/admins.cfg", QSettings::IniFormat);
		QStringList admins = config->childGroups();
		m_admins = QHash<QString, Admin_Admin>();
		
		for(unsigned int i = 0, j = admins.size(); i < j; i++)
		{
			config->beginGroup(admins[i]);
			m_admins[admins[i]].nom = config->value("nom").toString();
			m_admins[admins[i]].niveau = config->value("niveau").toInt();
			if(!m_niveaux.contains(m_admins[admins[i]].niveau))
				m_admins[admins[i]].niveau = 0;
			config->endGroup();
		}
		delete config;
	}
	
	if(joueur != -1)
		zUrt::instance()->serveur()->tell(joueur,
			tr("^3!readconfig^7 : %1 niveaux et %2 admins charges.")
			.arg(m_niveaux.size())
			.arg(m_admins.size())
		);
}
