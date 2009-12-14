#include "Admin.h"

// Sorted commands list, see Admin.h for syntax.
Admin_Command Module_Admin::m_commands[] = {
	{	tr("admintest"), &Module_Admin::cmd_admintest, "", false,
		0, "",
		tr("Displays your admin level.")
	},
	{	tr("bigtext"), &Module_Admin::cmd_generic, "bigtext", false,
		1, tr("[^5text^7]"),
		tr("Prints text at the center of player's screens.")
	},
	{	tr("cyclemap"), &Module_Admin::cmd_generic, "cyclemap", false,
		0, "",
		tr("Loads next map.")
	},
	{	tr("forceteam"), &Module_Admin::cmd_forceteam, "", false,
		2, tr("[^5name^7|^5id^7] [^5auto^7|^5blue^7|^5red^7|^5spec^7]"),
		tr("Forces a player to join a team (team's first letter is enough).")
	},
	{	tr("help"), &Module_Admin::cmd_help, "", false,
		0, tr("(^5command^7)"),
		tr("Lists available commands. Adding the command name gives specific help.")
	},
	{	tr("kick"), &Module_Admin::cmd_generic, "clientkick", true,
		1, tr("[^5name^7|^5id^7]"),
		tr("Kicks a player from the server.")
	},
	{	tr("listadmins"), &Module_Admin::cmd_listadmins, "", false,
		0, tr("(^5level^7) (^5name^7)"),
		tr("Lists the administrators.")
	},
	{	tr("map"), &Module_Admin::cmd_map, "", false,
		1, tr("[^5name^7]"),
		tr("Loads a map.")
	},
	{	tr("nextmap"), &Module_Admin::cmd_map, "", false,
		1, tr("[^5name^7]"),
		tr("Changes next map.")
	},
	{	tr("mute"), &Module_Admin::cmd_generic, "mute", true,
		1, tr("[^5name^7|^5id^7]"),
		tr("Mutes a player.")
	},
	{	tr("readconfig"), &Module_Admin::cmd_readconfig, "", false,
		0, "",
		tr("Reloads admins and levels.")
	},
	{	tr("restart"), &Module_Admin::cmd_generic, "map_restart", false,
		0, "",
		tr("Restarts the current map.")
	},
	{	tr("setlevel"), &Module_Admin::cmd_setlevel, "", false,
		2, tr("[^5name^7|^5id^7] [^5level^7]"),
		tr("Sets a player's admin level.")
	},
	{	tr("shuffleteams"), &Module_Admin::cmd_generic, "shuffleteams", false,
		0, "",
		tr("Shuffles teams.")
	},
	{	tr("slap"), &Module_Admin::cmd_generic, "slap", true,
		1, tr("[^5name^7|^5id^7]"),
		tr("Slaps a player.")
	},
	{	tr("veto"), &Module_Admin::cmd_generic, "veto", false,
		0, "",
		tr("Cancels the current vote.")
	}
};

unsigned int Module_Admin::m_numCommands =
	sizeof(m_commands) / sizeof(Admin_Command);

Module_Admin::Module_Admin()
{
	cmd_readconfig(NULL, -1, NULL, NULL);
}

QString Module_Admin::name()
{
	return "Admin";
}

QStringList Module_Admin::listens()
{
	return QStringList() << "say";
}

void Module_Admin::event(QString /*type*/, Arguments args)
{
	Module_Player *p = dynamic_cast<Module_Player*>(
		zUrt::instance()->module("Player"));
	unsigned int admin = args.get(0).toUInt();
	
	// Only keep said text
	args.truncate(2);
	
	Admin_Command *command = getCommand(args);
	if(!command)
		return;
	
	// Can the player use this command ?
	if(!commandPermitted(p, admin, command))
	{
		zUrt::instance()->server()->tell(admin,
			tr("^3!%1^7: Access denied.")
			.arg(command->name)
		);
		return;
	}
	
	// Are there enough arguments ?
	if(args.size() <= command->minArgs)
	{
		zUrt::instance()->server()->tell(admin,
			tr("Syntax: ^3!%1^7 %2")
			.arg(command->name)
			.arg(command->syntax)
		);
		return;
	}
	
	// Execute the handler
	(this->*command->handler)(p, admin, &args, command);
}

bool Module_Admin::commandPermitted(Module_Player *p, unsigned int player, Admin_Command *command)
{
	unsigned int level = getLevel(p, player);
	return m_levels[level].commands.contains(command);
}

Admin_Command *Module_Admin::getCommand(QString name)
{
	if(name[0] != '!')
		return NULL;
	
	name = name.right(name.size() - 1);
	Admin_Command *command = NULL;
	for(unsigned int i = 0; i < m_numCommands; i++)
		if(m_commands[i].name == name)
			command = &m_commands[i];
	return command;
}

Admin_Command *Module_Admin::getCommand(Arguments args, unsigned int index)
{
	return getCommand(args.get(index));
}

unsigned int Module_Admin::getLevel(Module_Player *p, int player)
{
	unsigned int level = 0;
	QString guid = p->get(player, "cl_guid");
	if(m_admins.contains(guid))
		level = m_admins[guid].level;
	return level;
}

bool Module_Admin::adminHigher(Module_Player *p, unsigned int a, unsigned int b)
{
	unsigned int la, lb;
	// Also check in configuration - doesn't have to be connected to test his level
	if(a > 100)
	{
		Admin_Admin *admin = NULL;
		if(!(admin = getAdmin(a)))
			return false; // Should have been checked before calling adminHigher
		la = admin->level;
	}
	else
		la = getLevel(p, a);
	if(b > 100)
	{
		Admin_Admin *admin = NULL;
		if(!(admin = getAdmin(b)))
			return false;
		lb = admin->level;
	}
	else
		lb = getLevel(p, b);
	return la >= lb;
}

Admin_Admin *Module_Admin::getAdmin(unsigned int id)
{
	QHashIterator<QString, Admin_Admin> i(m_admins);
	while(i.hasNext())
	{
		i.next();
		if(i.value().id == id)
			return &m_admins[i.key()];
	}
	return NULL;
}

unsigned int Module_Admin::getFreeAdminId()
{
	unsigned int id = 101;
	foreach(Admin_Admin admin, m_admins)
		if(id == admin.id)
			id++;
	return id;
}

QString Module_Admin::matchOneMap(QString map, int admin)
{
	QStringList maps = zUrt::instance()->server()->maps().filter(map);
	/*
	for(int i = 0; i < maps.count(); i++)
	{
		if(!list.contains(maps[i]))
			list.push_back(maps[i]);
	}*/
	
	if(maps.isEmpty())
	{
		zUrt::instance()->server()->tell(admin,
			tr("No map found.")
		);
	}
	else if(maps.size() == 1)
		return maps[0];
	else
	{
		QString out = tr("Several maps found, please be more precise:");
		for(int i = 0, j = maps.size(); i < j; i++)
			out += tr(" %1,")
				.arg(maps[i]);
		// Remove last comma
		zUrt::instance()->server()->tell(admin, out.left(out.size() - 1) + '.');
	}
	return "";
}


//////////////
// COMMANDS //
//////////////

void Module_Admin::cmd_generic(Module_Player *p, int player, Arguments *args, Admin_Command *command)
{
	if(command->minArgs == 0)
		zUrt::instance()->server()->rcon(command->serverCmd);
	else if(command->minArgs == 1)
	{
		if(!command->matchPlayer)
		{
			zUrt::instance()->server()->rcon(
				command->serverCmd +
				" \"^7" + Server::clean(args->get(1, true)) + "\""
			);
			return;
		}
		int target = p->matchOnePlayer(args->get(1), player);
		if(target < 0)
				return;
		if(!adminHigher(p, player, target))
		{
			zUrt::instance()->server()->tell(player,
				tr("^3!%1^7: Your target has a higher admin level than you.")
				.arg(command->name)
			);
			return;
		}
		zUrt::instance()->server()->rcon(command->serverCmd + " "
			+ QString::number(target));
	}
}

void Module_Admin::cmd_admintest(Module_Player *p, int player, Arguments */*args*/, Admin_Command *command)
{
	unsigned int level = getLevel(p, player);

	zUrt::instance()->server()->say(
		tr("^3!%1^7: %2^7 is a %3^7 (level %4).")
		.arg(command->name)
		.arg(p->get(player, "name"))
		.arg(m_levels[level].name)
		.arg(level)
	);
}

void Module_Admin::cmd_forceteam(Module_Player *p, int player, Arguments *args, Admin_Command *command)
{
	QChar letter = args->get(2).at(0);
	QHash <QChar, QString> teams;
		teams['b'] = "blue";
		teams['r'] = "red";
		teams['a'] = "free";
		teams['s'] = "spectator";
	
	if(!teams.contains(letter))
	{
		zUrt::instance()->server()->tell(player,
			tr("^3!%1^7: Invalid team.")
			.arg(command->name)
		);
	}
	else
	{
		int target = p->matchOnePlayer(args->get(1), player);
		if(target != -1)
			zUrt::instance()->server()->rcon(
				"forceteam " + QString::number(target) + " " + teams[letter]
			);
	}
}

void Module_Admin::cmd_help(Module_Player *p, int player, Arguments *args, Admin_Command *command)
{
	if(args->size() == 1)
	{
		unsigned int num = 0;
		QString out = "";
		for(unsigned int i = 0; i < m_numCommands; i++)
			if(commandPermitted(p, player, &m_commands[i]))
			{
				num++;
				out += tr(" !%1,").arg(m_commands[i].name);
			}
		out = tr("^3!%1^7: %n commands available:", "", num)
			.arg(command->name)
			+ out;
		zUrt::instance()->server()->tell(player, out.left(out.size() - 1) + '.');
		return;
	}
	
	QString name = args->get(1);
	if(name[0] != '!')
		name = '!' + name;
	Admin_Command *help = getCommand(name);
	if(!help)
	{
		zUrt::instance()->server()->tell(player,
			tr("^3!%1^7: Unknown command.")
			.arg(command->name)
		);
		return;
	}
	
	if(!commandPermitted(p, player, help))
	{
		zUrt::instance()->server()->tell(player,
			tr("^3!%1^7: Access to ^3!%2^7 denied.")
			.arg(command->name)
			.arg(help->name)
		);
		return;
	}
	
	zUrt::instance()->server()->tell(player,
		tr("Syntax: ^3!%1^7%2.")
		.arg(help->name)
		.arg(help->syntax != "" ? ' ' + help->syntax : "")
	);
	zUrt::instance()->server()->tell(player, help->help);
}

void Module_Admin::cmd_listadmins(Module_Player */*p*/, int player, Arguments *args, Admin_Command *command)
{
	// Check if we have got a level restriction, or a name search
	unsigned int level = 0;
	QString
		arg1 = args->get(1),
		arg2 = args->get(2);
	
	if(!arg1.isEmpty())
	{
		bool number = false;
		level = arg1.toUInt(&number);
		if(number)
		{
			if(!m_levels.contains(level))
			{
				zUrt::instance()->server()->tell(player,
					tr("^3!%1^7: Unknown level.")
					.arg(command->name)
				);
				return;
			}
		}
		else
			arg2 = arg1;
	}
	
	bool nameSearch = !arg2.isEmpty();
	
	// Get admins list, and group them by level
	QHash <unsigned int, QList<Admin_Admin> > matches;
	QHashIterator<QString, Admin_Admin> i(m_admins);
	while(i.hasNext())
	{
		i.next();
		if(	i.value().level >= level &&
			(!nameSearch
				|| Log::decolorise(i.value().name)
					.toLower()
					.contains(arg2)
			)
		)
			matches[i.value().level] << i.value();
	}
	
	// Sort levels
	unsigned int numAdmins = 0;
	QList<unsigned int> levels = matches.keys();
	qSort(levels.begin(), levels.end());
	
	// Build output
	QStringList out;
	QString tmp;
	
	foreach(unsigned int lvl, levels)
	{
		tmp = tr("%1^7:", "Level name").arg(m_levels[lvl].name);
		foreach(Admin_Admin admin, matches[lvl])
		{
			numAdmins++;
			tmp += tr(" %1^7(%2),")
				.arg(admin.name)
				.arg(admin.id);
		}
		out << tmp.left(tmp.size() - 1) + '.';
	}
	
	zUrt::instance()->server()->tell(player,
		tr("^3!%1^7: %n admins found.", "", numAdmins)
		.arg(command->name)
	);
	
	foreach(QString txt, out)
		zUrt::instance()->server()->tell(player, txt);
}

void Module_Admin::cmd_map(Module_Player */*p*/, int player, Arguments *args, Admin_Command *command)
{
	QString map = matchOneMap(args->get(1), player);
	if(map != "")
	{
		if(command->name == "map")
			zUrt::instance()->server()->rcon("map " + map);
		else if(command->name == "nextmap")
			zUrt::instance()->server()->set("g_nextmap", map);
	}
}

void Module_Admin::cmd_readconfig(Module_Player */*p*/, int player, Arguments */*args*/, Admin_Command *command)
{
	QSettings *config = NULL;
	QString name = command ? command->name : "readconfig";
	
	// Admin levels loading
	{
		config = new QSettings("config/levels.cfg", QSettings::IniFormat);
		QStringList levels = config->childGroups();
		m_levels = QHash<unsigned int, Admin_Level>();
		
		for(unsigned int i = 0, j = levels.size(); i < j; i++)
		{
			config->beginGroup(levels[i]);
			unsigned int level = levels[i].toInt();
			m_levels[level].name = config->value("name").toString();
	
			QStringList commands = config->value("commands").toString()
				.replace(" ", "").split("|");
			bool all = commands.contains("*");
			for(unsigned int k = 0; k < m_numCommands; k++)
				if(all || commands.contains(m_commands[k].name))
					m_levels[level].commands.append(&m_commands[k]);
			config->endGroup();
		}
		delete config;
	}
	
	// Admins loading
	{
		config = new QSettings("config/admins.cfg", QSettings::IniFormat);
		QStringList admins = config->childGroups();
		m_admins = QHash<QString, Admin_Admin>();
		
		for(unsigned int i = 0, j = admins.size(); i < j; i++)
		{
			config->beginGroup(admins[i]);
			m_admins[admins[i]].id = config->value("id").toUInt();
			m_admins[admins[i]].level = config->value("level").toUInt();
			m_admins[admins[i]].guid = admins[i];
			m_admins[admins[i]].name = config->value("name").toString();
			if(!m_levels.contains(m_admins[admins[i]].level))
				m_admins[admins[i]].level = 0;
			config->endGroup();
		}
		delete config;
	}
	
	QString out =
		tr("^3!%1^7: %n levels", "", m_levels.size())
		.arg(name)
		+ " " + tr("and %n admins loaded.", "", m_admins.size());
	
	if(player >= 0)
		zUrt::instance()->server()->tell(player, out);
	
	// No admins declared, give setlevel to everyone
	if(m_admins.size() == 0)
	{
		QStringList cmd = QStringList() << "!setlevel";
		m_levels[0].commands.append(getCommand(Arguments(cmd)));
	}
}

void Module_Admin::cmd_setlevel(Module_Player *p, int player, Arguments *args, Admin_Command *command)
{
	bool number = false;
	unsigned int id;
	int target = -1;
	QString guid = "", name = "";
	
	// First, check if the player is trying to access a saved admin
	id = args->get(1).toUInt(&number);
	if(number && id > 100)
	{
		Admin_Admin *admin = NULL;
		if((admin = getAdmin(id)))
		{
			target = id;
			guid = admin->guid;
			name = admin->name;
		}
	}
	
	// Admin not found, fall back to online players
	if(guid.isEmpty())
	{
		target = p->matchOnePlayer(args->get(1), player);
		if(target < 0)
			return; // Still not found - tell user
		name = p->get(target, "name");
	}
	if(!adminHigher(p, player, target))
	{
		zUrt::instance()->server()->tell(player,
			tr("^3!%1^7: Your target has a higher admin level than you.")
			.arg(command->name)
		);
		return;
	}
	
	unsigned int level = args->get(2).toUInt(&number);
	if(!number || !m_levels.contains(level))
	{
		zUrt::instance()->server()->tell(player,
			tr("^3!%1^7: Unknown level.")
			.arg(command->name)
		);
		return;
	}
	
	unsigned int myLevel = getLevel(p, player);
	if(myLevel != 0 && myLevel < level)
	{
		zUrt::instance()->server()->tell(player,
			tr("^3!%1^7: You cannot setlevel higher than your own admin level (%1).")
			.arg(command->name)
			.arg(myLevel)
		);
		return;
	}
	
	if(guid.isEmpty())
	{
		guid = p->get(target, "cl_guid");
		id = m_admins.contains(guid) ? m_admins[guid].id : getFreeAdminId();
	}
	
	QSettings *config = new QSettings("config/admins.cfg", QSettings::IniFormat);
	config->beginGroup(guid);
	
	if(level == 0)
		config->remove("");
	else
	{
		config->setValue("id", id);
		config->setValue("level", level);
		config->setValue("name", name);
	}
	
	config->endGroup();
	config->sync();
	delete config;
	
	cmd_readconfig(NULL, -1, NULL, NULL);
	
	zUrt::instance()->server()->say(
		tr("^3!%1^7: %2^7 was given %3^7 admin rights by %4^7.")
		.arg(command->name)
		.arg(name)
		.arg(m_levels[level].name)
		.arg(p->get(player, "name"))
	);
}
