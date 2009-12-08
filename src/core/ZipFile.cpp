#include "ZipFile.h"

ZipFile::ZipFile(QString path)
{
	m_file = new QFile(path);
	if(!m_file->exists())
		m_valid = false;
	m_file->open(QIODevice::ReadOnly);
	m_size = m_file->size();
}

QStringList ZipFile::listFiles()
{
	if(!m_valid)
		return QStringList();
	
	readCentralDirectory();
	return m_files;
}

void ZipFile::readCentralDirectory()
{
	const unsigned int
		CD_ENDSIZE = 22,
		CD_STARTSIG = 0x504B0102,
		CD_ENDSIG = 0x504b0506,
		CD_OFFSET = 16,
		CD_FILENAME_SIZE = 28,
		CD_FILENAME = 46;
	unsigned int sig, start, end, nameSize, blockStart, jump;
	m_files = QStringList();
	
	// On standard zip files, central dir ends 22 bytes before EOF
	end = m_size - CD_ENDSIZE;
	m_file->seek(end);
	sig = m_file->read(4).toHex().toUInt(NULL, 16);
	if(sig != CD_ENDSIG)
	{
		m_valid = false;
		return;
	}
	m_file->seek(m_file->pos() + CD_OFFSET - 4);
	start = littleEndian(m_file->read(4).toHex().toUInt(NULL, 16));
	
	// Go to beginning of central dir
	m_file->seek(start);
	
	// Read file blocks
	while((blockStart = m_file->pos()) != end)
	{
		sig = m_file->read(4).toHex().toUInt(NULL, 16);
		if(sig != CD_STARTSIG)
		{
			m_valid = false;
			return;
		}
		
		// Here, we just care about file names
		m_file->seek(blockStart + CD_FILENAME_SIZE);
		jump = nameSize = littleEndian(m_file->read(2).toHex().toUInt(NULL, 16), 2);
		jump += littleEndian(m_file->read(2).toHex().toUInt(NULL, 16), 2);
		jump += littleEndian(m_file->read(2).toHex().toUInt(NULL, 16), 2);
		m_file->seek(blockStart + CD_FILENAME);
		m_files << m_file->read(nameSize).constData();
		m_file->seek(blockStart + CD_FILENAME + jump);
	}
}

unsigned ZipFile::littleEndian(unsigned int n, unsigned int length)
{
	unsigned int out = 0;
	char *little = (char*) &out;
	char *big = (char*) &n;
	if(length > sizeof(int))
		length = sizeof(int);
	for(unsigned short i = length; i > 0; i--)
		little[i - 1] = big[length - i];
	return out;
}
