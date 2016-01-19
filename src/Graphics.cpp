#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iterator>
#include <vector>

#include "Color.h"
#include "Point.h"
#include "Size.h"
#include "Graphics.h"
#include "TiffImage.h"


Graphics Graphics::FromImage(TiffImage& image)
{
    return Graphics(image);
}

void Graphics::FillWithColor(Color color)
{
    for (unsigned int i = 0; i < _image.Width; i++)
        for (unsigned int j = 0; j < _image.Height; j++)
            _image.DrawPixel(Point(i, j), color);
}

void Graphics::DrawLine(Point pA, Point pB, Color color)
{
    int dx =  abs(pB.X - pA.X);
    int dy = -abs(pB.Y - pA.Y);

    int sx = pA.X < pB.X ? 1 : -1;
    int sy = pA.Y < pB.Y ? 1 : -1;

    int err = dx + dy; /* error value e_xy */
    int doubleErr;

    int x = pA.X;
    int y = pA.Y;
    
    for (;;)
    {
        _image.DrawPixel(Point(x, y), color);
        
        if (x == pB.X && y == pB.Y) break;

        doubleErr = 2 * err;
        
        if (doubleErr >= dy) { err += dy; x += sx; } /* e_xy+e_x > 0 */
        if (doubleErr <= dx) { err += dx; y += sy; } /* e_xy+e_y < 0 */
    }
}

void Graphics::DrawRectangle(Point pointNW, Size size, Color color)
{
    //  NW---width--NE
    //   |          |
    // height     height
    //   |          |
    //  SW---width--SE

    Point pointNE(pointNW.X + size.Width, pointNW.Y);
    Point pointSW(pointNW.X,              pointNW.Y + size.Height);
    Point pointSE(pointNW.X + size.Width, pointNW.Y + size.Height);

    DrawLine(pointNW, pointNE, color);
    DrawLine(pointNE, pointSE, color);
    DrawLine(pointSE, pointSW, color);
    DrawLine(pointSW, pointNW, color);
}

void Graphics::DrawPath(std::vector<Point> vec, Color color)
{
    for (auto it = vec.begin(); std::next(it) != vec.end(); ++it)
    {
        DrawLine(*it, *std::next(it), color);
    }
}

void Graphics::DrawClosedPath(std::vector<Point> vec, Color color)
{
    DrawPath(vec, color);
    DrawLine(vec.front(), vec.back(), color);
}

float Graphics::getPt(float n1, float n2, float perc)
{
    float dt = n2 - n1;

    return n1 + (perc * dt);
}    

void Graphics::DrawBezier(Point p0, Point p1, Point p2, Point p3, Color color)
{
    DrawLine(p0, p1, Color::FromRgb(128,0,128));
    DrawLine(p2, p3, Color::FromRgb(128,0,128));

    for(float t = 0; t < 1; t += 0.001)
    {
        // The Green Line
        float xa = getPt(p0.X, p1.X, t);
        float ya = getPt(p0.Y, p1.Y, t);
        float xb = getPt(p1.X, p2.X, t);
        float yb = getPt(p1.Y, p2.Y, t);
        float xc = getPt(p2.X, p3.X, t);
        float yc = getPt(p2.Y, p3.Y, t);

        // The Blue Line
        float xp = getPt(xa, xb, t);
        float yp = getPt(ya, yb, t);
        float xq = getPt(xb, xc, t);
        float yq = getPt(yb, yc, t);

        // The Black Dot
        float x = getPt(xp, xq, t);
        float y = getPt(yp, yq, t);

        _image.DrawPixel(Point((int) x, (int) y), color);
    }
}

void Graphics::DrawEllipsePixels(Point pointC, int x, int y, Color color)
{
    int pX = pointC.X;
    int pY = pointC.Y;

    _image.DrawPixel(Point(pX + x, pY + y), color);
    _image.DrawPixel(Point(pX + x, pY - y), color);
    _image.DrawPixel(Point(pX - x, pY - y), color);
    _image.DrawPixel(Point(pX - x, pY + y), color);
}

void Graphics::DrawEllipse(Point pointC, Size size, Color color)
{
    const int twoASquare = 2 * size.Width * size.Width;
    const int twoBSquare = 2 * size.Height * size.Height;

    // First set of points
    {
        int x = size.Width;
        int y = 0;

        int xChange = size.Height * size.Height * (1 - 2 * size.Width);
        int yChange = size.Width * size.Width;

        int ellipseError = 0;
        int stoppingX = twoBSquare * size.Width;
        int stoppingY = 0;

        while (stoppingX >= stoppingY)
        {
            DrawEllipsePixels(pointC, x, y, color);

            y++;
            stoppingY += twoASquare;
            ellipseError += yChange;
            yChange += twoASquare;

            if ((2 * ellipseError + xChange) > 0){
                x--;
                stoppingX -= twoBSquare;
                ellipseError += xChange;
                xChange += twoBSquare;
            }
        }
    }

    // Second set of points
    {
        int x = 0;
        int y = size.Height;

        int xChange = size.Height * size.Height;
        int yChange = size.Width * size.Width * (1 - 2 * size.Height);

        int ellipseError = 0;
        int stoppingX = 0;
        int stoppingY = twoASquare * size.Height;

        while (stoppingX <= stoppingY)
        {
            DrawEllipsePixels(pointC, x, y, color);

            x++;
            stoppingX += twoBSquare;
            ellipseError += xChange;
            xChange += twoBSquare;

            if ((2 * ellipseError + yChange) > 0){
                y--;
                stoppingY -= twoASquare;
                ellipseError += yChange;
                yChange += twoASquare;
            }
        }
    }
}
