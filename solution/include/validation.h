//
// Created by Арслан Ефимов on 11.11.2023.
//
#include <stdio.h>
#include <stdint.h>
#ifndef VALIDATION_H
#define VALIDATION_H
enum valid_status{
    VALIDATION_OK = 0,
    VALIDATION_ERROR
};
enum valid_status validate_count_data_input(int argc);
enum valid_status validate_angle(int angle);
#endif
