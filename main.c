#include "definitions.h"
#include <magic.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static char *mime_type(const char *filename)
{
    magic_t magic;
    const char *mime;
    char *ret;

    magic = magic_open(MAGIC_MIME_TYPE);
    magic_load(magic, NULL);

    mime = magic_file(magic, filename);
    if (mime) {
        ret = strdup(mime);
    }

    magic_close(magic);
    return ret;
}

static int print_data(intensity_data data)
{
    if (data.error) {
        fprintf(stderr, "Decoder library returned an error\n");
        return 1;
    }

    printf("%f\t%f\t%f\t%f\n", data.nw, data.ne, data.sw, data.se);

    return 0;
}

int main(int argc, char *argv[])
{
    char *file_mime;
    intensity_data data;

    if (argc != 2) {
        fprintf(stderr, "Expected to be called with 2 arguments\n");
        return 1;
    }

    file_mime = mime_type(argv[1]);

    if (file_mime != NULL && strcmp(file_mime, "image/png") == 0) {
        data = png_intensities(argv[1]);
    } else if (file_mime != NULL && strcmp(file_mime, "image/jpeg") == 0) {
        data = jpeg_intensities(argv[1]);
    } else {
        fprintf(stderr, "Unrecognized file type\n");
        return 1;
    }

    free(file_mime);
    return print_data(data);
}
