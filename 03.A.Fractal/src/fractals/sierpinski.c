#include <math.h>
#include <assert.h>

#include "image.h"
#include "fractal.h"

void sierpinski_subcarpet_(image_p picture, pixel_coord size, pixel_coord x, pixel_coord y, unsigned int stepsLeft);
void fill_white_(image_p picture, pixel_coord size, pixel_coord x, pixel_coord y);

void sierpinski_carpet(image_p picture, unsigned int steps)
{
    if (steps == 0)
    {
        fill_color(picture, 0);
        return;
    }

    pixel_coord size = (pixel_coord)pow(3, steps);
    image_p newPicture = create_image(size, size);
    fill_color(newPicture, 0);

    sierpinski_subcarpet_(newPicture, size, 0, 0, steps);
    scale_image_blin(newPicture, picture->width, picture->height);

    reassign_image(picture, newPicture, true);
}

void sierpinski_subcarpet_(image_p picture, pixel_coord size, pixel_coord x, pixel_coord y, unsigned int stepsLeft)
{
    assert(("stepsLeft must be positive", stepsLeft > 0));
    assert(("Invalid subpicture size", size <= picture->width));

    pixel_coord newSize = size / 3;

    if (stepsLeft == 1) {
        fill_white_(picture, newSize, x + newSize, y + newSize);
        return;
    }

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
        {
            if (i == 1 && j == 1)
                fill_white_(picture, newSize, x + j*newSize, y + i*newSize);
            else
                sierpinski_subcarpet_(picture, newSize, x + j*newSize, y + i*newSize, stepsLeft - 1);
        }
}

void fill_white_(image_p picture, pixel_coord size, pixel_coord x, pixel_coord y)
{
    assert(("Out of dimension", x >= 0 && y >= 0 && x < picture->width && y < picture->height));
    assert(("Invalid subpicture size", size <= picture->width));

    for (pixel_coord i = 0; i < size; ++i)
        for (pixel_coord j = 0; j < size; ++j)
            set_pixel(picture, x+j, y+i, 255);
}