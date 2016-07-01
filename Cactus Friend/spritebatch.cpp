#include "spritebatch.h"

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