#include "Camera.h"

sf::View Camera::getView(sf::Vector2f newCameraSpeed)
{
	cameraSpeed = newCameraSpeed;

	return view;
}

sf::FloatRect Camera::getViewPort()
{
	return view.getViewport();
}

void Camera::cameraZoom(sf::Event event)
{
	if (event.type == sf::Event::MouseWheelMoved)
	{
		if (event.mouseWheel.delta < 0)
		{
			view.zoom(1.1f);
		}
		if (event.mouseWheel.delta > 0)
		{
			view.zoom(0.95f);
		}
	}
}

void Camera::followEntitySmooth(sf::Vector2f entityPos, float deltaTime)
{
	camera.x = Lerp(camera.x, entityPos.x, deltaTime * cameraSpeed.x * 10);
	camera.y = Lerp(camera.y, entityPos.y, deltaTime * cameraSpeed.y * 10);

	view.setCenter(camera);
}

float Camera::Lerp(float x, float y, float z) //acceleration or deceleration
{
	return ((1.0f - z) * x) + (z * y);
}
