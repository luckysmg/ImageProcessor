//
// Created by luckysmg on 2021/3/15.
//
//
#pragma pack(2)

#include "Processor.h"
#include "Util.h"
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;


void Processor::divide24ImageToRGBAndGenImages(char *path) {


    FILE *file = fopen(path, "rb");
    FILE *pfoutr = fopen((rootPath + "r.bmp").data(), "wb");
    FILE *pfoutg = fopen((rootPath + "g.bmp").data(), "wb");
    FILE *pfoutb = fopen((rootPath + "b.bmp").data(), "wb");
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    int bmpWidth = 0;//图像的宽
    int bmpHeight = 0;//图像的高
    int bmpOffset = 0;


    fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, file);
    fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, file);

    bmpHeight = infoHeader.biHeight;
    bmpWidth = infoHeader.biWidth * 3;
    bmpOffset = fileHeader.bfOffBits;

    while (bmpWidth % 4 != 0) {
        bmpWidth++;
    }

    if (infoHeader.biBitCount >= 1) {

        int size = bmpHeight * bmpWidth;
        BYTE *img = new BYTE[size];
        BYTE *img1 = new BYTE[size];
        BYTE *img2 = new BYTE[size];
        BYTE *img3 = new BYTE[size];

        fseek(file, bmpOffset, 0);
        fread(img, sizeof(BYTE), size, file);

        for (int i = 0; i < bmpHeight; i++) {
            for (int j = 0; j < bmpWidth; j++) {
                switch (j % 3) {
                    case 0:
                        img1[i * bmpWidth + j] = 0;
                        img2[i * bmpWidth + j] = 0;
                        img3[i * bmpWidth + j] = img[i * bmpWidth + j];
                        break;
                    case 1:
                        img1[i * bmpWidth + j] = 0;
                        img2[i * bmpWidth + j] = img[i * bmpWidth + j];
                        img3[i * bmpWidth + j] = 0;
                        break;
                    case 2:
                        img1[i * bmpWidth + j] = img[i * bmpWidth + j];
                        img2[i * bmpWidth + j] = 0;
                        img3[i * bmpWidth + j] = 0;
                        break;
                }
            }
        }

        fwrite(&fileHeader, sizeof(fileHeader), 1, pfoutr);
        fwrite(&infoHeader, sizeof(infoHeader), 1, pfoutr);
        fwrite(img1, sizeof(BYTE), size, pfoutr);

        fwrite(&fileHeader, sizeof(fileHeader), 1, pfoutg);
        fwrite(&infoHeader, sizeof(infoHeader), 1, pfoutg);
        fwrite(img2, sizeof(BYTE), size, pfoutg);

        fwrite(&fileHeader, sizeof(fileHeader), 1, pfoutb);
        fwrite(&infoHeader, sizeof(infoHeader), 1, pfoutb);
        fwrite(img3, sizeof(BYTE), size, pfoutb);
    }
    fclose(file);
    fclose(pfoutr);
    fclose(pfoutg);
    fclose(pfoutb);

}


void Processor::covert24BitImageToGrey(char *path) {

    FILE *file = fopen(path, "rb");
    FILE *fout = fopen((rootPath + "huidu.bmp").data(), "wb");
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    int bmpWidth = 0;//图像的宽
    int bmpHeight = 0;//图像的高
    int bmpOffset = 0;

    fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, file);
    fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, file);

    bmpHeight = infoHeader.biHeight;
    bmpWidth = infoHeader.biWidth * 3;
    bmpOffset = fileHeader.bfOffBits;

    while (bmpWidth % 4 != 0) {
        bmpWidth++;
    }

    if (infoHeader.biBitCount >= 1) {

        int size = bmpHeight * bmpWidth;
        BYTE *img = new BYTE[size];
        BYTE *img1 = new BYTE[size];

        fseek(file, bmpOffset, 0);
        fread(img, sizeof(BYTE), size, file);

        for (int i = 0; i < bmpHeight; i++) {
            for (int j = 0; j < bmpWidth; j++) {
                if (j % 2 == 0) {
                    BYTE res = (img[i * bmpWidth + j] +
                                img[i * bmpWidth + j - 1] +
                                img[i * bmpWidth + j - 2]) / 3;

                    img1[i * bmpWidth + j] = res;
                    img1[i * bmpWidth + j - 1] = res;
                    img1[i * bmpWidth + j - 2] = res;
                }


            }
        }

        fwrite(&fileHeader, sizeof(fileHeader), 1, fout);
        fwrite(&infoHeader, sizeof(infoHeader), 1, fout);
        fwrite(img1, sizeof(BYTE), size, fout);
    }
    fclose(file);
    fclose(fout);
}

//C:\Users\luckysmg\Desktop\ImageProcessor\dim.bmp
void Processor::convertColor(char *path) {

    FILE *file = fopen(path, "rb");
    FILE *fout = fopen((rootPath + "fanse.bmp").data(), "wb");
    BITMAPFILEHEADER fileHeader;
    BITMAPINFOHEADER infoHeader;
    int bmpWidth = 0;//图像的宽
    int bmpHeight = 0;//图像的高
    int bmpOffset = 0;

    fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, file);
    fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, file);

    bmpHeight = infoHeader.biHeight;
    bmpWidth = infoHeader.biWidth * 3;
    bmpOffset = fileHeader.bfOffBits;

    while (bmpWidth % 4 != 0) {
        bmpWidth++;
    }

    if (infoHeader.biBitCount >= 1) {

        int size = bmpHeight * bmpWidth;
        BYTE *img = new BYTE[size];
        BYTE *img1 = new BYTE[size];

        fseek(file, bmpOffset, 0);
        fread(img, sizeof(BYTE), size, file);

        for (int i = 0; i < bmpHeight; i++) {
            for (int j = 0; j < bmpWidth; j++) {
                int res = 255 - img[i * bmpWidth + j];
                img1[i * bmpWidth + j] = res;
            }
        }

        fwrite(&fileHeader, sizeof(fileHeader), 1, fout);
        fwrite(&infoHeader, sizeof(infoHeader), 1, fout);
        fwrite(img1, sizeof(BYTE), size, fout);
    }
    fclose(file);
    fclose(fout);

}

void Processor::genHistogram(char *path) {
    int data[256];
    for (int i = 0; i < 256; ++i) {
        data[i] = 0;
    }
    ImageInfo imgInfo = readImage(path);
    int bmpHeight = imgInfo.infoHeader.biHeight;
    int bmpWidth = imgInfo.imgsize / imgInfo.infoHeader.biHeight;

    for (int i = 0; i < bmpHeight; i++) {
        for (int j = 0; j < bmpWidth; j++) {
            int key = imgInfo.img[i * bmpWidth + j];
            data[key] = data[key] + 1;
        }
    }

    int maxCount = 0;
    for (int i = 0; i < 256; ++i) {
        maxCount = max(maxCount, data[i]);
    }

    int resWidth = 256 * 3;
    int resHeight = maxCount;
    int resSize = resWidth * resHeight;
    BYTE *res = new BYTE[resSize];
    for (int i = 0; i < resSize; i++) {
        res[i] = 255;
    }

    for (int i = 0; i < 256; i++) {
        int count = data[i];
        int cur = 0;
        while (cur < count) {
            res[i * 3 + cur * resWidth] = 0;
            res[i * 3 + cur * resWidth + 1] = 0;
            res[i * 3 + cur * resWidth + 2] = 0;
            cur++;
        }
    }

    BITMAPFILEHEADER resFileHeader;
    BITMAPINFOHEADER resInfoHeader;

    resFileHeader.bfType = 19778;
    resFileHeader.bfOffBits = 54;
    resFileHeader.bfReserved1 = 0;
    resFileHeader.bfReserved2 = 0;
    resFileHeader.bfSize = resFileHeader.bfOffBits + 256 * resHeight * 3;

    resInfoHeader.biSize = 40;
    resInfoHeader.biWidth = 256;
    resInfoHeader.biHeight = resHeight;
    resInfoHeader.biPlanes = 1;
    resInfoHeader.biBitCount = 24;
    resInfoHeader.biCompression = imgInfo.infoHeader.biCompression;
    resInfoHeader.biSizeImage = resInfoHeader.biWidth * resInfoHeader.biHeight * resInfoHeader.biBitCount;
    resInfoHeader.biYPelsPerMeter = imgInfo.infoHeader.biYPelsPerMeter;
    resInfoHeader.biClrUsed = imgInfo.infoHeader.biClrUsed;
    resInfoHeader.biClrImportant = imgInfo.infoHeader.biClrImportant;

    write(resFileHeader, resInfoHeader, res, (rootPath + "Histogram.bmp").data(), resSize);
}

void Processor::histogramEqualization(char *path) {

    //先生成原来的直方图
    Processor::genHistogram(path);

    int data[256] = {0};
    ImageInfo imgInfo = readImage(path);
    int bmpHeight = imgInfo.infoHeader.biHeight;
    int bmpWidth = imgInfo.imgsize / imgInfo.infoHeader.biHeight;

    for (int i = 0; i < bmpHeight; i++) {
        for (int j = 0; j < bmpWidth; ++j) {
            int key = imgInfo.img[i * bmpWidth + j];
            data[key]++;
        }
    }
    int sum = 0;
    for (int i = 0; i < 256; ++i) {
        sum += data[i];
    }

    //计算每一个灰度级对应的概率
    double percents[256]{0.0};
    double resPer[256]{0.0};
    for (int i = 0; i < 256; i++) {
        percents[i] = (double) data[i] / (double) sum;
    }

    resPer[0] = percents[0];

    for (int i = 1; i < 256; i++) {
        resPer[i] = resPer[i - 1] + percents[i];
    }

    int newData[256];

    unordered_map<int, int> map;

    //进行灰度值映射
    for (int i = 0; i < 256; i++) {
        int newKey = int((double) 255 * (double) resPer[i] + 0.5);
        newData[newKey] = data[i];
        map[i] = newKey;
    }

    //赋值原数组
    for (int i = 0; i < 256; ++i) {
        data[i] = newData[i];
    }

    int maxCount = 0;
    for (int i = 0; i < 256; ++i) {
        maxCount = max(maxCount, data[i]);
    }

    int resWidth = 256 * 3;
    int resHeight = maxCount;
    int resSize = resWidth * resHeight;
    BYTE *res = new BYTE[resSize];
    for (int i = 0; i < resSize; i++) {
        res[i] = 255;
    }

    for (int i = 0; i < 256; i++) {
        int count = data[i];
        int cur = 0;
        while (cur < count) {
            res[i * 3 + cur * resWidth] = 0;
            res[i * 3 + cur * resWidth + 1] = 0;
            res[i * 3 + cur * resWidth + 2] = 0;
            cur++;
        }
    }

    BITMAPFILEHEADER resFileHeader;
    BITMAPINFOHEADER resInfoHeader;

    resFileHeader.bfType = 19778;
    resFileHeader.bfOffBits = 54;
    resFileHeader.bfReserved1 = 0;
    resFileHeader.bfReserved2 = 0;
    resFileHeader.bfSize = resFileHeader.bfOffBits + 256 * resHeight * 3;

    resInfoHeader.biSize = 40;
    resInfoHeader.biWidth = 256;
    resInfoHeader.biHeight = resHeight;
    resInfoHeader.biPlanes = 1;
    resInfoHeader.biBitCount = 24;
    resInfoHeader.biCompression = imgInfo.infoHeader.biCompression;
    resInfoHeader.biSizeImage = resInfoHeader.biWidth * resInfoHeader.biHeight * resInfoHeader.biBitCount;
    resInfoHeader.biYPelsPerMeter = imgInfo.infoHeader.biYPelsPerMeter;
    resInfoHeader.biClrUsed = imgInfo.infoHeader.biClrUsed;
    resInfoHeader.biClrImportant = imgInfo.infoHeader.biClrImportant;
    write(resFileHeader, resInfoHeader, res, (rootPath + "EqualizationHistogram.bmp").data(), resSize);

    BYTE *resImage = new BYTE[imgInfo.imgsize];
    for (int i = 0; i < bmpHeight; ++i) {
        for (int j = 0; j < bmpWidth; ++j) {
            int key = imgInfo.img[i * bmpWidth + j];
            resImage[i * bmpWidth + j] = map[key];
        }
    }
    write(imgInfo.fileHeader, imgInfo.infoHeader, imgInfo.pRGB, resImage, (rootPath + "EqualizationImage.bmp").data(),
          imgInfo.imgsize);
}

void Processor::averageImage(char *path) {
    //定义原始图像的宽和高
    unsigned int height = 0;
    unsigned int width = 0;

    int i = 0;
    int j = 0;
    BITMAPFILEHEADER bmpfileheader; //文件头
    BITMAPINFOHEADER bmpinfoheader; //信息头

    FILE *fpin; //读取操作流
    FILE *fpout; //读出操作流
    fpin = fopen(path, "rb");
    fread(&bmpfileheader, sizeof(BITMAPFILEHEADER), 1, fpin);//读取文件头
    fread(&bmpinfoheader, sizeof(BITMAPINFOHEADER), 1, fpin);//读取信息头
    height = bmpinfoheader.biHeight;
    width = bmpinfoheader.biWidth;

    //输入的数据
    RGB **RGBin;
    RGBin = (RGB **) malloc(sizeof(RGB *) * height);
    for (i = 0; i < height; i++) {
        RGBin[i] = (RGB *) malloc(sizeof(RGB) * width);
    }
    //读入像素信息
    for (i = 0; i < height; i++) {
        fread(RGBin[i], sizeof(tagRGB), width, fpin);
    }

    //输出的数据
    RGB **RGBout;
    RGBout = (RGB **) malloc(sizeof(RGB *) * height);
    for (i = 0; i < height; i++) {
        RGBout[i] = (RGB *) malloc(sizeof(RGB) * width);
    }


    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            //用3 X 3的滤波器
            if (i > 0 && i < height - 1 && j > 0 && j < width - 1) {
                //不位于边界的情况
                RGBout[j][i].blue = (int) ((RGBin[j - 1][i + 1].blue + RGBin[j][i + 1].blue + RGBin[j + 1][i + 1].blue +
                                            RGBin[j - 1][i].blue + RGBin[j][i].blue + RGBin[j + 1][i + 1].blue +
                                            RGBin[j - 1][i - 1].blue + RGBin[j][i - 1].blue +
                                            RGBin[j + 1][i - 1].blue) / 9);
                RGBout[j][i].green = (int) (
                        (RGBin[j - 1][i + 1].green + RGBin[j][i + 1].green + RGBin[j + 1][i + 1].green +
                         RGBin[j - 1][i].green + RGBin[j][i].green + RGBin[j + 1][i + 1].green +
                         RGBin[j - 1][i - 1].green + RGBin[j][i - 1].green + RGBin[j + 1][i - 1].green) / 9);
                RGBout[j][i].red = (int) (
                        (RGBin[j - 1][i + 1].red + RGBin[j][i + 1].red + RGBin[j + 1][i + 1].red + RGBin[j - 1][i].red +
                         RGBin[j][i].red + RGBin[j + 1][i + 1].red + RGBin[j - 1][i - 1].red + RGBin[j][i - 1].red +
                         RGBin[j + 1][i - 1].red) / 9);
            } else {
                //1.边界处理直接等于处理
                //RGBout[j][i] = RGBin[j][i];


                //2.边界处理
                RGBout[j][i].blue = (int) ((RGBin[getJInRange(width, j - 1)][getIInRange(height, i + 1)].blue +
                                            RGBin[getJInRange(width, j)][getIInRange(height, i + 1)].blue +
                                            RGBin[getJInRange(width, j + 1)][getIInRange(height, i + 1)].blue +
                                            RGBin[getJInRange(width, j - 1)][getIInRange(height, i)].blue +
                                            RGBin[getJInRange(width, j)][getIInRange(height, i)].blue +
                                            RGBin[getJInRange(width, j + 1)][getIInRange(height, i + 1)].blue +
                                            RGBin[getJInRange(width, j - 1)][getIInRange(height, i - 1)].blue +
                                            RGBin[getJInRange(width, j)][getIInRange(height, i - 1)].blue +
                                            RGBin[getJInRange(width, j + 1)][getIInRange(height, i - 1)].blue) / 9);

                RGBout[j][i].green = (int) ((RGBin[getJInRange(width, j - 1)][getIInRange(height, i + 1)].green +
                                             RGBin[getJInRange(width, j)][getIInRange(height, i + 1)].green +
                                             RGBin[getJInRange(width, j + 1)][getIInRange(height, i + 1)].green +
                                             RGBin[getJInRange(width, j - 1)][getIInRange(height, i)].green +
                                             RGBin[getJInRange(width, j)][getIInRange(height, i)].green +
                                             RGBin[getJInRange(width, j + 1)][getIInRange(height, i + 1)].green +
                                             RGBin[getJInRange(width, j - 1)][getIInRange(height, i - 1)].green +
                                             RGBin[getJInRange(width, j)][getIInRange(height, i - 1)].green +
                                             RGBin[getJInRange(width, j + 1)][getIInRange(height, i - 1)].green) / 9);

                RGBout[j][i].red = (int) ((RGBin[getJInRange(width, j - 1)][getIInRange(height, i + 1)].red +
                                           RGBin[getJInRange(width, j)][getIInRange(height, i + 1)].red +
                                           RGBin[getJInRange(width, j + 1)][getIInRange(height, i + 1)].red +
                                           RGBin[getJInRange(width, j - 1)][getIInRange(height, i)].red +
                                           RGBin[getJInRange(width, j)][getIInRange(height, i)].red +
                                           RGBin[getJInRange(width, j + 1)][getIInRange(height, i + 1)].red +
                                           RGBin[getJInRange(width, j - 1)][getIInRange(height, i - 1)].red +
                                           RGBin[getJInRange(width, j)][getIInRange(height, i - 1)].red +
                                           RGBin[getJInRange(width, j + 1)][getIInRange(height, i - 1)].red) / 9);

            }
        }
    }

    //将信息写入文件
    fpout = fopen((rootPath + "averageImage.bmp").data(), "wb");
    fwrite(&bmpfileheader, sizeof(BITMAPFILEHEADER), 1, fpout);
    fwrite(&bmpinfoheader, sizeof(BITMAPINFOHEADER), 1, fpout);
    for (i = 0; i < height; i++) {
        fwrite(RGBout[i], sizeof(tagRGB), width, fpout);
    }
    fclose(fpin);
    fclose(fpout);
}

void Processor::medianFiltering(char *path) {

    ImageInfo imgInfo = readImage(path);
    int bmpHeight = imgInfo.infoHeader.biHeight;
    int bmpWidth = imgInfo.imgsize / imgInfo.infoHeader.biHeight;
    for (int i = 0; i < bmpHeight; i++) {
        for (int j = 0; j < bmpWidth; ++j) {
            vector<int> vector;
            if (i > 0 && i < bmpHeight - 1 && j > 0 && j < bmpWidth) {

                vector.push_back(imgInfo.img[(i - 1) * bmpWidth + j - 1]);
                vector.push_back(imgInfo.img[i * bmpWidth + j - 1]);
                vector.push_back(imgInfo.img[(i + 1) * bmpWidth + j - 1]);
                vector.push_back(imgInfo.img[(i - 1) * bmpWidth + j]);
                vector.push_back(imgInfo.img[i * bmpWidth + j]);
                vector.push_back(imgInfo.img[(i + 1) * bmpWidth + j]);
                vector.push_back(imgInfo.img[(i - 1) * bmpWidth + j + 1]);
                vector.push_back(imgInfo.img[i * bmpWidth + j + 1]);
                vector.push_back(imgInfo.img[(i + 1) * bmpWidth + j + 1]);
                std::sort(vector.begin(), vector.end());
                imgInfo.img[i * bmpWidth + j] = vector.at(4);
            } else {
                //1.不处理，什么都不做

                //2.进行像素边界复制
                vector.push_back(imgInfo.img[getIInRange(bmpHeight, i - 1) * bmpWidth + getJInRange(bmpWidth, j - 1)]);
                vector.push_back(imgInfo.img[getIInRange(bmpHeight, i) * bmpWidth + getJInRange(bmpWidth, j - 1)]);
                vector.push_back(
                        imgInfo.img[(getIInRange(bmpHeight, i + 1)) * bmpWidth + getJInRange(bmpWidth, j - 1)]);
                vector.push_back(imgInfo.img[getIInRange(bmpHeight, i - 1) * bmpWidth + getJInRange(bmpWidth, j)]);
                vector.push_back(imgInfo.img[getIInRange(bmpHeight, i) * bmpWidth + getJInRange(bmpWidth, j)]);
                vector.push_back(imgInfo.img[getIInRange(bmpHeight, i + 1) * bmpWidth + getJInRange(bmpWidth, j)]);
                vector.push_back(imgInfo.img[getIInRange(bmpHeight, i - 1) * bmpWidth + getJInRange(bmpWidth, j + 1)]);
                vector.push_back(imgInfo.img[i * bmpWidth + j + 1]);
                vector.push_back(imgInfo.img[getIInRange(bmpHeight, i + 1) * bmpWidth + getJInRange(bmpWidth, j + 1)]);
                std::sort(vector.begin(), vector.end());
                imgInfo.img[i * bmpWidth + j] = vector.at(4);
            }
        }
    }
    write(imgInfo.fileHeader, imgInfo.infoHeader, imgInfo.img, (rootPath + "MedianFiltering.bmp").data(),
          imgInfo.imgsize);
}


void Processor::scaleImage(char *path) {

    ImageInfo imgInfo = readImage(path);
    int m_nHeight = imgInfo.infoHeader.biHeight;
    int bmpWidth = imgInfo.imgsize / imgInfo.infoHeader.biHeight;

    int m_nWidth = bmpWidth / (imgInfo.infoHeader.biBitCount / 8);
    int num;//记录每一行需要填充的字节
    if (m_nWidth * 3 % 4 != 0) {
        num = 4 - m_nWidth * 3 % 4;
    } else {
        num = 0;
    }

    double scale = 2;

    int desWidth = int(m_nWidth * scale);
    int desHeight = int(m_nHeight * scale);

    int num1;
    if (desWidth * 3 % 4 != 0) {
        num1 = 4 - m_nWidth * 3 % 4;
    } else {
        num1 = 0;
    }


    int desBufSize = ((desWidth * imgInfo.infoHeader.biBitCount + 31) / 32) * 4 * desHeight;

    unsigned char *ImageSize;
    ImageSize = new unsigned char[desBufSize];

    BITMAPFILEHEADER fileHeader;
    fileHeader.bfType = 0x4D42;
    fileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) +
                        desWidth * desHeight * imgInfo.infoHeader.biBitCount / 8;
    fileHeader.bfReserved1 = 0;
    fileHeader.bfReserved2 = 0;
    fileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    //Bitmap头信息
    BITMAPINFOHEADER infoHeader;
    infoHeader.biSize = sizeof(BITMAPINFOHEADER);
    infoHeader.biWidth = desWidth;
    infoHeader.biHeight = desHeight;
    infoHeader.biPlanes = 1;
    infoHeader.biBitCount = imgInfo.infoHeader.biBitCount;
    infoHeader.biCompression = imgInfo.infoHeader.biCompression;
    infoHeader.biSizeImage = 0;
    infoHeader.biXPelsPerMeter = 0;
    infoHeader.biYPelsPerMeter = 0;
    infoHeader.biClrUsed = 0;
    infoHeader.biClrImportant = 0;


    for (int i = 0; i < desHeight; i++) {
        for (int j = 0; j < desWidth; j++) {
            int tXN = int(j / scale);
            int tYN = int(i / scale);
            //值拷贝
            ImageSize[(i * desWidth + j) * 3 + i * num1] = imgInfo.img[(tYN * m_nWidth + tXN) * 3 + tYN * num];
            ImageSize[(i * desWidth + j) * 3 + i * num1 + 1] = imgInfo.img[(tYN * m_nWidth + tXN) * 3 + tYN * num + 1];
            ImageSize[(i * desWidth + j) * 3 + i * num1 + 2] = imgInfo.img[(tYN * m_nWidth + tXN) * 3 + tYN * num + 2];
        }
    }
    write(fileHeader, infoHeader, ImageSize, (rootPath + "scaledImage.bmp").data(), desBufSize);
}

void Processor::translateImage(char *path) {

    int tx = -100;
    int ty = -100;

    ImageInfo imgInfo = readImage(path);
    int bmpHeight = imgInfo.infoHeader.biHeight;
    int bmpWidth = imgInfo.imgsize / imgInfo.infoHeader.biHeight;


    BYTE *newImage = new BYTE[imgInfo.imgsize];
    int factor = imgInfo.infoHeader.biBitCount / 8;

    for (int i = 0; i < bmpHeight; i++) {
        for (int j = 0; j < bmpWidth; ++j) {
            int newX = j + tx * factor;
            int newY = i + ty;

            if (newX < 0 || newY < 0 || newX > bmpWidth - 1 || newY > bmpHeight - 1) {
                continue;
            }
            newImage[newY * bmpWidth + newX] = imgInfo.img[i * bmpWidth + j];
        }
    }
    if (imgInfo.infoHeader.biBitCount == 8) {
        write(imgInfo.fileHeader, imgInfo.infoHeader, imgInfo.pRGB, newImage, (rootPath + "translatedImage.bmp").data(),
              imgInfo.imgsize);
    } else {
        write(imgInfo.fileHeader, imgInfo.infoHeader, newImage, (rootPath + "translatedImage.bmp").data(),
              imgInfo.imgsize);

    }
}


void Processor::mirrorImage(char *path) {

    ImageInfo imgInfo = readImage(path);
    int bmpHeight = imgInfo.infoHeader.biHeight;
    int bmpWidth = imgInfo.imgsize / imgInfo.infoHeader.biHeight;

    BYTE *newImageV = new BYTE[imgInfo.imgsize];
    BYTE *newImageH = new BYTE[imgInfo.imgsize];

    for (int i = 0; i < bmpHeight; i++) {
        for (int j = 0; j < bmpWidth; ++j) {
            newImageV[i * bmpWidth + j] = imgInfo.img[(bmpHeight - 1 - i) * bmpWidth + j];
            newImageH[i * bmpWidth + j] = imgInfo.img[i * bmpWidth + (bmpWidth - 1 - j)];
        }
    }
    if (imgInfo.infoHeader.biBitCount == 8) {
        write(imgInfo.fileHeader, imgInfo.infoHeader, imgInfo.pRGB, newImageH, (rootPath + "mirrorImageH.bmp").data(),
              imgInfo.imgsize);
        write(imgInfo.fileHeader, imgInfo.infoHeader, imgInfo.pRGB, newImageV, (rootPath + "mirrorImageV.bmp").data(),
              imgInfo.imgsize);

    } else {
        write(imgInfo.fileHeader, imgInfo.infoHeader, newImageH, (rootPath + "mirrorImageH.bmp").data(),
              imgInfo.imgsize);
        write(imgInfo.fileHeader, imgInfo.infoHeader, newImageV, (rootPath + "mirrorImageV.bmp").data(),
              imgInfo.imgsize);

    }

}


void Processor::rotateImage(char *path) {

    double PI = 3.1415926;
    double angle = PI / 4;
    ImageInfo imgInfo = readImage(path);
    int bmpHeight = imgInfo.infoHeader.biHeight;
    int bmpWidth = imgInfo.imgsize / imgInfo.infoHeader.biHeight;

    int factor = imgInfo.infoHeader.biBitCount / 8;

    double h = bmpHeight * cos(angle) + bmpWidth / factor * sin(angle);
    double w = (bmpHeight * sin(angle) + bmpWidth / factor * cos(angle)) * factor;
    int height = (int) h;
    int width = (int) w;
    int size = height * width;

    cout << height << endl;
    cout << width << endl;
    BYTE *newImage = new BYTE[size];


    int num;//记录每一行需要填充的字节
    if (bmpWidth * 3 % 4 != 0) {
        num = 4 - bmpWidth * 3 % 4;
    } else {
        num = 0;
    }

    int num1;//记录每一行需要填充的字节
    if (width * 3 % 4 != 0) {
        num1 = 4 - width * 3 % 4;
    } else {
        num1 = 0;
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width / factor; ++j) {
            //转换到以图像为中心的坐标系，并进行逆旋

            int tX = (j - width / factor / 2) * cos(2 * PI - angle) + (-i + bmpHeight / 2) * sin(2 * PI - angle);
            int tY = -(j - width / factor / 2) * sin(2 * PI - angle) + (-i + bmpHeight / 2) * cos(2 * PI - angle);
            //如果这个坐标不在原图像内，则不赋值
            if (tX > bmpWidth / factor / 2 || tX < -bmpWidth / factor / 2 || tY > bmpHeight / 2 ||
                tY < -bmpHeight / 2) {
                continue;
            }

            //再转换到原坐标系下
            int tXN = tX + bmpWidth / factor / 2;
            int tYN = abs(tY - bmpHeight / 2);
            //值拷贝
            newImage[(i * width / factor + j) * 3 + i * num1] = imgInfo.img[(tYN * bmpWidth / factor + tXN) * 3 +
                                                                            tYN * num];
            newImage[(i * width / factor + j) * 3 + i * num1 + 1] = imgInfo.img[(tYN * bmpWidth / factor + tXN) * 3 +
                                                                                tYN * num + 1];
            newImage[(i * width / factor + j) * 3 + i * num1 + 2] = imgInfo.img[(tYN * bmpWidth / factor + tXN) * 3 +
                                                                                tYN * num + 2];


        }
    }

    BITMAPFILEHEADER resFileHeader;
    BITMAPINFOHEADER resInfoHeader;

    resFileHeader.bfType = 19778;
    resFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
    resFileHeader.bfReserved1 = 0;
    resFileHeader.bfReserved2 = 0;
    resFileHeader.bfSize = resFileHeader.bfOffBits + width * height;


    resInfoHeader.biSize = 40;
    resInfoHeader.biWidth = width / factor;
    resInfoHeader.biHeight = height;
    resInfoHeader.biPlanes = 1;
    resInfoHeader.biBitCount = imgInfo.infoHeader.biBitCount;
    resInfoHeader.biCompression = imgInfo.infoHeader.biCompression;
    resInfoHeader.biSizeImage = resInfoHeader.biWidth * resInfoHeader.biHeight * resInfoHeader.biBitCount;;
    resInfoHeader.biYPelsPerMeter = imgInfo.infoHeader.biYPelsPerMeter;
    resInfoHeader.biClrUsed = imgInfo.infoHeader.biClrUsed;
    resInfoHeader.biClrImportant = imgInfo.infoHeader.biClrImportant;


    if(imgInfo.infoHeader.biBitCount == 8){
        write(resFileHeader, resInfoHeader, imgInfo.pRGB,newImage, (rootPath + "rotated.bmp").data(), size);

    }else{
        write(resFileHeader, resInfoHeader, newImage, (rootPath + "rotated.bmp").data(), size);

    }


}