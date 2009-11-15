#include "Serveur.h"

Serveur::Serveur(QString adresse, quint16 port, QString rcon)
{
	m_adresse = new QHostAddress(adresse);
	m_port = port;
	m_rcon = rcon;
	m_socket = new QUdpSocket(this);
	m_connecte = true;
	
	if(Serveur::rcon("status") == "")
		Log::instance("coeur.log")->erreur("Connexion au serveur "
			+ adresse + " sur le port "
			+ QString().sprintf("%d", port)
			+ " impossible.");
	else
		Log::instance("coeur.log")->information("Connecte a "
			+ adresse + " sur le port " + QString().sprintf("%d.", port));
}

QString Serveur::rcon(QString commande)
{
	QString enTete = "\xFF\xFF\xFF\xFF";
	QString requete = enTete + "rcon " + m_rcon + " " + commande;

	m_socket->bind(0);
	m_socket->writeDatagram(requete.toStdString().c_str(), *m_adresse, m_port);
	m_socket->waitForReadyRead(500);
	if(!m_socket->hasPendingDatagrams())
	{
		m_connecte = false;
		return QString();
	}
	
	QByteArray datagram;
	datagram.resize(m_socket->pendingDatagramSize());
	m_socket->readDatagram(datagram.data(), datagram.size());
	
	QString retour = QString(datagram);
	if(retour.left(enTete.size()) != enTete)
		return QString();
	
	return retour.right(retour.size() - enTete.size());
}

bool Serveur::connecte()
{
	return m_connecte;
}
