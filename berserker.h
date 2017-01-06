#ifndef _BERSERKER_H_
#define _BERSERKER_H_
#include <string>
#include <memory>
#include "user.h"

class Berserker: public User {
    bool revived = false;
public:
	Berserker();
	void clearBuff() override;
	void setHp(int effect) override;
    void INeverDie();
    void beingAttack(std::shared_ptr<Character> c) override;
    std::string getRace() const override;
};

#endif
