CXX = g++
CXXFLAGS =  -std=c++14 -Wall -MMD -g
EXEC = cc3k
OBJECTS = archer.o BA.o BD.o berserker.o chamber.o character.o dragon.o draHorde.o dwarf.o elves.o enemy.o factory.o floor.o goblin.o human.o lancer.o main.o meHorde.o merchant.o normHorde.o object.o orc.o PH.o phoenix.o potion.o RH.o saber.o smallHorde.o textdisplay.o tile.o treasure.o troll.o user.o vampire.o WA.o werewolf.o WD.o

DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
