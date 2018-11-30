#pragma

#include <SFML/Graphics.hpp>

class Conversion
{
public:
	Conversion();

	void setValue(sf::Vector2f value, float m_conversion = 2.f);
	sf::Vector2f getConverted();
	sf::Vector2f getUnconverted();

	float m_conversion;
	sf::Vector2f m_value;
};
