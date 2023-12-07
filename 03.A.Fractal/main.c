#include "image.h"
#include "fractal.h"

int main()
{
    image_p img = create_image(500, 500);
    sierpinski_carpet(img, 5);

    save_pgm(img, "sierpinski_500x500_5.pgm");
    return 0;
}