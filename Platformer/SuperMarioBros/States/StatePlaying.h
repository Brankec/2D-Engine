#ifndef STATEPLAYING_H_INCLUDED
#define STATEPLAYING_H_INCLUDED

#include "../../State/StateBase.h"
#include "../Maps/Level.h"
#include "../Entities/Player.h"

#include <Box2D/Box2D.h>

class StatePlaying
	: public StateBase //inherit other classes here
{
 public:
	 StatePlaying(Game& game);

     void handleEvent    (sf::Event e)                   override;
     void handleInput    ()                              override;
     void update         (sf::Time deltaTime)            override;
     void fixedUpdate    (sf::Time deltaTime)            override;
     void render         (sf::RenderTarget& renderer)    override;

	 void pushState(bool*m_shouldPush)					 override;
	 void popState(bool & shouldPop)					 override;

private:
	bool* shouldPop;
	Level level;
	float x = Camera::getView().getCenter().x, y = Camera::getView().getCenter().y;
	sf::Color *backgroundColor;
	Player player;

private://for debugging
	sf::Texture texture;
};

#endif // STATEPLAYING_H_INCLUDED
