#include "Player.h"

QString Module_Player::name()
{
	return "Player";
}

QStringList Module_Player::listens()
{
	return QStringList()
		<< "ClientConnect"
		<< "ClientDisconnect"
		<< "ClientUserinfo";
}

void Module_Player::event(QString type, Arguments args)
{
	unsigned int id = args.get(0).toInt();
	if(type == "ClientConnect")
		m_players[id] = ConfigString();
	else if(type == "ClientDisconnect")
		m_players.remove(id);
	else if(type == "ClientUserinfo")
		m_players[id] = Arguments::mergeCs(args.cs(1), m_players[id]);
}

QString Module_Player::get(QString id, QString key)
{
	return get(id.toInt(), key);
}

QString Module_Player::get(unsigned int id, QString key)
{
	if(!connected(id))
		return "";
	if(!m_players[id].contains(key))
		return "";
	return m_players[id][key];
}

QHash<unsigned int, ConfigString> Module_Player::get()
{
	return m_players;
}

int Module_Player::matchOnePlayer(QString needle, int admin)
{
	QList <int> list;
	QString name;
	bool number = false;
	int id = needle.toInt(&number);
	
	if(number)
	{
		if(connected(id))
			return id;
		else
			zUrt::instance()->server()->tell(admin,
				tr("No players found.")
			);
		return -1;
	}
		
	QHashIterator<unsigned int, ConfigString> i(m_players);
	while(i.hasNext())
	{
		i.next();
		name = get(i.key(), "name");
		if(name != "" && name.toLower().contains(needle.toLower()))
			list << i.key();
	}
	
	if(list.isEmpty())
	{
		zUrt::instance()->server()->tell(admin,
			tr("No players found.")
		);
	}
	else if(list.size() == 1)
		return list[0];
	else
	{
		// Several matches, display id => name list.
		QString out = tr("Several players found, please use ID:");
		for(int i = 0, j = list.size(); i < j; i++)
			out += tr(" %1 => %2^7,", "id => name player list")
				.arg(list[i])
				.arg(get(list[i], "name"));
		// Remove last comma
		zUrt::instance()->server()->tell(admin, out.left(out.size() - 1) + '.');
	}
	return -1;
}

bool Module_Player::connected(QString id)
{
	return connected(id.toInt());
}

bool Module_Player::connected(unsigned int id)
{
	return m_players.contains(id);
}
