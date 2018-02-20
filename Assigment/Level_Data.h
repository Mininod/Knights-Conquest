#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

class Level_Data
{
public:
	Level_Data();
	~Level_Data();
	std::vector<std::string> LoadLevel(int levelNumber);
	void SaveLevel(std::vector<std::string> level);
	std::vector<int> LoadPlayerData();
	void SavePlayerData(std::vector<int> data);
	void WipeSaves();
private:
	std::fstream mFile;
	int VectorOfIntToSingleInt(std::vector<int> vectorOfInt);
	std::vector<int> GetLevelInfo(std::string level);
	bool FindLevel(int level);
	int CurLineSize;
};

