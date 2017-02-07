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



void QuadTree::printTree() {
    digPrint(root);
}

void QuadTree::digPrint(QuadNode * root) {
    if(root != nullptr) {
        for (int num=3; num >= 0; num--) {
            printElement(root);
            if (root->quads[num] != nullptr) {
                digPrint(root->quads[num]);
                
            }
        }
        return;
    }
}

void QuadTree::printElement(QuadNode *node) {
    for (int num=0; num < node->level*5; num++) {
        cout << " ";
    }
    cout << node->type << " " << to_string(node->level) << endl;
}
