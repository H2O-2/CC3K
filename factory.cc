#include <vector>
#include <string>
#include <memory>
#include <cstdlib>
#include "factory.h"
#include "human.h"
#include "elves.h"
#include "orc.h"
#include "dwarf.h"
#include "saber.h"
#include "lancer.h"
#include "berserker.h"
#include "archer.h"
#include "werewolf.h"
#include "vampire.h"
#include "goblin.h"
#include "troll.h"
#include "phoenix.h"
#include "dragon.h"
#include "merchant.h"
#include "meHorde.h"
#include "smallHorde.h"
#include "normHorde.h"
#include "RH.h"
#include "BA.h"
#include "BD.h"
#include "PH.h"
#include "WA.h"
#include "WD.h"

using namespace std;

Factory::Factory() {
	srand(time(0));
}

shared_ptr<Object> Factory::GenPlayer(string race) {
    if (race == HUMAN) {
        shared_ptr<Object> player (new Human);
        return player;
    } else if (race == ELVES) {
        shared_ptr<Object> player (new Elves);
        return player;
    } else if (race == DWARF) {
        shared_ptr<Object> player (new Dwarf);
        return player;
    } else if (race == ORC){
        shared_ptr<Object> player (new Orc);
        return player;
    } else if (race == ARCHER) {
        shared_ptr<Object> player (new Archer);
        return player;
    } else if (race == SABER) {
        shared_ptr<Object> player (new Saber);
        return player;
    } else if (race == LANCER) {
        shared_ptr<Object> player (new Lancer);
        return player;
    } else {
        shared_ptr<Object> player (new Berserker);
        return player;
    }
}

shared_ptr<Object> Factory::GenEnemy() {
	int index = rand() % E_INDEX;

	if (enemyV.at(index) == WEREWOLF) {
		shared_ptr<Object> enemy (new Werewolf);
        return enemy;
	} else if (enemyV.at(index) == VAMPIRE) {
		shared_ptr<Object> enemy (new Vampire);
        return enemy;
	} else if (enemyV.at(index) == GOBLIN) {
		shared_ptr<Object> enemy (new Goblin);
        return enemy;
	} else if (enemyV.at(index) == TROLL) {
		shared_ptr<Object> enemy (new Troll);
        return enemy;
	} else if (enemyV.at(index) == PHEONIX) {
		shared_ptr<Object> enemy (new Phoenix);
        return enemy;
	} else {
		shared_ptr<Object> enemy (new Merchant);
        return enemy;
	}
}

shared_ptr<Object> Factory::GenEnemy(string name) {
    if (name == WEREWOLF) {
        shared_ptr<Object> enemy (new Werewolf);
        return enemy;
    } else if (name == VAMPIRE) {
        shared_ptr<Object> enemy (new Vampire);
        return enemy;
    } else if (name == GOBLIN) {
        shared_ptr<Object> enemy (new Goblin);
        return enemy;
    } else if (name == TROLL) {
        shared_ptr<Object> enemy (new Troll);
        return enemy;
    } else if (name == PHEONIX) {
        shared_ptr<Object> enemy (new Phoenix);
        return enemy;
    } else {
        shared_ptr<Object> enemy (new Merchant);
        return enemy;
    }
}

shared_ptr<Object> Factory::GenPotion() {
	int index = rand() % P_INDEX;

	if (potionV.at(index) == RH_P) {
		shared_ptr<Object> potion (new RH);
        return potion;
	} else if (potionV.at(index) == BA_P) {
		shared_ptr<Object> potion (new BA);
        return potion;
	} else if (potionV.at(index) == BD_P) {
		shared_ptr<Object> potion (new BD);
        return potion;
	} else if (potionV.at(index) == PH_P) {
		shared_ptr<Object> potion (new PH);
        return potion;
	} else if (potionV.at(index) == WA_P) {
		shared_ptr<Object> potion (new WA);
        return potion;
	} else {
		shared_ptr<Object> potion (new WD);
        return potion;
	}
}

shared_ptr<Object> Factory::GenPotion(string name) {
    if (name == RH_P) {
        shared_ptr<Object> potion (new RH);
        return potion;
    } else if (name == BA_P) {
        shared_ptr<Object> potion (new BA);
        return potion;
    } else if (name == BD_P) {
        shared_ptr<Object> potion (new BD);
        return potion;
    } else if (name == PH_P) {
        shared_ptr<Object> potion (new PH);
        return potion;
    } else if (name == WA_P) {
        shared_ptr<Object> potion (new WA);
        return potion;
    } else {
        shared_ptr<Object> potion (new WD);
        return potion;
    }
}

shared_ptr<Object> Factory::GenTreasure() {
	int index = rand() % T_INDEX;

	if (treasureV.at(index) == M_HORDE) {
		shared_ptr<Object> treasure (new meHorde);
        return treasure;
	} else if (treasureV.at(index) == D_HORDE) {
		shared_ptr<Object> treasure (new DraHorde);
        return treasure;
	} else if (treasureV.at(index) == S_HORDE) {
		shared_ptr<Object> treasure (new SmallHorde);
        return treasure;
	} else {
		shared_ptr<Object> treasure (new NormHorde);
        return treasure;
	}
}

shared_ptr<Object> Factory::GenTreasure(string name) {
    if (name == M_HORDE) {
        shared_ptr<Object> treasure (new meHorde);
        return treasure;
    } else if (name == D_HORDE) {
        shared_ptr<Object> treasure (new DraHorde);
        return treasure;
    } else if (name == S_HORDE) {
        shared_ptr<Object> treasure (new SmallHorde);
        return treasure;
    } else {
        shared_ptr<Object> treasure (new NormHorde);
        return treasure;
    }
}

shared_ptr<Dragon> Factory::GenDragon(shared_ptr<DraHorde> dh) {
    shared_ptr<Dragon> dragon (new Dragon(dh));
    dh->attachDragon(dragon);
    return dragon;
}

shared_ptr<Dragon> Factory::GenDragon() {
    shared_ptr<Dragon> dragon (new Dragon());
    return dragon;
}
