
#include <stdint.h>
#ifndef IMAGE_H
#define IMAGE_H
struct image {
    uint64_t width, height;
    struct pixel* data;
};
struct __attribute__((packed)) pixel{
        uint8_t b, g, r;
    };
struct image rotate( struct image const source );

//Utils
int get_rotations(int angle);

struct image set_image(uint32_t width, uint32_t height);

struct image set_image_like_rotated(int rotations, struct image source_img_struct);

#endif
