#include "Arguments.h"

Arguments::Arguments(QStringList parametres)
{
	m_arguments = parametres;
	m_nombre = m_arguments.length();
	for(unsigned int i = 0; i < m_nombre; i++)
		if(m_arguments[i][m_arguments[i].length() - 1] == ':')
			m_arguments[i].resize(m_arguments[i].length() - 1);
}

QString Arguments::get(unsigned int index, bool fusionner)
{
	if(index >= m_nombre)
		return QString();
	
	if(!fusionner)
		return m_arguments[index];
	
	QStringList retour;
	for(unsigned int i = index; i < m_nombre; i++)
 		retour << m_arguments[i];
 	return retour.join(" ");
}
