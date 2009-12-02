#ifndef ADMIN_H
#define ADMIN_H

#include "../core/zUrt.h"
#include "Player.h"

struct Admin_Command
{
	QString name;
	unsigned int minArgs;
	QString syntax;
	QString help;
};

struct Admin_Level
{
	QString name;
	QList<Admin_Command *> commands;
};

struct Admin_Admin
{
	QString name;
	unsigned int level;
};

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
		
		static Admin_Command m_commands[];
		static unsigned int m_numCommands;
		
	private:
		QHash<unsigned int, Admin_Level> m_levels;
		QHash<QString, Admin_Admin> m_admins;
		
		void cmd_admintest(Module_Player *p, int player);
		void cmd_readconfig(int player);
};

#endif
