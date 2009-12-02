#ifndef __SLEEP_H__
#define __SLEEP_H__

#include <QThread>

class Sleep : public QThread
{
	public:
		static void sleep(unsigned long secs)
		{
			QThread::sleep(secs);
		}
		static void msleep(unsigned long msecs)
		{
			QThread::msleep(msecs);
		}
		static void usleep(unsigned int usecs)
		{
			QThread::usleep(usecs);
		}
};


#endif
