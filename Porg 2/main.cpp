//  Created by Christian Munte on 2/6/17


#include <iostream>
#include <string>
#include <sstream>

using namespace std;

const int IMG_SIZE = 32;

struct QuadNode {
    char type;
    int level;
    QuadNode * quads[4];
};

class QuadTree {
private:
    QuadNode * root;
    
public:
    QuadTree();
    char queryTree(int, int);
    bool sameTree(QuadNode *, QuadNode *);
    int numBlack();
    int largestRepeat();
    void frmStr(string);
    void dig(QuadNode *&, int, int , stringstream &);
    void printTree();
    void printElement(QuadNode *);
    void digPrint(QuadNode *);
    void printImage();
    
};

int main() { //iibbwwiwwbwwb
    string input;
    cin >> input;
    QuadTree tree;
    tree.frmStr(input);
    tree.printTree();
    return 0;
}

QuadTree::QuadTree() {
    root =  new QuadNode;
}

void QuadTree::frmStr(string input) {
    stringstream stream(input);
    
    dig(root, 0, 0, stream);
    
    cout << "done" << endl;
}

void QuadTree::dig(QuadNode *&root, int level, int quad, stringstream &stream) {
    char next;
    if (stream >> next) {
        if(next == 'i'){
            root->level = level;
            root->type = next;
            root->quads[quad] = new QuadNode;
            dig(root->quads[quad], level+1, 0, stream);
            quad ++;
        } else if (next == 'w' || next == 'b') {
            root->type = next;
            root->level = level;
            dig(root, level, quad + 1, stream);
        }
        if (quad == 4){
            return;
        }
    }
}

void QuadTree::printTree() {
    digPrint(root);
}

void QuadTree::digPrint(QuadNode * root) {
    for (int num=0; num < 4; num++) {
        if (root->quads[num] != nullptr && root != nullptr) {
            digPrint(root->quads[num]);
            printElement(root);
        }
    }
}

void QuadTree::printElement(QuadNode *node) {
    for (int num=0; 0 < node->level*5; num++) {
        cout << " ";
    }
    cout << node->type << " " << to_string(node->level+1);
}
