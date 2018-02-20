#pragma once
#include <iostream>
#include <string>
#include <math.h>
#include <stdio.h>
#include "Vector2.h"
#include "SDL.h"

class Bitmap
{
public:
	Bitmap();
	~Bitmap();
	void CreateBitmap(std::string fileName, bool useTransparency, int renderLayer);
	void DrawBitmap(Vector2 pos);
	int GetRenderLayer();
private:
	SDL_Renderer* mpRenderer;
	SDL_Surface* mpSurface;
	SDL_Texture* mpTexture;
	int mRenderLayer; //0 = the first rendered. The larger the number the later its rendered
};

