#include "Server.h"

Server::Server(QString address, quint16 port, QString password, QString path)
{
	m_address = new QHostAddress(address);
	m_port = port;
	m_rcon = password;
	m_path = path;
	m_maps = QStringList();
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
	loadMaps();
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

	m_socket->waitForReadyRead(500);
	if(reply && !m_socket->hasPendingDatagrams())
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

void Server::map(QString name)
{
	rcon("map " + name);
}

void Server::set(QString var, QString value)
{
	rcon("seta " + var + " \"" + clean(value) + "\"");
}

QString Server::get(QString var)
{
	QString data = rcon(var, true);
	QString before = "print\n\"" + var + "\" is:\"";
	data = data.right(data.length() -before.length());
	data = data.left(data.indexOf('"'));
	return Log::decolorise(data).trimmed();
}

bool Server::connected()
{
	return m_connected;
}

QStringList Server::maps()
{
	return m_maps;
}

void Server::loadMaps()
{
	QString home = get("fs_homepath");
	QString base = get("fs_basepath");
	QStringList
		paks = QStringList(),
		pakNames = get("sv_referencedPakNames").split(' ');
	unsigned int i, j, k, l;
	
	home = (QFileInfo(home).isAbsolute() ? home : m_path + '/' + home) + '/';
	base = (QFileInfo(base).isAbsolute() ? base : m_path + '/' + base) + '/';
	
	for(i = 0, j = pakNames.length(); i < j; i++)
	{
		QString file = pakNames[i] + ".pk3";
		if(QFile::exists(home + file))
			paks << home + file;
		if(QFile::exists(base + file))
			paks << base + file;
	}
		ZipFile *zip;
	QStringList files, parts, parts2;
	m_maps = QStringList();
	QString folder;
	for(i = 0, j = paks.length(); i < j; i++)
	{
		zip = new ZipFile(paks[i]);
		files = zip->listFiles();
		for(k = 0, l = files.size(); k < l; k++)
		{
			parts = files[k].split('/');
			folder = parts.first();
			if(folder == "maps")
			{
				parts2 = parts.last().split('.');
				if(parts2.last().toLower() == "bsp")
					m_maps << parts2.first();
			}
		}
		delete zip;
	}
}
