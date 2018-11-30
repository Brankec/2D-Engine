#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <functional> 
#include <cctype>
#include <locale>
#include <map>
#include "../Util/Camera.h"
#include "TileInteract.h"

class Map
{
public:
	void loadMap(std::string gameName, std::string fileName, b2World* world);
	void drawForeground(sf::RenderTarget& renderer);
	void drawInteractive(sf::RenderTarget& renderer);
	void drawBackgroundInteractable(sf::RenderTarget& renderer);
	void drawBackground(sf::RenderTarget& renderer);
	//void setClearColor(sf::Color &color);

	sf::Vector2i Sprite_sheet_coordinates(int tileIndex);
	void getValue(std::string &string);
	std::string getName(std::string string);
	void getFileValues(std::string &fileValue);
	sf::Vector2i getTwoValues(std::string &string);
	//sf::Vector3i getThreeValues(std::string &string); //for clear background color
	std::vector<int> getAllTileIndices(std::string string);
	template<typename T>
	void storeIndices(std::string to, std::vector<std::vector<sf::Vector2i>> &map, std::vector<T> &tiles, b2World* world);

public:
	sf::Texture tileTexture;
	//sf::Color* m_color;
	std::string fileValue;//values for level settings such as tile size
	int powOfN = 0;
	int objectiveTileCoords = 0; //the end goal of the level(such as a flag u have to reach)
	int whichLevel = 0;
	bool isTexture = true; //if there is no texture it signals the tile to use the default missing texture
	int amountOfTiles;
	sf::Vector2i spawnpoint;
	std::vector<TileInteract> tileBackground;
	std::vector<TileInteract> tileBackgroundInteract;
	std::vector<TileInteract> tileInteract;
	std::vector<std::vector<TileInteract>> tileInteractTest; //TODO: make a 2D vector
	std::vector<TileInteract> tileForeground;

	std::vector<std::vector<sf::Vector2i>> mapForeground, mapInteractable, mapBackground, mapBackgroundInteractable;
	std::vector<sf::Vector2i> tempMap;
	sf::Vector2i texturePerTileSize;

	//for opening the file containing all the map settings and tiles
	std::ifstream openfileForeground;
	std::ifstream openfileInteractable;
	std::ifstream openfileBackgroundInteractable;
	std::ifstream openfileBackground;
};

