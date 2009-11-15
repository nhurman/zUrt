#ifndef __ZURT_H__
#define __ZURT_H__

#include <QHash>
#include "Singleton.h"
#include "Module.h"

class zUrt : public Singleton<zUrt>
{
	public:
		zUrt();
		void charger(QString module);
	
	protected:
		QHash<QString, Module*> m_modules;
};

#endif