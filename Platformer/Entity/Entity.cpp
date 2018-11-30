#include "Entity.h"

void Entity::animation()
{

}

Entity::Entity()
{
}

void Entity::initEntity(sf::Vector2f size, sf::Vector2i entityPosition, sf::Texture & entityTexture, sf::Vector2i entitySpriteSize, sf::Vector2i startingEntityIndex, b2World * world, std::string collisionType)
{
	//setting the origin of the rectangle in the middle and initializing box2D physics
	m_entityPosition = entityPosition;
	entityRec.setOrigin(entityRec.getSize().x / 2, entityRec.getSize().y / 2);
	initBody(size, entityPosition, world, collisionType);

	entityRec.setTexture(&entityTexture);
	setEntityTexture(startingEntityIndex, entitySpriteSize); //temporary. Animation will be added later

	//Default values
	isCollidable = true;
	isDestructable = true;
	isAnimated = true;
}

void Entity::initEntity(sf::Vector2f size, sf::Vector2i entityPosition, sf::Texture & entityTexture, sf::Vector2i entitySpriteSize, sf::Vector2i startingEntityIndex, bool isTexture, b2World * world, std::string collisionType)
{
	m_entityPosition = entityPosition;
	m_entitySpriteSize = entitySpriteSize;
	initBody(size, entityPosition, world, collisionType);

	if (isTexture)
	{
		entityRec.setTexture(&entityTexture);
		setEntityTexture(startingEntityIndex, entitySpriteSize); //temporary. Animation will be added later
	}
	else
	{
		if (!entityTexture.loadFromFile("Map/NTF.png"))
			std::cout << "ERROR: Could not find NTF(NoTextureFound) placeholder image..." << std::endl;
		entityRec.setTexture(&entityTexture);
	}
}

void Entity::setEntityTexture(sf::Vector2i entityIndex, sf::Vector2i entitySpriteSize) //the index is the actual tile texture position.
{
	entityRec.setTextureRect(sf::IntRect(entityIndex.x, entityIndex.y, entitySpriteSize.x, entitySpriteSize.y));
}

void Entity::initBody(sf::Vector2f size, sf::Vector2i entityPosition, b2World * world, std::string collisionType)
{

	if (collisionType != "none")
	{
		b2BodyDef bodyDef;
		b2PolygonShape bodyShape;
		b2FixtureDef fixtureDef;


		if (collisionType == "static")
		{
			bodyDef.type = b2_staticBody;
		}
		else if (collisionType == "dynamic")
		{
			bodyDef.type = b2_dynamicBody;
		}

		bodyDef.position.Set(entityPosition.x, entityPosition.y);
		body = world->CreateBody(&bodyDef);

		//bodyShape.SetAsBox(entityRec.getSize().x / 2, entityRec.getSize().y / 1.5); //FIGURE THIS OUT BEFORE CONTINUING!!!
		bodyShape.SetAsBox(size.x / 2.0f, size.y / 2.0f); // temp
		std::cout << size.y / 2.0f << std::endl;

		fixtureDef.shape = &bodyShape;
		fixtureDef.density = 0.3f;
		fixtureDef.friction = 0.0;
		fixture = body->CreateFixture(&fixtureDef);

		body->SetFixedRotation(true);
		body->SetLinearDamping(0.5f);

		entityRec.setSize(size);
		std::cout << size.y << std::endl;

		entityRec.setPosition(sf::Vector2f(body->GetPosition().x, body->GetPosition().y));
		entityRec.setRotation(body->GetAngle());
	}
	else
	{
		entityRec.setSize(size);
	}
}
