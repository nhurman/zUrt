#ifndef __ARGUMENTS_H__
#define __ARGUMENTS_H__

#include <QStringList>
#include <QHash>

typedef QHash<QString, QString> ConfigString;

class Arguments
{
	public:
		Arguments(QStringList parameters);
		QString get(unsigned int index, bool merge = false);
		unsigned int size();
		void truncate(unsigned int index);
		ConfigString cs(unsigned int index);
		static ConfigString mergeCs(ConfigString a, ConfigString b);
	
	private:
		QStringList m_arguments;
		unsigned int m_size;
};

#endif
