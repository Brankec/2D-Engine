#pragma once
#include <SFML/Graphics.hpp>
#include "../../Map/Map.h"
#include <Box2D/Box2D.h>

class Level : public Map
{
public:
	//Level(b2World* world);
	Level();
	void loadTileMap(b2World* world);
};