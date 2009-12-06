#ifndef ADMIN_H
#define ADMIN_H

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
		Admin_Command *getCommand(Arguments args);
		unsigned int getLevel(Module_Player *p, int player);
		bool adminHigher(Module_Player *p, unsigned int a, unsigned int b);
		
		static Admin_Command m_commands[];
		static unsigned int m_numCommands;
		
	private:
		QHash<unsigned int, Admin_Level> m_levels;
		QHash<QString, Admin_Admin> m_admins;
		
		void cmd_generic(Module_Player *p, int player, Arguments *args, Admin_Command *command);
		void cmd_admintest(Module_Player *p, int player, Arguments *args, Admin_Command *command);
		void cmd_readconfig(Module_Player *p, int player, Arguments *args, Admin_Command *command);
		void cmd_setlevel(Module_Player *p, int player, Arguments *args, Admin_Command *command);
};

struct Admin_Admin
{
	QString name;
	unsigned int level;
};		
struct Admin_Command
{
	QString name;
	void (Module_Admin::*handler)(Module_Player*, int, Arguments*, Admin_Command*);
	QString serverCmd;
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
