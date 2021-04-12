//
// Created by luckysmg on 2021/3/28.
//
#pragma once
#pragma pack(2)

#include <iostream>
#include "Models.h"


#ifndef IMAGEPROCESSOR_UTIL_H
#define IMAGEPROCESSOR_UTIL_H


Headers getHeader(int width,int height,int biBitCount,ImageInfo oldInfo){


    BITMAPFILEHEADER resFileHeader;
    BITMAPINFOHEADER resInfoHeader;

    resFileHeader.bfType = 19778;
    resFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    resFileHeader.bfReserved1 = 0;
    resFileHeader.bfReserved2 = 0;
    resFileHeader.bfSize = resFileHeader.bfOffBits + width * height;

    resInfoHeader.biSize = 40;
    resInfoHeader.biWidth = width / (biBitCount / 8);
    resInfoHeader.biHeight = height;
    resInfoHeader.biPlanes = 1;
    resInfoHeader.biBitCount = biBitCount;
    resInfoHeader.biCompression = oldInfo.infoHeader.biCompression;
    resInfoHeader.biSizeImage = 0;
    resInfoHeader.biXPelsPerMeter = 0;
    resInfoHeader.biYPelsPerMeter = 0;
    resInfoHeader.biClrUsed = 0;
    resInfoHeader.biClrImportant = 0;

    Headers headers;
    headers.infoHeader = resInfoHeader;
    headers.fileHeader = resFileHeader;
    return headers;
}

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
