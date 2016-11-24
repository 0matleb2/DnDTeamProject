#pragma once
#include "Map.h"


class MapEditor {

public:

	MapEditor();
	~MapEditor();

	Map* getMap();

	void setMap(Map* map);

	void editMap();
	void loadMap();

private:

	Map* _map;
	std::vector<Map*> _loadedMaps;

};

