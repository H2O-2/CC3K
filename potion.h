#ifndef _POTION_H_
#define _POTION_H_
#include "object.h"

class User;

class Potion: public Object {
protected:
	int effect;
public:
    Potion(int effect);
    virtual void getEffect(std::shared_ptr<User> pc) = 0;
    //void attack(std::shared_ptr<Object> obj) override;
    void attack(std::shared_ptr<Object> obj);
    void beingAttack(std::shared_ptr<Character> c) override;
    ObjType getType() const override;
    virtual std::string getRace() const override = 0;
};

#endif
