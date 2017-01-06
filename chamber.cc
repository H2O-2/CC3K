#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <sstream>
#include "chamber.h"
#include "tile.h"
#include "object.h"
#include "enemy.h"
#include "dragon.h"
#include "user.h"
#include "treasure.h"
#include "merchant.h"

using namespace std;

class DraHorde;

const string NO = "no";
const string SO = "so";
const string EA = "ea";
const string WE = "we";
const string NE = "ne";
const string NW = "nw";
const string SE = "se";
const string SW = "sw";
const int SIDETILE = 8;
const vector<string> DIRECTION = { NO, SO, EA, WE, NE, NW, SE, SW};

shared_ptr<Tile> Chamber::dirConver(shared_ptr<Tile> t, string dir) {
	int x = t->getX() - diffFromFloor_x;
	int y = t->getY() - diffFromFloor_y;
	if (dir == NO) {
		return chamberTile[y - 1][x];
	} else if (dir == SO) {
		return chamberTile[y + 1][x];
	} else if (dir == EA) {
		return chamberTile[y][x + 1];
	} else if (dir == WE) {
		return chamberTile[y][x - 1];
	} else if (dir == NE) {
		return chamberTile[y - 1][x + 1];
	} else if (dir == NW) {
		return chamberTile[y - 1][x - 1];
	} else if (dir == SE) {
		return chamberTile[y + 1][x + 1];
	} else {
		return chamberTile[y + 1][x - 1];
	}
}

bool Chamber::moveSingleEnemy(int enemyX, int enemyY, string dir) {
	shared_ptr<Tile> cur = chamberTile[enemyY][enemyX];
	shared_ptr<Tile> next = dirConver(chamberTile[enemyY][enemyX], dir);
    shared_ptr<Object> obj = cur->getObj();
	shared_ptr<Enemy> e = dynamic_pointer_cast<Enemy> (obj);
    string userAround = checkRadius(enemyX, enemyY);
    bool moved = false;
    if (!next) {
        return false;
    }
    if (obj->getRace() == "D") {
        dragonCheck(cur);
        moved = true;
    } else if (userAround != "No User") {
        shared_ptr<Tile> user = dirConver(chamberTile[enemyY][enemyX], userAround);
        if (obj->getRace() == "M") {
            shared_ptr<User> pc = dynamic_pointer_cast<User>(user->getObj());
            if(pc->getMerDeath()) {
                enemyAttack(cur, user);
                moved = true;
            } else if (dynamic_pointer_cast<Enemy>(obj)->getHostile()) {
                enemyAttack(cur, user);
                moved = true;
            }
        } else {
            enemyAttack(cur, user);
            moved = true;
        }
    }
    if (!moved && checkMove(next)) {
        if (e->getHostile()) {
            e->hostileOff();
        }
		cur->toggleOccupy();
		next->toggleOccupy();
		next->attachObj(cur->getObj());
		cur->attachObj(nullptr);
        cur->notify();
        next->notify();
		moved = true;
	}
    return moved;
}

void Chamber::enemyAttack(shared_ptr<Tile> t, shared_ptr<Tile> user) {
    shared_ptr<Enemy> enm = dynamic_pointer_cast<Enemy> (t->getObj());
    shared_ptr<User> pc = dynamic_pointer_cast<User> (user->getObj());
    string s;
    int hpBefore = pc->getHp();
    if (enm->getHostile()) {
        // 50% chance of miss
        int hit = rand() % 2;
        if (hit) {
            t->attack(user);
        }
        int hpAfter = 0;
        if (pc) {
            hpAfter = pc->getHp();
        }
        int damage = hpBefore - hpAfter;
        stringstream ss;
        if (damage < 0) {
            ss << hpBefore;
            s = " " + enm->getRace() + "deals " + ss.str() + "damage to PC.";
        } else if (damage == 0) {
            s = " " + enm->getRace() + "'s attack missed.";
        } else {
            ss << damage;
            s = " " + enm->getRace() + " deals " +  ss.str() + " damage to PC.";
        }
    } else {
        enm->hostileOn();
    }
    AttInfo += s;
}

bool Chamber::chamber2Check(std::shared_ptr<Tile> t) {
    return (t->getY() >= 9 && t->getX() <= 49);
}

Chamber::Chamber(int height, int width, int diff_x, int diff_y) : height{height}, width{width},
                                                                  diffFromFloor_x{diff_x},
                                                                  diffFromFloor_y{diff_y} {
	srand(time(0));
	numOfMoves = 0;
	charInCham = false;
    for (int r = 0; r < height; r++) {
        vector<shared_ptr<Tile>> tempV;
        for (int c = 0; c < width; c++) {
            shared_ptr<Tile> temp;
            tempV.emplace_back(temp);
        }
        chamberTile.emplace_back(tempV);
    }
    
    for (int n = 0; n < DOORWAY; n++) {
        shared_ptr<Tile> temp;
        doorWayTile.emplace_back(temp);
    }
}

void Chamber::genPosn(shared_ptr<Object> obj) {
	bool validTile = false;
	while(!validTile) {
		shared_ptr<Tile> cur = chamberTile[rand() % height][rand() % width];
		if ((checkMove(cur) && height == C_2_HEIGHT && !chamber2Check(cur)) || (checkMove(cur) && height != C_2_HEIGHT)) {
            cur->attachObj(obj);
            cur->notify();
            cur->toggleOccupy();
            if (obj->getType() == ObjType::User) {
                dynamic_pointer_cast<User>(obj)->setPosn(cur->getX(), cur->getY());
            } else if (obj->getRace() == "Dragon Horde") {
                shared_ptr<DraHorde> d = dynamic_pointer_cast<DraHorde>(obj);
                d->setTile(cur);
            }
            validTile = true;
        }
    }
}

void Chamber::genPosn(shared_ptr<DraHorde> dh, shared_ptr<Dragon> d) {
    shared_ptr<Tile> cur = dh->getTile();
    bool validTile = false;
    while(!validTile) {
        string dir = DIRECTION[rand() % SIDETILE];
        shared_ptr<Tile> next = dirConver(cur, dir);
        if (checkMove(next)) {
            next->attachObj(d);
            next->notify();
            next->toggleOccupy();
            validTile = true;
        }
    }
}


void Chamber::setChamberTile(int r, int c, std::shared_ptr<Tile> t) {
    chamberTile[r][c] = t;
}

void Chamber::setDoorTile(int door, std::shared_ptr<Tile> t) {
    doorWayTile[door] = t;
}

shared_ptr<Tile> Chamber::getDoorTile(int n) {
    return doorWayTile[n];
}

bool Chamber::genGate() {
    if (!charInCham) {
        while (true) {
            shared_ptr<Tile> cur = chamberTile[rand() % height][rand() % width];
            if ((checkMove(cur) && height == C_2_HEIGHT && !chamber2Check(cur)) || (checkMove(cur) && height != C_2_HEIGHT)) {
                cur->setType(TileType::Gate);
                cur->notify();
                return true;
            }
        }
    }
    return false;
}

bool Chamber::charMove(string dir, int x, int y) {
    x -= diffFromFloor_x;
    y -= diffFromFloor_y;
	shared_ptr<Tile> cur = chamberTile[y][x];
	shared_ptr<Tile> next = dirConver(cur, dir);
    shared_ptr<Object> curObj = cur->getObj();
    shared_ptr<User> userPtr = dynamic_pointer_cast<User> (curObj);
    shared_ptr<Object> nextObj = next->getObj();
	if (checkMove(next) || next->getType() == TileType::Gate
        || next->getType() == TileType::Stair || next->getType() == TileType::DoorWay) {
		cur->toggleOccupy();
		next->toggleOccupy();
		next->attachObj(userPtr);
        if (next->getType() == TileType::Stair) {
            userPtr->setState(State::Stair);
            toggleCharStat();
        }
        cur->attachObj(nullptr);
        userPtr->setPosn(next->getX(), next->getY());
        cur->notify();
        next->notify();
		return true;
    } else if (nextObj && nextObj->getType() == ObjType::Treasure && dynamic_pointer_cast<Treasure> (nextObj)->open()) {
        cur->toggleOccupy();
        shared_ptr<Treasure> tPtr = dynamic_pointer_cast<Treasure> (next->getObj());
        tPtr->beingAttack(userPtr);
        next->attachObj(curObj);
        cur->attachObj(nullptr);
        userPtr->setPosn(next->getX(), next->getY());
        cur->notify();
        next->notify();
        return true;
    } else {
		return false;
	}
}

bool Chamber::charAtt(string dir, int x, int y) {
    x -= diffFromFloor_x;
    y -= diffFromFloor_y;
	shared_ptr<Tile> cur = chamberTile[y][x];
	shared_ptr<Tile> att = dirConver(cur, dir);
    shared_ptr<Object> objAtt = att->getObj();
    bool attackSuccess = false;
    if (objAtt) {
        if (objAtt->getType() == ObjType::Enemy) {
            string s;
            int hpBefore = dynamic_pointer_cast<Character>(objAtt)->getHp();
            cur->attack(att);
            int hpAfter = 0;
            if(objAtt) {
                hpAfter = dynamic_pointer_cast<Character>(objAtt)->getHp();
            }
            stringstream damage;
            stringstream hp;
            damage << hpBefore - hpAfter;
            hp << hpAfter;
            s = "PC deals " + damage.str() + " damage to " + objAtt->getRace() + " (" + hp.str() + " HP).";
            AttInfo += s;
            attackSuccess = true;
        }
    }
    return attackSuccess;
}

bool Chamber::charUse(string dir, int x, int y) {
    x -= diffFromFloor_x;
    y -= diffFromFloor_y;
	shared_ptr<Tile> cur = chamberTile[y][x];
	shared_ptr<Tile> use = dirConver(cur, dir);
	shared_ptr<Object> obj = use->getObj();
    if (obj) {
        if (obj->getType() == ObjType::Potion) {
            cur->attack(use);
            use->notify();
            return true;
        }
    }
    return false;
}

bool Chamber::checkMove(shared_ptr<Tile> t) {
	if ((!t->checkOccupy()) && t->getType() == TileType::FloorTile) {
		return true;
	} else {
		return false;
	}
}

void Chamber::moveEnem() {
    for (int i = 0; i < chamberTile.size(); i++) {
        for (int j = 0; j < chamberTile[i].size(); j++) {
            shared_ptr<Tile> t = chamberTile[i][j];
            shared_ptr<Object> obj = t->getObj();
            if (obj) {
                if (obj->getType() == ObjType::Enemy && ((height == C_2_HEIGHT && !chamber2Check(t)) || height != C_2_HEIGHT)) {
                    shared_ptr<Enemy> e = dynamic_pointer_cast<Enemy> (obj);
                    if (e->getMove() == numOfMoves) {
                        bool moved = false;
                        vector<string> dir = DIRECTION;
                        int n = 8;
                        while (!moved) {
                            if (n != 0) {
                                int acc = rand() % n;
                                string direction = dir[acc];
                                moved = moveSingleEnemy(j, i, direction);
                                dir.erase(dir.begin() + acc);
                                --n;
                            } else {
                                moved = true;
                            }
                        }
                        e->addMove();
                    }
                }
            }
        }
    }
    numOfMoves++;
}

bool Chamber::dragonCheck(shared_ptr<Tile> t) {
    shared_ptr<Object> cur = t->getObj();
    shared_ptr<Dragon> d = dynamic_pointer_cast<Dragon> (cur);
	shared_ptr<DraHorde> dh = d->getHorde();
    
    int hordeX = dh->getTile()->getX() - diffFromFloor_x;
    int hordeY = dh->getTile()->getY() - diffFromFloor_y;
    string userAround = checkRadius(hordeX, hordeY);
    
    int dragonX = t->getX() - diffFromFloor_x;
    int dragonY = t->getY() - diffFromFloor_y;
    string attackUser = checkRadius(dragonX, dragonY);
    
    if (d->getHostile() && attackUser != "No User") {
        shared_ptr<Tile> user = dirConver(chamberTile[dragonY][dragonX], attackUser);
        enemyAttack(t, user);
    } else if (!d->getHostile() && userAround != "No User") {
        d->hostileOn();
    } else {
        d->hostileOff();
    }
    return true;
}

string Chamber::checkRadius(int x, int y) {
	shared_ptr<Tile> t = chamberTile[y][x];
	for (int i = 0; i < SIDETILE; i++) {
		shared_ptr<Object> obj = dirConver(t, DIRECTION[i])->getObj();
        if (obj) {
            if (obj->getType() == ObjType::User) {
                return DIRECTION[i];
            }
        }
	}
	return "No User";
}

string Chamber::getAttInfo() {
    string acc = AttInfo;
    AttInfo = "";
    return acc;
}

void Chamber::attachTile(std::vector <std::shared_ptr<Tile>> t) {
	chamberTile.emplace_back(t);
}

bool Chamber::charStat() {
	return charInCham;
}

void Chamber::toggleCharStat() {
	if (charInCham) {
		charInCham = false;
	} else {
		charInCham = true;
	}
}

void Chamber::reset() {
    numOfMoves = 0;
    charInCham = false;
}
