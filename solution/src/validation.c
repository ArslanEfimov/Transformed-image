//
// Created by Арслан Ефимов on 11.11.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include "validation.h"
#ifndef VALIDATION_C
#define VALIDATION_C


enum valid_status validate_count_data_input(int argc){
    if(argc!=4){
        return VALIDATION_ERROR;
    }
    return VALIDATION_OK;
}


enum valid_status validate_angle(int angle){
    if(angle!=0 && angle!=90 && angle!=-90 && angle!=180 && angle!=-180 && angle!=270 && angle!=-270){
        return VALIDATION_ERROR;
    }
    return VALIDATION_OK;
}


#endif
