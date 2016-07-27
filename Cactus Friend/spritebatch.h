#pragma once
#include "main.h"
#include "vector2.h"
#include <SOIL.h>
#include <SDL_opengl.h>

struct TexturePixel {
	Vector2 position;
	int r, g, b;
};

struct TextureEntity {
	std::vector<TexturePixel> pixelList;
	int width, height;
	int coordinate[4];
};

//     "../Content/texture.bmp"
GLuint LoadTexture(const char* path);
void DrawLine(Vector2 position, Vector2 positionB, float thickness, double color[3]);
void DrawRect(Vector2 position, int width, int height, float thickness, double color[3]);
void DrawRectFill(Vector2 position, int width, int height, double color[3]);
void DrawRect(GLuint texture, Vector2 position, int width, int height);

int* GetPixelBMP(unsigned char* image, int x, int y, int width);
unsigned char* ReadBMP(char* path, int &width, int &height);

TextureEntity GetTextureEntity(unsigned char* image, Vector2 position, int imageWidth, int width, int height);
void DrawTextureEntity(TextureEntity entity, Vector2 position);