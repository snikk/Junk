#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <png.h>

#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#endif
#include <GLFW/glfw3.h>
#include "../util/Util.h"
#include "ImageLoader.h"
#include "IOManager.h"

Texture ImageLoader::loadPNG(const char* name) {
    struct Texture tex;

    png_image image;
    memset(&image, 0, sizeof(image));
    image.version = PNG_IMAGE_VERSION;

    long imageFileSize;
    char* imageFileContents = IOManager::readFile(name, &imageFileSize);

    if (png_image_begin_read_from_memory(&image, imageFileContents, imageFileSize)) {
        printf("Started reading from file!\n");
        png_bytep buffer;
        image.format = PNG_FORMAT_RGBA;

        long size = PNG_IMAGE_SIZE(image);
        buffer = (png_bytep) malloc(size);

        if (buffer != NULL) {
            if (png_image_finish_read(&image, NULL, buffer, 0, NULL)) {
                printf("width = %d | height = %d\n", image.width, image.height);

                tex.width = image.width;
                tex.height = image.height;

                glGenTextures(1, &tex.id);
                checkError("Gen Texture!");
                glActiveTexture(GL_TEXTURE0);
                checkError("Active Texture!");
                glBindTexture(GL_TEXTURE_2D, tex.id);
                checkError("Bind Texture!");
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image.width, image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
                checkError("Tex Image 2D!");

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                checkError("Param Wrap S!");
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                checkError("Param Wrap T!");
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                checkError("Parma Mag!");
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                checkError("Param Min!");

                glGenerateMipmap(GL_TEXTURE_2D);
                checkError("Generate Mipmap!");

                free(buffer);
            } else {
                printf("ERRRRRRRROR!\n");
                png_image_free(&image);
            }
            
        } else {
            printf("Couldn't allocate enought memory!\n");
        }
    } else {
        printf("Error reading image file\n");
    }

    return tex;
}
