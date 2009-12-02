#include "ParseurLog.h"

ParseurLog::ParseurLog()
{
	QString path = zUrt::instance()
		->reglages()
		->value("serveur/log")
		.toString();
	m_fichier = new QFile(path);
	if(!m_fichier->exists())
	{
		Log::instance("coeur")->erreur(
			tr("Le log d'Urban Terror est introuvable (%1).")
			.arg(m_fichier->fileName())
		);
		exit(0);
	}
	m_fichier->open(QIODevice::ReadOnly);
	m_fichier->seek(m_fichier->size());
}

void ParseurLog::lireFichier()
{
	if(!zUrt::instance()->serveur()->connecte())
		return;
	QTextStream in(m_fichier);
	while(true)
	{
		if(in.atEnd())
			Sleep::msleep(250);
		else
			parserLigne(in.readLine());
	}
}

void ParseurLog::parserLigne(QString ligne)
{
	QStringList segments = ligne.split(" ", QString::SkipEmptyParts);
	if(segments.length() < 3)
		return;
	// Heures:minutes
	segments.removeFirst();
	
	QString type = segments.takeFirst();
	if(type[type.length() - 1] == ':')
		type.resize(type.length() - 1);
	zUrt::instance()->evenement(type, segments);
}
