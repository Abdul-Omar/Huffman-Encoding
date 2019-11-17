/**
 * HCTree.cpp : all functions defined in HCTree.hpp are implemented here
 *
 * Author: Andrew Masters / Abdulkhaliq Omar
 */
#include "HCTree.hpp"
#include <stack>

/* Builds a full binary tree given the vector that is passed as an argument
 * Starts from the nodes and builds to the root
 * The last node connected will be the root */
void HCTree::build(const vector<unsigned int>& freqs) {
    priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> pq;

    for (int i = 0; i < freqs.size(); i++) {
        if (freqs[i] != 0) {
            HCNode* node = new HCNode(freqs[i], i);

            leaves[i] = node;  // add to leaves

            pq.emplace(node);  // add to the pq
        }
    }

    if (pq.size() == 1) {
        root = pq.top();
        pq.pop();
        return;
    }

    while (!pq.empty()) {
        HCNode* curParent = new HCNode(0, 0);

        HCNode* child0 = pq.top();

        pq.pop();

        HCNode* child1 = pq.top();
        pq.pop();

        child0->p = curParent;
        curParent->c0 = child0;

        child1->p = curParent;
        curParent->c1 = child1;

        curParent->count = child0->count + child1->count;

        // parent symbol equals greater child symbol
        unsigned char parSymbol;

        child0->symbol < child1->symbol ? (parSymbol = child0->symbol)
                                        : (parSymbol = child1->symbol);

        curParent->symbol = parSymbol;

        pq.emplace(curParent);  // add the parent to the pq

        // if one element left in pq, it becomes the root
        if (pq.size() == 1) {
            root = pq.top();
            pq.pop();  // make it the root;
            return;
        }
    }
}

/* Write the encoding bits of given symbol to the given BitOutputStream.
 * Write each encoding bit to the BitOutputStream.
 * For this function to work, build() must have been called before to create the
 * HCTree.
 */
void HCTree::encode(byte symbol, BitOutputStream& out) const {
    // get the node
    HCNode* node = leaves[symbol];

    stack<int> path;

    if (root == nullptr) return;

    // traverse bottom up to the root
    while (node != root) {
        // if left at left child
        if (node == node->p->c0) {
            path.push(0);
        }
        // if at right child
        else if (node == node->p->c1) {
            path.push(1);
        }

        node = node->p;  // traverse up;
    }

    while (!path.empty()) {
        int bit = path.top();  // get character

        // write it to file
        out.writeBit(bit);

        path.pop();
    }
}

/* Write the encoding bits of given symbol to ostream.
 * Write each encoding bit as char of either 0 or 1 to the ostream.
 * Perform a comprehensive search to find the encoding bits of the given symbol,
 * and use the leaves vector to achieve efficient encoding.
 * For this function to work, build() must be called before to create the
 * HCTree.
 */
void HCTree::encode(byte symbol, ostream& out) const {
    // get the node
    HCNode* node = leaves[symbol];

    stack<char> path;

    if (node == root) {
        path.push('0');

    }

    else {  // traverse bottom up to the root
        while (node != root) {
            // if left at left child
            if (node == node->p->c0) {
                path.push('0');
            }

            // if at right child
            else if (node == node->p->c1) {
                path.push('1');
            }

            node = node->p;  // traverse up;
        }
    }
    while (!path.empty()) {
        unsigned char nextChar = path.top();  // get character

        // print it to file
        out << nextChar;

        path.pop();
    }
}

/* Decode the sequence of bits from the given BitInputStream to return the coded
 * symbol. For this function to work, build() must have been called before to
 * create the HCTree.
 */
byte HCTree::decode(BitInputStream& in) const {
    // start at root
    HCNode* current = root;

    if (!root) return -1;

    if (!current->c0 && !current->c1) {
        return current->symbol;
    }

    // traverse bottom up to the root until leaf node
    // traverse bottom up to the root until leaf node
    while ((current->c0 != nullptr || current->c1 != nullptr)) {
        // read one bit from input stream
        int bit = in.readBit();
        if (bit == -1) return -1;

        // traverse child0 if char is 0, else traverse child1
        bit == 0 ? (current = current->c0) : (current = current->c1);
    }
    return current->symbol;
}

/* Decode the sequence of bits (represented as char of either 0 or 1)
 * from istream to return the coded symbol.
 * For this function to work, build() must be called before to create the
 * HCTree.
 */
byte HCTree::decode(istream& in) const {
    unsigned char nextChar;

    // start at root
    HCNode* current = root;

    if (!root) return -1;

    if (!current->c0 && !current->c1) {
        if (in.eof()) return -1;
        nextChar = (unsigned char)in.get();
        if (nextChar == '0' || nextChar == '1') return current->symbol;
        decode(in);
    }

    // traverse bottom up to the root until leaf node
    while ((current->c0 != nullptr || current->c1 != nullptr)) {
        // read one bit from input stream
        nextChar = (unsigned char)in.get();

        if (in.eof()) return -1;

        if (nextChar == '0') {
            current = current->c0;
        } else if (nextChar == '1') {
            current = current->c1;
        }
    }
    return current->symbol;  // return the char at this node
}

/* Deconstructor that calls the deleteAll function to deallocate all memory in
 * the heap*/
HCTree::~HCTree() { deleteAll(root); }

/* Helper Method for Deconstructor */
void HCTree::deleteAll(HCNode* root) {
    if (!root) return;

    deleteAll(root->c0);
    deleteAll(root->c1);
    delete (root);
}
