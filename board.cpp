#include "board.h"

using namespace std;

namespace gs {

Board::Board(unsigned int width, unsigned int height, unsigned int num)
{
	this->width = width;
	this->height = height;
	this->tiles = vector<vector<Tile*> >(width, vector<Tile*>(height));
	for (unsigned int i = 0; i < width; i++)
		for (unsigned int j = 0; j < height; j++)
			this->tiles[i][j] = new Tile(i, j);
}

Board::~Board(void)
{
	for (unsigned int i = 0; i < this->width; i++)
		for (unsigned int j = 0; j < this->height; j++)
			delete this->tiles[i][j];
}

int Board::getWidth(void)
{
	return this->width;
}

int Board::getHeight(void)
{
	return this->height;
}

Tile* Board::getTile(const Position& position)
{
	if (position.x >= this->width || position.y >= this->height)
		return 0;
	return this->tiles[position.x][position.y];
}

} // namespace gs
