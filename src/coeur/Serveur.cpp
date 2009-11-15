#include "Serveur.h"

Serveur::Serveur(QString adresse, quint16 port, QString rcon)
{
	m_adresse = new QHostAddress(adresse);
	m_port = port;
	m_rcon = rcon;
	m_socket = new QUdpSocket(this);
	m_socket->bind(0);
	m_connecte = true;
	
	if(this->rcon("status", true) == "")
		Log::instance("coeur")->erreur(
			tr("Connexion au serveur %1 sur le port %2 impossible.")
			.arg(m_adresse->toString())
			.arg(QString::number(m_port))
		);
	else
	{
		this->rcon("seta g_logsync 1");
		Log::instance("coeur")->information(
			tr("Connecté au serveur %1 sur le port %2.")
			.arg(m_adresse->toString())
			.arg(QString::number(m_port))
		);
	}
}

QString Serveur::rcon(QString commande, bool reponse)
{
	QString enTete = "\xFF\xFF\xFF\xFF";
	QString requete = enTete + "rcon " + m_rcon + " " + commande;

	m_socket->writeDatagram(requete.toStdString().c_str(), *m_adresse, m_port);
	if(!reponse)
		return QString();
	
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
