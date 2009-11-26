#ifndef __JOUEUR_H__
#define __JOUEUR_H__

#include <QHash>
#include "../coeur/zUrt.h"
#include "../coeur/Module.h"


class Module_Joueur : public Module
{
	Q_OBJECT

	public:
		QString nom();
		QStringList ecoute();
		QString get(QString id, QString cle);
		QString get(unsigned int id, QString cle);
		QHash<unsigned int, ConfigString> get();
		int matchOnePlayer(QString cle, unsigned int id_admin = -1);
		bool connecte(QString id);
		bool connecte(unsigned int id);

	public slots:
		void evenement(QString type, Arguments args);
	
	private:
		QHash<unsigned int, ConfigString> m_joueurs;
};

#endif
