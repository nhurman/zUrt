<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE TS>
<TS version="2.0" language="fr_FR" sourcelanguage="en">
<context>
    <name>Log</name>
    <message>
        <location filename="../src/core/Log.cpp" line="25"/>
        <source>[%1 %2] %3: %4</source>
        <translation>[%1 %2] %3 : %4</translation>
    </message>
    <message>
        <location filename="../src/core/Log.cpp" line="26"/>
        <source>MM/dd/yy</source>
        <translation>dd/MM/yy</translation>
    </message>
    <message>
        <location filename="../src/core/Log.cpp" line="27"/>
        <source>hh:mm</source>
        <translation>hh:mm</translation>
    </message>
    <message>
        <location filename="../src/core/Log.cpp" line="35"/>
        <source>Information</source>
        <translation>Information</translation>
    </message>
    <message>
        <location filename="../src/core/Log.cpp" line="40"/>
        <source>Error</source>
        <translation>Erreur</translation>
    </message>
</context>
<context>
    <name>LogParser</name>
    <message>
        <location filename="../src/core/LogParser.cpp" line="13"/>
        <source>Server&apos;s log not found (%1).</source>
        <translation>Log du serveur non trouvé (%1).</translation>
    </message>
</context>
<context>
    <name>Module_Admin</name>
    <message>
        <location filename="../src/modules/Admin.cpp" line="5"/>
        <source>admintest</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../src/modules/Admin.cpp" line="7"/>
        <source>Displays your admin level.</source>
        <translation>Affiche votre niveau d&apos;admin.</translation>
    </message>
    <message>
        <location filename="../src/modules/Admin.cpp" line="9"/>
        <source>kick</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../src/modules/Admin.cpp" line="10"/>
        <location filename="../src/modules/Admin.cpp" line="14"/>
        <source>[^3name^7|^3id^7]</source>
        <translation>[^3nom^7|^3id^7]</translation>
    </message>
    <message>
        <location filename="../src/modules/Admin.cpp" line="11"/>
        <source>Kicks a player from the server.</source>
        <translation>Ejecte un joueur du serveur.</translation>
    </message>
    <message>
        <location filename="../src/modules/Admin.cpp" line="13"/>
        <source>mute</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../src/modules/Admin.cpp" line="15"/>
        <source>Mutes a player.</source>
        <translation>Rend un joueur muet.</translation>
    </message>
    <message>
        <location filename="../src/modules/Admin.cpp" line="17"/>
        <source>readconfig</source>
        <translation></translation>
    </message>
    <message>
        <location filename="../src/modules/Admin.cpp" line="19"/>
        <source>Reloads admins and levels.</source>
        <translation>Recharge les administrateurs et les niveaux.</translation>
    </message>
    <message>
        <location filename="../src/modules/Admin.cpp" line="21"/>
        <source>setlevel</source>
        <translation>setlevel</translation>
    </message>
    <message>
        <location filename="../src/modules/Admin.cpp" line="22"/>
        <source>[^3name^7|^3id^7] [^3level^7]</source>
        <translation>[^3nom^7|^3id^7] [^3niveau^7]</translation>
    </message>
    <message>
        <location filename="../src/modules/Admin.cpp" line="23"/>
        <source>Sets a player&apos;s admin level.</source>
        <translation>Change le niveau d&apos;admin d&apos;un joueur.</translation>
    </message>
    <message>
        <location filename="../src/modules/Admin.cpp" line="63"/>
        <source>^3!%1^7: Access denied.</source>
        <translation>^3!%1^7 : Acces refuse.</translation>
    </message>
    <message>
        <location filename="../src/modules/Admin.cpp" line="73"/>
        <source>Syntax: ^3!%1^7 %2</source>
        <translation>Syntaxe : ^3!%1^7 %2</translation>
    </message>
    <message>
        <location filename="../src/modules/Admin.cpp" line="212"/>
        <source>^3!setlevel^7: Your target has a higher admin level than you.</source>
        <translation>^3!setlevel^7 : Votre cible a un niveau d&apos;admin plus eleve que le votre.</translation>
    </message>
    <message>
        <location filename="../src/modules/Admin.cpp" line="221"/>
        <source>^3!setlevel^7: No such level.</source>
        <translation>^3!setlevel^7 : Ce niveau n&apos;existe pas.</translation>
    </message>
    <message>
        <location filename="../src/modules/Admin.cpp" line="244"/>
        <source>^3!setlevel^7: %1^7 was given %2^7 admin rights by %3^7.</source>
        <translation>^3!setlevel^7 : %3^7 a donne les droits de %2^7 a %1^7.</translation>
    </message>
    <message>
        <location filename="../src/modules/Admin.cpp" line="134"/>
        <source>^3!admintest^7: %1^7 is a %2^7 (level %3).</source>
        <translation>^3!admintest^7: %1^7 est un  %2^7 (niveau %3).</translation>
    </message>
    <message numerus="yes">
        <location filename="../src/modules/Admin.cpp" line="187"/>
        <source>^3!readconfig^7: %n levels</source>
        <translation>
            <numerusform>^3!readconfig^7 : %n niveau</numerusform>
            <numerusform>^3!readconfig^7 : %n niveaux</numerusform>
        </translation>
    </message>
    <message numerus="yes">
        <location filename="../src/modules/Admin.cpp" line="188"/>
        <source>and %n admins loaded.</source>
        <translation>
            <numerusform>et %n admin charge.</numerusform>
            <numerusform>et %n admins charges.</numerusform>
        </translation>
    </message>
</context>
<context>
    <name>Module_Player</name>
    <message>
        <location filename="../src/modules/Player.cpp" line="59"/>
        <location filename="../src/modules/Player.cpp" line="76"/>
        <source>No players found.</source>
        <translation>Aucun joueur trouve.</translation>
    </message>
    <message>
        <location filename="../src/modules/Player.cpp" line="84"/>
        <source>Several players found, please use ID:</source>
        <translation>Plusieurs joueurs trouves, utilisez l&apos;ID :</translation>
    </message>
    <message>
        <location filename="../src/modules/Player.cpp" line="86"/>
        <source> %1 =&gt; %2^7, </source>
        <comment>id =&gt; name player list</comment>
        <translation> %1 =&gt; %2^7, </translation>
    </message>
</context>
<context>
    <name>QObject</name>
    <message>
        <location filename="../src/main.cpp" line="21"/>
        <source>---------- Starting up ----------</source>
        <translation>---------- Démarrage ----------</translation>
    </message>
</context>
<context>
    <name>Server</name>
    <message>
        <location filename="../src/core/Server.cpp" line="18"/>
        <source>Connected to %1 on port %2.</source>
        <translation>Connecté à %1 sur le port %2.</translation>
    </message>
    <message>
        <location filename="../src/core/Server.cpp" line="42"/>
        <source>Could not connect to %1 on port %2.</source>
        <translation>Connexion impossible à %1 sur le port %2.</translation>
    </message>
</context>
<context>
    <name>zUrt</name>
    <message>
        <location filename="../src/core/zUrt.cpp" line="12"/>
        <source>Hi everyone !</source>
        <comment>Bot greeting when it connects</comment>
        <translation>Salut tout le monde !</translation>
    </message>
    <message>
        <location filename="../src/core/zUrt.cpp" line="45"/>
        <source>Loading %1 module.</source>
        <translation>Chargement du module %1.</translation>
    </message>
</context>
</TS>
