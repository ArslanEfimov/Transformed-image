//
// Created by Арслан Ефимов on 11.11.2023.
//
#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#ifndef IMAGE_C
#define IMAGE_C

struct image set_image(uint32_t width, uint32_t height){
    struct image img = {0};
    img.width = width;
    img.height = height;
    img.data = malloc(sizeof(struct pixel) * img.width * img.height);
    return img;
}
#endif
