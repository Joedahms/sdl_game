find_path(SDL2_IMAGE_INCLUDE_DIR
    NAMES SDL2_image.h
    PATHS ${CMAKE_PREFIX_PATH}/include
    PATH_SUFFIXES SDL2)

find_library(SDL2_IMAGE_LIBRARY
    NAMES SDL2_image
    PATHS ${CMAKE_PREFIX_PATH}/lib)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SDL2_image DEFAULT_MSG SDL2_IMAGE_INCLUDE_DIR SDL2_IMAGE_LIBRARY)

mark_as_advanced(SDL2_IMAGE_INCLUDE_DIR SDL2_IMAGE_LIBRARY)

