#ifndef HEADER_LOG
#define HEADER_LOG

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDate>
#include <QTime>
#include <QHash>
#include <iostream>

class Log
{
	public:
		static Log *instance(QString nom);
		void information(QString information);		
		void erreur(QString erreur);
	
	private:
		static QHash<QString, Log*> m_instance;
		QFile *m_fichier;
		
		Log(QString nom);
		~Log();
		void ecrire(QString type, QString message, bool cout = false);
};

#endif
