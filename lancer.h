#ifndef _LANCER_H_
#define _LANCER_H_
#include <string>
#include <memory>
#include "user.h"

class Lancer: public User {
public:
	Lancer();
	void clearBuff() override;
	void setHp(int effect) override;
    void reMoney(double gold) override;
    void beingAttack(std::shared_ptr<Character> c) override;
    std::string getRace() const override;
};

#endif
