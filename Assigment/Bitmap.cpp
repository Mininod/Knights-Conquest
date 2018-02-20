#include "Bitmap.h"
#include "Global.h"
#include "Renderer.h"

Bitmap::Bitmap()
{
	mpRenderer = Global::GAME.GetRendererPtr()->GetSDLRenderPtr();
	mRenderLayer = 100;
}


Bitmap::~Bitmap()
{
	if (mpRenderer)
	{
		mpRenderer = nullptr;
	}

	if (mpSurface)
	{
		SDL_FreeSurface(mpSurface);
		mpSurface = nullptr;
	}

	if (mpTexture)
	{
		SDL_DestroyTexture(mpTexture);
		mpTexture = nullptr;
	}
}

void Bitmap::CreateBitmap(std::string fileName, bool useTransparency, int renderLayer)
{
	mRenderLayer = renderLayer;

	mpSurface = SDL_LoadBMP(fileName.c_str());

	if (!mpSurface)
	{
		std::cout << "Error loading Surface for bitmap" << std::endl;
		std::cout << SDL_GetError() << std::endl;
	}
	else
	{
		if (useTransparency)
		{
			Uint32 colourKey = SDL_MapRGB(mpSurface->format, 255, 0, 255);
			SDL_SetColorKey(mpSurface, SDL_TRUE, colourKey);
		}

		mpTexture = SDL_CreateTextureFromSurface(mpRenderer, mpSurface);

		if (!mpTexture)
		{
			std::cout << "Error loading Texture for bitmap in" << fileName.c_str() << std::endl;
			std::cout << SDL_GetError() << std::endl;
		}
	}
}

void Bitmap::DrawBitmap(Vector2 pos)
{
	Vector2 camPos = Global::GAME.GetRendererPtr()->GetCameraPos();
	int finalPos_x;
	int finalPos_y;
	if (mpTexture)
	{
		finalPos_x = (int) floor(pos.x - camPos.x);
		finalPos_y = (int) floor(pos.y - camPos.y);
		SDL_Rect destRect = { finalPos_x, finalPos_y, mpSurface->w, mpSurface->h };
		SDL_RenderCopy(mpRenderer, mpTexture, NULL, &destRect);
	}
}

int Bitmap::GetRenderLayer()
{
	return mRenderLayer;
}
