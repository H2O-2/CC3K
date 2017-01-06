#ifndef _PH_H_
#define _PH_H_
#include <string>
#include <memory>
#include "potion.h"

class User;

class PH: public Potion {
public:
	PH();
    void getEffect(std::shared_ptr<User> pc) override;
    std::string getRace() const override;
};

#endif
