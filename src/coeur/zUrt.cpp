#include "zUrt.h"

zUrt::zUrt()
{
	m_reglages = new QSettings("zurt.cfg", QSettings::IniFormat);
	m_serveur = new Serveur(
		m_reglages->value("serveur/ip").toString(),
		m_reglages->value("serveur/port").value<quint16>(),
		m_reglages->value("serveur/rcon").toString()
	);
	if(!m_serveur->connecte())
		return;
	
	m_log = new ParseurLog();
	m_log->lireFichier();
}

Serveur *zUrt::serveur()
{
	return m_serveur;
}

QSettings *zUrt::reglages()
{
	return m_reglages;
}

void zUrt::charger(Module *module)
{
	QString nom = module->nom();
	if(!m_modules.contains(nom))
	{
		m_modules[nom] = module;
		Log::instance("coeur")->information(
			tr("Chargement du module %1.")
			.arg(nom)
		);
	}
}