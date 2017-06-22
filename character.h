/****************************************
Name: character.h

Author: 岑哲鹏

Date:2017-

Description: the classes of characters in this
    game, and these classes include the functions
    or operations of corresponding character

Copyright: all by author
****************************************/


#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>
#include "basicinfo.h"



//character base class
class cBaseCharacter
{
protected:

    //check the validility of operation of character
    virtual bool IsOperateValid() {}


    virtual  ~cBaseCharacter() = default;
};

//class for Werewolf
class cWerewolf : public cBaseCharacter
{
public:
    bool IsOperateValid(TID target, bool bAlive);

    //kill the appointed target
    void Kill(TID target, vector<state> PlayerState);
};

//class for villager
class cVillager : public cBaseCharacter{};

//class for prophet
class cProphet : public cBaseCharacter
{
private:
    vector<int> PlayerCharOfProphet;		//the characters of players which have been checked

public:
    bool IsOperateValid(TID target, bool bAlive, TID ID);
    cProphet() :PlayerCharOfProphet(PlayerTotality, UnknownPlayer) {}

    //check the character of target
    void Check(TID target, vector<state> PlayerState, TPlayerChar Playerchar);
};

//class for witch
class cWitch : public cBaseCharacter
{
private:
    bool IsAntidoteUsed;        //whether witch has used antidote
    bool IsPoisonUsed;          //whether witch has used poison

public:
    enum eAction
    {
        UseAntidote,
        UsePoison,
        DoNothing
    };
    bool IsOperateValid(int action, TID target, vector<state> PlayerState);
    cWitch() :IsAntidoteUsed(false), IsPoisonUsed(false) {}
    void Medication(int action, TID target, vector<state> PlayerState);


    bool get_poison(){return IsPoisonUsed;}
    bool get_antidote() {return IsAntidoteUsed;}
};

class cHunter : public cBaseCharacter
{
public:
    bool IsOperateValid(TID target, bool bAlive, bool doshoot);

    //shoot the character of target when hunter is dead
    void Shoot(TID target, vector<state> PlayerState, bool doshoot);
};

class cCupido :public cBaseCharacter
{
private:
    bool IsCombineUsed;

public:
    bool IsOperateValid(TID target1, TID target2, vector<state> PlayerState);
    cCupido() :IsCombineUsed(false) {}
    void Combine(TID target1, TID target2, vector<state> PlayerState);		//combine two players
};

class cGuardian :public cBaseCharacter
{
private:
    TID LastGuarded;			//the player protected at last round

public:
    bool IsOperateValid(TID target, bool bAlive, TID ID);
    void Guard(TID target, vector<state> PlayerState);				//protect an appointed player

    cGuardian() :LastGuarded(PlayerTotality) {}
};


#endif
