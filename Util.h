//
// Created by luckysmg on 2021/3/28.
//
#pragma once
#pragma pack(2)

#include <iostream>
#include "Models.h"


#ifndef IMAGEPROCESSOR_UTIL_H
#define IMAGEPROCESSOR_UTIL_H


Headers getHeader(int width,int height,int biBitCount){


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
    resInfoHeader.biCompression = 0;
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

ImageInfo readImage(const char *filename) {
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
    imageInfo.imgSize = bmpHeight * bmpWidth;

    int bmpOffset = imageInfo.fileHeader.bfOffBits;

    fseek(bmp, bmpOffset, 0);

    auto *img = new unsigned char[imageInfo.imgSize];
    fread(img, sizeof(unsigned char), imageInfo.imgSize, bmp);
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

int OtsuThreshold(int width,int height,BYTE * data)
{

    const int GrayScale = 256;
    int pixelCount[GrayScale];
    float pixelPro[GrayScale];
    int i;
    for (i = 0; i < GrayScale; i++)//???????????????

    {

        pixelCount[i] = 0;

        pixelPro[i] = 0;

    }



    int j, pixelSum = width * height, threshold = 0;

//    unsigned char* data = (unsigned char*)frame->imageData;  //???????????????????????????



    for (i = 0; i < height; i++)//?????????????????????????????????????????????????????????

    {

        for (j = 0; j < width; j++)

        {

            pixelCount[(int)data[i * width + j]]++;  //???????????????????????????????????????

        }

    }



    //?????????????????????????????????????????????

    float maxPro = 0.0;

    int kk = 0;

    for (i = 0; i < GrayScale; i++)

    {

        pixelPro[i] = (float)pixelCount[i] / pixelSum;

        if (pixelPro[i] > maxPro)

        {

            maxPro = pixelPro[i];//????????????

            kk = i;

        }

    }



    //???????????????[0,255]

    float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;

    for (i = 0; i < GrayScale; i++)     //?????????????????????i?????????

    {

        w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;

        for (j = 0; j < GrayScale; j++)

        {

            if (j <= i)   //????????????

            {

                w0 += pixelPro[j];//???????????????????????????????????????

                u0tmp += j * pixelPro[j];

            }

            else   //????????????

            {

                w1 += pixelPro[j];//???????????????????????????????????????

                u1tmp += j * pixelPro[j];

            }

        }

        u0 = u0tmp / w0;//????????????????????0

        u1 = u1tmp / w1;//????????????????????1

        u = u0tmp + u1tmp;

        deltaTmp = w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);//g =??0(??0-??)^2+??1(??1-??)^2;????????????

        if (deltaTmp > deltaMax)

        {

            deltaMax = deltaTmp;

            threshold = i;

        }

    }

    return threshold;

}


#endif //IMAGEPROCESSOR_UTIL_H
