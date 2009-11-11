#ifndef HEADER_LOG
#define HEADER_LOG

#include <QFile>
#include <QTextStream>
#include <QString>

class Log
{
	public:
		Log(QString nom);
		~Log();
		void erreur(QString nom);
	private:
		QFile *m_fichier;
};

#endif
