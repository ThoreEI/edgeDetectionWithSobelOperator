#include "ImageProcessing.h"


int main() {
    const char * filenameColoredAnimal = "images/colored_animal.ppm";
    const char*  filenameGrayedOutAnimal = "images/grayed_out_animal.ppm";
    const char* filenameEdgeFilteredAnimal = "images/edge_filtered_animal.ppm";

    FILE *coloredPpmImage = fopen(filenameColoredAnimal, "r");
    FILE *grayedOutPpmImage = fopen(filenameGrayedOutAnimal, "w");
    ImageProcessing().convertToGray(coloredPpmImage, grayedOutPpmImage);

    grayedOutPpmImage = fopen(filenameColoredAnimal, "r");
    FILE *edgeFilteredPpmImage = fopen(filenameEdgeFilteredAnimal, "w");
    ImageProcessing().edgeDetection(grayedOutPpmImage, edgeFilteredPpmImage);
    return 0;
}


