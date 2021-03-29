#pragma pack(2)
#include "Processor.h"
using namespace std;

int main() {
    char* path = "C:\\Users\\luckysmg\\Desktop\\ImageProcessor\\noise2.bmp";


    //Processor::divide24ImageToRGBAndGenImages(path);
    //Processor::covert24BitImageToGrey(path);
    //Processor::convertColor(path);

    //Processor::genHistogram(path);
    //Processor::histogramEqualization(path);



    Processor::averageImage(path);

    Processor::medianFiltering(path);

//










    return 0;
}
