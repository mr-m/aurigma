#ifndef AURIGMA_COLOR_H
#define AURIGMA_COLOR_H

#include <cstdint> // std::uint8_t


class Color
{
public:
	const std::uint8_t R{0};
	const std::uint8_t G{0};
	const std::uint8_t B{0};

	Color(std::uint8_t r = 255, std::uint8_t g = 0, std::uint8_t b = 0):
		R(r),
		G(g),
		B(b)
	{}

	static const Color Black;
	static const Color Grey;
	static const Color White;
	static const Color Red;
	static const Color Green;
	static const Color Blue;
	static const Color Yellow;
	static const Color Fuchsia;
	static const Color Aqua;

	static Color FromRgb(std::uint8_t, std::uint8_t, std::uint8_t);
	static Color FromCmyk(std::uint8_t, std::uint8_t, std::uint8_t, std::uint8_t);
};


#endif // AURIGMA_COLOR_H
