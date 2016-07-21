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
	int width, height;
	int coordinate[4];
};

struct Font {
	std::vector<Character> characterList;
};

extern Font font;
extern int fontWidth, fontHeight;

void LoadFont();
Font LoadFontCoordinate(Font &font, unsigned char* image, int width, int height);
void DrawCharacter(std::vector<Character> characterList, Vector2 position, int index);
void DrawString(Font font, Vector2 position, std::string text);