#ifndef _FRACTAL_H_
#define _FRACTAL_H_

#include "image.h"

/**
 * @brief Draws empty fractal, assuming image is clean
 * @param picture 
 */
void empty_fractal(image_p picture);

/**
 * @brief Draws Sierpinski carpet fractal with specified depth
 * @param picture Image
 * @param steps Number of iterations
 */
void sierpinski_carpet(image_p picture, unsigned int steps);

#endif // _FRACTAL_H_
