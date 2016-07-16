#include "spritebatch.h"

int* GetPixelBMP(unsigned char* image, int x, int y, int width) {
	int pixel[3] = { image[(y * width + x) * 3], image[(y * width + x + 1) * 3], image[(y * width + x + 2) * 3] };
	return pixel;
}

unsigned char* ReadBMP(char* path, int &width, int &height) {
	FILE* f = fopen(path, "rb");

	unsigned char info[54];
	fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

											   // extract image height and width from header
	width = *(int*)&info[18];
	height = *(int*)&info[22];
	int data_offset = *(int*)(&info[0x0A]);
	fseek(f, (long int)(data_offset - 54), SEEK_CUR);

	int row_padded = (width * 3 + 3) & (~3);
	unsigned char* data = new unsigned char[row_padded];
	unsigned char tmp;

	unsigned char* newData = new unsigned char[width * height * 3];
	int increment = 0;

	for (int i = 0; i < height; i++)
	{
		fread(data, sizeof(unsigned char), row_padded, f);
		for (int j = 0; j < width * 3; j += 3)
		{
			// Convert (B, G, R) to (R, G, B)
			tmp = data[j];
			data[j] = data[j + 2];
			data[j + 2] = tmp;

			newData[increment] = data[j];
			newData[increment + 1] = data[j + 1];
			newData[increment + 2] = data[j + 2];

			increment += 3;
		}
	}
	return newData;
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