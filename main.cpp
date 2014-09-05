#include <iostream>

#include "game.h"

using namespace std;
using namespace gs;

void dump(Game* game)
{
	Player* p1 = *game->getPlayers().begin();
	Player* p2 = *(++game->getPlayers().begin());
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

	cout << "board width: " << board->getSize().width << endl;
	cout << "board height: " << board->getSize().height << endl;

	for (int i = 0; i < board->getSize().width; i++) {
		for (int j = 0; j < board->getSize().height; j++) {
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
			for (int j = 0; j < units.size(); j++)
				cout << units[j] << ' ';
			cout << endl;
		}
	}
}

int main(void)
{
	Game* game = new Game();
	Player* p1 = *game->getPlayers().begin();
	Player* p2 = *(++game->getPlayers().begin());
	Board* board = game->getBoard();

	p1->createUnit(board->getTile(Position(0, 0)));
	p1->createUnit(board->getTile(Position(0, 0)));
	p1->refreshUnits();

	p2->createUnit(board->getTile(Position(0, 1)));
	p2->createUnit(board->getTile(Position(1, 0)));
	p2->refreshUnits();

	(*p1->getUnits().begin())->attack(board->getTile(Position(0, 1)));
	p1->createUnit(board->getTile(Position(0, 0)));
	p1->refreshUnits();

	(*p2->getUnits().begin())->attack(board->getTile(Position(0, 0)));
	p2->refreshUnits();

	dump(game);
	delete game;
	return 0;
}
