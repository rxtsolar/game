#ifndef _GAME_H_
#define _GAME_H_

#include <list>

#include "board.h"
#include "player.h"
#include "unit.h"

namespace gs {

const unsigned int NUM_OF_PLAYERS = 2;
const unsigned int BOARD_WIDTH = 5;
const unsigned int BOARD_HEIGHT = 5;
const unsigned int TILE_LIMIT = 5;

class Game {
public:
	Game(void);
	virtual ~Game(void);

	virtual int getRound(void);
	virtual Player* getTurn(void);
	virtual std::list<Player*> getPlayers(void);
	virtual Board* getBoard(void);

	virtual void setRound(int);
	virtual void setTurn(Player*);
	virtual void addPlayer(Player*);
	virtual void removePlayer(Player*);
	virtual void setBoard(Board*);

private:
	int round;
	Player* turn;

	std::list<Player*> players;
	Board* board;
};

} // namespace gs

#endif
