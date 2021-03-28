#include <iostream>
#include "Models.h"




#ifndef IMAGEPROCESSOR_PROCESSOR_H
#define IMAGEPROCESSOR_PROCESSOR_H

using namespace std;
static const string rootPath = "C:/Users/luckysmg/Desktop/imgs/";

///图像处理器
class Processor {

private:
    static int getIInRange(int height,int i){
        if(i < 0){
            return 0;
        }

        if(i > height - 1){
            return height - 1;
        }
        return i;
    }

    static int getJInRange(int width,int j) {

        if (j < 0) {
            return 0;
        }
        if (j > width - 1) {
            return width - 1;
        }

        return j;
    }

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






};
#endif //IMAGEPROCESSOR_PROCESSOR_H