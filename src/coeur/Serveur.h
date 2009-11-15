#ifndef __SERVEUR_H__
#define __SERVEUR_H__

#include <QtNetwork>
#include "Log.h"

class Serveur : public QObject
{
	public:
		Serveur(QString adresse, quint16 port, QString password);
		QString rcon(QString commande, bool reponse = false);
		bool connecte();
	
	protected:
		QHostAddress *m_adresse;
		quint16 m_port;
		QString m_rcon;
	
	private:
		QUdpSocket *m_socket;
		bool m_connecte;
};

#endif
