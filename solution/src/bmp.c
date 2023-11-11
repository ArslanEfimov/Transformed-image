//
// Created by Арслан Ефимов on 08.11.2023.
//
#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#ifndef BMP_IO_C
#define BMP_IO_C
#define bFTYPE 0x4D42
#define BiSize 40
#define BiPlanes 1
#define BiBitCount 24

enum read_status read_bmp_header(FILE* in, struct bmp_header* header){
    if(fread(&header->bfType, sizeof(uint16_t), 1, in)!=1 || header->bfType!=bFTYPE){
        return READ_INVALID_SIGNATURE;
    }
    size_t header_size = sizeof(struct bmp_header) - sizeof(uint16_t);
    if(fread(((uint8_t*) header) + sizeof(uint16_t), header_size, 1, in)!=1){
        return READ_INVALID_HEADER;
    }
    return READ_OK;
}

uint32_t calculate_padding_row_size(struct image const* img){
    uint32_t row_count_pixels = img->width * sizeof(struct pixel);
    return (4-(row_count_pixels % 4)) %4;
}

struct bmp_header create_header(struct image const* img){
    struct bmp_header header = {0};
    uint32_t row_padding = calculate_padding_row_size(img);
    header.bfType = bFTYPE;
    header.bfileSize = (row_padding + img->width * sizeof(struct pixel)) * img->height + sizeof(struct bmp_header);
    header.bfReserved = 0;
    header.bOffBits = sizeof(struct bmp_header);
    header.biSize = BiSize;
    header.biWidth = img->width;
    header.biHeight = img->height;
    header.biPlanes = BiPlanes;
    header.biBitCount = BiBitCount;
    header.biCompression = 0;
    header.biSizeImage = 0;
    header.biXPelsPerMeter = 0;
    header.biYPelsPerMeter = 0;
    header.biClrUsed = 0;
    header.biClrImportant = 0;
    return header;


}

enum read_status from_bmp(FILE* in, struct image* img){

    struct bmp_header header = {0};
    enum read_status status = read_bmp_header(in, &header);
    if(status!=READ_OK){
        return status;
    }
    *img = (set_image(header.biWidth, header.biHeight));
    if(!img->data){
        free(img->data);
        return READ_INVALID_BITS;
    }
    uint32_t row_padding = calculate_padding_row_size(img);
    for (uint32_t i = 0; i < img->height; i++) {
        if (fread(&img->data[i * img->width], sizeof(struct pixel), img->width, in) != img->width) {
            free(img->data);
            return READ_INVALID_BITS; // Error reading image data
        }
        // Skip padding'а
        if(fseek(in, row_padding, SEEK_CUR)!=0){
            return READ_INVALID_BITS;
        }
    }

    return READ_OK;

}

enum write_status to_bmp(FILE* out, struct image const* img){
    struct bmp_header header = create_header(img);
    uint32_t row_padding = calculate_padding_row_size(img);
    if(fwrite(&header, sizeof(struct bmp_header), 1, out)!=1){
        return WRITE_ERROR;
    }
    for(uint32_t i = 0; i<img->height; i++){
        if(fwrite(img->data + i*img->width, sizeof(struct pixel), img->width, out)!=img->width){
            return WRITE_ERROR;
        }

        uint8_t padding_byte = 0;
        if(fwrite(&padding_byte, sizeof(uint8_t), row_padding, out)!=row_padding){
            return WRITE_ERROR;
        }
    }
    printf("%llu\n", (img->width*img->height)*sizeof(struct pixel));
    printf("all good");
    return WRITE_OK;
}

#endif
