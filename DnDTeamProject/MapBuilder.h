#pragma once
#include "Map.h"


class MapBuilder {

public:

	MapBuilder();
	~MapBuilder();

	Map* getMap();

	void construct();

private:

	Map* _map;


	void buildDimensions();
	void buildName();
	void buildLayout();



};
