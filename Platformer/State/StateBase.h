#ifndef STATEBASE_H_INCLUDED
#define STATEBASE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

class Game;

class StateBase
{
    public:
        StateBase(Game& game) :  m_pGame   (&game)
        {}

        virtual ~StateBase() = default;

        virtual void handleEvent    (sf::Event e) = 0; //Event loop(loop that is based on render speed)
        virtual void handleInput    () = 0; //Input loop(loop that is based on render speed)
        virtual void update         (sf::Time deltaTime) = 0; //Update loop(loop that is based on maximum loop speed)
        virtual void fixedUpdate    (sf::Time deltaTime) = 0; //Fixed game loop(generally it's 60 ticks per second. Can be adjusted in Game.cpp file)
        virtual void render         (sf::RenderTarget& renderer) = 0; //Render loop(loop that is based on maximum loop speed)

		virtual void pushState(bool*m_shouldPush) = 0;//method used for pushing a new stop on top of the current state
		virtual void popState(bool & shouldPop) = 0;//method used for popping the current state

    protected:
        Game* m_pGame;
		b2World world = b2Vec2(0.0, 10.f);//Box2D World initialization
};

#endif // STATEBASE_H_INCLUDED
