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
    QuadNode(){
        quads[0]=nullptr;
        quads[1]=nullptr;
        quads[2]=nullptr;
        quads[3]=nullptr;
    }
};

class QuadTree {
private:
    QuadNode * root;
    
public:
    QuadTree();
    char queryTree(int, int);
    char digTree(QuadNode *, int, int, int);
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
    tree.printImage();
    //cout << tree.queryTree(10, 19) << endl;
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
    bool deeper = false;
    while (stream >> next) {
        //cout << "level: " << level << " quad: " << quad << " type: " << next << endl;
        if(root->level < level) {
            deeper = true;
        }
        root->quads[quad] = new QuadNode;
        if(next=='i'){
            if(deeper) {
                //cout << "going deeper\n";
                root->quads[quad]->type = next;
                root->quads[quad]->level = level;
                dig(root->quads[quad], level+1, 0, stream);
            } else {
                root->type = next;
                root->level = level;
                dig(root, level+1, 0, stream);
            }
            //cout << "set level: " << root->level << " set type: " << root->type << endl;
            quad++;
        } else {
            root->quads[quad]->type = next;
            root->quads[quad]->level = level;
            quad++;
        }
        if(quad == 4){
            return;
        }
    }
}

char QuadTree::queryTree(int row, int col) {
    return digTree(root, row, col, IMG_SIZE);
}

void QuadTree::printImage() {
    //cout << queryTree(9, 18) << endl;
    cout << " ";
    for (int a=1; a<IMG_SIZE+1; a++) {
        cout << a%10;
    }
    cout << endl;
    for (int row=1; row < IMG_SIZE; row++) {
        cout << row%10;
        for (int col=0; col < IMG_SIZE; col++) {
            cout << queryTree(row, col);
        }
        cout << row%10 << endl;
    }
    cout << " ";
    for (int a=1; a<IMG_SIZE+1; a++) {
        cout << a%10;
    }
    cout << endl;
}

char QuadTree::digTree(QuadNode *root, int row, int col, int img) {
    if(root->type == 'b' || root->type == 'w'){
        if(root->type == 'b') {
            return '@';
        } else {
            return '.';
        }
    } else if (row <= img/2 && col < img/2) {
        return digTree(root->quads[0], row, col, img/2);
    } else if (row <= img/2 && col >= img/2) {
        return digTree(root->quads[1], row, col-(img/2), img/2);
    } else if (row > img/2 && col >= img/2) {
        return digTree(root->quads[2], row-(img/2), col-(img/2), img/2);
    } else if (row > img/2 && col < img/2) {
        return digTree(root->quads[3], row-(img/2), col, img/2);
    } else {
        return '?';
    }
}

void QuadTree::printTree() {
    printElement(root);
    digPrint(root);
}

void QuadTree::digPrint(QuadNode * root) {
    for(int quad = 3; quad >= 0; quad--) {
        if(root->quads[quad] != nullptr) {
            printElement(root->quads[quad]);
            digPrint(root->quads[quad]);
        }
    }
}

void QuadTree::printElement(QuadNode *node) {
    for (int num=0; num < node->level*5; num++) {
        cout << " ";
    }
    cout << node->type << " " << to_string(node->level) << endl;
}
