#ifndef _CONST_H_
#define _CONST_H_

namespace gs {

const int DEF_FPS = 25;
const int DEF_WIDTH = 1600;
const int DEF_HEIGHT = 900;
const int DEF_BPP = 32;

const unsigned int BOARD_WIDTH = 5;
const unsigned int BOARD_HEIGHT = 5;
const unsigned int MAX_TILE_UNITS = 5;
const int MAX_RESOURCES = 10;
const int START_MAX_RESOURCES = 0;
const int EACH_TURN_RESOURCES = 1;
const int MAX_HAND_CARDS = 10;
const int START_HAND_CARDS = 3;

constexpr const char* font_path = "resources/black_jack.ttf";
const float font_rate = 0.656;

} // namespace gs

#endif
