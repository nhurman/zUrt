#include "zUrt.h"

zUrt::zUrt()
{
	m_reglages = new QSettings("config/zurt.cfg", QSettings::IniFormat);
	m_serveur = new Serveur(
		m_reglages->value("serveur/ip").toString(),
		m_reglages->value("serveur/port").value<quint16>(),
		m_reglages->value("serveur/rcon").toString()
	);
	m_serveur->say("Salut tout le monde !");
}

void zUrt::demarrer()
{
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

Module *zUrt::module(QString nom)
{
	if(!m_modules.contains(nom))
		return NULL;
	return m_modules[nom];
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

void zUrt::evenement(QString type, QStringList parametres)
{
	Arguments args = Arguments(parametres);
	foreach(Module *module, m_modules)
		if(module->ecoute().contains(type))
			module->evenement(type, args);
}
