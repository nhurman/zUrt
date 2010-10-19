#ifndef __BAN_H_
#define __BAN_H_

#include <QObject>
#include <QString>
#include <QList>
#include <QDateTime>
#include <QSettings>
#include <QHash>

#include "../core/zUrt.h"
#include "Admin.h"

struct Ban_Ban;

class Module_Ban : public Module
{
	Q_OBJECT

	public:
		Module_Ban();
		QString name();
		QStringList listens();
		unsigned int ban(QString ip, QString guid, QString name, QString admin, QDateTime expiration);
		void readConfig();

	public slots:
		void event(QString type, Arguments args);

	protected:
		bool isBanned(QString ip, QString guid, short mode = MATCH_ANY);
		int getBanId(QString ip, QString guid, short mode = MATCH_ALL);

	private:
		QHash<unsigned int, Ban_Ban> m_bans;

		void writeConfig();

		enum
		{
			MATCH_ANY,
			MATCH_ALL
		};
};

struct Ban_Ban
{
	unsigned int id;
	QString ip;
	QString guid;
	QString name;
	QString admin;
	QDateTime expiration;
};

#endif
