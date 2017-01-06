#ifndef _ENEMY_H_
#define _ENEMY_H_
#include <memory>
#include "character.h"

class Enemy: public Character {
protected:
	bool hostile = false;
	int moves = 0;
public:
    Enemy(int hp, int att, int def, double gold = 0, int crit = 0);
	virtual void toggleHostile();
    virtual void hostileOn(); // turn hostile to true
    virtual void hostileOff(); // turn hostile to false
	bool getHostile() const; // get hostile
	int getMove() const; // get moves
	void addMove(); // add moves by 1
	void beingAttack(std::shared_ptr <Character> c) override;
    ObjType getType() const override;
};

#endif
