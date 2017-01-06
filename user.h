#ifndef _USER_H_
#define _USER_H_
#include "character.h"

enum class State {Chamber, Stair};

class User: public Character {
    std::vector <std::string> usedP;
	State curState;
    int x;
    int y;
    bool killedMerchant = false;
    bool chaosPotion = false; // this will be true if the user used potion called CP
public:
    User(int hp, int att, int def, double gold = 0, int crit = 0);
	State getState() const; // get curState
	void setState(State s); // set curState
	double getGold() const; // get gold
	virtual void clearBuff() = 0;
	virtual void setAtt(int effect); // set att
	virtual void setDef(int effect); // set def
	virtual void setHp(int effect) = 0; // set hp
    void setCrit(int effect);
	int getDef() const; // get def
    void beingAttack(std::shared_ptr<Character> c) override;
    void addPotion(std::string p); // add used potion to usedP.
    bool checkPotion(std::string p); // return true if the user used the potion.
    int getX() const; // get x
    int getY() const; // get y
    void toggleCP(); // make chaosPotion true if it's false, make it false otherwise
    bool getCP(); // return chaosPotion status
    void setPosn(const int x_x, const int y_y); // set x and y
    void setMerDeath(); // set killedMerchant
    bool getMerDeath(); // get killedMerchant
    ObjType getType() const override; // get ObjType
    virtual ~User();
};

#endif
