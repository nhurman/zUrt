#ifndef __LOG_H__
#define __LOG_H__

#include <QFile>
#include <QTextStream>
#include <QDate>
#include <QTime>
#include <QHash>
#include <QRegExp>

class Log : public QObject
{
	Q_OBJECT
	
	public:
		static Log *instance(QString nom);
		void information(QString information);
		void error(QString error);
		void data(QString data);
		static QString decolorise(QString str);
	
	private:
		QFile *m_file;
		
		Log(QString nom);
		~Log();
		void write(QString type, QString message);
};

#endif
