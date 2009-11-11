#include "Serveur.h"

Serveur::Serveur(QString adresse, quint16 port, QString password)
{
	m_adresse = new QHostAddress(adresse);
	m_port = port;
	m_password = password;
	m_socket = new QUdpSocket(this);
}

QString Serveur::rcon(QString commande)
{
	QString enTete = "\xFF\xFF\xFF\xFF";
	QString requete = enTete + "rcon " + m_password + " " + commande;

	m_socket->bind(0);
	m_socket->writeDatagram(requete.toStdString().c_str(), *m_adresse, m_port);
	m_socket->waitForReadyRead(500);
	if(!m_socket->hasPendingDatagrams())
		return QString();
	
	QByteArray datagram;
	datagram.resize(m_socket->pendingDatagramSize());
	m_socket->readDatagram(datagram.data(), datagram.size());
	
	QString retour = QString(datagram);
	if(retour.left(enTete.size()) != enTete)
		return QString();
	
	return retour.right(retour.size() - enTete.size());
}

