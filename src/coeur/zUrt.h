#ifndef __ZURT_H__
#define __ZURT_H__

#include <QHash>
#include <QSettings>
#include "ParseurLog.h"
#include "Singleton.h"
#include "Module.h"
#include "Serveur.h"

class zUrt : public QObject, public Singleton<zUrt>
{
	public:
		zUrt();
		void charger(Module *module);
		Serveur *serveur();
		QSettings *reglages();
	
	protected:
		QHash<QString, Module*> m_modules;
		QSettings *m_reglages;
		Serveur *m_serveur;
		ParseurLog *m_log;
};

#endif
