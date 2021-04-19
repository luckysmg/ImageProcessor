#pragma pack(2)
#pragma comment(linker, "/STACK:1024000000,1024000000")
#include "Processor.h"
using namespace std;

std::string readPath = "C:\\Users\\luckysmg\\Desktop\\ImageProcessor\\";


const char* getPath(std::string path);

int main() {

//    Processor::divide24ImageToRGBAndGenImages(getPath("rgb.bmp"));
//    Processor::covert24BitImageToGrey(getPath("rgb.bmp"));
//    Processor::convertColor(getPath("rgb.bmp"));

//    Processor::genHistogram(getPath("test.bmp"));
//    Processor::histogramEqualization(getPath("test.bmp"));

//    Processor::averageImage(getPath("noise2.bmp"));
//    Processor::medianFiltering(getPath("noise2.bmp"));

//    Processor::translateImage(getPath("lena.bmp"));
//    Processor::mirrorImage(getPath("lena.bmp"));
//    Processor::scaleImage(getPath("lena.bmp"));
//    Processor::rotateImage(getPath("lena.bmp"));



//    Processor::segmentationOnGivenThresholdFor8(getPath("testhuidu.bmp"));
//    Processor::segmentationByIterationFor8(getPath("testhuidu.bmp"));
//    Processor::segmentationByOTSU(getPath("testhuidu.bmp"));

//    Processor::segmentImageWithGrow(getPath("divide.bmp"));

    return 0;
}

const char* getPath(std::string path){
    return readPath.append(path).data();
}
