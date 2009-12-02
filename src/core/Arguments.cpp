#include "Arguments.h"

Arguments::Arguments(QStringList parameters)
{
	m_arguments = parameters;
	m_size = m_arguments.length();
	for(unsigned int i = 0; i < m_size; i++)
		if(m_arguments[i][m_arguments[i].length() - 1] == ':')
			m_arguments[i].resize(m_arguments[i].length() - 1);
}

unsigned int Arguments::size()
{
	return m_size;
}

QString Arguments::get(unsigned int index, bool merge)
{
	if(index >= m_size)
		return "";
	if(!merge)
		return m_arguments[index];
	
	QStringList out;
	for(unsigned int i = index; i < m_size; i++)
 		out << m_arguments[i];
 	return out.join(" ");
}

void Arguments::truncate(unsigned int index)
{
	m_arguments = get(index, true).split(" ");
	m_size = m_arguments.length();
}

ConfigString Arguments::cs(unsigned int index)
{
	QString str = get(index, true);
	QStringList segments = str.split("\\");
	segments.removeFirst();
	ConfigString cs;
	unsigned int size = segments.length();
	for(unsigned int i = 0; i + 1 < size; i += 2)
		cs[segments[i]] = segments[i + 1];
	return cs;
}

ConfigString Arguments::mergeCs(ConfigString a, ConfigString b)
{
	QHashIterator<QString, QString> i(a);
	while(i.hasNext())
	{
		i.next();
		b[i.key()] = i.value();
	}
	return b;
}
