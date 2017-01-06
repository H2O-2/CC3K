#ifndef _CHAMBER_H_
#define _CHAMBER_H_
#include <string>
#include <vector>
#include "textdisplay.h"
#include "draHorde.h"
#include "dragon.h"

const int DOORWAY = 6;
const int C_2_HEIGHT = 13;
const int DIFFCHAMBER2X = 37;
const int DIFFCHAMBER2Y = 2;

class Tile;
class Object;

class Chamber {
    std::vector <std::vector <std::shared_ptr<Tile>>> chamberTile;
    std::vector <std::shared_ptr<Tile>> doorWayTile;
	const int height;
	const int width;
    const int diffFromFloor_x;
    const int diffFromFloor_y;
	int numOfMoves;
	bool charInCham = false;
    std::string AttInfo;
    
    std::shared_ptr<Tile> dirConver(std::shared_ptr<Tile> t, std::string dir); // return the Tile on the direction dir to t 
	bool moveSingleEnemy(int enemyX, int enemyY, std::string dir); // move the Enemy on (enemyX, enemyY) to direction dir
    void enemyAttack(std::shared_ptr<Tile> t, std::shared_ptr<Tile> user); // let enemy attack on t and return true if succeed
public:
	Chamber(int height, int width, int diff_x, int diff_y);
	void genPosn(std::shared_ptr<Object> obj); // generate a random position and set the obj to the posn.
    void genPosn(std::shared_ptr<DraHorde> dh, std::shared_ptr<Dragon> d); // generate a random postion for d around dh
    std::shared_ptr<Tile> getDoorTile(int n);
    void setChamberTile(int r, int c, std::shared_ptr<Tile> t); // set chamber Tile posn
    void setDoorTile(int door, std::shared_ptr<Tile> t); // set doorWayTile posn
    bool genGate();
    bool chamber2Check(std::shared_ptr<Tile> t); // used for ensuring the position generated for chamber2 is not in chamber3
	bool charMove(std::string dir, int x, int y); // move the user in chamber. Return true if move is valid
	bool charAtt(std::string dir, int x, int y); // attack at direction dir. Return true if attack is valid
    bool charUse(std::string dir, int x, int y); // use the item at direction dir. Return true if usage is valid
	void moveEnem(); // move the enemy characters.
	bool dragonCheck(std::shared_ptr<Tile> t); // check if character is in 1 block radius of Dragon Horde
    std::string checkRadius(int x, int y); // return direction or "No User" if no user is near
	bool checkMove(std::shared_ptr<Tile> t); // return true if the next tile is moveable.
	void attachTile(std::vector <std::shared_ptr<Tile>> t); //attach tile to the vector.
	bool charStat(); // return true if the character is in the chamber.
	void toggleCharStat(); // set charInCham true if char in the chamber, false otherwise.
    void reset();
    std::string getAttInfo();
    friend void chamber_init(std::vector <std::vector <Tile>> grid, std::shared_ptr<Chamber> cham, int chamcol, int chamrow, int startcol, int startrow);
};

#endif
