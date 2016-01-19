#ifndef AURIGMA_TIFFIMAGE_H
#define AURIGMA_TIFFIMAGE_H

#include <cstdint> // std::uint8_t
#include <string> // std::string

#include "Color.h"
#include "Point.h"


enum class TiffImageMode
{
	RGB,
	CMYK
};

class TiffImage
{
public:
	const unsigned int Width{0};
	const unsigned int Height{0};

	TiffImage(Size size, TiffImageMode);
	virtual ~TiffImage();

	void DrawPixel(Point, Color = Color());
	void SaveToFile(const std::string&);

private:
	// Raw image data
	std::uint8_t* _image;

	TiffImageMode _mode{TiffImageMode::RGB};

	int _bitsPerSample;
	int _samplesPerPixel;
	int _photometricInterpretation;
};


#endif // AURIGMA_TIFFIMAGE_H
