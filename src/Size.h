#ifndef AURIGMA_SIZE_H
#define AURIGMA_SIZE_H


class Size
{
public:
    const unsigned int Width{0};
    const unsigned int Height{0};

    Size(unsigned int width = 0, unsigned int height = 0):
        Width(width),
        Height(height)
    {}
};


#endif // AURIGMA_SIZE_H
