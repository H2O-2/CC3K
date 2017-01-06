#ifndef _FLOOR_H_
#define _FLOOR_H_
#include "user.h"
#include "textdisplay.h"
#include "tile.h"
#include "chamber.h"
#include "factory.h"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <memory>

class User;

class Floor {
    std::vector <std::vector <std::shared_ptr<Tile>>> grid;
	std::vector <std::shared_ptr<Chamber>> room;
    std::shared_ptr<User> userPtr;
	std::shared_ptr<TextDisplay> td;
    std::shared_ptr<Factory> f;
    int level = 1; // the level character is currently in
    bool charInStair;
    std::string movement = "Player character has spawned.";
    bool stairMove(std::string dir, int x, int y); // character move in stair
    std::shared_ptr<Tile> dirConver(std::shared_ptr<Tile> t, std::string dir); // return the Tile on the direction dir to t
    bool inventByFile = false;
    std::ifstream file;
    void floorCtor();
    std::string converToStr (std::string dir);
    void moveEnm(); // move the enemy
    bool gg = false; // check if game over or not
public:
	Floor(); // constructor
    Floor(std::string fileName); // constructor
	~Floor(); // destructor
	void init(); // initialize floor, chamber.
	void createGame(std::string race); // create character, enemy, treasure, potion, and gate;
    void createByFile(std::string race); // create by file
	void charMove(std::string dir); // move the character
	void charAtt(std::string dir); // attack enemy
    void charUse(std::string dir); // use item
    bool checkDeath(); // check is User is dead
    double score(); // return character score
	void clearFloor(); // clear the floor
	void nextFloor(); // go to the next floor level
	void reset(); // reset the game
    bool gameOver(); // check if game over or not

	friend std::ostream &operator<<(std::ostream &out, const Floor &f);
    friend void chamber_init(std::vector <std::vector <Tile>> grid, std::shared_ptr<Chamber> cham, int chamcol, int chamrow, int startcol, int startrow);
};
	
#endif
