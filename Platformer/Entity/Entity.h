#pragma once

#include <iostream>
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "../Util/Conversion.h"
#include "../Sound/Sound.h"

class Entity : public Sound
{
public:
	Entity();
public:
	void initEntity(sf::Vector2f size, sf::Vector2i entityPosition, sf::Texture &entityTexture, sf::Vector2i entitySpriteSize, sf::Vector2i startingEntityIndex, b2World* world, std::string collisionType); //for player
	void initEntity(sf::Vector2f size, sf::Vector2i entityPosition, sf::Texture &entityTexture, sf::Vector2i entitySpriteSize, sf::Vector2i startingEntityIndex, bool isTexture, b2World* world, std::string collisionType); //for NPC

	void initBody(sf::Vector2f size, sf::Vector2i tilePosition, b2World* world, std::string collisionType);//method for initializing box2D physics
	void setEntityTexture(sf::Vector2i tileIndex, sf::Vector2i tileSpriteSize);//method for assigning texture from a spritesheet 

	void animation();

	b2Body* getBody() { return body; };
	b2Fixture* getFixture() { return fixture; };

protected:
	sf::RectangleShape entityRec;
	sf::Texture texture;
	b2Body *body = nullptr;
	b2Fixture *fixture = nullptr;
	b2Vec2 velocity = b2Vec2(0, 0);

	sf::Vector2i m_entityPosition;
	sf::Vector2i m_entitySpriteSize;
	bool isCollidable = false;
	bool isDestructable = false;
	bool isTrigger = false;
	bool isAnimated = false;
	bool isTriangleShape = false;

	Conversion conversion;
};