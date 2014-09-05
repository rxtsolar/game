#include "game.h"

using namespace std;

namespace gs {

Game::Game(void)
{
	for (unsigned int i = 0; i < NUM_OF_PLAYERS; i++)
		this->players.push_back(new Player());
	this->board = new Board(BOARD_WIDTH, BOARD_HEIGHT, TILE_LIMIT);
}

Game::~Game(void)
{
	list<Player*>::iterator it;
	for (it = players.begin(); it != players.end(); it++)
		delete *it;
}

int Game::getRound(void)
{
	return this->round;
}

Player* Game::getTurn(void)
{
	return this->turn;
}

list<Player*> Game::getPlayers(void)
{
	return this->players;
}

Board* Game::getBoard(void)
{
	return this->board;
}

void Game::setRound(int round)
{
	this->round = round;
}

void Game::setTurn(Player* player)
{
	this->turn = player;
}

void Game::addPlayer(Player* player)
{
	this->players.push_back(player);
}

void Game::removePlayer(Player* player)
{
	this->players.remove(player);
}

void Game::setBoard(Board* board)
{
	this->board = board;
}

} // namespace gs
