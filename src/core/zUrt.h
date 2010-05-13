#ifndef __ZURT_H__
#define __ZURT_H__

#include <QHash>
#include <QSettings>
#include "LogParser.h"
#include "Singleton.h"
#include "Module.h"
#include "Server.h"

class zUrt : public QObject, public Singleton<zUrt>
{
	Q_OBJECT
	
	public:
		zUrt();
		~zUrt();
		void run();
		void load(Module *module);
		Server *server();
		QSettings *settings();
		Module *module(QString name);
		void event(QString type, QStringList parameters);
	
	private:
		QHash<QString, Module*> m_modules;
		QSettings *m_settings;
		Server *m_server;
		LogParser *m_log;
};

#endif
