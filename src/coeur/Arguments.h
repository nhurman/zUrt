#ifndef __ARGUMENTS_H__
#define __ARGUMENTS_H__

#include <QStringList>

class Arguments
{
	public:
		Arguments(QStringList parametres);
		QString get(unsigned int index, bool fusionner = false);
	
	private:
		QStringList m_arguments;
		unsigned int m_nombre;
};

#endif
