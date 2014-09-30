#ifndef _BASIC_H_
#define _BASIC_H_

#include <ostream>

namespace gs {

struct Position {
	unsigned int x;
	unsigned int y;
	Position(void) : x(0), y(0) { }
	Position(int a, int b) : x(a), y(b) { }
	friend std::ostream& operator<<(std::ostream& stream, const Position& p)
	{
		stream << "(" << p.x << ", " << p.y << ")";
		return stream;
	}
};

struct Range {
	int start;
	int end;
	Range(void) : start(0), end(0) { }
	Range(int s, int e) : start(s), end(e) { }
};

enum Status {
	S_DEFAULT,
	S_CARD,
	S_TILE,
	S_UNIT,
};

} // namespace gs

#endif
