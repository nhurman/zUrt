#ifndef __PARSEURLOG_H__
#define __PARSEURLOG_H__

#include <QFile>
#include <QThread>

class ParseurLog : public QObject
{
	public:
		ParseurLog();
		void lireFichier();
	
	private:
		QFile *m_fichier;
};

#include "zUrt.h"

#endif