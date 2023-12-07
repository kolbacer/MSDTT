#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

/**
 * @brief One pixel data in-place 
 */
typedef uint8_t pixel_data;

/**
 * @brief Coordinate of a pixel and dimension of an image
 */
typedef unsigned int pixel_coord;

/**
 * @brief Structure to store image data and metadata
 */
struct image
{
    pixel_coord width, height;
    pixel_data *data;
};

/**
 * @brief Image for application
 */
typedef struct image image_t, *image_p;

/**
 * @brief Create image of given width and height
 * @param width,height Dimensions of an image
 * @returns an image
 */
image_p create_image(pixel_coord width, pixel_coord height);

/**
 * @brief Fill with random pixels
 * @param picture Image
 */
void fill_random(image_p picture);

/**
 * @brief Fill with specified color
 * @param picture Image
 * @param color
 */
void fill_color(image_p picture, pixel_data color);

/**
 * Image destructor
 * @param picture Image
 */
void free_image(image_p picture);

/**
 * @brief Scale image to specified dimensions
 * @param picture Image
 * @param newWidth New width
 * @param newHeight New height
 */
void scale_image(image_p picture, pixel_coord newWidth, pixel_coord newHeight);

/**
 * @brief Scale image to specified dimensions using bilinear interpolation.
 * See https://chao-ji.github.io/jekyll/update/2018/07/19/BilinearResize.html
 * @param picture Image
 * @param newWidth New width
 * @param newHeight New height
 */
void scale_image_blin(image_p picture, pixel_coord newWidth, pixel_coord newHeight);

/**
 * @brief Assign image to other instance
 * @param thisPicture Image to reassign
 * @param otherPicture Image to assign
 * @param freeData If true, frees old thisPicture's data after reassigning
 */
void reassign_image(image_p thisPicture, image_p otherPicture, bool freeData);

/**
 * @brief Save image to file in PGM format
 * @param picture Image
 * @param filename Name of file
 */
int save_pgm(image_p picture, const char *filename);

/**
 * @brief Get pixel's reference by coordinates
 * @param picture Image
 * @param x,y Pixel coordinates
 */
pixel_data* get_pixel(image_p picture, pixel_coord x, pixel_coord y);

/**
 * @brief Set the pixel of an image to given color
 * @param picture Image
 * @param x,y Pixel coordinates
 * @param color Color value
 */
void set_pixel(image_p picture, pixel_coord x, pixel_coord y, pixel_data color);

#endif // _IMAGE_H_
