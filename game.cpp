#include "game.h"

using namespace std;

namespace gs {

Game::Game(void)
{
	this->player1 = new Player(this);
	this->player2 = new Player(this);
	this->board = new Board(BOARD_WIDTH, BOARD_HEIGHT, TILE_LIMIT);
	this->round = 0;
	this->turn = player1;
}

Game::~Game(void)
{
	delete this->player1;
	delete this->player2;
	delete this->board;
}

int Game::getRound(void)
{
	return this->round;
}

Player* Game::getTurn(void)
{
	return this->turn;
}

Player* Game::getPlayer1(void)
{
	return this->player1;
}

Player* Game::getPlayer2(void)
{
	return this->player2;
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

void Game::setPlayer1(Player* player)
{
	this->player1 = player;
}

void Game::setPlayer2(Player* player)
{
	this->player2 = player;
}

void Game::setBoard(Board* board)
{
	this->board = board;
}

void Game::nextPlayer(Player* player)
{
	if (player == this->player1)
		turn = player2;
	else
		turn = player1;
}

} // namespace gs
