#ifndef ADMIN_H
#define ADMIN_H

#include "../coeur/Module.h"

class Module_Admin : public Module
{
	Q_OBJECT

	public:
		QString nom();
		QStringList ecoute();

	public slots:
		void evenement(QString type, QString parametres);
};

#endif // ADMIN_H
