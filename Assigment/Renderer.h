#pragma once
#include <iostream>
#include <vector>
#include "SDL.h"
#include "GameObject.h"

class Bitmap;
class Renderer
{
public:
	Renderer();
	~Renderer();
	void Render(std::vector<GameObject*> allGameObjects);
	SDL_Renderer* GetSDLRenderPtr();
	void SetCameraPos(Vector2 camPos);
	Vector2 GetCameraPos();
	void CameraFollow(Vector2 objPos);
private:
	SDL_Window* mpWindow;
	SDL_Renderer* mpRenderer;
	SDL_Rect mCamera;
	Bitmap* mBackground;
};

