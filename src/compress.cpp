/**
 * compress.cpp - file compresses given input file and
 * outputs into given output file
 *
 * Author: Andrew Masters / Abdulkhaliq Omar
 */
#include <fstream>
#include <iostream>

#include <cxxopts.hpp>
#include "FileUtils.hpp"
#include "HCNode.hpp"
#include "HCTree.hpp"
using namespace std;

/* Helper function for trueCompression function
 * If a leaf node is found, a 1 is written to the file
 * If a parent node is found, a 0 is written */
void trueCompressHelper(HCNode* root, ostream& out) {
    if (!root) return;

    if (root->c0 == nullptr && root->c1 == nullptr) {
        out << '1';
        out << root->symbol;
        return;
    }

    trueCompressHelper(root->c0, out);
    trueCompressHelper(root->c1, out);

    out << '0';
}

/* This function compresses a text file by reading an input file and
 * writing each char to its frequency in an output file
 */
void pseudoCompression(string inFileName, string outFileName) {
    // The tree to build
    HCTree hufTree;

    vector<unsigned int> freqs(256);  // vector containing frequencies

    // create an input stream to read file
    ifstream in;
    in.open(inFileName);

    // get the frequecing of each char in file
    // no skipping new line chars

    int symbol;
    // get the frequecing of each char in file
    // no skipping new line chars
    while (!in.eof()) {
        symbol = in.get();

        if (symbol == EOF) break;
        freqs.at((unsigned char)symbol)++;
    }

    in.close();  // close file

    // build tree
    hufTree.build(freqs);

    // create an output stream to write file to
    ofstream out;
    out.open(outFileName);

    // write file header info
    // frequencies of each letter plus new line
    for (int i = 0; i < freqs.size(); i++) {
        out << freqs[i] << endl;
    }

    int nextChar;
    // open file to write encoded info
    ifstream in2;
    in2.open(inFileName);

    // write compressed info to outfile
    while (!in2.eof()) {
        nextChar = in2.get();
        if (nextChar == -1) break;

        if (in2.eof()) break;

        hufTree.encode((unsigned char)nextChar, out);
    }

    in2.close();
    out.close();
}

/* True compression with bitwise i/o and small header
 * reads from the given input file and writes the tree
 * and binary to the output file */
void trueCompression(string inFileName, string outFileName) {
    // The tree to build
    HCTree hufTree;

    vector<unsigned int> freqs(256);  // vector containing frequencies

    // create an input stream to read file
    ifstream in;
    in.open(inFileName);

    int symbol;
    int numChars = 0;
    // get the frequecing of each char in file
    // no skipping new line chars
    while (!in.eof()) {
        symbol = in.get();

        if (symbol == EOF) break;

        freqs.at((unsigned char)symbol)++;

        numChars++;
    }

    in.close();  // close file

    // build tree
    hufTree.build(freqs);

    // create an output stream to write file to
    ofstream out;
    out.open(outFileName, ios::binary);

    // create bitstream output object to encode
    BitOutputStream bitOut(out);

    // write the header
    trueCompressHelper(hufTree.root, out);

    // additional 0 to indicate end of topology
    out << '0';

    // write num of characters in the original tree
    out << numChars;

    // add new line to seperate header from encoded part
    out << endl;

    // open file for reading
    ifstream inf;

    inf.open(inFileName);

    // cout << (unsigned char)inf.get() << endl;

    // write compressed info to outfile
    while (!inf.eof()) {
        int nextChar = inf.get();
        if (nextChar == -1) break;

        if (inf.eof()) break;

        hufTree.encode((unsigned char)nextChar, bitOut);
    }

    bitOut.flush();  // write to file any incomplete buf

    // close files
    inf.close();
    out.close();
}

/* Main program that runs the compress */
int main(int argc, char* argv[]) {
    /* for option parsing and file validity checking */
    cxxopts::Options options("./compress",
                             "Compresses files using Huffman Encoding");
    options.positional_help("./path_to_input_file ./path_to_output_file");

    bool isAsciiOutput = false;  // whether user wants ascii output

    string inFileName, outFileName;  // input and output file names

    options.allow_unrecognised_options().add_options()(
        "ascii", "Write output in ascii mode instead of bit stream",
        cxxopts::value<bool>(isAsciiOutput))(
        "input", "", cxxopts::value<string>(inFileName))(
        "output", "", cxxopts::value<string>(outFileName))(
        "h,help", "Print help and exit");

    options.parse_positional({"input", "output"});
    auto userOptions = options.parse(argc, argv);

    // if users wants help or file to read from is invalid
    if (userOptions.count("help") || !FileUtils::isValidFile(inFileName)) {
        cout << options.help({""}) << endl;
        exit(0);
    }

    // check for file validity
    if (!FileUtils::isValidFile(inFileName)) {
        return 0;
    }

    // check if input file is not empty
    if (FileUtils::isEmptyFile(inFileName)) {
        ofstream out(outFileName);

        return 0;
    }

    // if user wants ascii compression output
    if (isAsciiOutput) {
        // compress the file
        pseudoCompression(inFileName, outFileName);
    }

    else {
        trueCompression(inFileName, outFileName);
    }

    return 0;
}
