#include <fstream>
#include <iostream>

using namespace std;

class FileUtils {
  public:
    /* Check if a given data file is valid */
    static bool isValidFile(string fileName) {
        ifstream in;
        in.open(fileName, ios::binary);

        // Check if input file was actually opened
        if (!in.is_open()) {
            cout << "Invalid input file. No file was opened. Please try "
                    "again.\n";
            return false;
        }

        in.close();
        return true;
    }

    /* Check if given file is empty */
    static bool isEmptyFile(string fileName) {
        ifstream inFile;
        // if the given file is empty, output empty file
        inFile.open(fileName, ios::binary);
        inFile.get();
        if (inFile.eof()) {
            inFile.close();
            return true;
        }
        inFile.close();
        return false;
    }
};
