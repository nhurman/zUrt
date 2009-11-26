#ifndef ADMIN_H
#define ADMIN_H

#include "../coeur/Module.h"
#include "../coeur/zUrt.h"
#include "../modules/Joueur.h"

class Module_Admin : public Module
{
	Q_OBJECT

	public:
		QString nom();
		QStringList ecoute();

	public slots:
		void evenement(QString type, Arguments args);
};

#endif
