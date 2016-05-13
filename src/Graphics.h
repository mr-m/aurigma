#ifndef AURIGMA_GRAPHICS_H
#define AURIGMA_GRAPHICS_H

#include <vector>

#include "Color.h"
#include "Point.h"
#include "Size.h"
#include "TiffImage.h"


class Graphics
{
public:
    static Graphics FromImage(TiffImage&);

    void FillWithColor(Color = Color());
    void DrawLine(Point, Point, Color = Color());
    void DrawRectangle(Point, Size, Color = Color());
    void DrawPath(std::vector<Point>, Color = Color());
    void DrawClosedPath(std::vector<Point>, Color = Color());
    void DrawEllipse(Point, Size, Color = Color());
    void DrawBezier(Point, Point, Point, Point, Color = Color());
//    static void DrawText(std::string, position);

private:
    TiffImage& _image;

    Graphics(TiffImage& image):
        _image(image)
    {}

    float getPt(float, float, float);
    void DrawEllipsePixels(Point, int, int, Color = Color());
};


#endif // AURIGMA_GRAPHICS_H
