#pragma once
#include "main.h"
#include "vector2.h"
#include <SOIL.h>
#include <SDL_opengl.h>

//     "../Content/texture.bmp"
GLuint LoadTexture(const char* path);
void DrawLine(Vector2 position, Vector2 positionB, float thickness, double color[3]);
void DrawRect(Vector2 position, int width, int height, float thickness, double color[3]);
void DrawRectFill(Vector2 position, int width, int height, double color[3]);
void DrawRect(GLuint texture, Vector2 position, int width, int height);