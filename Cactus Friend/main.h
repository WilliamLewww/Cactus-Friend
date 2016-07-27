#pragma once
#include <SDL.h>
#include <SDL_opengl.h>
#include "input.h"
#include "interface.h"

static const int BORDERLEFT = 2, BORDERRIGHT = 172, BORDERTOP = 14, BORDERBOTTOM = 182;
static const int SCREENWIDTH = 176, SCREENHEIGHT = 200;
static SDL_Window* displayWindow;

extern bool isRunning;

float ConvertColor(int rgbValue);