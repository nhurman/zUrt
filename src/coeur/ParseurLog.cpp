#include "ParseurLog.h"

ParseurLog::ParseurLog()
{
	m_fichier = new QFile(
		zUrt::instance()
		->reglages()
		->value("serveur/log")
		.toString());
	if(m_fichier->exists())
	{
		m_fichier->open(QIODevice::ReadOnly);
		m_fichier->seek(m_fichier->size());
	}
}

void ParseurLog::lireFichier()
{
	if(!zUrt::instance()->serveur()->connecte())
		return;
	QTextStream in(m_fichier);
	while(true)
	{
		if(in.atEnd())
			usleep(250000);
		else
		{
			QString ligne = in.readLine();
			std::cout << ligne.toStdString() << std::endl;
		}
	}
}