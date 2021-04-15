//
// Created by luckysmg on 2021/3/28.
//

#ifndef IMAGEPROCESSOR_MODELS_H
#define IMAGEPROCESSOR_MODELS_H


typedef unsigned char  BYTE;
typedef unsigned short WORD;
typedef unsigned long  DWORD;
typedef long    LONG;
typedef struct {
    WORD    bfType;
    DWORD   bfSize;
    WORD    bfReserved1;
    WORD    bfReserved2;
    DWORD   bfOffBits;
} BITMAPFILEHEADER;

typedef struct {
    DWORD      biSize;
    LONG       biWidth;
    LONG       biHeight;
    WORD       biPlanes;
    WORD       biBitCount;
    DWORD      biCompression;
    DWORD      biSizeImage;
    LONG       biXPelsPerMeter;
    LONG       biYPelsPerMeter;
    DWORD      biClrUsed;
    DWORD      biClrImportant;
} BITMAPINFOHEADER;

///RGB结构
typedef struct tagRGB
{
    BYTE blue;
    BYTE green;
    BYTE red;
}RGB;

typedef struct tagRGBQUAD {
    unsigned char  rgbBlue;
    unsigned char  rgbGreen;
    unsigned char  rgbRed;
    unsigned char  rgbReserved;
} RGBQUAD;

typedef struct tagIMGINFO {
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    RGBQUAD pRGB[256];
    BYTE* img;
    int imgSize;
} ImageInfo;


typedef struct tagHeaders {
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
}Headers;

class Point{

public:
    int x;
    int y;

    bool operator== (const Point* other) const{
        if(other->x == this->x && other->y == this->y){
            return true;
        }
        return false;
    }
};


#endif //IMAGEPROCESSOR_MODELS_H
