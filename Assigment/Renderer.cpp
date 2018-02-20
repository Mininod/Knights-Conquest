#include "Renderer.h"
#include "Global.h"
#include "UI.h"
#include "Collision.h"
#include "Bitmap.h"

Renderer::Renderer()
{
	mpWindow = nullptr;
	mpRenderer = nullptr;

	//startup
	SDL_Init(SDL_INIT_VIDEO);

	//create the window
	mpWindow = SDL_CreateWindow(
		"RogueLike Game", //title
		250, //initial x pos
		150, //intial y pos
		640, //width in pixels
		480, //heigh in pixels
		0    //window behaviour flags
	);

	if (!mpWindow)
	{
		std::cout << "WINDOW initialisation failed: " << SDL_GetError() << std::endl;
		std::cout << "Press any key to continue" << std::endl;
		getchar();
		return;
	}

	//now create the renderer
	mpRenderer = SDL_CreateRenderer(
		mpWindow,
		-1,
		0
	);

	if (!mpRenderer)
	{
		std::cout << "RENDERER initialisation failed: " << SDL_GetError() << std::endl;
		std::cout << "Press any key to continune\n" << std::endl;
		getchar();

		return;
	}
	mCamera = {0,0, 600, 440};
}


Renderer::~Renderer()
{
	if (mpRenderer)
	{
		SDL_DestroyRenderer(mpRenderer);
		mpRenderer = nullptr;
	}

	if (mpWindow)
	{
		SDL_DestroyWindow(mpWindow);
		mpRenderer = nullptr;
	}
}

void Renderer::Render(std::vector<GameObject*> allGameObjects)
{	
	if (!mBackground)
	{
		mBackground = new Bitmap;
		mBackground->CreateBitmap("Assets/Background.bmp", true, 0);
	}
	
	if (mpRenderer)
	{
		//creating the camera in the right place
		SDL_RenderClear(mpRenderer);
		float camera_w = (float) mCamera.w;
		float camera_h = (float) mCamera.h;
		std::vector<float> cameraCollider = { 0, 0, camera_w, camera_h };
		Vector2 camPos((float) mCamera.x, (float) mCamera.y);
		mBackground->DrawBitmap(camPos);
		//gets all the game objects within the game
		for (size_t i = 0, foo = allGameObjects.size(); i < foo; i++)
		{
			if (allGameObjects[i]->isActive())
			{
				Vector2 objpos = allGameObjects[i]->GetPostion();
				std::vector<float> objCollider = allGameObjects[i]->GetCollider()->GetCollisionDimensions();
				//checking that the object is colliding with the camera
				if (allGameObjects[i]->GetCollider()->IsColliding(objpos, objCollider, camPos, cameraCollider))
				{
					allGameObjects[i]->Draw();
				}
			}
		}
		Global::GAME.GetUI()->Draw(camPos);
		SDL_RenderPresent(mpRenderer);
	}
}

SDL_Renderer * Renderer::GetSDLRenderPtr()
{
	return mpRenderer;
}

void Renderer::SetCameraPos(Vector2 camPos)
{
	mCamera.x = (int) camPos.x;
	mCamera.y = (int) camPos.y;
}

Vector2 Renderer::GetCameraPos()
{
	Vector2 pos;
	pos.x = (float) mCamera.x;
	pos.y = (float) mCamera.y;
	return pos;
}

void Renderer::CameraFollow(Vector2 objPos)
{
	mCamera.x = (int) objPos.x - (mCamera.w / 2);
	mCamera.y = (int) objPos.y - (mCamera.h / 2);
}
