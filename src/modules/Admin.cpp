#include "Admin.h"

QString Module_Admin::nom()
{
	return "Admin";
}

QStringList Module_Admin::ecoute()
{
	return QStringList() << "say";
}

void Module_Admin::evenement(QString type, QString parametres)
{
}
