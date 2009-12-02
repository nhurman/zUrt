#ifndef __MODULE_H__
#define __MODULE_H__

#include <QObject>
#include <QStringList>
#include "Arguments.h"

class Module : public QObject
{
	Q_OBJECT
	
	public:
		// Returns the module's name
		virtual QString name() = 0;
		// Returns a list of the events handled by this module
		virtual QStringList listens() = 0;
	
	public slots:
		virtual void event(QString type, Arguments args) = 0;
};

#endif
