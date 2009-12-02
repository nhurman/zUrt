#include "Admin.h"

// Sorted commands list, see Admin.h for syntax.
Admin_Command Module_Admin::m_commands[] = {
	{	tr("admintest"), 0, "",
		tr("Displays your admin level.")
	},
	{	tr("kick"), 1, tr("[^3name^7|^3id^7]"),
		tr("Kicks a player from the server.")
	},
	{	tr("mute"), 1, tr("[^3name^7|^3id^7]"),
		tr("Mutes a player.")
	},
	{	tr("readconfig"), 0, "",
		tr("Reloads admins and levels.")
	}
};

unsigned int Module_Admin::m_numCommands =
	sizeof(Module_Admin::m_commands) / sizeof(Admin_Command);

Module_Admin::Module_Admin()
{
	cmd_readconfig(-1);
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
	unsigned int admin = args.get(0).toInt();
	
	// Only keep said text
	args.truncate(2);
	
	Admin_Command *command = getCommand(args);
	if(!command)
		return;
	
	// Can the player use this command ?
	unsigned int level = getLevel(p, admin);
	if(!m_levels[level].commands.contains(command))
	{
		zUrt::instance()->server()->tell(admin,
			tr("^3!%1^7 : Access denied.")
			.arg(command->name)
		);
		return;
	}
	
	// Are there enough arguments ?
	if(args.size() <= command->minArgs)
	{
		zUrt::instance()->server()->tell(admin,
			tr("Syntax : ^3!%1^7 %2")
			.arg(command->name)
			.arg(command->syntax)
		);
		return;
	}
	
	// Command execution
	if(command->name == "admintest")
		cmd_admintest(p, admin);
	else if(command->name == "kick")
	{
		int player = p->matchOnePlayer(args.get(1), admin);
		if(player != -1)
			zUrt::instance()->server()->kick(player);
	}
	else if(command->name == "mute")
	{
		int player = p->matchOnePlayer(args.get(1), admin);
		if(player != -1)
			zUrt::instance()->server()->mute(player);
	}
	else if(command->name == "readconfig")
		cmd_readconfig(admin);
}

Admin_Command *Module_Admin::getCommand(Arguments args)
{
	QString name = args.get(0);
	if(name[0] != '!')
		return NULL;
	
	name = name.right(name.size() - 1);
	Admin_Command *command = NULL;
	for(unsigned int i = 0; i < m_numCommands; i++)
		if(m_commands[i].name == name)
			command = &m_commands[i];
	return command;
}

unsigned int Module_Admin::getLevel(Module_Player *p, int player)
{
	unsigned int level = 0;
	QString guid = p->get(player, "cl_guid");
	if(m_admins.contains(guid))
		level = m_admins[guid].level;
	return level;
}

//////////////
// COMMANDS //
//////////////

void Module_Admin::cmd_admintest(Module_Player *p, int player)
{
	unsigned int level = getLevel(p, player);
	
	zUrt::instance()->server()->say(
		tr("^3!admintest^7 : %1^7 is a %2^7 (level %3).")
		.arg(p->get(player, "name"))
		.arg(m_levels[level].name)
		.arg(level)
	);
}

void Module_Admin::cmd_readconfig(int player)
{
	QSettings *config = NULL;
	
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
			m_admins[admins[i]].name = config->value("name").toString();
			m_admins[admins[i]].level = config->value("level").toInt();
			if(!m_levels.contains(m_admins[admins[i]].level))
				m_admins[admins[i]].level = 0;
			config->endGroup();
		}
		delete config;
	}
	
	QString out =
		tr("^3!readconfig^7 : %1 levels", "", m_levels.size())
			.arg(m_levels.size())
		+ " " + tr("and %2 admins loaded.", "", m_admins.size())
			.arg(m_admins.size());
	
	if(player == -1)
		Log::instance("admin")->information(out);
	else
		zUrt::instance()->server()->tell(player, out);
}
