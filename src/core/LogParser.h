#ifndef __LOGPARSER_H__
#define __LOGPARSER_H__

#include <QFile>
#include <QStringList>
#include "Sleep.h"

class LogParser : public QObject
{
	Q_OBJECT

	public:
		LogParser();
		void readFile();

	private:
		QFile *m_file;

		void parseLine(QString line);
};

#include "zUrt.h"

#endif
