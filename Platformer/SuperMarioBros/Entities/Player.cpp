#include "Player.h"

//Player::Player(sf::Vector2f size, sf::Vector2i entityPosition, sf::Texture & entityTexture, sf::Vector2i entitySpriteSize, sf::Vector2i startingEntityIndex, b2World * world, std::string collisionType)
//{
//	initEntity(size, entityPosition, entityTexture, entitySpriteSize, startingEntityIndex,  world, collisionType);
//}

Player::Player()
{
	Camera::getView(sf::Vector2f(6, 20)).setCenter(300, 700);
}

void Player::update(sf::Time deltaTime)
{
	entityRec.setPosition(body->GetPosition().x, body->GetPosition().y);
	entityRec.setRotation(body->GetAngle());

	Camera::followEntitySmooth(sf::Vector2f(entityRec.getPosition().x, entityRec.getPosition().y - 250), deltaTime.asSeconds());
}

void Player::initPlayerTEMPORARY(sf::Vector2f size, sf::Vector2i entityPosition, sf::Texture & entityTexture, sf::Vector2i entitySpriteSize, sf::Vector2i startingEntityIndex, b2World * world, std::string collisionType)
{
	initEntity(size, entityPosition, entityTexture, entitySpriteSize, startingEntityIndex, world, collisionType);
	Camera::getView().setCenter(entityRec.getPosition().x, entityRec.getPosition().y - 250);
}

void Player::draw(sf::RenderTarget &renderer)
{
	renderer.draw(entityRec);
}

void Player::controls()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) //Placeholder
	{
		velocity.x = -1000000;
		body->ApplyForceToCenter(b2Vec2(velocity.x, velocity.y), true);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		velocity.x = 1000000;
		body->ApplyForceToCenter(b2Vec2(velocity.x, velocity.y), true);
	}
	else
	{
		body->ApplyForceToCenter(b2Vec2(velocity.x * 0.95, velocity.y), true);
	}

	//for (b2ContactEdge* ce = body->GetContactList(); ce != nullptr; ce = ce->next) {
	//	b2Contact* c = ce->contact;
	//	if (c->IsTouching()) {
	//		b2WorldManifold manifold;
	//		c->GetWorldManifold(&manifold);
	//		// Check if the points are below
	//		bool below = false;
	//		for (int i = 0; i < b2_maxManifoldPoints; i++) {
	//			if (manifold.points[i].y < body->GetPosition().y - entityRec.getSize().y / 1.5f + 0.01f) {
	//				below = true;
	//				break;
	//			}
	//		}
	//		if (below) {
	//			// We can jump
	//			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
	//				body->ApplyLinearImpulse(b2Vec2(0.0f, 10000000.0f), b2Vec2(0.0f, 0.0f), true);
	//				break;
	//			}
	//		}
	//	}
	//}
}
