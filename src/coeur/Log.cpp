#include "Log.h"

QHash<QString, Log*> Log::m_instance;

Log *Log::instance(QString nom)
{
	if(!m_instance.contains(nom))
		m_instance[nom] = new Log(nom);
	return m_instance[nom];
}
Log::Log(QString nom)
{
	m_fichier = new QFile(nom);
	m_fichier->open(QIODevice::Append);
}

Log::~Log()
{
	m_fichier->close();
}

void Log::ecrire(QString type, QString message, bool cout)
{
	QTextStream out(m_fichier);
	QString ligne = QDate::currentDate().toString("[dd/MM/yy ")
		+ QTime::currentTime().toString("hh:mm]")
		+ " " + type + " : " + message;
	out << ligne << endl;
	cout && std::cout << ligne.toStdString() << std::endl;
}

void Log::information(QString information)
{
	ecrire("Information", information);
}

void Log::erreur(QString erreur)
{
	ecrire("Erreur", erreur, true);
}
