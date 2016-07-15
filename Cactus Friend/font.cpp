#include "font.h"

Font LoadFont(unsigned char* image, int width, int height) {
	Font font;

	bool a = false;
	int minX = -1, minY = height, maxX = 0, maxY = 0;

	for (int x = 0; x < width; x++) {
		Character character;
		a = false;

		for (int y = 0; y < height; y++) {
			//std::cout << *GetPixelBMP(image, x, y, width) << " ";

			if (*GetPixelBMP(image, x, y, width) > 0) {
				a = true;

				if (minX == -1) { minX = x; }
				if (y < minY) { minY = y; }
				if (x > maxX) { maxX = x; }
				if (y > maxY) { maxY = y; }
			}
		}

		//std::cout << std::endl;

		if (a == false) {
			if (minX != -1) {
				character.coordinate[0] = minX;
				character.coordinate[1] = minY;
				character.coordinate[2] = (maxX + 1) - minX;
				character.coordinate[3] = (maxY + 1) - minY;
			}

			minX = -1;
			minY = height;
			maxX = 0;
			maxY = 0;
		}

		font.characterList.push_back(character);
	}

	return font;
}