#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "../core/zUrt.h"

class Module_Player : public Module
{
	Q_OBJECT

	public:
		QString name();
		QStringList listens();
		QString get(QString id, QString key);
		QString get(unsigned int id, QString key);
		QHash<unsigned int, ConfigString> get();
		int matchOnePlayer(QString cle, int admin = -1);
		bool connected(QString id);
		bool connected(unsigned int id);

	public slots:
		void event(QString type, Arguments args);
	
	private:
		QHash<unsigned int, ConfigString> m_players;
};

#endif
