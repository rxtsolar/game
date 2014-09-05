#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>

#include "basic.h"
#include "tile.h"

namespace gs {

class Board {
public:
	Board(int width, int height, int limit);
	virtual ~Board(void);

	virtual int getWidth(void);
	virtual int getHeight(void);
	virtual Tile* getTile(const Position&);
private:
	int width;
	int height;
	std::vector<std::vector<Tile*> > tiles;
};

} // namespace gs

#endif
