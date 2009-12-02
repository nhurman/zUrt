#include "Server.h"

Server::Server(QString address, quint16 port, QString password)
{
	m_address = new QHostAddress(address);
	m_port = port;
	m_rcon = password;
	m_socket = new QUdpSocket(this);
	m_socket->bind(0);
	m_connected = true;
	
	m_interval.addSecs(10);
	
	rcon("status", true);
	set("g_logSync", "1");
	Log::instance("core")->information(
		tr("Connected to %1 on port %2.")
		.arg(m_address->toString())
		.arg(m_port)
	);
}

QString Server::rcon(QString command, bool reply)
{
	if(!m_connected)
		return "";
	static const int RCON_INTERVAL = 500;
	if(m_interval.elapsed() < RCON_INTERVAL)
		Sleep::msleep(RCON_INTERVAL - m_interval.elapsed());
	QString header = "\xFF\xFF\xFF\xFF";
	QString query = header + "rcon " + m_rcon + " " + command;

	m_socket->writeDatagram(query.toStdString().c_str(), *m_address, m_port);
	m_interval.start();
	if(!reply)
		return "";
	
	m_socket->waitForReadyRead(500);
	if(!m_socket->hasPendingDatagrams())
	{
		m_connected = false;
		Log::instance("core")->error(
			tr("Could not connect to %1 on port %2.")
			.arg(m_address->toString())
			.arg(m_port)
		);
		exit(0);
	}
	
	QByteArray datagram;
	datagram.resize(m_socket->pendingDatagramSize());
	m_socket->readDatagram(datagram.data(), datagram.size());
	
	QString out = QString(datagram);
	if(out.left(header.size()) != header)
		return "";
	
	return out.right(out.size() - header.size());
}

QString Server::clean(QString str)
{
	return str.replace("\"", "");
}

void Server::say(QString str)
{
	rcon("say \"^7" + clean(str) + "\"");
}

void Server::tell(int id, QString str)
{
	rcon("tell " + QString::number(id) + "\"^7" + clean(str) + "\"");
}

void Server::kick(int id)
{
	rcon("kick " + QString::number(id));
}

void Server::mute(int id)
{
	rcon("mute " + QString::number(id));
}

void Server::set(QString var, QString value)
{
	rcon("seta " + var + " \"" + clean(value) + "\"");
}

void Server::reload()
{
	rcon("reload");
}

bool Server::connected()
{
	return m_connected;
}
