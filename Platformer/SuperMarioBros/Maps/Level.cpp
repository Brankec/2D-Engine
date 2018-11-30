#include "Level.h"

//Level::Level(b2World* world)
Level::Level()
{
	//loadMap("SuperMarioBros", "level1", world);
}

void Level::loadTileMap(b2World* world)
{
	loadMap("SuperMarioBros", "level1", world);
}
