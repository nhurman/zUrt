#ifndef __BONJOUR_H__
#define __BONJOUR_H__

#include "../coeur/zUrt.h"
#include "../coeur/Module.h"

class Module_Bonjour : public Module
{
	public:
		QStringList ecoute();
		QString nom();
	
	public slots:
		void evenement(QString type, QString parametres);
};

#endif
