#include "font.h"

Font LoadFontCoordinate(Font &font, unsigned char* image, int width, int height) {
	Character character;
	int incrementIndex = 0;
	bool a = false;
	int minX = -1, minY = height, maxX = 0, maxY = 0;

	for (int x = 0; x < width; x++) {
		a = false;

		for (int y = 0; y < height; y++) {
			if (*GetPixelBMP(image, x, y, width) > 0) {
				a = true;

				if (minX == -1) { minX = x; }
				if (y < minY) { minY = y; }
				if (x > maxX) { maxX = x; }
				if (y > maxY) { maxY = y; }
			}
		}

		if (a == false) {
			if (minX != -1) {
				character.coordinate[0] = minX;
				character.coordinate[1] = minY;
				character.coordinate[2] = (maxX + 1) - minX;
				character.coordinate[3] = (maxY + 1) - minY;

				character.characterIndex = incrementIndex;
				incrementIndex += 1;

				font.characterList.push_back(character);
			}

			minX = -1;
			minY = height;
			maxX = 0;
			maxY = 0;
		}
	}

	return font;
}

Font LoadFontPixel(Font &font, unsigned char* image, int width, int height) {
	Character character;
	int incrementIndex = 0;
	bool a = false;

	for (int x = 0; x < width; x++) {
		a = false;

		for (int y = 0; y < height; y++) {
			if (*GetPixelBMP(image, x, y, width) > 0) {
				character.pixelList.push_back(Vector2(x, height - y));
				a = true;
			}
		}

		if (a == false) {
			font.characterList.push_back(character);
			character.pixelList.clear();
		}
	}

	return font;
}

void DrawString(Font font) {
	for (auto &character : font.characterList) {
		for (auto &pixel : character.pixelList) {
			glColor3f(1, 1, 1);
			glBegin(GL_POINTS);
			glVertex2i(pixel.x - (SCREENWIDTH / 2), pixel.y - (SCREENHEIGHT / 2));
			glEnd();
		}
	}
}

void DrawFont() {
	Font font;
	int width, height;
	unsigned char* fontImage = ReadBMP("../Content/font.bmp", width, height);
	DrawString(LoadFontPixel(font, fontImage, width, height));
}