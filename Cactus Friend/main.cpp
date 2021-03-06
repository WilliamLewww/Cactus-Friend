#include "main.h"

void LoadContent();
void Update(int gameTime);
void Render(SDL_Window* window, SDL_GLContext context);

SDL_Event event;
SDL_GLContext context;

bool isRunning = true;
int frameStart, frameEnd, deltaTime = 0;
int main(int argc, char *argv[]) {
	displayWindow = SDL_CreateWindow("Cactus Friend", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS);
	context = SDL_GL_CreateContext(displayWindow);
	glOrtho(-SCREENWIDTH / 2, SCREENWIDTH / 2, SCREENHEIGHT / 2, -SCREENHEIGHT / 2, 0, 1);

	LoadContent();

	while (isRunning) {
		RemoveInitialPress();
		leftButtonPress = false;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				isRunning = false;

			GetKeys(event);
			GetButtons(event);
		}

		if (deltaTime < 1 / 60) {
			frameStart = SDL_GetTicks();
			SDL_Delay(1);
			frameEnd = SDL_GetTicks();
			deltaTime = frameEnd - frameStart;
		}
		frameStart = SDL_GetTicks();
		Update(deltaTime);
		Render(displayWindow, context);
		frameEnd = SDL_GetTicks();
		deltaTime = frameEnd - frameStart;
	}

	return 0;
}

TextureEntity enemy;
int enemyWidth, enemyHeight;
void LoadContent() {
	LoadFont();

	unsigned char* enemyTexture = ReadBMP("../Content/spritesheet.bmp", enemyWidth, enemyHeight);
	enemy = GetTextureEntity(enemyTexture, Vector2(0, 0), 500, 21, 20);
	std::cout << enemyHeight;
}

void Update(int gameTime) {
	UpdateInterface(displayWindow);
}

void Render(SDL_Window* window, SDL_GLContext context) {
	SDL_GL_MakeCurrent(window, context);
	glClearColor(ConvertColor(69), ConvertColor(177), ConvertColor(237), 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);

	DrawInterface();
	DrawTextureEntity(enemy, Vector2(10, 10));

	SDL_GL_SwapWindow(window);
}

float ConvertColor(int rgbValue) {
	return (float)rgbValue / 255;
}