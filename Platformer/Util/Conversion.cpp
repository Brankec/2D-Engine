#include "Conversion.h"

Conversion::Conversion()
{
}

void Conversion::setValue(sf::Vector2f value, float conversion)
{
	m_value = value;
	m_conversion = conversion;
}

sf::Vector2f Conversion::getConverted()
{
	return sf::Vector2f(m_value.x * m_conversion, m_value.y * m_conversion);
}

sf::Vector2f Conversion::getUnconverted()
{
	return sf::Vector2f(m_value.x / m_conversion, m_value.y / m_conversion);
}
