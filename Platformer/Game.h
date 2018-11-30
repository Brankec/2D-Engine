#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <memory>
#include <stack>
#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "State/StateBase.h"

class Game
{
public:
	Game();

	void run();

	template<typename T, typename... Args>
	void pushState(Args&&... args);

	void popState();

	const sf::RenderWindow& getWindow() const;

private:
	void handleEvent();
	void tryPop();

	StateBase& getCurrentState();

	sf::RenderWindow m_window;
	std::stack<std::unique_ptr<StateBase>> m_states;

	bool m_shouldPop = false;
	bool m_shouldPush[2] = { false, false }; //0) playing state, 1) ingame menu state
	sf::Color color = { 70, 85, 57 };
};

template<typename T, typename... Args>
void Game::pushState(Args&&... args)
{
	m_states.push(std::make_unique<T>(std::forward<Args>(args)...));
}

#endif // GAME_H_INCLUDED

