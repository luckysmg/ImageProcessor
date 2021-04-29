#include <iostream>
#include "Models.h"
#include <vector>
#include <set>




#ifndef IMAGEPROCESSOR_PROCESSOR_H
#define IMAGEPROCESSOR_PROCESSOR_H

using namespace std;
static const string rootPath = "C:/Users/luckysmg/Desktop/imgs/";

///图像处理器
class Processor {

private:
    static int getIInRange(unsigned int height,int i){
        if(i < 0){
            return 0;
        }

        if(i > height - 1){
            return height - 1;
        }
        return i;
    }

    static int getJInRange(unsigned int width,int j) {

        if (j < 0) {
            return 0;
        }
        if (j > width - 1) {
            return width - 1;
        }

        return j;
    }

    static void dfs(const BYTE *img, int x, int y,int dx,int dy, int width, int height, int lastVal,BYTE* res);

    static void dfs(const BYTE *img,BYTE* flags,int x,int y,int width,int last);


public:



    ///*****第一次*******
    ///将图片RGB分离，并且生成三张新的图片
    static void divide24ImageToRGBAndGenImages(const char* path);

    ///24位彩色图像灰度化
    static void covert24BitImageToGrey(const char* path);

    ///反色
    static void convertColor(const char* path);


    ///*****第二次*******
    ///生成直方图
    static void genHistogram(const char* path);

    ///直方图均衡化
    static void histogramEqualization(const char* path);


    ///*****第三次*******

    ///平均处理（基于模板卷积运算）
    static void averageImage(const char* path);

    ///中值滤波
    static void medianFiltering(const char* path);

    ///图像缩放
    static void scaleImage(const char* path);


    ///图像平移
    static void translateImage(const char* path);

    ///图像镜像
    static void mirrorImage(const char* path);

    ///图像旋转
    static void rotateImage(const char* path);


    ///根据给定的阈值，生成直方图并且标明阈值
    static void genHistogramWithGivenThreshold(const char* path,int value);

    ///给定阈值分割
    static void segmentationOnGivenThresholdFor8(const char* path);

    ///迭代法阈值分割
    static void segmentationByIterationFor8(const char* path);

    ///OTSU法阈值分割
    static void segmentationByOTSU(const char* path);

    ///分割图像（生长）
    static void segmentImageWithGrow(const char* path);


    ///基于Prewitt来做边缘检测
    static void edgeDetectByPrewitt(const char* path);

    ///基于Sobel来做边缘检测
    static void edgeDetectBySobel(const char* path);

    ///基于LOG来做边缘检测
    static void edgeDetectByLOG(const char* path);

    ///霍夫变换
    static void Processor:: hough(char *filename, int alpha);


    ///连通域分析
    static void connectedDomainAnalysis(const char* path);


    ///轮廓提取
    static void contourExtraction(const char* path);










};
#endif //IMAGEPROCESSOR_PROCESSOR_H