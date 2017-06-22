/****************************************
Name: basicinfo.h

Author: 林文镔，岑哲鹏，夏卓凡

Date:2017-

Description: the basic defination of
    varied, enum and vector

Copyright: all by authors
****************************************/

#ifndef BASICINFO_H
#define BASICINFO_H

#include<vector>
#include<string>
#include<QtWidgets>

using namespace std;

#define PlayerTotality 8				//the total amount of players
#define CharacterTotality 7				//the total amount of character
#define UnknownPlayer -1				//the players whose characters are unknown
#define LEN(s) 1+s.size()
#define REFUZE 951
#define MAX_SIZE 200

typedef unsigned int TID;				//to describe player's ID number (start from 0)
typedef unsigned int TPlayerChar;		//to describe player's character(look up "enum character" for specific info)

//A list of response
enum enResponseList
{
    RM_KILL,
    RM_TALK,
    RM_ANTIDOTE,
    RM_BADGE,
    RM_EXILE,
    RM_INDICATE,
    RM_NOTE,
    RM_POISON,
    RM_WITCH,
    RM_NAME,
    RM_XOHTER,
    RM_HUNTER,
    RM_GROUP,
    RM_VOTE
};

extern vector<string> vecCommandList;

//A list of command from server, and it is correspond to
//the vecCommandList.
enum enCommandList
{
    CM_SHOW,
    CM_KILL,
    CM_BADGE,
    CM_EXILE,
    CM_INDICATE,
    CM_WITCH,
    CM_HUNTER,
    CM_NOTE,
    CM_CHARACTER,
    CM_TALK,
    CM_XOTHER,
    CM_RESULT,
    CM_GROUP,
    CM_SYNCA,
    CM_SYNCD,
    CM_IDRES,
    CM_VOTE,
    CM_SYNCBADGE,
    CM_STOP,
    CM_PUBLIC,
    CM_TEAM
};

enum enIdentity
{
    werewolf, villager, prophet, witch, hunter, cupido, guardian
};

enum eAction
{
    UseAntidote,
    UsePoison,
    DoNothing
};


enum msgType
{
    progressMsg, publicMsg ,teamMsg
};

enum stateType
{
    publicState,teamState
};

enum timerType
{
    votingTimer,//“投票倒计时”
    statementTimer,//“发言倒计时”
    wolfDiscussion,//“狼人讨论倒计时”
    wolfVoting,//“狼人投票倒计时”
    witchTimer,//“女巫操作倒计时”
    prophetTimer,//“预言家操作倒计时”
    badgeTimer,//“警徽转移操作倒计时”
    noteTimer,//“遗言倒计时”
    hunterTimer,//“猎人操作倒计时”
    badgeVoting//“警长竞选投票倒计时”
};


//the state of a player, it can be modified when new
//characters such as Cupido and guardian are added
struct state
{
    bool bAlive;						//true stands for live, false stands for death
    bool bDying;						//true stands for being going to die or being killed by werewolf
    //bool IsCombined;					//true stands for being combined with another player by Cupido
    //bool IsGuarded;					//true stands for being protected from killing of werewolf by guardian
    bool bBadged;						//true stands for being the police
    state() :bAlive(true), bDying(false)
        //, IsCombined(false), IsGuarded(false)
        , bBadged(false)
    {}
};

QString str2qstr(const string str);//string转QString

string qstr2str(const QString qstr);//QString转string

#endif // BASICINFO_H
