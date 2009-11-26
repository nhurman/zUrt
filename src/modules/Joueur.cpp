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
	unsigned int id = args.get(1).toInt();
	if(type == "ClientConnect")
		m_joueurs[id] = ConfigString();
	else if(type == "ClientDisconnect")
		m_joueurs.remove(id);
	else if(type == "ClientUserinfo")
		m_joueurs[id] = Arguments::fusionnerCs(m_joueurs[id], args.cs(1));
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

int Module_Joueur::matchOnePlayer(QString cle, unsigned int id_admin)
{
	QList <int> liste;
	QString nom;
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
		if(connecte(id_admin))
			zUrt::instance()->serveur()->tell(id_admin,
				tr("Aucun joueur trouve pour la recherche %1.")
				 .arg(cle)
			);
		return -1;
	}
	else if(liste.size() == 1)
		return liste[0];
	else
	{
		// Lister les joueurs avec la correspondance id => pseudo
		return -1;
	}
}

bool Module_Joueur::connecte(QString id)
{
	return connecte(id.toInt());
}

bool Module_Joueur::connecte(unsigned int id)
{
	return m_joueurs.contains(id);
}
