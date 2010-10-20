#include "Ban.h"

Module_Ban::Module_Ban()
{
	readConfig();
}

QString Module_Ban::name()
{
	return "Ban";
}

QStringList Module_Ban::listens()
{
	return QStringList() << "ClientUserinfo";
}

void Module_Ban::event(QString /*type*/, Arguments args)
{
	// Get Ip and GUID then check if they are in the ban list
	ConfigString cs = args.cs(1);
	QString guid = cs["cl_guid"];
	QString ip = cs["ip"];

	if(isBanned(ip, guid, MATCH_ANY))
		zUrt::instance()->server()->rcon("clientkick "
			+ args.get(0));
}

int Module_Ban::getBanId(QString ip, QString guid, short mode)
{
	Ban_Ban ban;
	QHash<unsigned int, Ban_Ban>::iterator i, end;
	QDateTime currentDateTime = QDateTime::currentDateTimeUtc();
	int erased = 0, key = -1;

	for(i = m_bans.begin(), end = m_bans.end(); i != end; i++)
	{
		ban = i.value();

		// Remove old bans
		if(ban.expiration.toTime_t() != 0 && ban.expiration <= currentDateTime)
		{
			i = m_bans.erase(i);
			erased++;

			if(i == end)
				break;
		}

		short n = 0;

		if(guid != "" && ban.guid == guid)
			n++;
		if(ip != "" && ban.ip == ip)
			n++;

		if(n == 2 || (mode == MATCH_ANY && n == 1))
		{
			key = i.key();
			break;
		}
	}

	if(erased > 0)
		writeConfig();

	return key;
}

bool Module_Ban::isBanned(QString ip, QString guid, short mode)
{
	return getBanId(ip, guid, mode) >= 0;
}

unsigned int Module_Ban::ban(QString ip, QString guid, QString name, QString admin, QDateTime expiration)
{
	int id = getBanId(ip, guid, MATCH_ALL);

	if(id >= 0)
		return id;

	id = 0;
	while(m_bans.contains(id))
		id++;

	// Remove port number from ip
	{
		int pos = ip.indexOf(':');
		if(pos >= 0)
			ip = ip.left(pos);
	}

	Ban_Ban ban;
	ban.id = id;
	ban.ip = ip;
	ban.guid = guid;
	ban.name = name;
	ban.expiration = expiration;
	ban.admin = (admin == "") ? "console" : admin;

	m_bans[id] = ban;
	writeConfig();
	return id;
}

void Module_Ban::readConfig()
{
	QHash<unsigned int, Ban_Ban>::iterator i, end;
	QSettings *config = new QSettings("config/bans.cfg", QSettings::IniFormat);
	QStringList bans = config->childGroups();

	m_bans.clear();

	for(unsigned int i = 0, j = bans.size(); i < j; i++)
	{
		config->beginGroup(bans[i]);
		unsigned int id = bans[i].toUInt();

		m_bans[id].id = id;
		m_bans[id].ip = config->value("ip").toString();
		m_bans[id].guid = config->value("guid").toString();
		m_bans[id].name = config->value("name").toString();
		m_bans[id].admin = config->value("admin").toString();
		m_bans[id].expiration.setTime_t(
			config->value("expiration").toUInt());
		config->endGroup();
	}
	delete config;
}

void Module_Ban::writeConfig()
{
	Ban_Ban ban;
	QHash<unsigned int, Ban_Ban>::iterator i, end;
	QSettings *config = new QSettings("config/bans.cfg", QSettings::IniFormat);

	config->clear();
	for(i = m_bans.begin(), end = m_bans.end(); i != end; i++)
	{
		ban = i.value();

		config->beginGroup(QString::number(ban.id));
		config->setValue("id", ban.id);
		config->setValue("ip", ban.ip);
		config->setValue("guid", ban.guid);
		config->setValue("name", ban.name);
		config->setValue("admin", ban.admin);
		config->setValue("expiration", ban.expiration.toTime_t());
		config->endGroup();
	}

	config->sync();
	delete config;
}

