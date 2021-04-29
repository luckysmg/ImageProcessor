#pragma pack(2)
#pragma comment(linker, "/STACK:1024000000,1024000000")
#include "Processor.h"

using namespace std;
//
void menu(){
    std::cout << "数字图像处理" << "\n" << "输入数字选择功能" << "\n" << "1:24位分色" << "\n" << "2:8位灰度化" << "\n" << "3:8位反色"
              << "\n" << "4:绘制直方图" << "\n" << "5:直方图均衡化" << "\n" << "6:平均滤波" << "\n" << "7:中值滤波" << "\n" << "8:缩放"
              << "\n"
              << "9:平移" << "\n" << "10:镜像" << "\n" << "11:旋转" << "\n" << "12:固定阈值分割" << "\n" << "13:迭代阈值分割" << "\n"
              << "14:大津法" << "\n" << "15:区域生长" << "\n" << "16:分裂合并" << "\n" << "17:Prewitt" << "\n" << "18:Sobel"
              << "\n" << "19:LOG" << "\n"
              << "20:直线检测" << "\n" << "21:连通域分析" << "\n" << "22:轮廓提取" << "\n"<<"批处理"<<"\n";

}

int main() {

    //menu();






//
//    Processor::divide24ImageToRGBAndGenImages("C:/Users/luckysmg/Desktop/ImageProcessor/rgb.bmp");
//    Processor::covert24BitImageToGrey("C:/Users/luckysmg/Desktop/ImageProcessor/rgb1.bmp");
//    Processor::convertColor("C:/Users/luckysmg/Desktop/ImageProcessor/rgb.bmp");
//
//    Processor::genHistogram("C:/Users/luckysmg/Desktop/ImageProcessor/test.bmp");
//    Processor::histogramEqualization("C:/Users/luckysmg/Desktop/ImageProcessor/test.bmp");
//
//    Processor::averageImage("C:/Users/luckysmg/Desktop/ImageProcessor/noise2.bmp");
//    Processor::medianFiltering("C:/Users/luckysmg/Desktop/ImageProcessor/noise2.bmp");
//
//    Processor::translateImage("C:/Users/luckysmg/Desktop/ImageProcessor/lena.bmp");
//    Processor::mirrorImage("C:/Users/luckysmg/Desktop/ImageProcessor/lena.bmp");
//    Processor::scaleImage("C:/Users/luckysmg/Desktop/ImageProcessor/lena.bmp");
//    Processor::rotateImage("C:/Users/luckysmg/Desktop/ImageProcessor/lena.bmp");
//
//    Processor::segmentationOnGivenThresholdFor8("C:/Users/luckysmg/Desktop/ImageProcessor/testhuidu.bmp");
//    Processor::segmentationByIterationFor8("C:/Users/luckysmg/Desktop/ImageProcessor/testhuidu.bmp");
//    Processor::segmentationByOTSU("C:/Users/luckysmg/Desktop/ImageProcessor/testhuidu.bmp");
//
//    Processor::segmentImageWithGrow("C:/Users/luckysmg/Desktop/ImageProcessor/divide.bmp");
//    Processor::edgeDetectByPrewitt("C:/Users/luckysmg/Desktop/ImageProcessor/lena.bmp");
//    Processor::edgeDetectBySobel("C:/Users/luckysmg/Desktop/ImageProcessor/lena.bmp");
//    Processor::edgeDetectByLOG("C:/Users/luckysmg/Desktop/ImageProcessor/lena.bmp");


//    Processor::hough("C:/Users/luckysmg/Desktop/ImageProcessor/testline.bmp",20);

//    Processor::connectedDomainAnalysis("C:/Users/luckysmg/Desktop/ImageProcessor/area.bmp");
//    Processor::contourExtraction("C:/Users/luckysmg/Desktop/ImageProcessor/area.bmp");

    return 0;
}
