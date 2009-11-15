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
	m_fichier = new QFile("logs/" + nom);
	m_fichier->open(QIODevice::Append);
}

Log::~Log()
{
	m_fichier->close();
}

void Log::ecrire(QString type, QString message)
{
	QTextStream out(m_fichier);
	QString ligne = QObject::tr("[%1 %2] %3 : %4")
					.arg(QDate::currentDate().toString(tr("dd/MM/yy")))
					.arg(QTime::currentTime().toString(tr("hh:mm")))
					.arg(type)
					.arg(message);
	out << ligne << endl;
}

void Log::information(QString information)
{
	ecrire(tr("Information"), information);
}

void Log::erreur(QString erreur)
{
	ecrire(tr("Erreur"), erreur);
}
