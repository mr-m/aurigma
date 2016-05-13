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

// TiffImage - лучше было бы отдельно Image, без специфики кодека.
// Потенциально ведь изображение можно не только в TiffFormat сохранять.
class TiffImage
{
public:
    // По идее, это должны быть закрытые поля
    const unsigned int Width{0};
    const unsigned int Height{0};

    TiffImage(Size size, TiffImageMode);
    // Виртуальность тут ни к чему
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
