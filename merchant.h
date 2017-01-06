#ifndef _MERCHANT_H_
#define _MERCHANT_H_
#include <string>
#include <memory>
#include <vector>
#include "enemy.h"
#include "meHorde.h"

class Merchant: public Enemy {
	std::shared_ptr<meHorde> mh;
public:
	Merchant();
	std::shared_ptr<meHorde> getHorde(); // get mh
	std::string getRace() const override;
};

#endif
