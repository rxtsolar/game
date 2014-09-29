#ifndef _GAME_H_
#define _GAME_H_

#include "board.h"
#include "const.h"
#include "player.h"
#include "unit.h"

namespace gs {

class Board;

class Game {
public:
	Game(void);
	virtual ~Game(void);

	virtual int getRound(void);
	virtual Tile* getSelectedTile(void);
	virtual Unit* getSelectedUnit(void);
	virtual Player* getTurn(void);
	virtual Player* getPlayer1(void);
	virtual Player* getPlayer2(void);
	virtual Board* getBoard(void);

	virtual void setRound(int);
	virtual void selectTile(Tile* tile);
	virtual void selectUnit(Unit* unit);
	virtual void setTurn(Player*);
	virtual void setPlayer1(Player*);
	virtual void setPlayer2(Player*);
	virtual void setBoard(Board*);

	virtual void nextPlayer(Player*);

private:
	int round;
	Tile* tile;
	Unit* unit;
	Player* turn;
	Player* player1;
	Player* player2;
	Board* board;
};

} // namespace gs

#endif
