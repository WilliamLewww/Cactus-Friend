#pragma once
#include <SDL.h>
#include <SDL_opengl.h>
#include "input.h"
#include "interface.h"

static const int SCREENWIDTH = 176, SCREENHEIGHT = 200;
static SDL_Window* displayWindow;

float ConvertColor(int rgbValue);