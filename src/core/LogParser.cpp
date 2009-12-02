#include "LogParser.h"

LogParser::LogParser()
{
	QString path = zUrt::instance()
		->settings()
		->value("server/log")
		.toString();
	m_file = new QFile(path);
	if(!m_file->exists())
	{
		Log::instance("core")->error(
			tr("Server's log not found (%1).")
			.arg(m_file->fileName())
		);
		exit(0);
	}
	m_file->open(QIODevice::ReadOnly);
	m_file->seek(m_file->size());
}

void LogParser::readFile()
{
	if(!zUrt::instance()->server()->connected())
		return;
	QTextStream in(m_file);
	while(true)
	{
		if(in.atEnd())
			Sleep::msleep(250);
		else
			parseLine(in.readLine());
	}
}

void LogParser::parseLine(QString line)
{
	QStringList segments = line.split(" ", QString::SkipEmptyParts);
	if(segments.length() < 3)
		return;
	// Hours:minutes
	segments.removeFirst();
	
	QString type = segments.takeFirst();
	if(type[type.length() - 1] == ':')
		type.resize(type.length() - 1);
	zUrt::instance()->event(type, segments);
}
