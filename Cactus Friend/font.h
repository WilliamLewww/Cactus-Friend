#pragma once
#include "spritebatch.h"
#include <vector>

struct Pixel {
	Vector2 position;

	int r, g, b;
};

struct Character {
	int characterIndex;

	std::vector<Pixel> pixelList;
	int coordinate[4];
};

struct Font {
	std::vector<Character> characterList;
};

void DrawFont();
Font LoadFontCoordinate(Font &font, unsigned char* image, int width, int height);
void DrawString(Font font);