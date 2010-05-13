#include "zUrt.h"

zUrt::zUrt()
{
	m_settings = new QSettings("config/zurt.cfg", QSettings::IniFormat);
	m_server = new Server(
		m_settings->value("server/ip").toString(),
		m_settings->value("server/port").value<quint16>(),
		m_settings->value("server/rcon").toString(),
		m_settings->value("server/path").toString()
	);
	m_server->say(tr("Hi everyone !", "Bot greeting when it connects"));
}

zUrt::~zUrt()
{
	delete m_settings;
	delete m_server;
	delete m_log;
}

void zUrt::run()
{
	m_log = new LogParser();
	m_log->readFile();
}

Server *zUrt::server()
{
	return m_server;
}

QSettings *zUrt::settings()
{
	return m_settings;
}

Module *zUrt::module(QString name)
{
	if(!m_modules.contains(name))
		return NULL;
	return m_modules[name];
}

void zUrt::load(Module *module)
{
	QString name = module->name();
	if(!m_modules.contains(name))
	{
		m_modules[name] = module;
		Log::instance("core")->information(
			tr("Loading %1 module.")
			.arg(name)
		);
	}
}

void zUrt::event(QString type, QStringList parameters)
{
	Arguments args = Arguments(parameters);
	foreach(Module *module, m_modules)
		if(module->listens().contains(type))
			module->event(type, args);
}
