#ifndef _FACTORY_H_
#define _FACTORY_H_
#include <string>
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>
#include "draHorde.h"
#include "dragon.h"

//using namespace std;

const std::string HUMAN = "Human";
const std::string ELVES = "Elves";
const std::string DWARF = "Dwarf";
const std::string ORC = "Orc";
const std::string ARCHER = "Archer";
const std::string SABER = "Saber";
const std::string BERSERKER = "Berserker";
const std::string LANCER = "Lancer";
const std::string WEREWOLF = "W";
const std::string VAMPIRE = "V";
const std::string GOBLIN = "N";
const std::string TROLL = "T";
const std::string PHEONIX = "X";
const std::string MERCHANT = "M";
const std::string RH_P = "RH";
const std::string BA_P = "BA";
const std::string BD_P = "BD";
const std::string PH_P = "PH";
const std::string WA_P = "WA";
const std::string WD_P = "WD";
const std::string M_HORDE = "MerHorde";
const std::string D_HORDE = "DraHorde";
const std::string S_HORDE = "SmallHorde";
const std::string N_HORDE = "NormHorde";
const int E_INDEX = 18;
const int P_INDEX = 6;
const int T_INDEX = 8;

class Object;

class Factory {
	const std::vector <std::string> enemyV = {"W", "W", "W", "W", "V", "V", "V", "N", "N", "N", "N", "N", "T", "T", "X", "X", "M", "M"};
	const std::vector <std::string> potionV = {"RH", "BA", "BD", "PH", "WA", "WD"};
	const std::vector <std::string> treasureV = {"DraHorde", "SmallHorde", "SmallHorde", "NormHorde", "NormHorde", "NormHorde", "NormHorde", "NormHorde"};
public:
	Factory();
	std::shared_ptr<Object> GenPlayer(std::string race);
	std::shared_ptr<Object> GenEnemy();
	std::shared_ptr<Object> GenPotion();
	std::shared_ptr<Object> GenTreasure();
    std::shared_ptr<Object> GenEnemy(std::string name);
    std::shared_ptr<Object> GenPotion(std::string name);
    std::shared_ptr<Object> GenTreasure(std::string name);
    std::shared_ptr<Dragon> GenDragon(std::shared_ptr<DraHorde> dh);
    std::shared_ptr<Dragon> GenDragon();
};

#endif
