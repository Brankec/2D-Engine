#include "Map.h"
#include <string>

void Map::getValue(std::string &string)//removes the labels in the text file
{
	for (int i = 0; i < string.size(); i++) 
	{
		if (string[i] == '=')
		{
			string.erase(0, i + 1);
			break;
		}
	}
}

std::string Map::getName(std::string string)//gets the labels in the text file
{
	for (int i = 0; i < string.size(); i++)
	{
		if (string[i] == '=')
		{
			string.erase(i, string.size() - i);
			break;
		}
	}
	return string;
}

void Map::getFileValues(std::string &fileValue)
{
	std::string tempString = getName(fileValue);

	//if (tempString == "backgroundColor")
	//{
	//	std::cout << fileValue << std::endl;
	//	sf::Vector3i temp = getThreeValues(fileValue);

	//	*m_color = sf::Color(temp.x, temp.y, temp.z);
	//}

	if (tempString == "tileSize")
	{
		std::cout << fileValue << std::endl;
		getValue(fileValue);
		powOfN = pow(2, stoi(fileValue));
	}

	else if (tempString == "amountOfTilesX")
	{
		std::cout << fileValue << std::endl;
		getValue(fileValue);
		amountOfTiles = stoi(fileValue);
	}

	else if (tempString == "texturePerTileSize")
	{
		std::cout << fileValue << std::endl;
		getValue(fileValue);
		texturePerTileSize.x = stoi(fileValue);
		texturePerTileSize.y = stoi(fileValue);
	}

	else if (tempString == "objectiveTileCoords")
	{
		std::cout << fileValue << std::endl;
		getValue(fileValue);
		objectiveTileCoords = stoi(fileValue);
	}

	else if (tempString == "whichLevel")
	{
		std::cout << fileValue << std::endl;
		getValue(fileValue);
		whichLevel = stoi(fileValue);
	}

	else if (tempString == "spawnpoint")
	{
		std::cout << fileValue << std::endl;
		spawnpoint = getTwoValues(fileValue);
	}
}

sf::Vector2i Map::getTwoValues(std::string &string)//removes the labels in the text file
{
	getValue(string);
	std::string a = string, b = string;
	for (int i = 0; i < string.size(); i++)
	{
		if (string[i] == ',')
		{
			a.erase(i + 1, string.size() - (i + 1));
			b.erase(0, i + 1);
			break;
		}
	}
	return { stoi(a), stoi(b) };
}

//sf::Vector3i Map::getThreeValues(std::string & string)
//{
//	getValue(string);
//	std::string r = string, g = string, b = string;
//	int firstCommaIndex = 0;
//	for (int i = 0; i < string.size(); i++)  //Doesnt work, second parameter is the same as first and third is second
//	{
//		if (string[i] == ',')
//		{
//			r.erase(i + 1, string.size() - (i + 1));
//			if(firstCommaIndex != 0) //to make sure the first loop was made
//				g.substr(firstCommaIndex, (i+1) - firstCommaIndex);
//			b.erase(0, i + 1);
//
//			firstCommaIndex = i + 1;
//			break;
//		}
//	}
//	return { stoi(r), stoi(g), stoi(b) };
//}

std::vector<int> Map::getAllTileIndices(std::string string) // gets the whole line of indices and then stores individual one into a vector of ints
{
	std::vector<int> temp;
	int previous = 0;
	for (int i = 0; i < string.size(); i++)
	{
		if (string[i] == ' ')
		{
			temp.push_back(stoi(string.substr(previous, i - previous + 1)));
			previous = i + 1;
		}
		else
		{
			continue;
		}
	}

	return temp;
}
template<typename T>
void Map::storeIndices(std::string to, std::vector<std::vector<sf::Vector2i>> &map, std::vector<T> &tiles, b2World* world) //reads and stores all the indices from the text file
{
	std::string collisionType;
	getValue(fileValue);
	collisionType = fileValue;

	std::cout << fileValue << std::endl;
	while (openfileInteractable.good())
	{
		while (getName(fileValue) != to)
		{
			std::vector<int> tileIndex;
			std::getline(openfileInteractable, fileValue);
			tileIndex = getAllTileIndices(fileValue);

			for (auto &index : tileIndex)
			{
				tempMap.push_back(Sprite_sheet_coordinates(index - 1)); //the indices will always be for 1 less inside the code(so 0 is actually -1 and 1 is actually 0)

				if (&index == &tileIndex.back())//checks if it's the last element before going to the next line
				{
					map.push_back(tempMap);
					tempMap.clear();
				}
			}
		}
		break;
	}
	if (map.size() != 0)
	{
		for (int x = 0; x < map[1].size(); x++)
		{
			for (int y = 0; y < map.size(); y++)
			{
				if (map[y][x].x != -1 && map[y][x].y != -1)
				{
					tiles.emplace_back(sf::Vector2f((float)powOfN, (float)powOfN),
						sf::Vector2i(x * (float)powOfN, y * (float)powOfN),//tile x position
						tileTexture,
						texturePerTileSize,
						map[y][x],//spritesheet coordinates
						isTexture,//is there texture(turns false if no texture was loaded/found)
						world,
						collisionType);
				}
			}
		}
	}
}

sf::Vector2i Map::Sprite_sheet_coordinates(int tileIndex)
{
	if (tileIndex == -1)
		return sf::Vector2i(-1, -1);//for empty cells in game
	else
	{
		sf::Vector2i coords;
		coords.x = (tileIndex % amountOfTiles) * texturePerTileSize.x;   //amount of tiles ONLY in 1 row (on the X axis)
		coords.y = (tileIndex / amountOfTiles) * texturePerTileSize.y;  //leave it like this for now


		return coords;
	}
}

void Map::loadMap(std::string gameName, std::string fileName, b2World* world)
{
	mapInteractable.clear();

	openfileInteractable.open(gameName + "/Assets/Levels/" + fileName + ".txt");

	if (openfileInteractable.is_open())
	{
		std::getline(openfileInteractable, fileValue);
		std::cout << fileValue << std::endl;
		getValue(fileValue);
		if (!tileTexture.loadFromFile(fileValue))//we pass the texture by reference to the instance of a tile down the line
		{
			isTexture = false;
		}

		while (fileValue != "start") //loops until the first thing it encounters is background
		{
			std::getline(openfileInteractable, fileValue);
			getFileValues(fileValue);//storing map info
		}

		std::getline(openfileInteractable, fileValue);
		if (getName(fileValue) == "Background")//TODO: Figure out how to make this into a loop instead of hardcoding it
		{
			storeIndices("BackgroundInteractable", mapBackground, tileBackground, world);
		}
		if (getName(fileValue) == "BackgroundInteractable")
		{
			storeIndices("Interactable", mapBackgroundInteractable, tileBackgroundInteract, world);
		}
		if (getName(fileValue) == "Interactable")
		{
			storeIndices("Foreground", mapInteractable, tileInteract, world);
		}
		if (getName(fileValue) == "Foreground")
		{
			storeIndices("end", mapForeground, tileForeground, world);
		}
	}
}

void Map::drawForeground(sf::RenderTarget& renderer)
{
	for (auto tile : tileForeground)
	{
		tile.TEMPORARYdrawingMETHOD(renderer);
	}
}

void Map::drawInteractive(sf::RenderTarget& renderer)
{
	//float cam_x = Camera::getView().getCenter().x;
	//int cam_x_tile = cam_x / tileInteract[2].tileRec.getSize().x;
	//int Tile_row_width = (renderer.getView().getSize().x + 2000) / mapInteractable[1].size(); //mapMain is the position of the tiles from the text file
	//float cam_y = Camera::getView().getCenter().y;
	//int cam_y_tile = cam_y / tileInteract[2].tileRec.getSize().y;
	//int Tile_column_height = (renderer.getView().getSize().y) + 100 / mapInteractable.size();

	//int X_border_right = std::min((int)mapInteractable[1].size(), cam_x_tile + Tile_row_width / 2);
	//int Y_border_right = std::min((int)mapInteractable.size(), cam_y_tile + Tile_column_height / 2);

	//for (int x = std::max(cam_x_tile - Tile_row_width / 2, 0); x < X_border_right; x++)
	//	for (int y = std::max(cam_y_tile - Tile_column_height / 2, 0); y < Y_border_right; y++)
	//	{
	//		renderer.draw(tileInteract[x].tileRec);
	//	}

	//TODO: Make a 2D vector of tileInteract so you can use the above code for rendering
	for (auto tile : tileInteract)
	{
		tile.TEMPORARYdrawingMETHOD(renderer);
		tile.update();
	}
}

void Map::drawBackgroundInteractable(sf::RenderTarget & renderer)
{
	for (auto tile : tileBackgroundInteract)
	{
		tile.TEMPORARYdrawingMETHOD(renderer);
	}
}

void Map::drawBackground(sf::RenderTarget & renderer)
{
	for (auto tile : tileBackground)
	{
		tile.TEMPORARYdrawingMETHOD(renderer);
	}
}

//void Map::setClearColor(sf::Color & color)
//{
//	m_color = &color;
//}
