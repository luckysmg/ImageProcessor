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

public:


    ///*****第一次*******
    ///将图片RGB分离，并且生成三张新的图片
    static void divide24ImageToRGBAndGenImages(char* path);

    ///24位彩色图像灰度化
    static void covert24BitImageToGrey(char* path);

    ///反色
    static void convertColor(char* path);


    ///*****第二次*******
    ///生成直方图
    static void genHistogram(char* path);

    ///直方图均衡化
    static void histogramEqualization(char* path);


    ///*****第三次*******

    ///平均处理（基于模板卷积运算）
    static void averageImage(char* path);

    ///中值滤波
    static void medianFiltering(char* path);

    ///图像缩放
    static void scaleImage(char* path);


    ///图像平移
    static void translateImage(char* path);

    ///图像镜像
    static void mirrorImage(char* path);

    ///图像旋转
    static void rotateImage(char* path);


    ///根据给定的阈值，生成直方图并且标明阈值
    static void genHistogramWithGivenThreshold(char* path,int value);

    ///给定阈值分割
    static void segmentationOnGivenThresholdFor8(char* path);

    ///迭代法阈值分割
    static void segmentationByIterationFor8(char* path);

    ///OTSU法阈值分割
    static void segmentationByOTSU(char* path);

    ///分割图像（生长）
    static void segmentImageWithGrow(char* path);







};
#endif //IMAGEPROCESSOR_PROCESSOR_H