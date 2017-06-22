#include "basicinfo.h"

//Command Message
vector<string> vecCommandList
{
    "_S",	//CM_SHOW = Show parametre string in UI
    "_K",	//CM_KILL = ant to return the victim's ID
    "_B",	//CM_BADGE = Want to return ID vote for police
    "_E",	//CM_EXILE = Want to return ID vote for exile
    "_I",	//CM_INDICATE = Want to return ID to identify
    "_W",	//CM_WITCH = Operation of witch
    "_H",	//CM_HUNTER = Want to return ID to shoot
    "_N",	//CM_NOTE = Want to return the note
    "_C",	//CM_CHARACTER = Tell the result of pick character
    "_T",	//CM_TALK = Want return talking
    "_X",	//CM_XOTHER = Want to Move badge
    "_R",	//CM_RESULT = End Game and Show Result
    "_G",	//CM_GROUP = Begin a Group talk
    "_YA",	//CM_SYNCA = Sync alive
    "_YD",	//CM_SYNCD = Sync dying
    "_IR",	//CM_IDRES = Result of Indication
    "_V",	//CM_VOTE = Vote case
    "_SB",  //badge result
    "_ST",   //CM_STOP = stop talk
    "_PU",  //CM_PUBLIC = in public
    "_TE"   //CM_TEAM = in team
};

QString str2qstr(const string str)
{
    return QString::fromLocal8Bit(str.data());
}

string qstr2str(const QString qstr)
{
    QByteArray cdata = qstr.toLocal8Bit();
    return string(cdata);
}
