#include "png.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t size)
{
    png_image image;

    image.version = PNG_IMAGE_VERSION;
    image.opaque = NULL;

    if (png_image_begin_read_from_memory(&image, Data, size)) return 0;

    image.format = PNG_FORMAT_GRAY;
    
    size_t img_size = PNG_IMAGE_SIZE(image);
    void *img_buffer = malloc(img_size);

    png_image_finish_read(&image, NULL, img_buffer, PNG_IMAGE_ROW_STRIDE(image), NULL);

    free(img_buffer);

    return 0;
}
