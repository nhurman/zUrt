#ifndef __SERVER_H__
#define __SERVER_H__

#include <QtNetwork>
#include <QTime>
#include <QFileInfo>
#include "Log.h"
#include "Sleep.h"
#include "ZipFile.h"

class Server : public QObject
{
	Q_OBJECT

	public:
		Server(QString address, quint16 port, QString password, QString path);
		QString rcon(QString command, bool reply = false);
		void say(QString texte);
		void tell(int id, QString texte);
		void map(QString name);
		void set(QString var, QString value);
		QString get(QString var);
		QStringList maps();
		bool connected();

		static QString clean(QString str);

	protected:
		QHostAddress *m_address;
		quint16 m_port;
		QString m_rcon;
		QString m_path;
		QStringList m_maps;
		
		void loadMaps();

	private:
		QUdpSocket *m_socket;
		bool m_connected;
		QTime m_interval;
};

#endif
