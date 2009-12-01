#ifndef ADMIN_H
#define ADMIN_H

#include "../coeur/Module.h"
#include "../coeur/zUrt.h"
#include "../modules/Joueur.h"

struct Commande
{
	QString nom;
	unsigned int minArgs;
	QString syntaxe;
	QString aide;
};

class Module_Admin : public Module
{
	Q_OBJECT

	public:
		QString nom();
		QStringList ecoute();

	public slots:
		void evenement(QString type, Arguments args);
		
	protected:
		Commande *getCommande(Arguments args);
		
		static Commande m_commandes[];
		static unsigned int m_nombreCommandes;
};

#endif
