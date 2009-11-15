#ifndef __ZURT_H__
#define __ZURT_H__

#include <QHash>
#include <QSettings>
#include "Singleton.h"
#include "Module.h"
#include "Serveur.h"

class zUrt : public Singleton<zUrt>
{
	public:
		zUrt();
		void charger(Module *module);
		Serveur *serveur();
	
	protected:
		QHash<QString, Module*> m_modules;
		QSettings *m_reglages;
		Serveur *m_serveur;
};

#endif
