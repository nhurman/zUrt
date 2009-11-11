#include "Log.h"

Log::Log(QString nom)
{
	m_fichier = new QFile(nom);
	m_fichier->open(QIODevice::Append);
}

Log::~Log()
{
	m_fichier->close();
}

void Log::erreur(QString erreur)
{
	QTextStream out(m_fichier);
	out << QTime::currentTime().toString("[hh:mm]") << " Erreur : " << erreur  << endl;
}
