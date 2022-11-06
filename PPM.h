#ifndef EDGEDETECTIONWITHSOBELOPERATOR_PPM_H
#define EDGEDETECTIONWITHSOBELOPERATOR_PPM_H
#include <iostream>
#include "fstream"
#include "string"
using namespace std;

class PPM {
public:
    static string readData(const string & fileOfPpmImage) {
        string readData;
        ifstream inFile(fileOfPpmImage);
        if (!inFile)
            cout << "An error occurred. Could not open the file." << endl;
        else
            while (getline(inFile, readData, ';')); // reading all lines and save them in a string
        inFile.close();
        return readData;
    }

    static void writeData(const string& fileOfPpmImage, const string& fileOfNewPpmImage) {
        ofstream outFile;
        outFile.open(fileOfNewPpmImage,ios::out);
        if (!outFile)
            cout << "An error occurred. Could not open the file." << endl;
        else
            outFile << fileOfPpmImage << flush; // free up buffer after the data of the image is written down
        outFile.close();
    }
};
#endif //EDGEDETECTIONWITHSOBELOPERATOR_PPM_H
