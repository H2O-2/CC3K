#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#include <string>
#include <vector>
#include <memory>
#include "object.h"

class Character : public Object {
protected:
	int hp;
	int att;
	int def;
    int crit;
	double gold = 0;
public:
    Character(int hp, int att, int def, double gold, int crit);
	int getAtt(); // get the value of att
    virtual void reMoney(double money); // recalculate money for the character
    void attack(std::shared_ptr<Object> obj, std::shared_ptr<Object> mySelf); // myself attacks obj
	double getGold(); // get the value of gold
    int getHp() const; // get the value of hp
    int getCrit() const; // get the value of Crit
    virtual std::string getRace() const override = 0;
    virtual void beingAttack(std::shared_ptr<Character> c) override = 0; // character being attacked by c
};

#endif
