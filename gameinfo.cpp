#include "gameinfo.h"

void PlayerInfo::DefIdentity()
{
    switch (m_nch)
    {
    case werewolf:
        pBaseIdentity = new cWerewolf;
        m_strIdentity = "werewolf";
        break;
    case villager:
        pBaseIdentity = new cVillager;
        m_strIdentity = "Villager";
        break;
    case prophet:
        pBaseIdentity = new cProphet;
        m_strIdentity = "prophet";
        break;
    case witch:
        pBaseIdentity = new cWitch;
        m_strIdentity = "witch";
        break;
    case hunter:
        pBaseIdentity = new cHunter;
        m_strIdentity = "hunter";
        break;
    default:
        break;
    }
}


PlayerInfo::PlayerInfo(std::string strName)
    :m_strIdentity(), m_stateSelf()
{
    m_nch = -1;
    m_strPlayerName = strName;
    DefIdentity();
}


std::string PlayerInfo::GetName()
{
    return m_strPlayerName;
}


void GameInfo::Parse(const string & str, string &strComm, string &strPara)
{
    if (str.empty())
    {
        return;
    }
    strComm = str.substr(0, str.find("|")); //strComm stores the command
    strPara = str.substr(1 + str.find("|"));//strPara stores the parameter

}


void GameInfo::DoParametres
(
    int nComm,	//Case of Command
    const string & str	//Parametre of Command
)
{
    //这里的注释将使用中文

    vector<bool> validtarget(PlayerTotality, false);//可以被操作的目标，此vector将用于UI显示

    switch (nComm) {

    //指令为在UI上显示
    case CM_SHOW:
        pmainwindow->addLine(str);
        break;


    //指令为狼人杀人，参数str为可以被杀的目标
    //例如，玩家0,2,5,6可以杀，那么str为"0 2 5 6"
    case CM_KILL:
    {
        if (PlayerSelf.m_nch == werewolf
            &&PlayerSelf.m_stateSelf.bAlive)
        {
            int end=0;
            while(end<str.size()){
                validtarget[int(str[end])-48]=true;
                end += 2;
            }

            pmainwindow->setButtons(CM_KILL,validtarget);

        }
        break;
    }

    //指令为选警长，参数与狼人杀人同理
    case CM_BADGE:
    {
        if (PlayerSelf.m_stateSelf.bAlive)
        {
            int end=0;
            while(end<str.size()){
                validtarget[int(str[end])-48]=true;
                end += 2;
            }
            pmainwindow->setButtons(CM_BADGE,validtarget);
        }
        break;
    }

    //指令为白天票人，参数与狼人杀人同理
    case CM_EXILE:
    {
        if (PlayerSelf.m_stateSelf.bAlive)
        {
            int end=0;
            while(end<str.size()){
                validtarget[int(str[end])-48]=true;
                end += 2;
            }
            pmainwindow->setButtons(CM_EXILE,validtarget);
        }
        break;
    }


    //指令为预言家查人
    case CM_INDICATE:
    {
        if (PlayerSelf.m_nch == prophet     //如果本人是预言家
            &&PlayerSelf.m_stateSelf.bAlive)//且活着
        {
            for (int i = 0;i < PlayerTotality;++i)  //可操作目标为目前活着的人
                validtarget[i] = playerstate[i].bAlive;
            validtarget[PlayerSelf.get_ID()]=false;

            pmainwindow->setButtons(CM_INDICATE,validtarget);

        }
        break;
    }

    //指令为女巫进行操作
    case CM_WITCH:
    {
        if (PlayerSelf.m_nch == witch
            &&PlayerSelf.m_stateSelf.bAlive)//如果本人为女巫且活着
        {
            cWitch* WitchPlayer = dynamic_cast<cWitch*>(PlayerSelf.pBaseIdentity);
            int antidotetarget=0;
            QString msg;

            for (int i = 0;i < PlayerTotality;++i){

                //可被操作目标根据IsOperationValid函数确定，这里的可被操作目标指的是可以被毒死的目标
                validtarget[i] = WitchPlayer->IsOperateValid(WitchPlayer->UsePoison, i, playerstate);

                if(WitchPlayer->IsOperateValid(WitchPlayer->UseAntidote, i, playerstate))
                    antidotetarget=i;       //这里指的是可以被解药救的目标
            }
            msg = str2qstr(to_string(antidotetarget+1)) + "号玩家被狼人杀了";

            if(!WitchPlayer->get_antidote())    //如果女巫有解药，UI将显示被杀者
                pmainwindow->addLine(msg,teamMsg);
            pmainwindow->setButtons(CM_WITCH,validtarget,WitchPlayer->get_poison(),WitchPlayer->get_antidote());
        }
        break;
    }

    //指令为猎人狙人
    case CM_HUNTER:
    {
        if (PlayerSelf.m_nch == hunter)     //如果本人是猎人
        {
            cHunter* HunterPlayer = dynamic_cast<cHunter*>(PlayerSelf.pBaseIdentity);
            for (int i = 0;i < PlayerTotality;++i)
                validtarget[i] = playerstate[i].bAlive; //可操作目标为目前活着的人

            if (!PlayerSelf.m_stateSelf.bAlive)
            {
                pmainwindow->setButtons(CM_HUNTER,validtarget);
            }
        }
        break;
    }

    //指令为留遗言
    case CM_NOTE:
    {
        if (!PlayerSelf.m_stateSelf.bAlive)
        {
            pmainwindow->setButtons(CM_NOTE);
        }
        break;
    }

    //指令为分配身份和ID
    case CM_CHARACTER:
    {
        string strID(str.substr(str.find("|") + 1, str.find(" "))),
            strCharacter(str.substr(str.find(" ") + 1));

        PlayerSelf.set_ID(stoi(strID));
        PlayerSelf.m_nch = stoi(strCharacter);
        pmainwindow->setId(PlayerSelf.get_ID());
        pmainwindow->setIdentity((enIdentity)PlayerSelf.m_nch);
        PlayerSelf.DefIdentity();
        break;
    }

    //指令为白天发言
    case CM_TALK:
    {
        pmainwindow->setButtons(CM_TALK);
        break;
    }

    //指令为转移警徽
    case CM_XOTHER:
    {
        if (PlayerSelf.m_stateSelf.bBadged)//如果本人现为警长
        {
            for (int i = 0;i < PlayerTotality;++i)
                validtarget[i] = playerstate[i].bAlive;//可操作目标为目前活着的人
            pmainwindow->setButtons(CM_XOTHER,validtarget);
            PlayerSelf.m_stateSelf.bBadged = false;
        }
        break;
    }

    //指令为公布最终结果
    case CM_RESULT:
    {
        vector<int> vecIdentity(PlayerTotality,0);
        string identity,result;
        QString msg;
        identity = str.substr(0,str.find(" "));
        result = str.substr(str.find(" "));
        if(identity.size()==8)
        {
            for(int i=0;i<PlayerTotality;++i)
                vecIdentity[i]=identity[i]-48;
        }
        if(stoi(result)==1)
            msg = "村民获胜，请村民发表胜利感言";
        else
            msg = "狼人获胜，请开始你们的表演";
        pmainwindow->addLine(msg,progressMsg);
        pmainwindow->showIdentity(vecIdentity);
        pmainwindow->resetGame();
        break;
    }

    //指令为狼人内部自由讨论
    case CM_GROUP:
    {
        pmainwindow->setButtons(CM_GROUP);
        break;
    }

    //指令为同步存活情况
    //参数为一个01串
    //例如0,3,4号玩家死亡，其余或者，参数为01100111
    case CM_SYNCA:
    {
        for (int i = 0;i < PlayerTotality;++i)
        {
            if (str[i] == '0'
                    &&playerstate[i].bAlive==true){
                playerstate[i].bAlive = false;
                pmainwindow->die(i);    //如果一个玩家本来是活的，同步后死了，将在UI上显示"死"
            }
            else
                if (str[i] == '1')
                    playerstate[i].bAlive = true;
        }
        PlayerSelf.m_stateSelf.bAlive = playerstate[PlayerSelf.get_ID()].bAlive; //并同步本人状态
        break;
    }

    //指令为同步濒死状态的人（被狼人杀了但天还没亮）
    case CM_SYNCD:
    {
        for (int i = 0;i < PlayerTotality;++i)
        {
            if (str[i] == '0')
                playerstate[i].bDying = false;
            else
                if (str[i] == '1')
                    playerstate[i].bDying = true;
        }
        PlayerSelf.m_stateSelf.bDying = playerstate[PlayerSelf.get_ID()].bDying;
        break;
    }

    //指令为返回预言家查人结果
    //参数为被查者ID以及其身份
    //例如查的结果为0号为好人，参数为"0 0"，但是最后UI显示为”1号是好人“（没有0号）
    case CM_IDRES:
    {
        if (PlayerSelf.m_nch == prophet
            &&PlayerSelf.m_stateSelf.bAlive)
        {
            string indicatee,result;
            indicatee = str.substr(0,str.find(" "));
            result = str.substr(str.find(" "));
            QString msg = "玩家";
            msg += QString::number((stoi(indicatee)+1),10);
            if(stoi(result)==0)
                msg += "是好人";
            else
                msg += "是狼";
            pmainwindow->addLine(msg,teamMsg);
        }
        break;
    }

    //指令为同步警长状况
    case CM_SYNCBADGE:
    {
        int police=stoi(str);
        for(int i=0;i<PlayerTotality;++i)
        {
            if(i==police){
                playerstate[i].bBadged=true;
                pmainwindow->showBadge(i);//本来不是警长，现在是了，显示警徽
            }
            else
                pmainwindow->hideBadge(i);//本来是现在不是，隐藏警徽
        }
        if(police==PlayerSelf.get_ID())
            PlayerSelf.m_stateSelf.bBadged=true;//同步自身状态
        break;
    }

    //显示投票结果
    case CM_VOTE:
    {
        string voter,votee;
        voter=str.substr(0,str.find('~'));
        votee=str.substr(str.find('~')+1);
        if(playerstate[stoi(voter)-1].bAlive)
        {
            QString voteresult= "玩家";
            voteresult += str2qstr(str.substr(0,str.find('~')));
            if(stoi(votee) > PlayerTotality)
                voteresult += "弃票";
            else
            {
                voteresult += "投了";
                voteresult+=str2qstr(votee);
            }

            pmainwindow->addLine(voteresult);
        }
        break;
    }

    //指令为在公共频道显示，如所有人的白天发言，遗言等
    case CM_PUBLIC:
    {
        pmainwindow->addLine(str,publicMsg);
        break;
    }

    //指令为在团队频道显示，如狼人讨论
    case CM_TEAM:
    {
        pmainwindow->addLine(str,teamMsg);
        break;
    }
    default:
        break;
    }
    validtarget.~vector();
}


void GameInfo::Feedback(enCommandList nResp, int target, string str, eAction action) {


    string msg;     //最终msg格式为"_XXX|YYYYYY"

    switch (nResp)
    {
    case CM_SHOW:
        break;


    case CM_KILL:{
        cWerewolf* WerewolfPlayer = dynamic_cast<cWerewolf*>(PlayerSelf.pBaseIdentity);
        WerewolfPlayer->Kill(target, playerstate);
        msg = "_K|" + to_string(target);
        pmainwindow->client->SendMsg(msg.c_str(), LEN(msg));
        break;
    }

    case CM_BADGE:{
        msg = "_B|"+to_string(PlayerSelf.get_ID()+1);
        msg += "~";
        msg += to_string(target+1);
        pmainwindow->client->SendMsg(msg.c_str(), LEN(msg));
        break;
    }

    case CM_EXILE:{
        msg = "_E|"+to_string(PlayerSelf.get_ID()+1);
        msg += "~";
        msg += to_string(target+1);
        pmainwindow->client->SendMsg(msg.c_str(), LEN(msg));
        break;
    }

    case CM_INDICATE:{
        msg = "_I|" + to_string(target);
        pmainwindow->client->SendMsg(msg.c_str(), LEN(msg));
        break;
    }

    //指令为女巫进行操作
    case CM_WITCH:{
        cWitch* WitchPlayer = dynamic_cast<cWitch*>(PlayerSelf.pBaseIdentity);
        if (action  == UsePoison)   //如果女巫用毒药
        {
            WitchPlayer->Medication(WitchPlayer->UsePoison, target, playerstate);
            msg = "_P|" + to_string(target);    //response指令为_P
            pmainwindow->client->SendMsg(msg.c_str(), LEN(msg));
        }
        else
        {
            if (action == UseAntidote) //如果女巫用解药
            {
                for (int i = 0;i < PlayerTotality;++i){
                    if(WitchPlayer->IsOperateValid(WitchPlayer->UseAntidote, i, playerstate))
                        target=i;
                }

                msg = "_A|" + to_string(target);    //response指令为_A
                pmainwindow->client->SendMsg(msg.c_str(), LEN(msg));
                WitchPlayer->Medication(WitchPlayer->UseAntidote, target, playerstate);
            }
            else    //女巫什么都不干
            {
                msg = "_W|";        //response指令为_W
                pmainwindow->client->SendMsg(msg.c_str(), LEN(msg));
            }
        }
        break;
    }

    case CM_HUNTER:{
        cHunter* HunterPlayer = dynamic_cast<cHunter*>(PlayerSelf.pBaseIdentity);
        if (target != REFUZE ) {
            HunterPlayer->Shoot(target, playerstate, action);
            msg = "_H|" + to_string(target);
            pmainwindow->client->SendMsg(msg.c_str(), LEN(msg));
        }
        else {
            msg = "_H|" + to_string(REFUZE);//猎人不狙，参数为REFUZE（951）
            pmainwindow->client->SendMsg(msg.c_str(), LEN(msg));
        }

        break;
    }
    case CM_NOTE:{
        if (target != REFUZE) {
            msg = "_N|" + to_string(PlayerSelf.get_ID()); //死者还没讲完遗言时，response指令为_N
            msg += " : ";
            msg += str;
            pmainwindow->client->SendMsg(msg.c_str(), LEN(msg));
        }

        else {
            msg = "_ST|" + to_string(REFUZE);   //时间到或结束遗言时，response指令为_ST
            pmainwindow->client->SendMsg(msg.c_str(), LEN(msg));
        }
        break;
    }
    case CM_CHARACTER:
        break;

    case CM_TALK:{
        //正常发言与遗言基本同理
        if (target != REFUZE) {
            msg = "_T|Player " + to_string(PlayerSelf.get_ID() + 1);//没讲完，response指令为_T
            msg += " : ";
            msg += str;
            pmainwindow->client->SendMsg(msg.c_str(), LEN(msg));
        }

        else {
            msg = "_ST|";
            pmainwindow->client->SendMsg(msg.c_str(), LEN(msg));
        }
        break;
    }
    case CM_XOTHER:{
        if (target != REFUZE) {
            msg = "_X|" + to_string(target);
            pmainwindow->client->SendMsg(msg.c_str(), LEN(msg));
        }
        else {
            msg = "_X|" + to_string(REFUZE);//撕警徽，参数为REFUZE（951）
            pmainwindow->client->SendMsg(msg.c_str(), LEN(msg));
        }
        break;
    }
    case CM_RESULT:
        break;

    case CM_GROUP:
    {
        //狼人讨论与正常发言同理，但是他们的讨论是自由的，没有顺序的
        if (target != REFUZE) {
            msg = "_T|" + to_string(PlayerSelf.get_ID()+1);
            msg += " : ";
            msg += str;

            pmainwindow->client->SendMsg(msg.c_str(), LEN(msg));
        }

        else {
            msg = "_ST|" + to_string(REFUZE);
            pmainwindow->client->SendMsg(msg.c_str(), LEN(msg));
        }
        break;
    }
    case CM_SYNCA:
        break;
    case CM_SYNCD:
        break;
    case CM_IDRES:
        break;
    case CM_VOTE:
        break;
    case CM_PUBLIC:
        break;
    case CM_TEAM:
        break;
    default:break;
    }


}
