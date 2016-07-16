#pragma once
#include "spritebatch.h"
#include <vector>

struct Character {
	int characterIndex;

	std::vector<Vector2> pixelList;
	int coordinate[4];
};

struct Font {
	std::vector<Character> characterList;
};

void DrawFont();
Font LoadFontCoordinate(Font &font, unsigned char* image, int width, int height);
void DrawString(Font font);