#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>


namespace Camera
{
	void cameraZoom(sf::Event event);
	void followEntitySmooth(sf::Vector2f entityPos, float deltaTime);

	sf::View getView(sf::Vector2f newCameraSpeed = { 0, 0 });

	sf::FloatRect getViewPort();

	float Lerp(float x, float y, float z);

	static sf::View view;
	static sf::Vector2f camera;
	static sf::Vector2f cameraSpeed = { 10, 10 };
};