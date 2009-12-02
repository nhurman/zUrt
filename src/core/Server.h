#ifndef __SERVER_H__
#define __SERVER_H__

#include <QtNetwork>
#include <QTime>
#include "Log.h"
#include "Sleep.h"

class Server : public QObject
{
	public:
		Server(QString address, quint16 port, QString password);
		QString rcon(QString command, bool reply = false);
		void say(QString texte);
		void tell(int id, QString texte);
		void kick(int id);
		void mute(int id);
		void reload();
		void set(QString var, QString value);
		bool connected();
		
		static QString clean(QString str);
	
	protected:
		QHostAddress *m_address;
		quint16 m_port;
		QString m_rcon;
	
	private:
		QUdpSocket *m_socket;
		bool m_connected;
		QTime m_interval;
};

#endif
