#pragma once
#include <vector>
#include <string>
#include "GameObject.h"
#include "Level_Data.h"
#include "SDL.h"

class Renderer;
class Player;
class UI;

enum mKeysPressedList 
{
	KEY_ESCAPE, KEY_W, KEY_A, KEY_S, KEY_D, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, SIZE_OF_KEY_PRESSED_LIST_ENUM 
};

class Game
{
public:
	Game();
	~Game();
	std::vector<GameObject*> GetAllGameObjects();
	void AddGameObject(GameObject* gameObject);
	bool IsKeyPressed(mKeysPressedList key);
	void RunGame();
	Renderer* GetRendererPtr();
	std::vector<std::string> GetLevelInfo();
	int GetBlockSize();
	Player* GetPlayer();
	void RemoveGameObject(int vectorValue);
	UI* GetUI();
	Level_Data* GetLevelDataPtr();
private:
	std::vector<GameObject*> mAllGameObjects;
	Renderer* mpRenderer;
	Level_Data* mAccessToSaveandLoad;
	bool mLoopGame;
	int mCurrentLevel;
	int mBlockSize;
	int mMaxLevel;
	std::vector<std::string> mLoadedLevel;

	Player* mPlayer;
	UI* mUI;

	std::string FloorArangementCheck(Vector2 pos);

	void KeyUpdate();
	void LevelUpdate();
	void LoadLevel(int level);
	void NextLevelCheck();
	void UpdateLoadedLevel();
	void RemoveAllGameObjectsButNotThePLAYER();
	bool mKeysPressed[SIZE_OF_KEY_PRESSED_LIST_ENUM];
	SDL_Event mEvent;

	int FPS = 120;
	int frameDelay;
	Uint32 frameStart;
	int frameTime;

	void Debug();
};
