#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../Util/Camera.h"
#include <Box2D/Box2D.h>

class TileInteract
{
public:
	TileInteract(sf::Vector2f size, sf::Vector2i tilePosition, sf::Texture &tileTexture, sf::Vector2i tileSpriteSize, sf::Vector2i tileIndex, bool isTexture, b2World* world, std::string collisionType);
	void update();
	void TEMPORARYdrawingMETHOD(sf::RenderTarget &renderer);
	void initBody(sf::Vector2f size, sf::Vector2i tilePosition, b2World* world, std::string collisionType);

	b2Body* getBody() { return body; };
	b2Fixture* getFixture() { return fixture; };

private:
	void animation();
	void setTileTexture(sf::Vector2i tileIndex, sf::Vector2i tileSpriteSize);

public:
	sf::RectangleShape tileRec;
	sf::Vector2i m_tilePosition;
	sf::Vector2i m_tileSpriteSize;
	bool isCollidable = false;
	bool isDestructable = false;
	bool isTrigger = false;
	bool isAnimated = false;
	bool isTriangleShape = false;
private:
	b2Body *body = nullptr;
	b2Fixture *fixture = nullptr;
};