#ifndef edgeDetectionWithSobelOperator
#define edgeDetectionWithSobelOperator
#include <iostream>
#include "string"
using namespace std;

class ImageProcessing {
public:
    ImageProcessing() = default;
    const int  filter[3][3] = {{-1,-1,-1},
                               {-1,8,-1},
                               {-1,-1,-1}};

    struct Header {
        char type[2]; //type of the given map (P1, P2, P3)
        int width;
        int height;
        int brightness;
    } header{};

    struct RGB {
        int red;
        int green;
        int blue;
    } pixel{};

    void convertToGray(FILE * coloredPpmImage, FILE * grayedOutPpmImage) {
        if (!isFilePresent(coloredPpmImage))
            return;
        readAndPrintHeaderOfPpmImage(coloredPpmImage, grayedOutPpmImage);
        int numberOfPixel = header.width * header.height;
        for (int countOfPixel = 0; countOfPixel < numberOfPixel; countOfPixel++)
        {
            fscanf(coloredPpmImage, "%d %d %d", &pixel.red, &pixel.green, &pixel.blue); //saving the read pixel information
            int grayedOutPixel = (pixel.red + pixel.green + pixel.green) / 3; // computing the gray pixel value
            // write the body
            if (0 < countOfPixel && countOfPixel % header.width == 0) // writing a new line if the current line ends
                fprintf (grayedOutPpmImage, "%c", '\n');
            fprintf(grayedOutPpmImage, "%d ", grayedOutPixel); // three times R,G,B -> Grey, Grey, Grey
        }
        fclose(coloredPpmImage);
        fclose(grayedOutPpmImage);
    }

    void edgeDetection(FILE * grayedOutPpmImage, FILE * edgeFilteredPpmImage) {
        if (!isFilePresent(grayedOutPpmImage))
            return;

        readAndPrintHeaderOfPpmImage(grayedOutPpmImage, edgeFilteredPpmImage);

        // fill 2D Array with read body-information
        int pixelData[header.height][header.width];
        for (int height = 0; height < header.height; height++)
        {
            for (int width = 0; width < header.width; width++)
            {
                int currentPixel;
                fscanf(grayedOutPpmImage, "%d", &currentPixel);
                pixelData[height][width] = currentPixel;
            }
        }

        for (int height = 0; height < header.height; height++)
        {
            if (0 < height)
                fprintf(edgeFilteredPpmImage, "%c", '\n'); //end of line --> printing a new line
            for (int width = 0; width < header.width; width++)
            {
                // computing the respective current index
                int currentPixel = pixelData[height][width];
                int up = height - 1;
                int down = height + 1;
                int left = width - 1;
                int right = width + 1;

                currentPixel *= filter[1][1]; // multiply by the factor 8

                // subtract all existing pixels around currentPixel
                if (up > 0)
                {
                    currentPixel += pixelData[up][width] * filter[0][1];
                    if (left > 0)
                        currentPixel += pixelData[up][left] * filter[0][0];
                    if (right < header.width)
                        currentPixel += pixelData[up][right] * filter[0][2];
                }

                if (left > 0)
                    currentPixel += pixelData[height][left] * filter[1][0];
                if (right < header.width)
                    currentPixel += pixelData[height][right] * filter[1][2];

                if (down < header.height)
                {
                    currentPixel += pixelData[down][width] * filter[2][1];
                    if (left > 0)
                        currentPixel += pixelData[down][left] * filter[2][0];
                    if (right < header.width)
                        currentPixel += pixelData[down][right] * filter[2][2];
                }

                if (currentPixel < 0) // no negative values allowed
                    currentPixel = 0;

                fprintf(edgeFilteredPpmImage, "%d ", currentPixel); // write down the edited pixel
            }
        }
        fclose(grayedOutPpmImage);
        fclose(edgeFilteredPpmImage);
    }

    static bool isFilePresent(FILE * inputFile)
    {

        if (inputFile != nullptr)
            return true;
        cout << "An error occurred. Could not open the file." << endl;
        return false;
    }
    static void skipTheComment(FILE *inputFile) { // comments in ppm/pgm images possible
        char comment = ' ';
        while (comment != '\n')
            fscanf(inputFile, "%c", &comment);
    }

    void readAndPrintHeaderOfPpmImage(FILE * inputFile, FILE * outputFile) {
        fscanf(inputFile, "%s", header.type);

        while(header.width == 0 || header.height == 0 )
        {
            skipTheComment(inputFile);
            fscanf(inputFile, "%d %d", &header.width, &header.height);
        }
        while(header.brightness == 0)
        {
            skipTheComment(inputFile);
            fscanf(inputFile,"%d" ,&header.brightness);
        }
        skipTheComment(inputFile);
        //finished reading -> write header
        fprintf(outputFile, "%s\n", "P2");
        fprintf(outputFile, "%d %d\n", header.width, header.height);
        fprintf(outputFile, "%d\n", header.brightness);
    }
};
#endif //edgeDetectionWithSobelOperator
