#include "StatePlaying.h"

StatePlaying::StatePlaying(Game& game)
	: StateBase(game)
{
	level.loadTileMap(&world);

	texture.loadFromFile("SuperMarioBros/Assets/Textures/Player/player.gif");

	player.initPlayerTEMPORARY(sf::Vector2f(64, 96), //64 96 default
		sf::Vector2i(300, 700),
		texture,
		sf::Vector2i(16, 32),
		sf::Vector2i(1, 1),
		&world,
		"dynamic");
}

void StatePlaying::handleEvent(sf::Event e)
{

}

void StatePlaying::handleInput()
{
	player.controls();
}

void StatePlaying::update(sf::Time deltaTime)
{
}

void StatePlaying::fixedUpdate(sf::Time deltaTime)
{
	world.Step(1.f / 60.f, 6, 2);

	player.update(deltaTime);
}

void StatePlaying::render(sf::RenderTarget& renderer)
{
	level.drawBackground(renderer);
	level.drawBackgroundInteractable(renderer);
	level.drawInteractive(renderer);

	player.draw(renderer);

	level.drawForeground(renderer);

	renderer.setView(Camera::getView(sf::Vector2f(10.f, 1.f)));
}

void StatePlaying::pushState(bool*m_shouldPush)
{
}

void StatePlaying::popState(bool & shouldPop)
{
	this->shouldPop = &shouldPop;
}
