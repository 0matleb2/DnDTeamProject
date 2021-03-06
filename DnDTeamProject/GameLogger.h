#pragma once
#include <vector>

#include "Dice.h"
#include "Map.h"
#include "MapLogger.h"
#include "Character.h"
#include "CharacterLogger.h"

class GameDirector;

class GameLogger
{
public:

	~GameLogger();

	// singleton pattern
	static GameLogger* instance();

	// set objects to be logged
	void setPC(Character* pc);
	void setNPCs(std::vector<Character*>* npcs);
	void setMap(Map* map);
	void setAll(Map* map);

	void setDir(GameDirector* dir);

	// getters
	CharacterLogger* getPC();

	

	void clearNPCs();

	// turn logging on/off
	void loggingPC(bool choice);
	void loggingNPCs(bool choice);
	void loggingMap(bool choice);
	void loggingDice(bool choice);
	void loggingDir(bool choice);
	
	void loggingAll(bool choice);

	// set file destination
	void setFile(std::string fileName);
	// set to same as director
	void setFile();

	//get file destination
	std::string getFile();

	//print log contents
	void printLog();

private:
	GameLogger();

	static GameLogger* _loggerInstance;
	CharacterLogger* _loggedPC;
	std::vector<CharacterLogger*>* _loggedNPCs;
	MapLogger* _loggedMap;
	GameDirector* _loggedDir;

	std::string _destination;
	
};
