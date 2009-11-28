#ifndef __SERVEUR_H__
#define __SERVEUR_H__

#include <QtNetwork>
#include <QTime>
#include "Log.h"
#include "Sleep.h"

class Serveur : public QObject
{
	public:
		Serveur(QString adresse, quint16 port, QString password);
		QString rcon(QString commande, bool reponse = false);
		void say(QString texte);
		void tell(int id, QString texte);
		void kick(int id);
		void mute(int id);
		void reload();
		void set(QString var, QString valeur);
		bool connecte();
		
		static QString nettoyer(QString str);
	
	protected:
		QHostAddress *m_adresse;
		quint16 m_port;
		QString m_rcon;
	
	private:
		QUdpSocket *m_socket;
		bool m_connecte;
		QTime delai;
};

#endif
