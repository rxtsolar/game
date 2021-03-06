#include "game.h"

using namespace std;

namespace gs {

Game::Game(void)
{
	this->player1 = new Player(this);
	this->player2 = new Player(this);
	this->board = new Board(BOARD_WIDTH, BOARD_HEIGHT, MAX_TILE_UNITS);
	this->player1->createHero(this->board->getTile(Position(0, 2)));
	this->player2->createHero(this->board->getTile(Position(4, 2)));
	for (unsigned int i = 0; i < START_HAND_CARDS; i++)
		this->player1->drawCard();
	for (unsigned int i = 0; i < START_HAND_CARDS + 1; i++)
		this->player2->drawCard();

	this->round = 0;
	this->turn = this->player1;
	this->turn->startTurn();
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
		this->turn = this->player2;
	else if (player == this->player2)
		this->turn = this->player1;
	this->turn->startTurn();
}

void Game::end(void)
{
	this->turn = 0;
}

bool Game::isFinished(void)
{
	return !this->turn;
}

} // namespace gs
