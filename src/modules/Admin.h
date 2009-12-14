#ifndef __ADMIN_H__
#define __ADMIN_H__

#include "../core/zUrt.h"
#include "Player.h"

struct Admin_Admin;
struct Admin_Command;
struct Admin_Level;

class Module_Admin : public Module
{
	Q_OBJECT

	public:
		Module_Admin();
		QString name();
		QStringList listens();

	public slots:
		void event(QString type, Arguments args);

	protected:
		bool commandPermitted(Module_Player *p, unsigned int player, Admin_Command *command);
		Admin_Command *getCommand(QString name);
		Admin_Command *getCommand(Arguments args, unsigned int index = 0);
		unsigned int getLevel(Module_Player *p, int player);
		bool adminHigher(Module_Player *p, unsigned int a, unsigned int b);
		Admin_Admin *getAdmin(unsigned int id);
		unsigned int getFreeAdminId();
		QString matchOneMap(QString map, int admin = -1);
		
	private:
		QHash<unsigned int, Admin_Level> m_levels;
		QHash<QString, Admin_Admin> m_admins;
		static Admin_Command m_commands[];
		static unsigned int m_numCommands;
		
		void cmd_generic(Module_Player *p, int player, Arguments *args, Admin_Command *command);
		void cmd_admintest(Module_Player *p, int player, Arguments *args, Admin_Command *command);
		void cmd_help(Module_Player *p, int player, Arguments *args, Admin_Command *command);
		void cmd_forceteam(Module_Player *p, int player, Arguments *args, Admin_Command *command);
		void cmd_listadmins(Module_Player *p, int player, Arguments *args, Admin_Command *command);
		void cmd_map(Module_Player *p, int player, Arguments *args, Admin_Command *command);
		void cmd_readconfig(Module_Player *p, int player, Arguments *args, Admin_Command *command);
		void cmd_setlevel(Module_Player *p, int player, Arguments *args, Admin_Command *command);
};

struct Admin_Admin
{
	unsigned int id;
	unsigned int level;
	QString guid;
	QString name;
};
struct Admin_Command
{
	QString name;
	void (Module_Admin::*handler)(Module_Player*, int, Arguments*, Admin_Command*);
	QString serverCmd; // Only used with generic handler
	bool matchPlayer; // Only used with generic handler
	unsigned int minArgs;
	QString syntax;
	QString help;
};

struct Admin_Level
{
	QString name;
	QList<Admin_Command *> commands;
};

#endif
