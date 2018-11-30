#include "TileInteract.h"

TileInteract::TileInteract(sf::Vector2f size, sf::Vector2i tilePosition, sf::Texture &tileTexture, sf::Vector2i tileSpriteSize, sf::Vector2i tileIndex, bool isTexture, b2World* world, std::string collisionType)
{
	m_tilePosition = tilePosition;
	tileRec.setOrigin(tileRec.getSize().x / 2, tileRec.getSize().y / 2);
	initBody(size, tilePosition, world, collisionType);

	if (isTexture)
	{
		tileRec.setTexture(&tileTexture);
		setTileTexture(tileIndex, tileSpriteSize);
	}
	else
	{
		if (!tileTexture.loadFromFile("Map/NTF.png"))
			std::cout << "ERROR: Could not find NTF(NoTextureFound) placeholder image..." << std::endl;
		tileRec.setTexture(&tileTexture);
	}

}

void TileInteract::setTileTexture(sf::Vector2i tileIndex, sf::Vector2i tileSpriteSize) //the index is the actual tile texture position.
{
	tileRec.setTextureRect(sf::IntRect(tileIndex.x, tileIndex.y, tileSpriteSize.x, tileSpriteSize.y));
}

void TileInteract::update()
{
	if ((tileRec.getPosition().x + 64 + tileRec.getSize().x / 2) >= (Camera::getView().getCenter().x - Camera::getView().getSize().x / 2) && // PLACEHOLDER DRAWING OPTIMIZATION!!!!!
		(tileRec.getPosition().x - tileRec.getSize().x / 2) <= (Camera::getView().getCenter().x + Camera::getView().getSize().x / 2))
	{
		if (body != nullptr && fixture != nullptr)
		{
			tileRec.setPosition(body->GetPosition().x, body->GetPosition().y);
			tileRec.setRotation(body->GetAngle());
		}
		else
		{
			tileRec.setPosition((float)m_tilePosition.x, (float)m_tilePosition.y); //For some reason, after initial view port all the none labeled tiles in text file go invisible and this body never gets called
		}

		if (isAnimated)
		{
			animation();
		}
	}
}

void TileInteract::animation()
{
}

void TileInteract::TEMPORARYdrawingMETHOD(sf::RenderTarget &renderer)
{
	if ((tileRec.getPosition().x + 64 + tileRec.getSize().x / 2) >= (Camera::getView().getCenter().x - Camera::getView().getSize().x / 2) && // PLACEHOLDER DRAWING OPTIMIZATION!!!!!
		(tileRec.getPosition().x - tileRec.getSize().x / 2) <= (Camera::getView().getCenter().x + Camera::getView().getSize().x / 2))
	{
		update();
		renderer.draw(tileRec);
	}
}

void TileInteract::initBody(sf::Vector2f size, sf::Vector2i tilePosition, b2World* world, std::string collisionType)
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

		bodyDef.position.Set(tilePosition.x, tilePosition.y);
		body = world->CreateBody(&bodyDef);

		bodyShape.SetAsBox(size.x / 2.f, size.y / 2.f);

		fixtureDef.shape = &bodyShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3;
		fixture = body->CreateFixture(&fixtureDef);

		tileRec.setSize(size);

		tileRec.setPosition(sf::Vector2f(body->GetPosition().x, body->GetPosition().y));
		tileRec.setRotation(body->GetAngle());
	}
	else
	{
		tileRec.setSize(size);
	}
}
