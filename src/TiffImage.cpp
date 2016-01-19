#include <algorithm> // std::min
#include <cstdint> // std::uint8_t
#include <cstdio>
#include <cstring>
#include <string> // std::string
#include <tiffio.h>

#include "Color.h"
#include "Point.h"
#include "Size.h"
#include "TiffImage.h"

TiffImage::TiffImage(Size size, TiffImageMode mode):
	Width(size.Width),
	Height(size.Height),
	_mode(mode)
{
	if (_mode == TiffImageMode::RGB)
	{
		_bitsPerSample = 8;
		_samplesPerPixel = 3;
		_photometricInterpretation = PHOTOMETRIC_RGB;
	}

	if (_mode == TiffImageMode::CMYK)
	{
		_bitsPerSample = 8;
		_samplesPerPixel = 4;
		_photometricInterpretation = PHOTOMETRIC_SEPARATED;
	}

	_image = new std::uint8_t[Width * Height * _samplesPerPixel];
}

void TiffImage::DrawPixel(Point point, Color color)
{
	if (point.X < 0 || point.X >= (int) Width ||
		point.Y < 0 || point.Y >= (int) Height) return;
	
	size_t pixelOffset = (point.Y * Width + point.X) * _samplesPerPixel;

	if (_mode == TiffImageMode::RGB)
	{	
	    _image[pixelOffset + 0] = color.R;
	    _image[pixelOffset + 1] = color.G;
	    _image[pixelOffset + 2] = color.B;
	}

	if (_mode == TiffImageMode::CMYK)
	{
		float c = 1.0 - (color.R / 255.0);
		float m = 1.0 - (color.G / 255.0);
		float y = 1.0 - (color.B / 255.0);

		float k = std::min(c, std::min(m, y));

		c = (c - k) / (1.0 - k);
		m = (m - k) / (1.0 - k);
		y = (y - k) / (1.0 - k);

	    _image[pixelOffset + 0] = (int) (255.0 * c);
	    _image[pixelOffset + 1] = (int) (255.0 * m);
	    _image[pixelOffset + 2] = (int) (255.0 * y);
	    _image[pixelOffset + 3] = (int) (255.0 * k);
	}
}

void TiffImage::SaveToFile(const std::string& filename)
{
	TIFF* file = TIFFOpen(filename.c_str(), "w");
	if (file == nullptr) return;

	// set the tags in the new image file
	TIFFSetField(file, TIFFTAG_IMAGEWIDTH, Width);
	TIFFSetField(file, TIFFTAG_IMAGELENGTH, Height);
	TIFFSetField(file, TIFFTAG_BITSPERSAMPLE, _bitsPerSample);
	TIFFSetField(file, TIFFTAG_SAMPLESPERPIXEL, _samplesPerPixel);
	TIFFSetField(file, TIFFTAG_ROWSPERSTRIP, Height);
	TIFFSetField(file, TIFFTAG_PHOTOMETRIC, _photometricInterpretation);
	TIFFSetField(file, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
	// TIFFSetField(file, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT); // origin of the image

	if (_mode == TiffImageMode::CMYK)
	{
		TIFFSetField(file, TIFFTAG_INKSET, INKSET_CMYK);
	}

	TIFFWriteEncodedStrip(file, 0, _image, Width * Height * _samplesPerPixel);

	// Close the output file
	TIFFClose(file);
}

TiffImage::~TiffImage()
{
	// Destroy the buffer
	if (_image) _TIFFfree(_image);
}
