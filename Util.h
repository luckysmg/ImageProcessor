//
// Created by luckysmg on 2021/3/28.
//
#pragma once
#pragma pack(2)

#include <iostream>
#include "Models.h"


#ifndef IMAGEPROCESSOR_UTIL_H
#define IMAGEPROCESSOR_UTIL_H

ImageInfo readImage(char *filename) {
    ImageInfo imageInfo;
    FILE *bmp;
    fopen_s(&bmp, filename, "rb");

    fread(&imageInfo.fileHeader, sizeof(BITMAPFILEHEADER), 1, bmp);

    fread(&imageInfo.infoHeader, sizeof(BITMAPINFOHEADER), 1, bmp);

    if (imageInfo.infoHeader.biBitCount == 8) {
        fread(&imageInfo.pRGB, sizeof(RGBQUAD), 256, bmp);
    }
    int bmpHeight = imageInfo.infoHeader.biHeight;
    int bmpWidth = imageInfo.infoHeader.biWidth * imageInfo.infoHeader.biBitCount / 8;

    while (bmpWidth % 4 != 0) {
        bmpWidth++;
    }
    imageInfo.imgsize = bmpHeight * bmpWidth;

    int bmpOffset = imageInfo.fileHeader.bfOffBits;

    fseek(bmp, bmpOffset, 0);

    auto *img = new unsigned char[imageInfo.imgsize];
    fread(img, sizeof(unsigned char), imageInfo.imgsize, bmp);
    imageInfo.img = img;
    fclose(bmp);
    return imageInfo;
}

void
write(BITMAPFILEHEADER fileHeader, BITMAPINFOHEADER infoHeader, unsigned char *img, const char *filename, int size) {
    FILE *file;
    fopen_s(&file, filename, "wb");
    fwrite(&fileHeader, sizeof(fileHeader), 1, file);
    fwrite(&infoHeader, sizeof(infoHeader), 1, file);
    fwrite(img, sizeof(unsigned char), size, file);
    fclose(file);
}
void write(BITMAPFILEHEADER fileHeader, BITMAPINFOHEADER infoHeader, RGBQUAD* pRGB, unsigned char* img, const char* filename,int size) {
    FILE* file;
    fopen_s(&file, filename, "wb");
    fwrite(&fileHeader, sizeof(fileHeader), 1, file);
    fwrite(&infoHeader, sizeof(infoHeader), 1, file);
    fwrite(pRGB, sizeof(RGBQUAD), 256, file);
    fwrite(img, sizeof(unsigned char), size, file);
    fclose(file);
}

#endif //IMAGEPROCESSOR_UTIL_H
