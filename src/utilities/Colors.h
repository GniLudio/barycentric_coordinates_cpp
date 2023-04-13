#pragma once
#include "math/Vec4f.h"

struct Colors {
	static const Vec4f WHITE;
	static const Vec4f BLACK;
	static const Vec4f RED;
	static const Vec4f GREEN;
	static const Vec4f BLUE;
	static const Vec4f YELLOW;
	static const Vec4f MAGENTA;
	static const Vec4f CYAN;
};

const Vec4f Colors::WHITE = {1, 1, 1};
const Vec4f Colors::BLACK = {0, 0, 0};

const Vec4f Colors::RED = {1, 0, 0};
const Vec4f Colors::GREEN = {0, 1, 0};
const Vec4f Colors::BLUE = {0, 0, 1};

const Vec4f Colors::YELLOW = {1, 1, 0};
const Vec4f Colors::MAGENTA = {1, 0, 1};
const Vec4f Colors::CYAN = {0, 1, 1};