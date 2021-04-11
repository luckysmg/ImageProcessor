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
    ImageInfo imginfo;
    FILE *bmp;
    fopen_s(&bmp, filename, "rb");

    fread(&imginfo.fileHeader, sizeof(BITMAPFILEHEADER), 1, bmp);

    fread(&imginfo.infoHeader, sizeof(BITMAPINFOHEADER), 1, bmp);

    if (imginfo.infoHeader.biBitCount == 8) {
        fread(&imginfo.pRGB, sizeof(RGBQUAD), 256, bmp);
    }
    int bmpHeight = imginfo.infoHeader.biHeight;
    int bmpWidth = imginfo.infoHeader.biWidth * imginfo.infoHeader.biBitCount / 8;

    while (bmpWidth % 4 != 0) {
        bmpWidth++;
    }
    imginfo.imgsize = bmpHeight * bmpWidth;

    int bmpOffset = imginfo.fileHeader.bfOffBits;

    fseek(bmp, bmpOffset, 0);

    auto *img = new unsigned char[imginfo.imgsize];
    fread(img, sizeof(unsigned char), imginfo.imgsize, bmp);
    imginfo.img = img;
    fclose(bmp);
    return imginfo;
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
