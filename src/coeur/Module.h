#ifndef __MODULE_H__
#define __MODULE_H__

#include <QObject>
#include <QStringList>
#include "Arguments.h"

class Module : public QObject
{
	Q_OBJECT
	
	public:
		// Renvoie le nom du module
		virtual QString nom() = 0;
		// Renvoie la liste des types d'évènements que ce module gère
		virtual QStringList ecoute() = 0;
	
	public slots:
		virtual void evenement(QString type, Arguments args) = 0;
};

#endif
