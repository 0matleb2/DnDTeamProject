#include <conio.h>
#include "GameDirector.h"
#include "FileIO.h"
#include "CampaignEditor.h"
#include "MapEditor.h"
#include "CharacterEditor.h"
#include "ItemBuilder.h"


GameDirector::GameDirector() {
}

void GameDirector::startGame() {
}

void GameDirector::printLogo() {
	for (int i = 0, n = dndLogo.size(); i < n; ++i) {
		std::cout << dndLogo[i] << std::endl;
	}
}



GameDirector* GameDirector::_gameDirectorInstance = new GameDirector();

GameDirector::~GameDirector() {
}

GameDirector * GameDirector::instance() {
	if (!_gameDirectorInstance)
		_gameDirectorInstance = new GameDirector();

	return _gameDirectorInstance;
}

Character * GameDirector::getPlayerCharacter() {
	return _playerCharacter;
}

Campaign * GameDirector::getCampaign() {
	return _campaign;
}

void GameDirector::setPlayerCharacter(Character * playerCharacter) {
	_playerCharacter = playerCharacter;
}

void GameDirector::setCampaign(Campaign * campaign) {
	_campaign = campaign;
}

void GameDirector::mainMenu() {

	bool onMainMenu = true;
	while (onMainMenu) {
		printLogo();
		switch (menu(mainMenuOptions)) {
		case 1:
			playMenu();
			break;
		case 2:
			creatorMenu();
			break;
		case 3:
			credits();
			system("cls");
			break;
		case 4:
			onMainMenu = false;
			break;
		}
	}
}

void GameDirector::playMenu() {

	bool onPlayMenu = true;
	while (onPlayMenu) {
		printLogo();
		std::vector<std::string> playMenuOptions;
		playMenuOptions.push_back("Campaign:\t" + (_campaign ? _campaign->getName() + ", " + std::to_string(_campaign->getCampaign().size()) + " levels" : ""));
		playMenuOptions.push_back("Character\t" + (_playerCharacter ? _playerCharacter->getName() + ", Level: " + std::to_string(_playerCharacter->getLvl()) : ""));
		playMenuOptions.push_back("Start game!");
		playMenuOptions.push_back("Create a new character");
		playMenuOptions.push_back("Return to main menu");

		std::vector<Campaign*> loadedCampaigns;
		std::vector<Character*> loadedCharacters;
		std::vector<std::string> loadedCampaignMenuOptions;
		std::vector<std::string> loadedCharacterMenuOptions;
		CharacterEditor characterEditor;
		switch (menu(playMenuOptions, "Choose a campaign and a character to play")) {
		case 1:
			loadedCampaigns = loadCampaigns();
			for (int i = 0, n = loadedCampaigns.size(); i < n; ++i) {
				loadedCampaignMenuOptions.push_back(loadedCampaigns[i]->getName() + ", " + std::to_string(loadedCampaigns[i]->getCampaign().size()) + " levels");
			}
			printLogo();
			_campaign = loadedCampaigns[menu(loadedCampaignMenuOptions, "Which campaign do you want to play?") - 1];
			break;
		case 2:
			loadedCharacters = loadCharacters();
			for (int i = 0, n = loadedCharacters.size(); i < n; ++i) {
				loadedCharacterMenuOptions.push_back(loadedCharacters[i]->getName() + ", Level: " + std::to_string(loadedCharacters[i]->getLvl()));
			}
			printLogo();
			_playerCharacter = loadedCharacters[menu(loadedCharacterMenuOptions, "Which character do you want to play with?") - 1];
			break;
		case 3:
			if (_playerCharacter && _campaign) {
				startGame();
			}
			else {
				std::cout << "A character and a campaign must be selected to play." << std::endl;
			}
			break;
		case 4:
			characterEditor.newCharacter();
			_playerCharacter = characterEditor.getCharacter();
			break;
		case 5:
			onPlayMenu = false;
			break;
		}
	}
}

void GameDirector::creatorMenu() {
	
	bool onCreatorMenu = true;
	while (onCreatorMenu) {
		printLogo();
		CampaignEditor campaignEditor;
		MapEditor mapEditor;
		CharacterEditor characterEditor;
		ItemBuilder itemBuilder;
		switch (menu(creatorMenuOptions, "What do you want to do?")) {
		case 1: //Create a new campaign
			campaignEditor.newCampaign();
			break;
		case 2: //Create a new map
			mapEditor.newMap();
			break;
		case 3: //Create a new character
			characterEditor.newCharacter();
		case 4: //Create a mew item
			itemBuilder.newItem();
			break;
		case 5: //Edit an existing campaign
			if (campaignEditor.loadCampaign())
				campaignEditor.editCampaign();
			break;
		case 6: //Edit an exisiting map
			if (mapEditor.loadMap())
				mapEditor.editMap();
			break;
		case 7: //Edit an exisiting character
			if (characterEditor.loadCharacter())
				characterEditor.editCharacter();
			break;
		case 8: //Delete a saved campaign
			deleteCampaign();
			break;
		case 9: //Delete a saved map
			deleteMap();
			break;
		case 10: //Delete a saved character
			deleteCharacter();
			break;
		case 11: //Delete a saved item
			deleteItem();									
			break;
		case 12: //Return to main menu
			onCreatorMenu = false;
			break;
		}
	}
}

void GameDirector::credits() {

	for (int i = 0, n = encsLogo.size(); i < n; ++i) {
		std::cout << encsLogo[i] << std::endl;
	}

	std::cout << "\tConcordia University" << std::endl;
	std::cout << "\tFaculty of Engineering and Computer Science" << std::endl;
	std::cout << "\tDepartment of Computer Science & Software Engineering" << std::endl;
	std::cout << "\t1515 St. Catherine W., EV 3.139" << std::endl;
	std::cout << "\tMontreal, Quebec, Canada" << std::endl;
	std::cout << "\tH3G 2W1" << std::endl << std::endl;

	std::cout << "\tDeveloped for: " << std::endl << std::endl;
	std::cout << "\t\tCOMP 345" << std::endl;
	std::cout << "\t\tAdvanced Program Design with C++" << std::endl;
	std::cout << "\t\tInstructor: Dr. Mohamed Taleb" << std::endl;
	std::cout << "\t\tFall 2016" << std::endl << std::endl;

	std::cout << "\tDeveloped by:" << std::endl << std::endl;
	std::cout << "\t\tCharles Boudreau" << std::endl;
	std::cout << "\t\tEric Morgan" << std::endl;
	std::cout << "\t\tMathieu Leblanc" << std::endl;
	std::cout << "\t\t\Robert Nguyen" << std::endl << std::endl << std::endl;

	std::cout << "Press any key to return to the Main Menu..." << std::endl;
	_getch();
}
