#pragma pack(2)
#pragma comment(linker, "/STACK:1024000000,1024000000")
#include "Processor.h"

using namespace std;

int main() {

    Processor::divide24ImageToRGBAndGenImages("C:/Users/luckysmg/Desktop/ImageProcessor/rgb.bmp");
    Processor::covert24BitImageToGrey("C:/Users/luckysmg/Desktop/ImageProcessor/rgb1.bmp");
    Processor::convertColor("C:/Users/luckysmg/Desktop/ImageProcessor/rgb.bmp");

    Processor::genHistogram("C:/Users/luckysmg/Desktop/ImageProcessor/test.bmp");
    Processor::histogramEqualization("C:/Users/luckysmg/Desktop/ImageProcessor/test.bmp");

    Processor::averageImage("C:/Users/luckysmg/Desktop/ImageProcessor/noise2.bmp");
    Processor::medianFiltering("C:/Users/luckysmg/Desktop/ImageProcessor/noise2.bmp");

    Processor::translateImage("C:/Users/luckysmg/Desktop/ImageProcessor/lena.bmp");
    Processor::mirrorImage("C:/Users/luckysmg/Desktop/ImageProcessor/lena.bmp");
    Processor::scaleImage("C:/Users/luckysmg/Desktop/ImageProcessor/lena.bmp");
    Processor::rotateImage("C:/Users/luckysmg/Desktop/ImageProcessor/lena.bmp");

    Processor::segmentationOnGivenThresholdFor8("C:/Users/luckysmg/Desktop/ImageProcessor/testhuidu.bmp");
    Processor::segmentationByIterationFor8("C:/Users/luckysmg/Desktop/ImageProcessor/testhuidu.bmp");
    Processor::segmentationByOTSU("C:/Users/luckysmg/Desktop/ImageProcessor/testhuidu.bmp");

    Processor::segmentImageWithGrow("C:/Users/luckysmg/Desktop/ImageProcessor/divide.bmp");
    Processor::edgeDetectByPrewitt("C:/Users/luckysmg/Desktop/ImageProcessor/lena.bmp");
    Processor::edgeDetectBySobel("C:/Users/luckysmg/Desktop/ImageProcessor/lena.bmp");
    Processor::edgeDetectByLOG("C:/Users/luckysmg/Desktop/ImageProcessor/lena.bmp");


    Processor::hough("C:/Users/luckysmg/Desktop/ImageProcessor/testline.bmp",40);

    Processor::connectedDomainAnalysis("C:/Users/luckysmg/Desktop/ImageProcessor/area.bmp");
    Processor::contourExtraction("C:/Users/luckysmg/Desktop/ImageProcessor/area.bmp");

    return 0;
}
