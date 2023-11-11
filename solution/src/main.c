#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include "validation.h"
#include <unistd.h>

void print_error(const char* s){
    fprintf(stderr, "%s\n", s);
    exit(1);
}

void print_success(const char* s){
    fprintf(stdout, "%s\n", s);
    exit(0);
}

int main( int argc, char** argv ) {

    if(validate_count_data_input(argc) == VALIDATION_ERROR){
        print_error("Incorrect data entry, example: <source-image> <transformed-image> <angle>");
    }
    const char* source_image = argv[1];
    const char* transformed_image = argv[2];
    int angle = atoi(argv[3]); //to int

    if(validate_angle(angle)!=VALIDATION_OK){
        print_error("Angle should be 0 or -90 or 90 or -180 or 180 or -270 or 270");
    }
    struct image source_img_struct = {0};
    FILE* in = fopen(source_image, "rb");

    if(access(source_image, R_OK) == -1){
        print_error("No read access to the source image file");
    }
    if(in == NULL){
        print_error("Not find input file");
        free(source_img_struct.data);
    }
    if(from_bmp(in, &source_img_struct)!=READ_OK){
        print_error("Problem with reading input file");
        free(source_img_struct.data);
        fclose(in);
    }
    fclose(in);

    FILE* out = fopen(transformed_image, "wb");

    if(access(transformed_image, W_OK) == -1){
        print_error("No write access to the transformed image file");
    }

    int rotations = get_rotations(angle);
    source_img_struct = set_image_like_rotated(rotations, source_img_struct);

    if(to_bmp(out, &source_img_struct)!=WRITE_OK){
        print_error("Problem with writing output file");
        free(source_img_struct.data);
        fclose(out);
    }

    fclose(out);
    print_success("The Image rotated successfully!");
}
