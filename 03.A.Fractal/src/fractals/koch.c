#include <math.h>
#include <assert.h>

#include "image.h"
#include "fractal.h"

const float cos60 = 0.5;
const float sin60 = 0.866025;
const float sqrt3 = 1.732051;

void koch_curve(image_p picture, pixel_point_t p1, pixel_point_t p2, unsigned int steps);

void koch_snowflake(image_p picture, unsigned int steps)
{
    if (steps == 0)
    {
        fill_color(picture, 255);
        return;
    }

    pixel_coord side = (pixel_coord)pow(4, steps);
    pixel_coord size = ceil((float)side * 2 / sqrt3);
    pixel_coord h = floor((float)side * sqrt3 / 2);

    pixel_point_t A = {size / 2, 0};
    pixel_point_t B = {A.x - (side / 2), h};
    pixel_point_t C = {A.x + (side / 2), h};

    image_p newPicture = create_image(size, size);
    fill_color(newPicture, 255);

    koch_curve(newPicture, A, B, steps-1);
    koch_curve(newPicture, B, C, steps-1);
    koch_curve(newPicture, C, A, steps-1);

    scale_image_blin(newPicture, picture->width, picture->height);
    reassign_image(picture, newPicture, true);
}

void koch_curve(image_p picture, pixel_point_t p1, pixel_point_t p2, unsigned int steps)
{
    assert(("Out of dimension", p1.x >= 0 && p1.y >= 0 && p1.x < picture->width && p1.y < picture->height &&
                                p2.x >= 0 && p2.y >= 0 && p2.x < picture->width && p2.y < picture->height));

    if (steps == 0)
        return draw_line(picture, p1, p2, 0);

    int dx = (int)p2.x - (int)p1.x;
    int dy = (int)p2.y - (int)p1.y;

    // line vector
    float vx = (float)dx / 3;
    float vy = (float)dy / 3;

    // rotate 60 degrees
    float vx_ = vx*cos60 - vy*sin60;
    float vy_ = vx*sin60 + vy*cos60;

    // triangle vertices
    pixel_point_t A = {round((float)p1.x + (float)dx / 3), round((float)p1.y + (float)dy / 3)};
    pixel_point_t B = {round((float)A.x + vx_), round((float)A.y + vy_)};
    pixel_point_t C = {round((float)p1.x + (float)dx * 2 / 3), round((float)p1.y + (float)dy * 2 / 3)};

    koch_curve(picture, p1, A, steps-1);
    koch_curve(picture, A, B, steps-1);
    koch_curve(picture, B, C, steps-1);
    koch_curve(picture, C, p2, steps-1);
}