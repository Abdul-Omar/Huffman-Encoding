/**
 * HCTree.hpp - class HCTree defined ; All implementation is in HCTree.cpp
 *
 * Author: Andrew Masters / Abdulkhaliq Omar
 */
#ifndef HCTREE_HPP
#define HCTREE_HPP

#include <fstream>
#include <queue>
#include <vector>
#include "BitInputStream.hpp"
#include "BitOutputStream.hpp"
#include "HCNode.hpp"

using namespace std;

/** The HCTree class : defines all variables and functions
 *  Function implementation is in HCTree.cpp */
class HCTree {
  private:
    vector<HCNode*> leaves;  // a vector storing pointers to all leaf HCNodes

  public:
    HCNode* root;  // the root of HCTree

    /* Class constructor that initalizes the root node and the ASCII vector of
     * nodes*/
    HCTree() {
        root = nullptr;
        leaves = vector<HCNode*>(256, (HCNode*)0);
    }

    /* Deconstructor that calls the deleteAll function to deallocate all memory
     * in the heap*/
    ~HCTree();

    /* Helper method for deconstructor to deallocate memory in the heap*/
    void deleteAll(HCNode* root);

    /* Builds a full binary tree given the vector that is passed as an argument
     * Starts from the nodes and builds to the root
     * The last node connected will be the root */
    void build(const vector<unsigned int>& freqs);

    /* Write the encoding bits of given symbol to the given BitOutputStream.
     * Write each encoding bit to the BitOutputStream.
     * For this function to work, build() must have been called before to create
     * the HCTree.
     */
    void encode(byte symbol, BitOutputStream& out) const;

    /* Write the encoding bits of given symbol to ostream.
     * Write each encoding bit as char of either 0 or 1 to the ostream.
     * Perform a comprehensive search to find the encoding bits of the given
     * symbol, and use the leaves vector to achieve efficient encoding. For this
     * function to work, build() must be called before to create the HCTree.
     */
    void encode(byte symbol, ostream& out) const;

    /* Decode the sequence of bits from the given BitInputStream to return the
     * coded symbol. For this function to work, build() must have been called
     * before to create the HCTree.
     */
    byte decode(BitInputStream& in) const;

    /* Decode the sequence of bits (represented as char of either 0 or 1)
     * from istream to return the coded symbol.
     * For this function to work, build() must be called before to create the
     * HCTree.
     */
    byte decode(istream& in) const;
};

#endif  // HCTREE_HPP
