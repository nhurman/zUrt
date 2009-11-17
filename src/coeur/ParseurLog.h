#ifndef __PARSEURLOG_H__
#define __PARSEURLOG_H__

#include <QFile>
#include <QStringList>
#include "Sleep.h"

class ParseurLog : public QObject
{
	public:
		ParseurLog();
		void lireFichier();
	
	private:
		QFile *m_fichier;
		
		void parserLigne(QString ligne);
};

#include "zUrt.h"

#endif
