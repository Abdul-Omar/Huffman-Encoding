/** uncompress.cpp - reads from a given compress file and decompresses to the
 * given output file
 *
 * Author: Andrew Masters / Abdulkhaliq Omar
 */
#include <fstream>
#include <iostream>

#include <stack>
#include "FileUtils.hpp"
#include "HCNode.hpp"
#include "HCTree.hpp"

using namespace std;

/* Helper function for trueDecompression function if bit 1 is read, a node is
 * created if bit 0 is read, a parent node is created*/
HCNode* reBuildTree(ifstream& in) {
    stack<HCNode*> tree;

    while (true) {
        char bit;

        in >> bit;

        if (bit == '1') {
            // read next ascii char following it
            unsigned char ch = (unsigned char)in.get();

            HCNode* node = new HCNode(0, ch);

            tree.emplace(node);

        }

        else if (bit == '0') {
            // if tree size is 1, we are done
            if (tree.size() == 1) {
                return tree.top();
                break;
            }

            else {
                // otherwise, get next two children and join them to new parent
                HCNode* parent = new HCNode(0, '0');

                HCNode* child1 = tree.top();

                tree.pop();

                HCNode* child0 = tree.top();

                tree.pop();

                parent->c1 = child1;

                parent->c0 = child0;

                tree.emplace(parent);
            }
        }
    }
}

/* Pseudo decompression with ascii encoding and naive header Reads the
 * compressed input file and outputs into the given output file. Uses ascii
 * table.
 */
void pseudoDecompression(string inFileName, string outFileName) {
    // The tree to build
    HCTree hufTree;

    vector<unsigned int> freqs(256);  // vector containing frequencies

    // create an input stream to read file
    ifstream in;

    in.open(inFileName);

    unsigned int frequency;

    int size = freqs.size();

    // get frequency of each character
    for (int i = 0; i < freqs.size(); i++) {
        in >> frequency;
        freqs[i] = frequency;
    }

    // build tree
    hufTree.build(freqs);

    // create an output stream to write file to
    ofstream out(outFileName);

    unsigned char symbol;

    // write decompressed info to file
    while (1) {
        symbol = hufTree.decode(in);

        if (in.eof()) break;

        if (symbol == -1) break;
        out << symbol;
        out.flush();
    }

    in.close();
    out.close();
}

/* True decompression with bitwise i/o and small header.  Reads from given
 * compressed input file and outputs onto given output file. Must rebuild tree
 * with helper function and read from binary of compressed file to decompress
 * */
void trueDecompression(string inFileName, string outFileName) {
    // The tree to build
    HCTree hufTree;

    // create an input stream to read file
    ifstream in;

    in.open(inFileName, ios::binary);

    // build tree
    hufTree.root = reBuildTree(in);

    int numChars;

    in >> numChars;
    in.get();
    // create an output stream to write file to
    ofstream out;
    out.open(outFileName);

    int symbol;
    // create new BitInputStream object
    BitInputStream bitIn(in);
    // write decompressed info to file
    while (numChars > 0 && !in.eof()) {
        // if end of file
        if (in.eof()) break;
        // decode each byte
        symbol = hufTree.decode(bitIn);

        if (symbol == -1) break;
        out << (unsigned char)symbol;
        // out.flush();
        numChars--;
    }

    // close files
    in.close();
    out.close();
}

/* Main program that runs the uncompress */
int main(int argc, char* argv[]) {
    // check for file validity
    if (!FileUtils::isValidFile(argv[1])) {
        return 0;
    }

    // check if input file is not empty
    if (FileUtils::isEmptyFile(argv[1])) {
        ofstream out(argv[2]);
        return 0;
    }

    string inFileName(argv[1]);
    string outFileName(argv[2]);

    // pseudoDecompression(inFileName, outFileName);

    trueDecompression(argv[1], argv[2]);

    return 0;
}
