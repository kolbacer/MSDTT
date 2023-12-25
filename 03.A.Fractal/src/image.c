#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "image.h"

image_p create_image(pixel_coord width, pixel_coord height)
{
    assert(("Invalid dimensions", width > 0 && height > 0));

    image_t *v = malloc(sizeof(image_t));
    v->width = width;
    v->height = height;
    v->data = malloc(sizeof(pixel_data) * width * height);

    return v;
}

void fill_random(image_p picture)
{
    pixel_data *p = picture->data;
    for(pixel_coord z = 0; z < picture->height * picture->width; ++z, ++p)
        *p = (pixel_data) rand();
}

void fill_color(image_p picture, pixel_data color)
{
    assert(("Invalid color", color >= 0 && color <= 255));

    pixel_data *p = picture->data;
    for(pixel_coord z = 0; z < picture->height * picture->width; ++z, ++p)
        *p = color;
}

void free_image(image_p picture)
{
    free(picture->data);
    free(picture);
}

void scale_image(image_p picture, pixel_coord newWidth, pixel_coord newHeight)
{
    assert(("Invalid dimensions", newWidth > 0 && newHeight > 0));

    if (picture->width == newWidth && picture->height==newHeight) return;

    image_p newPicture = create_image(newWidth, newHeight);
    for (pixel_coord y = 0; y < newHeight; ++y)
        for (pixel_coord x = 0; x < newWidth; ++x)
            set_pixel(newPicture, x, y,*get_pixel(
                    picture,
                    x * picture->width / newWidth,
                    y * picture->height / newHeight));
    reassign_image(picture, newPicture, true);
}

void scale_image_blin(image_p picture, pixel_coord newWidth, pixel_coord newHeight)
{
    assert(("Invalid dimensions", newWidth > 0 && newHeight > 0));

    if (picture->width == newWidth && picture->height==newHeight) return;

    image_p newPicture = create_image(newWidth, newHeight);

    double x_ratio, y_ratio;
    x_ratio = (picture->width - 1.0) / (newWidth - 1.0);
    y_ratio = (picture->height - 1.0) / (newHeight - 1.0);

    for (int i = 0; i < newHeight; i++) {
        for (int j = 0; j < newWidth; j++) {
            double x_l = floor(x_ratio * (double)j);
            double y_l = floor(y_ratio * (double)i);
            double x_h = ceil(x_ratio * (double)j);
            double y_h = ceil(y_ratio * (double)i);

            double x_weight = (x_ratio * (double)j) - x_l;
            double y_weight = (y_ratio * (double)i) - y_l;

            double a = picture->data[(int)y_l * picture->width + (int)x_l];
            double b = picture->data[(int)y_l * picture->width + (int)x_h];
            double c = picture->data[(int)y_h * picture->width + (int)x_l];
            double d = picture->data[(int)y_h * picture->width + (int)x_h];

            double pixel = a * (1.0 - x_weight) * (1.0 - y_weight) +
                           b * x_weight * (1.0 - y_weight) +
                           c * y_weight * (1.0 - x_weight) +
                           d * x_weight * y_weight;

            newPicture->data[i * newWidth + j] = (pixel_data)pixel;
        }
    }

    reassign_image(picture, newPicture, true);
}

void reassign_image(image_p thisPicture, image_p otherPicture, bool freeData)
{
    thisPicture->width = otherPicture->width;
    thisPicture->height = otherPicture->height;
    pixel_data *tmp = thisPicture->data;
    thisPicture->data = otherPicture->data;
    if (freeData) free(tmp);
}

int save_pgm(image_p picture, const char *filename)
{
    FILE *to = fopen(filename, "w");
    fprintf(to, "P2\n%u %u\n255\n", picture->width, picture->height);

    pixel_data *p = picture->data;
    for(pixel_coord y = 0; y < picture->height; ++y)
        for(pixel_coord x = 0; x < picture->width; ++x)
            fprintf(to, "%u%c", *(p++), x == picture->width - 1 ? '\n' : ' ');

    fclose(to);
    return 0;
}

pixel_data* get_pixel(image_p picture, pixel_coord x, pixel_coord y)
{
    assert(("Out of dimension", x >= 0 && y >= 0 && x < picture->width && y < picture->height));

    return &picture->data[picture->width * y + x];
}

void set_pixel(image_p picture, pixel_coord x, pixel_coord y, pixel_data color)
{
    assert(("Out of dimension", x >= 0 && y >= 0 && x < picture->width && y < picture->height));
    assert(("Invalid color", color >= 0 && color <= 255));

    picture->data[picture->width * y + x] = color;
}

void draw_line(image_p picture, pixel_point_t p1, pixel_point_t p2, pixel_data color)
{
    assert(("Out of dimension", p1.x >= 0 && p1.y >= 0 && p1.x < picture->width && p1.y < picture->height &&
                                p2.x >= 0 && p2.y >= 0 && p2.x < picture->width && p2.y < picture->height));
    assert(("Invalid color", color >= 0 && color <= 255));

    int dx = (int)p2.x - (int)p1.x;
    int dy = (int)p2.y - (int)p1.y;

    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float x_inc = (float)dx / (float)steps;
    float y_inc = (float)dy / (float)steps;

    float x = (float)p1.x;
    float y = (float)p1.y;
    for (int i = 0; i <= steps; i++) {
        set_pixel(picture, round(x), round(y), color);
        x += x_inc;
        y += y_inc;
    }
}

