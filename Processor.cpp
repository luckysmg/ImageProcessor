//
// Created by luckysmg on 2021/3/15.
//
//
#pragma pack(2)

#include "Processor.h"
#include "Util.h"

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
    //进行灰度值映射
    for (int i = 0; i < 256; i++) {
        int newKey = int((double)255 * (double) resPer[i] + 0.5);
        data[newKey] = data[i];
        data[i] = 0;
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

    write(resFileHeader, resInfoHeader, res, (rootPath + "Equalization.bmp").data(), resSize);

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

}



