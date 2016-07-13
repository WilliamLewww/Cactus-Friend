#include "interface.h"

void DrawInterface() {
	GLuint exitTexture = LoadTexture("../Content/exit.bmp");
	DrawRect(exitTexture, Vector2(SCREENWIDTH - 10, 2), 8, 8);

	double color[3] = { ConvertColor(100), ConvertColor(100), ConvertColor(100) };
	DrawRect(Vector2(0, 0), SCREENWIDTH, 11, 1, color);
	DrawRect(Vector2(0, 12), SCREENWIDTH, SCREENHEIGHT - 13, 1, color);
	DrawRect(Vector2(1, 13), SCREENWIDTH - 2, SCREENHEIGHT - 15, 1, color);
	DrawRect(Vector2(2, 14), SCREENWIDTH - 4, SCREENHEIGHT - 17, 1, color);
	color[0] = ConvertColor(160); color[1] = ConvertColor(160); color[2] = ConvertColor(160);
	DrawRect(Vector2(1, 1), SCREENWIDTH - 2, 9, 1, color);
	DrawLine(Vector2(SCREENWIDTH - 10, 2), Vector2(SCREENWIDTH - 10, 10), 1, color);
	color[0] = ConvertColor(175); color[1] = ConvertColor(175); color[2] = ConvertColor(175);
	DrawRectFill(Vector2(2, 2), 163, 8, color);
}

bool moveWindow;
Vector2 fixedMousePosition;
void UpdateInterface(SDL_Window* window) {
	POINT p;
	GetCursorPos(&p);

	if (mouseY < 11 && leftButtonDown == true && moveWindow == false && CheckMouseOnEntity(Vector2(SCREENWIDTH - 10, 2), 8, 8) == false) {
		fixedMousePosition = Vector2(mouseX, mouseY);
		moveWindow = true;
	}
	else {
		if (leftButtonDown == false) { moveWindow = false; }
	}

	if (CheckMouseOnEntity(Vector2(SCREENWIDTH - 10, 2), 8, 8) == true && leftButtonPress == true) {
		isRunning = false;
	}

	if (moveWindow == true) {
		SDL_SetWindowPosition(window, p.x - fixedMousePosition.x, p.y - fixedMousePosition.y);
	}
}