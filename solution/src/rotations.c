//
// Created by Арслан Ефимов on 09.11.2023.
//

#include <stdlib.h>
#include <stdint.h>
#include "image.h"

//Counts the number of turns by 90 degrees, taking into account negative hums
int get_rotations(int angle){
    int rotations = ((angle + 360) % 360) / 90;
    rotations = (4- rotations) % 4;
    return rotations;
}


struct image rotate( struct image const source) {
    struct image rotated;
    rotated = set_image(source.height, source.width); //Reverse the order of height and width for rotation
        for (uint32_t i = 0; i < source.height; i++) {
            for (uint32_t j = 0; j < source.width; j++) {
                rotated.data[j * rotated.width + (rotated.width - 1 - i)] = source.data[i * source.width + j];

            }
        }
    return rotated;
}

struct image set_image_like_rotated(int rotations, struct image source_img_struct){
    for(int r = 0; r < rotations; r++){
        struct image rotated = rotate(source_img_struct);
        free(source_img_struct.data);
        source_img_struct = rotated;
    }
    return source_img_struct;
}
