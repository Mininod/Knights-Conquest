#include "Level_Data.h"



Level_Data::Level_Data()
{
	/*std::vector<std::string> foo = { { "L:3;H:2;W:2;" }, { "Hi" }, { "Ho" } }; Testing Stuff
	std::vector<std::string> test = LoadLevel(1);
	for (int i = 0; i < test.size(); i++)// test stuff
	{
		std::cout << test[i] << std::endl;
	}*/
}


Level_Data::~Level_Data()
{
}

std::vector<std::string> Level_Data::LoadLevel(int levelNumber)
{
	std::vector<std::string> outPut;
	mFile.open("UserLevelData.txt", std::ios::out | std::ios::in);
	std::string dataOnCurLine;
	bool UserDataFound = false;
	if (FindLevel(levelNumber))
	{
		UserDataFound = true;
	}


	if (UserDataFound == false)
	{
		mFile.close();
		mFile.open("LevelData.txt", std::ios::in | std::ios::out);
	}
	
	if (FindLevel(levelNumber))
	{
		fpos_t tellG = mFile.tellg(); // may cause problems should be int
		mFile.seekg(tellG - (CurLineSize + 2));
		std::getline(mFile, dataOnCurLine);
		outPut.push_back(dataOnCurLine);
		std::vector<int> levelInfo = GetLevelInfo(dataOnCurLine);
		int size = levelInfo[1];
		for (int i = 0; i < size; i++)
		{
			std::getline(mFile, dataOnCurLine);
			outPut.push_back(dataOnCurLine);
		}
	}
	else
	{
		std::cout << "Level Number doesn't exist" << std::endl;
	}
	mFile.close();
	return outPut;
}

void Level_Data::SaveLevel(std::vector<std::string> level)
{
	mFile.open("UserLevelData.txt", std::ios::in | std::ios::out | std::ios::trunc);
	std::vector<int> vecLevel = GetLevelInfo(level[0]);
		std::cout << mFile.tellg();
		fpos_t tellG = mFile.tellg(); // may cause problems should be int
		//mFile.seekg(tellG - (CurLineSize + 2));
		int size = level.size();
		for (int i = 0; i < size; i++)
		{
			mFile << level[i] << std::endl;
		}
	mFile.close();
}

int Level_Data::VectorOfIntToSingleInt(std::vector<int> vectorOfInt) // Converts a vector of ints to a single int
{
	int k = 0;
	int size = vectorOfInt.size();
	for (int i = 0; i < size; i++)
	{
		k = 10 * k + vectorOfInt[i] - 48;
	}

	return k;
}

std::vector<int> Level_Data::GetLevelInfo(std::string level)
{
	std::vector<int> levelInfo;
	int i = 2;
	bool quit = false;
	for (int k = 0; k < 3; k++)
	{
		for (std::vector<int> NumVec; quit == false; i++)
		{
			if (level[i] == ';')
			{
				levelInfo.push_back(VectorOfIntToSingleInt(NumVec));
				quit = true;
			}
			else
			{
				NumVec.push_back(level[i]);
			}
		}
		i += 2;
		quit = false;
	}
	return levelInfo;
}

bool Level_Data::FindLevel(int level)
{
	if (mFile.is_open())
	{
		std::string dataOnCurLine;
		bool quit = false;
		mFile.seekg(0);
		while (quit == false)
		{
			std::vector<int> vecCurLvlData;
			std::getline(mFile, dataOnCurLine);
			CurLineSize = dataOnCurLine.size();
			if (dataOnCurLine == "END" || mFile.peek() == EOF)
			{
				std::cout << "Error: End of file reached. Level not found" << std::endl;
				quit = true;
			}
			else
			{
				vecCurLvlData = GetLevelInfo(dataOnCurLine);
				if (vecCurLvlData[0] == level)
				{
					mFile.seekp(mFile.tellg());
					return true;
				}
				else
				{
					for (int i = 0; i < vecCurLvlData[1]; i++)
					{
						std::getline(mFile, dataOnCurLine);
					}
				}
			}
		}
	}
	else
	{
		std::cout << "Error opening LevelData.txt" << std::endl;
		getchar();
		exit(0);
	}
	return false;
}

std::vector<int> Level_Data::LoadPlayerData()
{
	mFile.open("PlayerData.txt", std::ios::in | std::ios::out);
	std::vector<int> output; // 0 = hearts, 1 = coins, 2 = keys , 3 = level
	if (mFile.is_open())
	{
		int curOutput;
		for (int i = 0; i < 5; i++)
		{
			mFile >> curOutput;
			output.push_back(curOutput);
		}
	}
	else
	{
		std::cout << "Error opening LevelData.txt" << std::endl;
		getchar();
		exit(0);
	}
	mFile.close();
	return output;
}

void Level_Data::SavePlayerData(std::vector<int> data)
{
	mFile.open("PlayerData.txt", std::ios::in | std::ios::out | std::ios::trunc);
	if (mFile.is_open())
	{
		for (int i = 0; i < 5; i++)
		{
			mFile << data[i] << std::endl;
		}
	}
	else
	{
		std::cout << "Error opening LevelData.txt" << std::endl;
		getchar();
		exit(0);
	}
	mFile.close();
}

void Level_Data::WipeSaves()
{
	mFile.open("PlayerData.txt", std::ios::in | std::ios::out | std::ios::trunc);
	mFile.close();
	mFile.open("UserLevelData.txt", std::ios::in | std::ios::out | std::ios::trunc);
	mFile.close();
}
