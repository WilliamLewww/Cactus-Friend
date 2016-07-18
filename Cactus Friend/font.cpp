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
	Pixel pixel;
	int incrementIndex = 0;
	bool a = false;

	int minX = -1;

	for (int x = 0; x < width; x++) {
		a = false;

		for (int y = 0; y < height; y++) {
			if (*GetPixelBMP(image, x, y, width) > 0) {
				a = true;

				if (minX == -1) { minX = x; }

				pixel.position = Vector2(x - minX, height - y);
				pixel.r = *GetPixelBMP(image, x, y, width);
				pixel.g = *(GetPixelBMP(image, x, y, width) + 1);
				pixel.b = *(GetPixelBMP(image, x, y, width) + 2);
				character.pixelList.push_back(pixel);
			}
		}

		if (a == false) {
			if (minX != -1) {
				font.characterList.push_back(character);
				character.pixelList.clear();
			}

			minX = -1;
		}
	}

	return font;
}

void DrawString(Font font, int index) {
	for (auto &pixel : font.characterList[index].pixelList) {
		//glColor3f(ConvertColor(pixel.r), ConvertColor(pixel.g), ConvertColor(pixel.b));
		glColor3f(0, 0, 0);
		glBegin(GL_POINTS);
		glVertex2d(pixel.position.x - (SCREENWIDTH / 2), pixel.position.y - (SCREENHEIGHT / 2));
		glEnd();
	}
}

void DrawFont() {
	Font font;
	int width, height;
	unsigned char* fontImage = ReadBMP("../Content/font.bmp", width, height);
	DrawString(LoadFontPixel(font, fontImage, width, height), 0);
}