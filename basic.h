#ifndef _BASIC_H_
#define _BASIC_H_

namespace gs {

struct Position {
	int x;
	int y;
	Position(void) : x(0), y(0) { }
	Position(int a, int b) : x(a), y(b) { }
	bool operator==(const Position& p) { return x == p.x && y == p.y; }
};

struct Range {
	int start;
	int end;
	Range(void) : start(0), end(0) { }
	Range(int s, int e) : start(s), end(e) { }
};

struct Size {
	int width;
	int height;
	Size(void) : width(0), height(0) { }
	Size(int w, int h) : width(w), height(h) { }
};

} // namespace gs

#endif
