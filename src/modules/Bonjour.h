#ifndef __BONJOUR_H__
#define __BONJOUR_H__

#include "../coeur/zUrt.h"
#include "../coeur/Module.h"

class Module_Bonjour : public Module
{
	Q_OBJECT

	public:
		QString nom();
		QStringList ecoute();

	public slots:
		void evenement(QString type, Arguments args);
};

#endif
