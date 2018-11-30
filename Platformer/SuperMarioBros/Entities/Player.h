#include "../../Entity/Entity.h"
#include "../../Util/Camera.h"

class Player : public Entity
{
public:
	Player();
	//Player(sf::Vector2f size, sf::Vector2i entityPosition, sf::Texture & entityTexture, sf::Vector2i entitySpriteSize, sf::Vector2i startingEntityIndex, b2World * world, std::string collisionType);

	void update(sf::Time deltaTime);

	void initPlayerTEMPORARY(sf::Vector2f size, sf::Vector2i entityPosition, sf::Texture & entityTexture, sf::Vector2i entitySpriteSize, sf::Vector2i startingEntityIndex, b2World * world, std::string collisionType);

	void draw(sf::RenderTarget &renderer);

	void controls();

public:
	int healthStage = 1; //default small mario
};

