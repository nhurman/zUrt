#ifndef SERVEUR_H
#define SERVEUR_H

#include <QtNetwork>

class Serveur : public QObject
{
	public:
		Serveur(QString adresse, quint16 port, QString password);
		QString rcon(QString commande);
	
	protected:
		QHostAddress *m_adresse;
		quint16 m_port;
		QString m_password;
		QUdpSocket *m_socket;
};

#endif

