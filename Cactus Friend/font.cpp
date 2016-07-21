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

				pixel.position = Vector2(x - minX, height - y);
				pixel.r = *GetPixelBMP(image, x, y, width);
				pixel.g = *(GetPixelBMP(image, x, y, width) + 1);
				pixel.b = *(GetPixelBMP(image, x, y, width) + 2);
				character.pixelList.push_back(pixel);
			}
		}

		if (a == false) {
			if (minX != -1) {
				character.coordinate[0] = minX;
				character.coordinate[1] = minY;
				character.coordinate[2] = (maxX + 1) - minX;
				character.coordinate[3] = (maxY + 1) - minY;

				character.width = (maxX + 1) - minX;
				character.height = (maxY + 1) - minY;

				character.characterIndex = incrementIndex;
				incrementIndex += 1;

				font.characterList.push_back(character);
				character.pixelList.clear();
			}

			minX = -1;
			minY = height;
			maxX = 0;
			maxY = 0;
		}
	}

	return font;
}

void DrawString(Font font, Vector2 position, std::string text) {
	int spacing = 0, number;
	for (int x = 0; x < text.size(); x++) {
		switch (text[x]) {
		case ':':
			number = 10;
			DrawCharacter(font.characterList, Vector2(position.x + spacing, position.y), number);
			spacing += font.characterList[number].width + 1;
			break;
		case 'P':
			number = 11;
			DrawCharacter(font.characterList, Vector2(position.x + spacing, position.y), number);
			spacing += font.characterList[number].width + 1;
			break;
		case 'o':
			number = 14;
			DrawCharacter(font.characterList, Vector2(position.x + spacing, position.y), number);
			spacing += font.characterList[number].width + 1;
			break;
		case 'i':
			number = 12;
			DrawCharacter(font.characterList, Vector2(position.x + spacing, position.y), number);
			spacing += font.characterList[number].width + 1;
			break;
		case 'n':
			number = 13;
			DrawCharacter(font.characterList, Vector2(position.x + spacing, position.y), number);
			spacing += font.characterList[number].width - 1;
			break;
		case 't':
			number = 16;
			DrawCharacter(font.characterList, Vector2(position.x + spacing, position.y), number);
			spacing += font.characterList[number].width + 1;
			break;
		case 's':
			number = 15;
			DrawCharacter(font.characterList, Vector2(position.x + spacing, position.y), number);
			spacing += font.characterList[number].width + 1;
			break;
		default:
			number = (int)text[x] - 48;
			DrawCharacter(font.characterList, Vector2(position.x + spacing, position.y), number);
			spacing += font.characterList[number].width + 1;
			break;
		}
	}
}

void DrawCharacter(std::vector<Character> characterList, Vector2 position, int index) {
	for (auto &pixel : characterList[index].pixelList) {
		//glColor3f(ConvertColor(pixel.r), ConvertColor(pixel.g), ConvertColor(pixel.b));
		glColor3f(0.1, 0.1, 0.1);
		glBegin(GL_POINTS);
		glVertex2d(pixel.position.x - (SCREENWIDTH / 2) + position.x, pixel.position.y - (SCREENHEIGHT / 2) + position.y);
		glEnd();
	}
}

Font font;
int fontWidth, fontHeight;
void LoadFont() {
	unsigned char* fontImage = ReadBMP("../Content/font.bmp", fontWidth, fontHeight);
	LoadFontPixel(font, fontImage, fontWidth, fontHeight);
}