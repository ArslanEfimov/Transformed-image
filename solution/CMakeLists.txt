file(GLOB_RECURSE sources CONFIGURE_DEPENDS
    src/*.c
    src/*.h
    include/*.h
)

add_executable(image-transformer ${sources}
        include/bmp.h
        src/bmp.c
        src/rotations.c
        src/images_manager.c
        include/validation.h
        src/validation.c)
target_include_directories(image-transformer PRIVATE src include)
