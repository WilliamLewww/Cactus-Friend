#pragma once
#include "spritebatch.h"
#include <vector>

struct Character {
	int coordinate[4];
};

struct Font {
	std::vector<Character> characterList;
};

Font LoadFont(unsigned char* image, int width, int height);