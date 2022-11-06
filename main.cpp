#include <iostream>
#include "ImageProcessing.h"

int main() {
#include "PPM.h"
#include "ImageProcessing.h"
#include "direct.h"

    using std::cout;
    using std::cin;
    using std::endl;
    using std::string;

    char pathOfProgram[256];
    char locationOfColoredPicture[256];
    char locationOfGrayedOutPicture[256];
    char locationOfEdgeFilteredImage[256];

    void getTheAbsolutePathOfTheImages();

        getTheAbsolutePathOfTheImages();
        string dataOfImage = PPM::readData(locationOfColoredPicture);
        PPM::writeData(dataOfImage, locationOfColoredPicture);

        auto imageProcessing = new ImageProcessing();
        FILE *coloredPpmImage = fopen(locationOfColoredPicture, "r");
        FILE *grayedOutPpmImage = fopen(locationOfGrayedOutPicture, "w");
        imageProcessing->convertToGray(coloredPpmImage, grayedOutPpmImage);

        //reopening the file --> resetting pointer & changing mode
        grayedOutPpmImage = fopen(locationOfGrayedOutPicture, "r");

        FILE *edgeFilteredPpmImage = fopen(locationOfEdgeFilteredImage, "w");
        imageProcessing->edgeDetection(grayedOutPpmImage, edgeFilteredPpmImage);
        return 0;
    }

    void getTheAbsolutePathOfTheImages() {
        getcwd(pathOfProgram, 256); // getting the path to the program
        strcpy(locationOfColoredPicture, pathOfProgram); //copy them
        strcpy(locationOfGrayedOutPicture, pathOfProgram);
        strcpy(locationOfEdgeFilteredImage, pathOfProgram);
        strcat(locationOfColoredPicture, "\\files\\coloredPicture.ppm"); // concatenate the specific filename
        strcat(locationOfGrayedOutPicture, "\\files\\grayedOutPicture.ppm");
        strcat(locationOfEdgeFilteredImage, "\\files\\edgeFilteredPicture.ppm");
    }
}
}

