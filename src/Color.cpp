#include <cstdint> // std::uint8_t

#include "Color.h"

const Color Color::Black =   Color(  0,  0,  0);
const Color Color::Grey =    Color(128,128,128);
const Color Color::White =   Color(255,255,255);
const Color Color::Red =     Color(255,  0,  0);
const Color Color::Green =   Color(  0,255,  0);
const Color Color::Blue =    Color(  0,  0,255);
const Color Color::Yellow =  Color(255,255,  0);
const Color Color::Fuchsia = Color(255,  0,255);
const Color Color::Aqua =    Color(  0,255,255);

Color Color::FromRgb(std::uint8_t r, std::uint8_t g, std::uint8_t b)
{
	return Color(r, g, b);
}

Color Color::FromCmyk(std::uint8_t c, std::uint8_t m, std::uint8_t y, std::uint8_t k)
{
	std::uint8_t r = 255 * (1-c) * (1-k);
	std::uint8_t g = 255 * (1-m) * (1-k);
	std::uint8_t b = 255 * (1-y) * (1-k);

	return Color(r, g, b);
}
