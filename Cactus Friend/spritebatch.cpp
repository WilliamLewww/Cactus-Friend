#include "spritebatch.h"

int* GetPixelBMP(unsigned char* image, int x, int y, int width, int height) {
	int pixel[3] = { image[y * width + x], image[y * width + x + 1], image[y * width + x + 2] };
	return pixel;
}

//The color of pixel (i, j) is stored at data[j * width + i], data[j * width + i + 1] and data[j * width + i + 2]
unsigned char* ReadBMP(char* path, int &width, int &height) {
	FILE* file = fopen(path, "rb");
	unsigned char header[54];
	fread(header, sizeof(unsigned char), 54, file); // read the 54-byte header

											   // extract image height and width from header
	width = *(int*)&header[18];
	height = *(int*)&header[22];

	int size = 3 * width * height;
	unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
	fread(data, sizeof(unsigned char), size, file); // read the rest of the data at once
	fclose(file);

	for (int x = 0; x < size; x += 3) {
		unsigned char temp = data[x];
		data[x] = data[x + 2];
		data[x + 2] = temp;
	}

	return data;
}

GLuint LoadTexture(const char* path) {
	GLuint texture = SOIL_load_OGL_texture(
		path,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	if (0 == texture) {
		printf("SOIL loading error: '%s'\n", SOIL_last_result());
		return -1;
	}

	return texture;
}

void DrawLine(Vector2 position, Vector2 positionB, float thickness, double color[3]) {
	glLineWidth(thickness);
	glColor3f(color[0], color[1], color[2]);
	glBegin(GL_LINES);
	glVertex2d(position.x - (SCREENWIDTH / 2), position.y - (SCREENHEIGHT / 2));
	glVertex2d(positionB.x - (SCREENWIDTH / 2), positionB.y - (SCREENHEIGHT / 2));
	glEnd();
}

void DrawRect(GLuint texture, Vector2 position, int width, int height) {
	Vector2 vectors[4]{
		Vector2(0, 0),
		Vector2(1, 0),
		Vector2(1, 1),
		Vector2(0, 1)
	};

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_QUADS);
	glColor3f(255, 255, 255);
	for (int x = 0; x < 4; x++) {
		glTexCoord2f(vectors[x].x, vectors[x].y);
		vectors[x].x *= width;
		vectors[x].y *= height;
		vectors[x] += Vector2(position.x, position.y);
		vectors[x] -= Vector2(SCREENWIDTH / 2, SCREENHEIGHT / 2);

		glVertex2f(vectors[x].x, vectors[x].y);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void DrawRect(Vector2 position, int width, int height, float thickness, double color[3]) {
	DrawLine(Vector2(position.x, position.y), Vector2(position.x + width, position.y), thickness, color);
	DrawLine(Vector2(position.x + width, position.y), Vector2(position.x + width, position.y + height), thickness, color);
	DrawLine(Vector2(position.x + 1, position.y), Vector2(position.x + 1, position.y + height), thickness, color);
	DrawLine(Vector2(position.x, position.y + height), Vector2(position.x + width, position.y + height), thickness, color);
}

void DrawRectFill(Vector2 position, int width, int height, double color[3]) {
	Vector2 vectors[4]{
		Vector2(0, 0),
		Vector2(1, 0),
		Vector2(1, 1),
		Vector2(0, 1)
	};

	glBegin(GL_QUADS);
	glColor3f(color[0], color[1], color[2]);
	for (int x = 0; x < 4; x++) {
		vectors[x].x *= width;
		vectors[x].y *= height;
		vectors[x] += Vector2(position.x, position.y);
		vectors[x] -= Vector2(SCREENWIDTH / 2, SCREENHEIGHT / 2);

		glVertex2d(vectors[x].x, vectors[x].y);
	}
	glEnd();
}