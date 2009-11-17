#ifndef __LOG_H__
#define __LOG_H__

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDate>
#include <QTime>
#include <QHash>

class Log : public QObject
{
	public:
		static Log *instance(QString nom);
		void information(QString information);
		void erreur(QString erreur);
		void donnees(QString donnees);
	
	private:
		QFile *m_fichier;
		
		Log(QString nom);
		~Log();
		void ecrire(QString type, QString message);
};

#endif
