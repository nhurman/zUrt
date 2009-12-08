#ifndef __ZIPFILE_H__
#define __ZIPFILE_H__

#include <QStringList>
#include <QFile>

/*
 * For ZIP file format, see
 * http://www.onicos.com/staff/iz/formats/zip.html
 */


class ZipFile
{
	public:
		ZipFile(QString path);
		QStringList listFiles();
		static unsigned int littleEndian(unsigned int n, unsigned int length = 4);
	
	private:
		QFile *m_file;
		QDataStream *m_stream;
		unsigned int m_size;
		bool m_valid;
		QStringList m_files;
		
		void readCentralDirectory();
};

#endif
