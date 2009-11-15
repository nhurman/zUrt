#ifndef __MODULE_H__
#define __MODULE_H__

#include <QObject>
#include <QStringList>
#include "Serveur.h"

class Module : public QObject
{
	Q_OBJECT
	
	public:
		void setServeur(Serveur *serveur) : m_serveur(serveur) {}
		
		// Renvoie la liste des types d'évènements que ce module gère
		virtual QStringList ecoute() = 0;
		// Renvoie le nom du module
		virtual QString nom() = 0;
	
	public slots:
		virtual void evenement(QString type, QString evenement) = 0;
	
	protected:
		Serveur *m_serveur;
};

#endif
