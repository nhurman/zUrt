#ifndef ADMIN_H
#define ADMIN_H

#include "../coeur/zUrt.h"
#include "Joueur.h"

struct Admin_Commande
{
	QString nom;
	unsigned int minArgs;
	QString syntaxe;
	QString aide;
};

struct Admin_Niveau
{
	QString nom;
	QList<Admin_Commande *> commandes;
};

struct Admin_Admin
{
	QString nom;
	unsigned int niveau;
};

class Module_Admin : public Module
{
	Q_OBJECT

	public:
		Module_Admin();
		QString nom();
		QStringList ecoute();

	public slots:
		void evenement(QString type, Arguments args);
		
	protected:
		Admin_Commande *getCommande(Arguments args);
		unsigned int getNiveau(Module_Joueur *j, int joueur);
		
		static Admin_Commande m_commandes[];
		static unsigned int m_nombreCommandes;
		
	private:
		QHash<unsigned int, Admin_Niveau> m_niveaux;
		QHash<QString, Admin_Admin> m_admins;
		
		void cmd_admintest(Module_Joueur *j, int joueur);
		void cmd_readconfig(int joueur);
};

#endif
