#include "board.h"

using namespace std;

namespace gs {

Board::Board(const Size& size, int num)
{
	this->size = size;
	this->tiles = vector<vector<Tile*> >(size.width,
					     vector<Tile*>(size.height));
	for (int i = 0; i < size.width; i++)
		for (int j = 0; j < size.height; j++)
			this->tiles[i][j] = new Tile(i, j, num);
}

Board::~Board(void)
{
	for (int i = 0; i < this->size.width; i++)
		for (int j = 0; j < this->size.height; j++)
			delete this->tiles[i][j];
}

Size Board::getSize(void)
{
	return size;
}

Tile* Board::getTile(const Position& position)
{
	if (position.x < 0 || position.y < 0)
		return 0;
	if (position.x >= this->size.width || position.y >= this->size.height)
		return 0;
	return this->tiles[position.x][position.y];
}

} // namespace gs
