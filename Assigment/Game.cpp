#include "Game.h"
#include "Static.h"
#include "Player.h"
#include "Enemy.h"
#include "UI.h"
#include "Item.h"
#include "Renderer.h"
#include "Door.h"

Game::Game()
{
	mLoopGame = true;
	frameDelay = 1000 / FPS;
	mpRenderer = new Renderer;
	mAccessToSaveandLoad = new Level_Data;
	mCurrentLevel = mAccessToSaveandLoad->LoadPlayerData()[3];
	mBlockSize = 32;
	mMaxLevel = 6;
	mPlayer = new Player("Dave", PLAYER, Vector2(550, 80), Vector2(0, 0), Vector2(32, 32));
	mUI = new UI(mPlayer);
	LoadLevel(mCurrentLevel);

	for (size_t i = 0; i < mAllGameObjects.size(); i++)
	{
		std::cout << mAllGameObjects[i]->GetBitmap()->GetRenderLayer() << std::endl;
	}
}


Game::~Game()
{
	int size = mAllGameObjects.size();
	for (int i = 0; i < size; i++)
	{
		delete mAllGameObjects[i];
		mAllGameObjects[i] = nullptr;
	}

	if (mpRenderer)
	{
		delete mpRenderer;
		mpRenderer = nullptr;
	}

	if (mAccessToSaveandLoad)
	{
		delete mAccessToSaveandLoad;
		mAccessToSaveandLoad = nullptr;
	}

	if (mUI)
	{
		delete mUI;
		mUI = nullptr;
	}
}

std::vector<GameObject*> Game::GetAllGameObjects()
{
	return mAllGameObjects;
}

void Game::AddGameObject(GameObject* gameObject)
{
	int renderLayer = gameObject->GetBitmap()->GetRenderLayer();
	bool quit = false;
	for (size_t i = 0; i < mAllGameObjects.size(); i++)
	{
		if (mAllGameObjects[i]->GetBitmap()->GetRenderLayer() >= renderLayer)
		{
			mAllGameObjects.insert(mAllGameObjects.begin() + i, gameObject);
			quit = true;
			break;
		}
	}

	if (quit == false)
	{
		mAllGameObjects.push_back(gameObject);
	}
}

bool Game::IsKeyPressed(mKeysPressedList key)
{
	return mKeysPressed[key];
}

void Game::RunGame()
{
	while (mLoopGame)
	{
		frameStart = SDL_GetTicks();

		KeyUpdate();
		for (size_t i = 0, foo = mAllGameObjects.size(); i < foo; i++)
		{
			if (mAllGameObjects[i]->isActive())
			{
				mAllGameObjects[i]->Update();
			}
		}

		Debug();

		mpRenderer->Render(mAllGameObjects);

		if (IsKeyPressed(KEY_ESCAPE))
		{
			if (mCurrentLevel < mMaxLevel)
			{
				mLoopGame = false;
				UpdateLoadedLevel();
				mAccessToSaveandLoad->SaveLevel(mLoadedLevel);
				std::vector<int> foo;
				foo.push_back(mPlayer->GetHealth());
				foo.push_back(GetUI()->GetItemAmount(COIN));
				foo.push_back(GetUI()->GetItemAmount(KEY));
				foo.push_back(mCurrentLevel);
				mAccessToSaveandLoad->SavePlayerData(foo);
			}
			else
			{
				mCurrentLevel = 1;
				mPlayer->SetHealth(-1);
				mAccessToSaveandLoad->WipeSaves();
			}
		}
		if (mPlayer->GetHealth() <= 0)
		{
			mPlayer->SetHealth(-1);
			mAccessToSaveandLoad->WipeSaves();
			RemoveAllGameObjectsButNotThePLAYER();
			mCurrentLevel = 1;
			LoadLevel(1);
		}

		NextLevelCheck();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}
}

Renderer * Game::GetRendererPtr()
{
	return mpRenderer;
}

std::vector<std::string> Game::GetLevelInfo()
{
	return mLoadedLevel;
}

int Game::GetBlockSize()
{
	return mBlockSize;
}

Player * Game::GetPlayer()
{
	return mPlayer;
}

void Game::RemoveGameObject(int vectorValue)
{
	mAllGameObjects[vectorValue]->SetActiveState(false);
}

UI * Game::GetUI()
{
	return mUI;
}

Level_Data * Game::GetLevelDataPtr()
{
	return mAccessToSaveandLoad;
}

void Game::KeyUpdate()
{
	while (SDL_PollEvent(&mEvent) != NULL)
	{
		if (mEvent.type == SDL_KEYDOWN)
		{
			SDL_Keycode keyPressed = mEvent.key.keysym.sym;

			switch (keyPressed)
			{
			case SDLK_ESCAPE:
				mKeysPressed[KEY_ESCAPE] = true;
				break;
			case SDLK_w:
				mKeysPressed[KEY_W] = true;
				break;
			case SDLK_s:
				mKeysPressed[KEY_S] = true;
				break;
			case SDLK_a:
				mKeysPressed[KEY_A] = true;
				break;
			case SDLK_d:
				mKeysPressed[KEY_D] = true;
				break;
			case SDLK_UP:
				mKeysPressed[KEY_UP] = true;
				break;
			case SDLK_DOWN:
				mKeysPressed[KEY_DOWN] = true;
				break;
			case SDLK_LEFT:
				mKeysPressed[KEY_LEFT] = true;
				break;
			case SDLK_RIGHT:
				mKeysPressed[KEY_RIGHT] = true;
				break;
			}
		}
		else if (mEvent.type == SDL_KEYUP)
		{
			SDL_Keycode keyPressed = mEvent.key.keysym.sym;

			switch (keyPressed)
			{
			case SDLK_ESCAPE:
				mKeysPressed[KEY_ESCAPE] = false;
				break;
			case SDLK_w:
				mKeysPressed[KEY_W] = false;
				break;
			case SDLK_s:
				mKeysPressed[KEY_S] = false;
				break;
			case SDLK_a:
				mKeysPressed[KEY_A] = false;
				break;
			case SDLK_d:
				mKeysPressed[KEY_D] = false;
				break;
			case SDLK_UP:
				mKeysPressed[KEY_UP] = false;
				break;
			case SDLK_DOWN:
				mKeysPressed[KEY_DOWN] = false;
				break;
			case SDLK_LEFT:
				mKeysPressed[KEY_LEFT] = false;
				break;
			case SDLK_RIGHT:
				mKeysPressed[KEY_RIGHT] = false;
				break;
			}
		}
	}
}
void Game::LevelUpdate()
{
	int size = mAllGameObjects.size();
	for (int i = 0; i < size; i++)
	{
		Vector2 objPos = mAllGameObjects[i]->GetPostion();
		objPos.x /= mBlockSize;
		objPos.y /= mBlockSize;
		int finalPos_x = (int)floor(objPos.x);
		int finalPos_y = (int)floor(objPos.y);
		mLoadedLevel[finalPos_y][finalPos_x] = mAllGameObjects[i]->GetLevelSymbol();
	}
}
void Game::LoadLevel(int level)
{
	mLoadedLevel = mAccessToSaveandLoad->LoadLevel(level);
	int size =  mLoadedLevel.size();
	int stringSize;
	Vector2 inGamePos;
	std::string fileName;
	for (int i = 1; i < size; i++)
	{
		stringSize = mLoadedLevel[i].size();
		for (int k = 0; k < stringSize; k++)
		{
			inGamePos.x = (float) k * mBlockSize;
			inGamePos.y = (float) (i - 1) * mBlockSize; //-1 as the top row of the level is information about the level. its not to be included
			switch (mLoadedLevel[i][k])
			{
			case PLAYER:
				mPlayer->SetPostion(inGamePos);
				AddGameObject(mPlayer);
				break;
			case DOOR:
				AddGameObject(new Door("Door", DOOR, inGamePos, Vector2(0, 0), Vector2(32, 32), "Assets/Door.bmp", 2));
				break;
			case BAT:
				AddGameObject(new Enemy("Batto", BAT, inGamePos, Vector2(0, 0), Vector2(32, 32)));
				break;
			case SLUG:
				AddGameObject(new Enemy("Sluggo", SLUG, inGamePos, Vector2(0, 0), Vector2(32, 32)));
				break;
			case COIN:
				AddGameObject(new Item("Coin", COIN, inGamePos, Vector2(0, 0), Vector2(16, 16)));
				AddGameObject(new Static("Stone", CRATE, inGamePos, Vector2(0, 0), Vector2(32, 32), "Assets/Crate.bmp", 3));
				break;
			case HEALTH_POT:
				AddGameObject(new Item("HealthPot", HEALTH_POT, inGamePos, Vector2(0, 0), Vector2(16, 16)));
				AddGameObject(new Static("Stone", CRATE, inGamePos, Vector2(0, 0), Vector2(32, 32), "Assets/Crate.bmp", 3));
				break;
			case KEY:
				AddGameObject(new Item("Key", KEY, inGamePos, Vector2(0, 0), Vector2(16, 16)));
				AddGameObject(new Static("Stone", CRATE, inGamePos, Vector2(0, 0), Vector2(32, 32), "Assets/Crate.bmp", 3));
				break;
			case EXIT:
				AddGameObject(new Door("Exit", EXIT, inGamePos, Vector2(0, 0), Vector2(32, 32), "Assets/Trapdoor.bmp", 3));
			case FAKE_WALL:
				break;
			}
			if (mLoadedLevel[i][k] != WALL && mLoadedLevel[i][k] != FAKE_WALL)
			{
				fileName = FloorArangementCheck(Vector2((float) k, (float) i));
				AddGameObject(new Static("Floor1", FLOOR, inGamePos, Vector2(0, 0), Vector2(0, 0), fileName, 1));
			}
		}
	}

}

void Game::NextLevelCheck()
{
	Vector2 pos = mPlayer->GetPostion();
	int column = floor(pos.x /= mBlockSize);
	int row = floor(pos.y /= mBlockSize) + 1;

	if (mLoadedLevel[row][column] == EXIT) 
	{
		RemoveAllGameObjectsButNotThePLAYER();

		mCurrentLevel++;

		if (mCurrentLevel >= mMaxLevel)
		{
			LoadLevel(mCurrentLevel);
			std::cout << "No more levels" << std::endl;
			AddGameObject(new Static("GAMEOVER", CRATE, Vector2(-260, -180), Vector2(0, 0), Vector2(0, 0), "Assets/Gameover.bmp", 5));
		}
		else
		{
			LoadLevel(mCurrentLevel);
		}
	}

}

void Game::UpdateLoadedLevel()
{

	for (size_t i = 0; i < mAllGameObjects.size(); i++)
	{
		if (mAllGameObjects[i]->GetLevelSymbol() != CRATE)
		{
			Vector2 pos = mAllGameObjects[i]->GetPostion();
			int column = floor(pos.x / mBlockSize);
			int row = floor(pos.y / mBlockSize) + 1;
			if (mAllGameObjects[i]->isActive())
			{
				mLoadedLevel[row][column] = mAllGameObjects[i]->GetLevelSymbol();
			}
			else
			{
				mLoadedLevel[row][column] = '.';
			}
		}
	}
}

void Game::RemoveAllGameObjectsButNotThePLAYER()
{
	for (size_t i = mAllGameObjects.size() - 1; i > 0; i--)
	{
		if (mAllGameObjects[i]->GetLevelSymbol() == PLAYER) {
			mAllGameObjects.pop_back();
		}
		else
		{
			delete mAllGameObjects[i];
			mAllGameObjects[i] = nullptr;
			mAllGameObjects.pop_back();
		}
	}
}

std::string Game::FloorArangementCheck(Vector2 pos)
{
	std::string output;
	int x = (int) pos.x;
	int y = (int) pos.y;
	//Top
	bool TM = true;
	//Middle
	bool MR = true;
	bool ML = true;
	//Bottom
	bool BM = true;
	//Finding out if the tiles are walls so it safe to put a floor there
	if (mLoadedLevel[y - 1][x] == WALL)
	{
		TM = false;
	}

	if (mLoadedLevel[y][x + 1] == WALL)
	{
		MR = false;
	}

	if (mLoadedLevel[y][x - 1] == WALL)
	{
		ML = false;
	}

	if (mLoadedLevel[y + 1][x] == WALL)
	{
		BM = false;
	}


	if (TM && MR && ML && BM)
	{
		output = "Assets/floorMiddle.bmp";
	}
	else if (TM && MR  && ML)
	{
		output = "Assets/floorBottomMiddle.bmp";
	}
	else if (BM && MR && ML)
	{
		output = "Assets/floorTopMiddle.bmp";
	}
	else if (TM  && MR  && BM )
	{
		output = "Assets/floorMiddleLeft.bmp";
	}
	else if (TM  && ML && BM )
	{
		output = "Assets/floorMiddleRight.bmp";
	}
	else if (TM && ML)
	{
		output = "Assets/floorBottomRight.bmp";
	}
	else if (TM && MR)
	{
		output = "Assets/floorBottomLeft.bmp";
	}
	else if (BM && ML)
	{
		output = "Assets/floorTopRight.bmp";
	}
	else if (BM && MR)
	{
		output = "Assets/floorTopLeft.bmp";
	}
	else if (BM && TM)
	{
		output = "Assets/floorUpDown.bmp";
	}
	else if (ML && MR)
	{
		output = "Assets/floorRightLeft.bmp";
	}
	else
	{
		output = "Assets/floorMiddle.bmp";
	}
	return output;
}

void Game::Debug()
{

}
