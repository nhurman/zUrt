#include "Serveur.h"

Serveur::Serveur(QString adresse, quint16 port, QString password)
{
	m_adresse = new QHostAddress(adresse);
	m_port = port;
	m_rcon = password;
	m_socket = new QUdpSocket(this);
	m_socket->bind(0);
	m_connecte = true;
	
	delai.addSecs(10);
	
	if(rcon("status", true) == "")
		Log::instance("coeur")->erreur(
			tr("Connexion au serveur %1 sur le port %2 impossible.")
			.arg(m_adresse->toString())
			.arg(QString::number(m_port))
		);
	else
	{
		set("g_logSync", "1");
		//reload();
		Log::instance("coeur")->information(
			tr("Connecté au serveur %1 sur le port %2.")
			.arg(m_adresse->toString())
			.arg(QString::number(m_port))
		);
	}
}

QString Serveur::rcon(QString commande, bool reponse)
{
	if(!m_connecte)
		return QString();
	static const int INTERVALLE_RCON = 500;
	if(delai.elapsed() < INTERVALLE_RCON)
		Sleep::msleep(INTERVALLE_RCON);
	QString enTete = "\xFF\xFF\xFF\xFF";
	QString requete = enTete + "rcon " + m_rcon + " " + commande;

	m_socket->writeDatagram(requete.toStdString().c_str(), *m_adresse, m_port);
	delai.start();
	if(!reponse)
		return QString();
	
	m_socket->waitForReadyRead(500);
	if(!m_socket->hasPendingDatagrams())
	{
		m_connecte = false;
		Log::instance("coeur")->erreur(
			tr("Connexion au serveur %1 sur le port %2 impossible.")
			.arg(m_adresse->toString())
			.arg(QString::number(m_port))
		);
		exit(0);
	}
	
	QByteArray datagram;
	datagram.resize(m_socket->pendingDatagramSize());
	m_socket->readDatagram(datagram.data(), datagram.size());
	
	QString retour = QString(datagram);
	if(retour.left(enTete.size()) != enTete)
		return QString();
	
	return retour.right(retour.size() - enTete.size());
}

QString Serveur::nettoyer(QString str)
{
	return str.replace("\"", "");
}

void Serveur::say(QString texte)
{
	rcon("say \"^7" + nettoyer(texte) + "\"");
}

void Serveur::tell(int id, QString texte)
{
	rcon("tell " + QString::number(id) + "\"^7" + nettoyer(texte) + "\"");
}

void Serveur::kick(int id)
{
	rcon("kick " + QString::number(id));
}

void Serveur::mute(int id)
{
	rcon("mute " + QString::number(id));
}

void Serveur::set(QString var, QString valeur)
{
	rcon("seta " + var + " \"" + nettoyer(valeur) + "\"");
}

void Serveur::reload()
{
	rcon("reload");
}

bool Serveur::connecte()
{
	return m_connecte;
}
