#include "zUrt.h"

zUrt::zUrt()
{
	m_reglages = new QSettings("zurt.cfg", QSettings::IniFormat);
	m_serveur = new Serveur(
		m_reglages->value("serveur/ip").toString(),
		m_reglages->value("serveur/port").value<quint16>(),
		m_reglages->value("serveur/rcon").toString()
	);
}

Serveur *zUrt::serveur()
{
	return m_serveur;
}

void zUrt::charger(Module *module)
{
	QString nom = module->nom();
	if(!m_modules.contains(nom))
	{
		module->setServeur(m_serveur)
		m_modules[nom] = module;
	}
}