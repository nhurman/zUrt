#ifndef __ARGUMENTS_H__
#define __ARGUMENTS_H__

#include <QStringList>
#include <QHash>

typedef QHash<QString, QString> ConfigString;

class Arguments
{
	public:
		Arguments(QStringList parametres);
		QString get(unsigned int index, bool fusionner = false);
		ConfigString cs(unsigned int index);
		static ConfigString fusionnerCs(ConfigString a, ConfigString b);
	
	private:
		QStringList m_arguments;
		unsigned int m_nombre;
};

#endif
