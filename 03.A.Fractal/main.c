#include "image.h"
#include "fractal.h"

int main()
{
    image_p img1 = create_image(500, 500);
    sierpinski_carpet(img1, 5);
    save_pgm(img1, "sierpinski_500x500_5.pgm");

    image_p img2 = create_image(1200, 1200);
    koch_snowflake(img2, 5);
    save_pgm(img2, "koch_1200x1200_5.pgm");

    return 0;
}