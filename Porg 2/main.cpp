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
    bool sameTree(QuadNode, QuadNode);
    int numBlack();
    int largestRepeat();
    void frmStr(string);
    void printTree();
    void printImage();
    
};

int main() { //iibbwwiwwbwwb
    string input;
    cin >> input;
    QuadTree tree;
    tree.frmStr(input);
    
    return 0;
}

QuadTree::QuadTree() {
    root =  new QuadNode;
}

void QuadTree::frmStr(string input) {
    char each;
    int level = 0, count = 0;
    stringstream stream(input);
    
    while (stream >> each) {
        if (count == 4) {
            level -= 5;
            count = 0;
        }
        for(int space=0; space < level; space++){
            cout << " ";
        }
        cout << each << endl;
        count++;
        if (each == 'i' && count != 5) {
            level += 5;
            count = 0;
        }
    }
}
