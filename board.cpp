#include "board.h"

using namespace std;

namespace gs {

Board::Board(int width, int height, int num)
{
	this->width = width;
	this->height = height;
	this->tiles = vector<vector<Tile*> >(width, vector<Tile*>(height));
	for (int i = 0; i < width; i++)
		for (int j = 0; j < height; j++)
			this->tiles[i][j] = new Tile(i, j, num);
}

Board::~Board(void)
{
	for (int i = 0; i < this->width; i++)
		for (int j = 0; j < this->height; j++)
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
	if (position.x < 0 || position.y < 0)
		return 0;
	if (position.x >= this->width || position.y >= this->height)
		return 0;
	return this->tiles[position.x][position.y];
}

} // namespace gs
