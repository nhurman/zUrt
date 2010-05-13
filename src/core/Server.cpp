#include "Server.h"

Server::Server(QString address, quint16 port, QString password, QString path)
{
	m_address = new QHostAddress(address);
	m_port = port;
	m_rcon = password;
	m_path = path;
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

Server::~Server()
{
	delete m_address;
	delete m_socket;
}

QString Server::rcon(QString command, bool reply)
{
	if(!m_connected)
		return "";
	static const int RCON_INTERVAL = 510;
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
	
	if(!reply)
		m_socket->readAll();

	QByteArray datagram;
	datagram.resize(m_socket->pendingDatagramSize());
	m_socket->readDatagram(datagram.data(), datagram.size());
	QString out = QString(datagram);
	if(out.left(header.size()) != header)
		return "";

	return out.right(out.size() - header.size());
}

void Server::say(QString str)
{
	str = clean(str).trimmed();
	unsigned int size = str.size();
	const unsigned int TRIM = 60;
	if(size > TRIM)
	{
		int i, split = str.indexOf(' ', TRIM) - 1;
		for(i = split; i >= 0; i++)
			if(str[i] == ' ')
				break;
		if(i <= 0)
			i = TRIM;
		
		rcon("say \"^7" + str.left(i) + "\"");
		say(str.right(str.size() - i));
	}
	else
		rcon("say \"^7" + clean(str) + "\"");
}

void Server::tell(int id, QString str)
{
	str = clean(str).trimmed();
	unsigned int size = str.size();
	const unsigned int TRIM = 52;
	if(size > TRIM)
	{
		int i, split = str.indexOf(' ', TRIM) - 1;
		for(i = split; i >= 0; i++)
			if(str[i] == ' ')
				break;
		if(i <= 0)
			i = TRIM;
		
		rcon("tell " + QString::number(id) + " \"^7" + str.left(i) + "\"");
		tell(id, str.right(str.size() - i));
	}
	else
		rcon("tell " + QString::number(id) + " \"^7" + str + "\"");
}

QString Server::get(QString var)
{
	QString data = rcon(var, true);
	QString before = "print\n\"" + var + "\" is:\"";
        data = data.right(data.size() -before.size());
	data = data.left(data.indexOf('"'));
	return Log::decolorise(data).trimmed();
}

void Server::set(QString var, QString value)
{
	rcon("seta " + var + " \"" + clean(value) + "\"");
}

QStringList Server::maps()
{
	return m_maps;
}

void Server::loadMaps()
{
	QString home = get("fs_homepath");
	QString base = get("fs_basepath");
	QString game = get("fs_game");
	QStringList paks, paths;
	unsigned int i, j, k, l;
	
	home = (QFileInfo(home).isAbsolute() ? home : m_path + '/' + home) + '/';
	base = (QFileInfo(base).isAbsolute() ? base : m_path + '/' + base) + '/';
	paths << home + game << base + game;
	
	// Get pk3s list
	QDir dir;
	dir.setFilter(QDir::Files);
	dir.setNameFilters(QStringList() << "*.pk3");
	
	foreach(QString path, paths)
	{
		dir.cd(path);
		if(!dir.exists())
		{
			Log::instance("core")->error(tr("PK3s listing - folder %1 does not exist."));
			continue;
		}
		QFileInfoList list = dir.entryInfoList();
		foreach(QFileInfo file, list)
			paks << dir.filePath(file.fileName());
	} 
	
	ZipFile *zip;
	QStringList files, parts, parts2;
	m_maps = QStringList();
	QString folder;
        for(i = 0, j = paks.size(); i < j; i++)
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

bool Server::connected()
{
	return m_connected;
}

QString Server::clean(QString str)
{
	return str.replace("\"", "");
}
