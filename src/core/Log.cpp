#include "Log.h"

Log *Log::instance(QString name)
{
	static QHash<QString, Log*> m_instances;
	if(!m_instances.contains(name))
		m_instances[name] = new Log(name);
	return m_instances[name];
}

Log::Log(QString name)
{
	m_file = new QFile("logs/" + name + ".log");
	m_file->open(QIODevice::Append);
}

Log::~Log()
{
	m_file->close();
}

void Log::write(QString type, QString message)
{
	QTextStream out(m_file);
	QString ligne = QObject::tr("[%1 %2] %3 : %4")
					.arg(QDate::currentDate().toString(tr("dd/MM/yy")))
					.arg(QTime::currentTime().toString(tr("hh:mm")))
					.arg(type)
					.arg(message);
	out << ligne << endl;
}

void Log::information(QString information)
{
	write(tr("Information", "From log"), information);
}

void Log::error(QString error)
{
	write(tr("Error", "From log"), error);
}

void Log::data(QString data)
{
	m_file->write(data.toStdString().c_str());
}
