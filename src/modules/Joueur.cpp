#include "Joueur.h"

QString Module_Joueur::nom()
{
	return "Joueur";
}

QStringList Module_Joueur::ecoute()
{
	return QStringList()
		<< "ClientConnect"
		<< "ClientDisconnect"
		<< "ClientUserinfo";
}

void Module_Joueur::evenement(QString type, Arguments args)
{
	unsigned int id = args.get(0).toInt();
	if(type == "ClientConnect")
		m_joueurs[id] = ConfigString();
	else if(type == "ClientDisconnect")
		m_joueurs.remove(id);
	else if(type == "ClientUserinfo")
		m_joueurs[id] = Arguments::fusionnerCs(args.cs(1), m_joueurs[id]);
}

QString Module_Joueur::get(QString id, QString cle)
{
	return get(id.toInt(), cle);
}

QString Module_Joueur::get(unsigned int id, QString cle)
{
	if(!connecte(id))
		return QString();
	if(!m_joueurs[id].contains(cle))
		return QString();
	return m_joueurs[id][cle];
}

QHash<unsigned int, ConfigString> Module_Joueur::get()
{
	return m_joueurs;
}

unsigned int Module_Joueur::matchOnePlayer(QString cle, unsigned int id_admin)
{
	QList <int> liste;
	QString nom;
	bool nombre = false;
	int id = cle.toInt(&nombre);
	
	if(nombre)
	{
		if(connecte(id))
			return id;
		else
			zUrt::instance()->serveur()->tell(id_admin,
				tr("Aucun joueur trouve avec l'id %1.")
				.arg(QString::number(id))
			);
		return -1;
	}
		
	QHashIterator<unsigned int, ConfigString> i(m_joueurs);
	while(i.hasNext())
	{
		i.next();
		nom = get(i.key(), "name");
		if(nom != "" && nom.toLower().contains(cle.toLower()))
			liste << i.key();
	}
	
	if(liste.isEmpty())
	{
		zUrt::instance()->serveur()->tell(id_admin,
			tr("Aucun joueur trouve.")
		);
	}
	else if(liste.size() == 1)
		return liste[0];
	else
	{
		// Plusieurs correspondances, liste id => pseudo
		QString out = "Plusieurs joueurs ont ete trouves, "
			"veuillez utiliser l'id : ";
		for(int i = 0, j = liste.size(); i < j; i++)
			out += tr("%1 = %2^7, ")
				.arg(liste[i])
				.arg(get(i, "name"));
		zUrt::instance()->serveur()->tell(id_admin, out.left(out.size() - 2));
	}
	return -1;
}

bool Module_Joueur::connecte(QString id)
{
	return connecte(id.toInt());
}

bool Module_Joueur::connecte(unsigned int id)
{
	return m_joueurs.contains(id);
}
