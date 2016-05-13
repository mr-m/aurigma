#include <iostream>
#include <vector>

#include "Color.h"
#include "Point.h"
#include "Size.h"
#include "Graphics.h"
#include "TiffImage.h"


void DrawStuffOnImage(TiffImage& img)
{
    Graphics g = Graphics::FromImage(img);

    g.FillWithColor(Color::Black);

    g.DrawLine(
        Point(2, 2),
        Point(198, 148),
        Color::Green);

    g.DrawRectangle(
        Point(16, 8),
        Size(40, 40),
        Color::Aqua);

    g.DrawEllipse(
        Point(80, 40),
        Size(50, 30),
        Color::Grey);

    g.DrawEllipse(
        Point(140, 50),
        Size(20, 46),
        Color::Yellow);

    g.DrawPath(
        std::vector<Point>{
            Point(10, 140),
            Point(20, 120),
            Point(30, 130),
            Point(40, 110)
        }, Color::White);

    g.DrawClosedPath(
        std::vector<Point>{
            Point(160,  90),
            Point(170,  80),
            Point(180,  90),
            Point(180, 100),
            Point(170, 110),
            Point(160, 100)
        }, Color::Red);

    g.DrawBezier(
        Point(70, 100),
        Point(50, 140),
        Point(120, 80),
        Point(130, 130),
        Color::Fuchsia);
}

int main()
{
    std::cout << "Hello, World!" << std::endl;

    TiffImage img1(Size(200, 150), TiffImageMode::RGB);
    TiffImage img2(Size(200, 150), TiffImageMode::CMYK);

    DrawStuffOnImage(img1);
    DrawStuffOnImage(img2);

    img1.SaveToFile("img1_rgb.tiff");
    img2.SaveToFile("img2_cmyk.tiff");

    return 0;
}
