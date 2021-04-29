//
// Created by luckysmg on 2021/3/15.
//
//
#pragma pack(2)

#include "Processor.h"
#include "Util.h"
#include <algorithm>
#include <unordered_map>

using namespace std;


void Processor::divide24ImageToRGBAndGenImages(const char *path) {

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


void Processor::covert24BitImageToGrey(const char *path) {

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

    fclose(file);
    fclose(fout);
}

//C:\Users\luckysmg\Desktop\ImageProcessor\dim.bmp
void Processor::convertColor(const char *path) {

    FILE *file = fopen(path, "rb");
    FILE *fout = fopen((rootPath + "convertedImage.bmp").data(), "wb");
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

void Processor::genHistogram(const char *path) {
    int data[256];
    for (int i = 0; i < 256; ++i) {
        data[i] = 0;
    }
    ImageInfo imgInfo = readImage(path);
    int bmpHeight = imgInfo.infoHeader.biHeight;
    int bmpWidth = imgInfo.imgSize / imgInfo.infoHeader.biHeight;

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

void Processor::histogramEqualization(const char *path) {

    //先生成原来的直方图
    Processor::genHistogram(path);

    int data[256] = {0};
    ImageInfo imgInfo = readImage(path);
    int bmpHeight = imgInfo.infoHeader.biHeight;
    int bmpWidth = imgInfo.imgSize / imgInfo.infoHeader.biHeight;

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

    BYTE *resImage = new BYTE[imgInfo.imgSize];
    for (int i = 0; i < bmpHeight; ++i) {
        for (int j = 0; j < bmpWidth; ++j) {
            int key = imgInfo.img[i * bmpWidth + j];
            resImage[i * bmpWidth + j] = map[key];
        }
    }


    if (imgInfo.infoHeader.biBitCount == 8) {
        write(imgInfo.fileHeader, imgInfo.infoHeader, imgInfo.pRGB, resImage,
              (rootPath + "EqualizationImage.bmp").data(),
              imgInfo.imgSize);
    } else {
        write(imgInfo.fileHeader, imgInfo.infoHeader, resImage, (rootPath + "EqualizationImage.bmp").data(),
              imgInfo.imgSize);
    }

}

void Processor::averageImage(const char *path) {
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

void Processor::medianFiltering(const char *path) {

    ImageInfo imgInfo = readImage(path);
    int bmpHeight = imgInfo.infoHeader.biHeight;
    int bmpWidth = imgInfo.imgSize / imgInfo.infoHeader.biHeight;
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
          imgInfo.imgSize);
}


void Processor::scaleImage(const char *path) {

    ImageInfo imgInfo = readImage(path);
    int m_nHeight = imgInfo.infoHeader.biHeight;
    int bmpWidth = imgInfo.imgSize / imgInfo.infoHeader.biHeight;

    int factor = imgInfo.infoHeader.biBitCount / 8;

    int m_nWidth = bmpWidth / factor;
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
    if (desWidth * factor % 4 != 0) {
        num1 = 4 - m_nWidth * factor % 4;
    } else {
        num1 = 0;
    }


    int desBufSize = ((desWidth * imgInfo.infoHeader.biBitCount + 31) / 32) * 4 * desHeight;

    unsigned char *img;
    img = new unsigned char[desBufSize];

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
            img[(i * desWidth + j) * factor + i * num1] = imgInfo.img[(tYN * m_nWidth + tXN) * factor +
                                                                            tYN * num];
            img[(i * desWidth + j) * factor + i * num1 + 1] = imgInfo.img[(tYN * m_nWidth + tXN) * factor +
                                                                                tYN * num + 1];
            img[(i * desWidth + j) * factor + i * num1 + 2] = imgInfo.img[(tYN * m_nWidth + tXN) * factor +
                                                                                tYN * num + 2];
        }
    }
    write(fileHeader, infoHeader, imgInfo.pRGB, img, (rootPath + "scaledImage.bmp").data(), desBufSize);
}

void Processor::translateImage(const char *path) {

    int tx = -100;
    int ty = -100;

    ImageInfo imgInfo = readImage(path);
    int bmpHeight = imgInfo.infoHeader.biHeight;
    int bmpWidth = imgInfo.imgSize / imgInfo.infoHeader.biHeight;


    BYTE *newImage = new BYTE[imgInfo.imgSize];
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
              imgInfo.imgSize);
    } else {
        write(imgInfo.fileHeader, imgInfo.infoHeader, newImage, (rootPath + "translatedImage.bmp").data(),
              imgInfo.imgSize);

    }
}


void Processor::mirrorImage(const char *path) {

    ImageInfo imgInfo = readImage(path);
    int bmpHeight = imgInfo.infoHeader.biHeight;
    int bmpWidth = imgInfo.imgSize / imgInfo.infoHeader.biHeight;

    BYTE *newImageV = new BYTE[imgInfo.imgSize];
    BYTE *newImageH = new BYTE[imgInfo.imgSize];

    for (int i = 0; i < bmpHeight; i++) {
        for (int j = 0; j < bmpWidth; ++j) {
            newImageV[i * bmpWidth + j] = imgInfo.img[(bmpHeight - 1 - i) * bmpWidth + j];
            newImageH[i * bmpWidth + j] = imgInfo.img[i * bmpWidth + (bmpWidth - 1 - j)];
        }
    }
    if (imgInfo.infoHeader.biBitCount == 8) {
        write(imgInfo.fileHeader, imgInfo.infoHeader, imgInfo.pRGB, newImageH, (rootPath + "mirrorImageH.bmp").data(),
              imgInfo.imgSize);
        write(imgInfo.fileHeader, imgInfo.infoHeader, imgInfo.pRGB, newImageV, (rootPath + "mirrorImageV.bmp").data(),
              imgInfo.imgSize);

    } else {
        write(imgInfo.fileHeader, imgInfo.infoHeader, newImageH, (rootPath + "mirrorImageH.bmp").data(),
              imgInfo.imgSize);
        write(imgInfo.fileHeader, imgInfo.infoHeader, newImageV, (rootPath + "mirrorImageV.bmp").data(),
              imgInfo.imgSize);

    }

}


void Processor::rotateImage(const char *path) {

    double PI = acos(-1.0);
    double angle = PI / 4.0;
    ImageInfo imgInfo = readImage(path);
    int bmpHeight = imgInfo.infoHeader.biHeight;
    int bmpWidth = imgInfo.imgSize / imgInfo.infoHeader.biHeight;

    BYTE *newImage = new BYTE[imgInfo.imgSize];

    for (int i = 0; i < bmpHeight; i++) {
        for (int j = 0; j < bmpWidth; ++j) {

            double x = (double) j * cos(angle) + (double) i * sin(angle);
            double y = (double) -j * sin(angle) + (double) i * cos(angle);
            int newX = (int) x;
            int newY = (int) y;

            if (newX < 0 || newX >= bmpWidth || newY < 0 || newY >= bmpHeight) {
                continue;
            }
            newImage[newY * bmpWidth + newX] = imgInfo.img[i * bmpWidth + j];
        }
    }

    if (imgInfo.infoHeader.biBitCount == 8) {
        write(imgInfo.fileHeader, imgInfo.infoHeader, imgInfo.pRGB, newImage, (rootPath + "rotatedImage.bmp").data(),
              imgInfo.imgSize);

    } else {
        write(imgInfo.fileHeader, imgInfo.infoHeader, newImage, (rootPath + "rotatedImage.bmp").data(),
              imgInfo.imgSize);
    }
}


void Processor::genHistogramWithGivenThreshold(const char *path, int value) {

    int data[256];
    for (int i = 0; i < 256; ++i) {
        data[i] = 0;
    }
    ImageInfo imgInfo = readImage(path);
    int bmpHeight = imgInfo.infoHeader.biHeight;
    int bmpWidth = imgInfo.imgSize / imgInfo.infoHeader.biHeight;

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

    int cur = 0;
    while (cur < resHeight) {
        res[value * 3 + cur * resWidth] = 0;
        res[value * 3 + cur * resWidth + 1] = 0;
        res[value * 3 + cur * resWidth + 2] = 255;
        cur++;
    }


    Headers headers = getHeader(resWidth, resHeight, 24);

    write(headers.fileHeader, headers.infoHeader, res, (rootPath + "HistogramWithValue.bmp").data(), resSize);

}


void Processor::segmentationOnGivenThresholdFor8(const char *path) {

    ImageInfo imgInfo = readImage(path);
    int bmpHeight = imgInfo.infoHeader.biHeight;
    int bmpWidth = imgInfo.imgSize / imgInfo.infoHeader.biHeight;
    BYTE *newImage = new BYTE[imgInfo.imgSize];

    int value = 140;
    Processor::genHistogramWithGivenThreshold(path, value);
    for (int i = 0; i < bmpHeight; i++) {
        for (int j = 0; j < bmpWidth; ++j) {
            int origin = imgInfo.img[i * bmpWidth + j];
            if (origin > value) {
                newImage[i * bmpWidth + j] = 255;
            } else {
                newImage[i * bmpWidth + j] = 0;
            }
        }
    }

    if (imgInfo.infoHeader.biBitCount == 8) {
        write(imgInfo.fileHeader, imgInfo.infoHeader, imgInfo.pRGB, newImage,
              (rootPath + "SegmentationImage.bmp").data(), imgInfo.imgSize);
    } else {
        write(imgInfo.fileHeader, imgInfo.infoHeader, newImage, (rootPath + "SegmentationImage.bmp").data(),
              imgInfo.imgSize);
    }
}

void Processor::segmentationByIterationFor8(const char *path) {

    ImageInfo imgInfo = readImage(path);
    int bmpHeight = imgInfo.infoHeader.biHeight;
    int bmpWidth = imgInfo.imgSize / imgInfo.infoHeader.biHeight;
    BYTE *newImage = new BYTE[imgInfo.imgSize];
    int value = 127;
    int curVal = 0;

    vector<int> data1;
    vector<int> data2;

    while (true) {
        for (int i = 0; i < bmpHeight; ++i) {
            for (int j = 0; j < bmpWidth; ++j) {
                int cur = imgInfo.img[i * bmpWidth + j];
                if (cur < value) {
                    data1.push_back(cur);
                } else {
                    data2.push_back(cur);
                }
            }
        }
        int sum1 = 0;
        int sum2 = 0;
        for (auto &item : data1) {
            sum1 += item;
        }
        for (auto &item : data2) {
            sum2 += item;
        }
        int va1 = sum1 / data1.size();
        int va2 = sum2 / data2.size();

        curVal = (va1 + va2) / 2;
        data1.clear();
        data2.clear();
        if (curVal - value < 2) {
            break;
        } else {
            value = curVal;
        }
    }


    value = curVal;

    Processor::genHistogramWithGivenThreshold(path, value);
    for (int i = 0; i < bmpHeight; i++) {
        for (int j = 0; j < bmpWidth; ++j) {
            int origin = imgInfo.img[i * bmpWidth + j];
            if (origin > 140) {
                newImage[i * bmpWidth + j] = 255;
            } else {
                newImage[i * bmpWidth + j] = 0;
            }
        }
    }

    if (imgInfo.infoHeader.biBitCount == 8) {
        write(imgInfo.fileHeader, imgInfo.infoHeader, imgInfo.pRGB, newImage,
              (rootPath + "SegmentationImage.bmp").data(), imgInfo.imgSize);
    } else {
        write(imgInfo.fileHeader, imgInfo.infoHeader, newImage, (rootPath + "SegmentationImage.bmp").data(),
              imgInfo.imgSize);
    }

}

void Processor::segmentationByOTSU(const char *path) {

    ImageInfo imgInfo = readImage(path);
    int bmpHeight = imgInfo.infoHeader.biHeight;
    int bmpWidth = imgInfo.imgSize / imgInfo.infoHeader.biHeight;
    BYTE *newImage = new BYTE[imgInfo.imgSize];

    int value = OtsuThreshold(bmpWidth, bmpHeight, imgInfo.img);

    Processor::genHistogramWithGivenThreshold(path, value);
    for (int i = 0; i < bmpHeight; i++) {
        for (int j = 0; j < bmpWidth; ++j) {
            int origin = imgInfo.img[i * bmpWidth + j];
            if (origin > 140) {
                newImage[i * bmpWidth + j] = 255;
            } else {
                newImage[i * bmpWidth + j] = 0;
            }
        }
    }

    if (imgInfo.infoHeader.biBitCount == 8) {
        write(imgInfo.fileHeader, imgInfo.infoHeader, imgInfo.pRGB, newImage,
              (rootPath + "SegmentationImage.bmp").data(), imgInfo.imgSize);
    } else {
        write(imgInfo.fileHeader, imgInfo.infoHeader, newImage, (rootPath + "SegmentationImage.bmp").data(),
              imgInfo.imgSize);
    }

}

void Processor::segmentImageWithGrow(const char *path) {

    //divide

    ImageInfo imgInfo = readImage(path);
    int bmpHeight = imgInfo.infoHeader.biHeight;
    int bmpWidth = imgInfo.imgSize / imgInfo.infoHeader.biHeight;

    //种子图片
    BYTE *seedsImage = new BYTE[imgInfo.imgSize];

    //生成完成的结果图片
    BYTE *resImage = new BYTE[imgInfo.imgSize]{0};

    //种子点
    vector<Point> seeds;
    for (int i = 0; i < bmpHeight; ++i) {
        for (int j = 0; j < bmpWidth; ++j) {

            int origin = imgInfo.img[i * bmpWidth + j];
            if (origin > 250) {
                Point p;
                p.x = j;
                p.y = i;
                seeds.push_back(p);
                seedsImage[i * bmpWidth + j] = 255;
            } else {
                seedsImage[i * bmpWidth + j] = 0;
            }
        }
    }
    //生成种子图片
    write(imgInfo.fileHeader, imgInfo.infoHeader, imgInfo.pRGB, seedsImage,
          (rootPath + "SegmentationSeedsImage.bmp").data(), imgInfo.imgSize);


    for (auto &item : seeds) {
        int x = item.x;
        int y = item.y;
        resImage[y * bmpWidth + x] = 255;
        dfs(imgInfo.img, x, y, 0, 1, bmpWidth, bmpHeight, imgInfo.img[y * bmpWidth + x], resImage);
        dfs(imgInfo.img, x, y, 0, -1, bmpWidth, bmpHeight, imgInfo.img[y * bmpWidth + x], resImage);
        dfs(imgInfo.img, x, y, 1, 0, bmpWidth, bmpHeight, imgInfo.img[y * bmpWidth + x], resImage);
        dfs(imgInfo.img, x, y, -1, 0, bmpWidth, bmpHeight, imgInfo.img[y * bmpWidth + x], resImage);
    }

    write(imgInfo.fileHeader, imgInfo.infoHeader, imgInfo.pRGB, resImage,
          (rootPath + "SegmentationResultImage.bmp").data(), imgInfo.imgSize);
}

void Processor::dfs(const BYTE *img, int x, int y, int dx, int dy, int width, int height, int lastVal, BYTE *res) {
    if (x <= 0 || x >= width - 1 || y <= 0 || y >= height - 1) {
        return;
    }

    int val = img[y * width + x];

    //生长条件
    if (abs(val - lastVal) < 10) {
        res[y * width + x] = 255;
        //周围进行找路径
        dfs(img, x + dx, y + dy, dx, dy, width, height, val, res);
    }
}

void Processor::edgeDetectByPrewitt(const char *path) {

    ImageInfo imgInfo = readImage(path);
    int bmpHeight = imgInfo.infoHeader.biHeight;
    int bmpWidth = imgInfo.imgSize / imgInfo.infoHeader.biHeight;
    BYTE *resImage = new BYTE[imgInfo.imgSize]{0};


    for (int i = 0; i < bmpHeight; ++i) {
        for (int j = 0; j < bmpWidth; ++j) {
            if (i == 0 || i == bmpHeight - 1 || j == 0 || j == bmpWidth - 1) {
                continue;
            }

            int dx = imgInfo.img[(i - 1) * bmpWidth + j - 1] + imgInfo.img[(i - 1) * bmpWidth + j] +
                     imgInfo.img[(i - 1) * bmpWidth + j + 1] - imgInfo.img[(i + 1) * bmpWidth + j - 1]
                     - imgInfo.img[(i + 1) * bmpWidth + j] - imgInfo.img[(i + 1) * bmpWidth + j + 1];

            int dy = imgInfo.img[(i + 1) * bmpWidth + j + 1] + imgInfo.img[i * bmpWidth + j + 1] +
                     imgInfo.img[(i - 1) * bmpWidth + j + 1] - imgInfo.img[(i + 1) * bmpWidth + j - 1] -
                     imgInfo.img[i * bmpWidth + j - 1] - imgInfo.img[(i - 1) * bmpWidth + j - 1];

            int val = (int) sqrt(dx * dx + dy * dy);
            resImage[i * bmpWidth + j] = val;

        }
    }
    write(imgInfo.fileHeader, imgInfo.infoHeader, imgInfo.pRGB, resImage,
          (rootPath + "edgeDetectImagePrewitt.bmp").data(), imgInfo.imgSize);
}

void Processor::edgeDetectBySobel(const char *path) {

    ImageInfo imgInfo = readImage(path);
    int bmpHeight = imgInfo.infoHeader.biHeight;
    int bmpWidth = imgInfo.imgSize / imgInfo.infoHeader.biHeight;
    BYTE *resImage = new BYTE[imgInfo.imgSize]{0};


    for (int i = 0; i < bmpHeight; ++i) {
        for (int j = 0; j < bmpWidth; ++j) {
            if (i == 0 || i == bmpHeight - 1 || j == 0 || j == bmpWidth - 1) {
                continue;
            }

            int dx = imgInfo.img[(i - 1) * bmpWidth + j - 1] + 2 * imgInfo.img[(i - 1) * bmpWidth + j] +
                     imgInfo.img[(i - 1) * bmpWidth + j + 1] - imgInfo.img[(i + 1) * bmpWidth + j - 1]
                     - 2 * imgInfo.img[(i + 1) * bmpWidth + j] - imgInfo.img[(i + 1) * bmpWidth + j + 1];

            int dy = imgInfo.img[(i + 1) * bmpWidth + j + 1] + 2 * imgInfo.img[i * bmpWidth + j + 1] +
                     imgInfo.img[(i - 1) * bmpWidth + j + 1] - imgInfo.img[(i + 1) * bmpWidth + j - 1] -
                     2 * imgInfo.img[i * bmpWidth + j - 1] - imgInfo.img[(i - 1) * bmpWidth + j - 1];

            int val = (int) sqrt(dx * dx + dy * dy);
            resImage[i * bmpWidth + j] = val;

        }
    }

    write(imgInfo.fileHeader, imgInfo.infoHeader, imgInfo.pRGB, resImage,
          (rootPath + "edgeDetectImageSobel.bmp").data(), imgInfo.imgSize);

}

void Processor::edgeDetectByLOG(const char *path) {

    ImageInfo imgInfo = readImage(path);
    int bmpHeight = imgInfo.infoHeader.biHeight;
    int bmpWidth = imgInfo.imgSize / imgInfo.infoHeader.biHeight;
    BYTE *resImage = new BYTE[imgInfo.imgSize];


    for (int i = 0; i < bmpHeight; ++i) {
        for (int j = 0; j < bmpWidth; ++j) {
            if (i == 0 || i == bmpHeight - 1 || j == 0 || j == bmpWidth - 1) {
                continue;
            }

            int val = 4 * imgInfo.img[i * bmpWidth + j] - imgInfo.img[(i - 1) * bmpWidth + j] -
                      imgInfo.img[(i + 1) * bmpWidth + j] - imgInfo.img[i * bmpWidth + j + 1] -
                      imgInfo.img[i * bmpWidth + j - 1];
            if (val < 0)val = 0;
            if (val > 255)val = 255;
            resImage[i * bmpWidth + j] = val;
        }
    }
    write(imgInfo.fileHeader, imgInfo.infoHeader, imgInfo.pRGB, resImage, (rootPath + "edgeDetectLogImage.bmp").data(),
          imgInfo.imgSize);

}

void Processor:: hough(char *filename, int alpha) {
    ImageInfo imgInfo = readImage(filename);
    int bmpHeight = imgInfo.infoHeader.biHeight;
    int bmpWidth = imgInfo.imgSize / imgInfo.infoHeader.biHeight;
    int luo = (int) (sqrt(pow(imgInfo.infoHeader.biWidth, 2) +
                          pow(imgInfo.infoHeader.biHeight, 2)) + 1);
    //直线数组
    int **count = (int **) malloc(sizeof(int *) * luo);
    for (int i = 0; i < luo; i++) {
        count[i] = (int *) malloc(sizeof(int) * 180);
    }
    for (int i = 0; i < luo; i++) {
        for (int j = 0; j < 180; j++) {
            count[i][j] = 0;
        }
    }

    int **startX = (int **) malloc(sizeof(int *) * luo);
    for (int i = 0; i < luo; i++) {
        startX[i] = (int *) malloc(sizeof(int) * 180);
    }
    for (int i = 0; i < luo; i++) {
        for (int j = 0; j < 180; j++) {
            startX[i][j] = 0;
        }
    }
    int start_flag = 0;

    int **endX = (int **) malloc(sizeof(int *) * luo);
    for (int i = 0; i < luo; i++) {
        endX[i] = (int *) malloc(sizeof(int) * 180);
    }
    for (int i = 0; i < luo; i++) {
        for (int j = 0; j < 180; j++) {
            endX[i][j] = 0;
        }
    }

    int **startY = (int **) malloc(sizeof(int *) * luo);
    for (int i = 0; i < luo; i++) {
        startY[i] = (int *) malloc(sizeof(int) * 180);
    }
    for (int i = 0; i < luo; i++) {
        for (int j = 0; j < 180; j++) {
            startY[i][j] = 0;
        }
    }

    int **endY = (int **) malloc(sizeof(int *) * luo);
    for (int i = 0; i < luo; i++) {
        endY[i] = (int *) malloc(sizeof(int) * 180);
    }
    for (int i = 0; i < luo; i++) {
        for (int j = 0; j < 180; j++) {
            endY[i][j] = 0;
        }
    }

    //直线上的点计数
    for (int i = 0; i < luo; i++) {
        for (int j = 0; j < 180; j++) {
            start_flag = 0;
            double angle = j * 3.1415926 / 180;
            for (int x = 0; x < imgInfo.infoHeader.biWidth; x++) {
                for (int y = 0; y < imgInfo.infoHeader.biHeight; y++) {
                    if (i == (int) (x * cos(angle) + y * sin(angle)) &&
                        imgInfo.img[y * bmpWidth + x] == 0) {
                        if (start_flag == 0) {
                            startX[i][j] = x;
                            startY[i][j] = y;
                            start_flag = 1;
                        }
                        endX[i][j] = x;
                        endY[i][j] = y;
                        count[i][j]++;
                    }
                }
            }
        }
    }
    //确定端点
    for (int i = 0; i < luo; i++) {
        for (int j = 0; j < 180; j++) {
            if (startX[i][j] > endX[i][j]) {
                int tempX = startX[i][j];
                startX[i][j] = endX[i][j];
                endX[i][j] = tempX;
            }
            if (startY[i][j] > endY[i][j]) {
                int tempY = startY[i][j];
                startY[i][j] = endY[i][j];
                endY[i][j] = tempY;
            }
        }
    }
//清空
    for (int x = 0; x < bmpWidth; x++) {
        for (int y = 0; y < imgInfo.infoHeader.biHeight; y++) {
            imgInfo.img[y * bmpWidth + x] = 255;
        }
    }

    for (int i = 0; i < luo; i++) {
        for (int j = 0; j < 180; j += 5) {
            if (count[i][j] > alpha) {
                for (int x = 0; x < imgInfo.infoHeader.biWidth; x++) {
                    if (endX[i][j] >= x && startX[i][j] <= x) {
                        double angle = j * 3.14159 / 180;
                        if (angle != 0) {
                            double rect_y = (i - x * cos(angle)) / sin(angle);

                            imgInfo.img[(int) rect_y * bmpWidth + x] = 0;
                        }
                        if (j == 0) {
                            for (int climb = startY[i][j]; climb < endY[i][j]; climb++) {
                                imgInfo.img[climb * bmpWidth + i] = 0;
                            }
                        }
                    }
                }
            }
        }
    }

    write(imgInfo.fileHeader, imgInfo.infoHeader, imgInfo.pRGB, imgInfo.img,
          (rootPath + "lineDetectImage.bmp").data(),
          imgInfo.infoHeader.biSizeImage);
}

void Processor::connectedDomainAnalysis(const char *path) {


    ImageInfo imgInfo = readImage(path);

    int bmpHeight = imgInfo.infoHeader.biHeight;
    int bmpWidth = imgInfo.imgSize / imgInfo.infoHeader.biHeight;

    //二值化
    for (int i = 0; i < bmpHeight; ++i) {
        for (int j = 0; j < bmpWidth; ++j) {
            int origin = imgInfo.img[i * bmpWidth + j];
            if (origin > 240) {
                imgInfo.img[i * bmpWidth + j] = 255;
            } else {
                imgInfo.img[i * bmpWidth + j] = 0;
            }
        }
    }

    //标记数组
    BYTE *flags = new BYTE[imgInfo.imgSize]{0};

    //递归标记
    for (int i = 0; i < bmpHeight; ++i) {
        for (int j = 0; j < bmpWidth; ++j) {
            dfs(imgInfo.img, flags, j, i, bmpWidth, imgInfo.img[i * bmpWidth + j]);
        }
    }

    for (int i = 0; i < bmpHeight; ++i) {
        for (int j = 0; j < bmpWidth; ++j) {
            if (flags[i * bmpWidth + j] == 1) {
                imgInfo.img[i * bmpWidth + j] = 140;
            }
        }
    }

    write(imgInfo.fileHeader, imgInfo.infoHeader, imgInfo.pRGB, imgInfo.img,
          (rootPath + "connectedDomainAnalysisImage.bmp").data(), imgInfo.imgSize);
}

void Processor::dfs(const BYTE *img, BYTE *flags, int x, int y, int width, int last) {
    //如果已经标记了，或者是白色的无效区域，返回
    if (flags[y * width + x] != 0 || img[y * width + x] == 255) {
        return;
    }
    int cur = img[y * width + x];
    //如果灰度相同,进行标记,并且在周围进行寻找标记
    if (cur == last) {
        flags[y * width + x] = 1;
        dfs(img, flags, x + 1, y, width, cur);
        dfs(img, flags, x - 1, y, width, cur);
        dfs(img, flags, x, y + 1, width, cur);
        dfs(img, flags, x, y - 1, width, cur);
    }
}

void Processor::contourExtraction(const char *path) {

    ///轮廓提取

    ImageInfo imgInfo = readImage(path);
    int bmpHeight = imgInfo.infoHeader.biHeight;
    int bmpWidth = imgInfo.imgSize / imgInfo.infoHeader.biHeight;


    //二值化
    for (int i = 0; i < bmpHeight; ++i) {
        for (int j = 0; j < bmpWidth; ++j) {
            int origin = imgInfo.img[i * bmpWidth + j];
            if (origin > 240) {
                imgInfo.img[i * bmpWidth + j] = 255;
            } else {
                imgInfo.img[i * bmpWidth + j] = 0;
            }
        }
    }


    ///0代表不是边界，1代表是边界
    BYTE *isBounds = new BYTE[imgInfo.imgSize]{0};

    for (int i = 0; i < bmpHeight; ++i) {
        for (int j = 0; j < bmpWidth; ++j) {
            //如果是白色区域，不操作
            if (imgInfo.img[i * bmpWidth + j] == 255)continue;
            if (i == 0 || i == bmpHeight - 1 || j == 0 || j == bmpWidth - 1) {
                continue;
            }

            int curX = j;
            int curY = i;

            bool isBound = false;
            for (int x = curX - 1; x <= curX + 1; ++x) {
                for (int y = curY - 1; y <= curY + 1; ++y) {
                    if (imgInfo.img[y * bmpWidth + x] != 0) {
                        isBound = true;
                        break;
                    }
                }
            }
            if(isBound){
                isBounds[i * bmpWidth + j] = 1;
            }
        }
    }

    for (int i = 0; i < bmpHeight; ++i) {
        for (int j = 0; j < bmpWidth; ++j) {

            if(isBounds[i * bmpWidth + j] == 1){
                imgInfo.img[i * bmpWidth + j] = 0;
            }else {
                imgInfo.img[i * bmpWidth + j] = 255;

            }
        }
    }


    write(imgInfo.fileHeader, imgInfo.infoHeader, imgInfo.pRGB, imgInfo.img,
          (rootPath + "contourExtractionImage.bmp").data(), imgInfo.imgSize);

}





