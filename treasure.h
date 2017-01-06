#ifndef _TREASURE_H_
#define _TREASURE_H_
#include "object.h"
#include "user.h"

class Treasure: public Object {
protected:
	int gold;
	bool canBeOpened;
public:
    Treasure(int gold, bool open = true);
	int goldValue();
    //void attack(std::shared_ptr<Object> obj) override;
    void attack(std::shared_ptr<Object> obj);
    void beingAttack(std::shared_ptr<Character> obj) override;
    ObjType getType() const override;
    virtual std::string getRace() const override = 0;
    virtual bool open();
};

#endif
