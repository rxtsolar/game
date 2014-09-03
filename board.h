#ifndef _BOARD_H_
#define _BOARD_H_

#include <vector>

#include "basic.h"
#include "tile.h"

namespace gs {

class Board {
public:
	Board(const Size&);
	virtual ~Board(void);

	virtual Size getSize(void);
	virtual Tile* getTile(const Position&);
private:
	Size size;
	std::vector<std::vector<Tile*> > tiles;
};

} // namespace gs

#endif
