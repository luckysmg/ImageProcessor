#pragma pack(2)
#include "Processor.h"
using namespace std;

int main() {
    char* path = "C:\\Users\\luckysmg\\Desktop\\ImageProcessor\\divide.bmp";


//    Processor::divide24ImageToRGBAndGenImages(path);
//    Processor::covert24BitImageToGrey(path);
//    Processor::convertColor(path);
//    Processor::genHistogram(path);
//    Processor::histogramEqualization(path);

//    Processor::averageImage(path);
//    Processor::medianFiltering(path);
//    Processor::translateImage(path);
//    Processor::mirrorImage(path);
//    Processor::scaleImage(path);
//    Processor::rotateImage(path);
//    Processor::segmentationOnGivenThresholdFor8(path);
//    Processor::segmentationByIterationFor8(path);
//
//    Processor::segmentationByOTSU(path);

    Processor::segmentImageWithGrow(path);


















    return 0;
}
