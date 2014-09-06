#include <iostream>

#include "game.h"

using namespace std;
using namespace gs;

void dump(Game* game)
{
	Player* p1 = game->getPlayer1();
	Player* p2 = game->getPlayer2();
	Board* board = game->getBoard();

	cout << endl;
	cout << "player 1: ";
	unordered_set<Unit*> units1 = p1->getUnits();
	for (unordered_set<Unit*>::iterator it = units1.begin();
			it != units1.end(); it++)
		cout << (void*)*it << ' ';
	cout << endl;

	cout << "player 2: ";
	unordered_set<Unit*> units2 = p2->getUnits();
	for (unordered_set<Unit*>::iterator it = units2.begin();
			it != units2.end(); it++)
		cout << (void*)*it << ' ';
	cout << endl;

	cout << "board width: " << board->getWidth() << endl;
	cout << "board height: " << board->getHeight() << endl;

	for (int i = 0; i < board->getWidth(); i++) {
		for (int j = 0; j < board->getHeight(); j++) {
			Tile* tile = board->getTile(Position(i, j));
			cout << "tile " << tile << " (" << i << ", " << j << "): ";
			if (tile->getPlayer() == p1)
				cout << "player1";
			else if (tile->getPlayer() == p2)
				cout << "player2";
			else
				cout << "no player. ";
			cout << endl;
			vector<Unit*> units = tile->getUnits();
			for (unsigned int j = 0; j < units.size(); j++)
				cout << units[j] << ' ';
			cout << endl;
		}
	}
}

int main(void)
{
	Game* game = new Game();
	Player* p1 = game->getPlayer1();
	Player* p2 = game->getPlayer2();
	Board* board = game->getBoard();
	Tile* t;
	Unit* u;

	t = board->getTile(Position(0, 0));
	p1->createHero(t);
	p1->createPawn(t);
	p1->endTurn();

	t = board->getTile(Position(0, 1));
	p2->createHero(t);
	t = board->getTile(Position(1, 0));
	p2->createPawn(t);
	p2->endTurn();

	t = board->getTile(Position(0, 0));
	u = p1->selectUnit(t, 1);
	t = board->getTile(Position(0, 1));
	p1->attack(u, t);
	t = board->getTile(Position(0, 0));
	p1->createPawn(t);
	p1->endTurn();

	t = board->getTile(Position(1, 0));
	u = p2->selectUnit(t, 0);
	t = board->getTile(Position(0, 0));
	p2->attack(u, t);
	p2->endTurn();

	dump(game);
	delete game;
	return 0;
}
