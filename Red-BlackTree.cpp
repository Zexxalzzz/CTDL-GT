#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    string color;
    Node *left;
    Node *right;
    Node *parent;

    Node(int data){
        this->data = data;
        color = "RED";
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

struct RedBlackTree{
    Node* root;
    Node* NIL;
    RedBlackTree()
    {
        NIL = new Node(0);
        NIL->color = "BLACK";
        NIL->left = NIL->right = NIL;
        root = NIL;
    }
    
    void leftRotate(Node* key)
    {
        Node* x = key->right;                
        key->right = x->left;                
        if (x->left != NIL) {                
            x->left->parent = key;
        }
        x->parent = key->parent;            
        if (key->parent == nullptr) {   
                root = x;
        }
        else if (key == key->parent->left) {
            key->parent->left = x;
        }
        else {
            key->parent->right = x;
        }
        x->left = key;                       
        key->parent = x;
    }

    void rightRotate(Node* key)
    {
        Node* y = key->left;
        key->left = y->right;
        if (y->right != NIL) {
            y->right->parent = key;
        }
        y->parent = key->parent;
        if (key->parent == nullptr) {
            root = y;
        }
        else if (key == key->parent->right) {
            key->parent->right = y;
        }
        else {
            key->parent->left = y;
        }
        y->right = key;
        key->parent = y;
    }

    void fixInsert(Node *key){
        while (key != root && key->parent->color == "RED"){       
                                                                  
            if(key->parent == key->parent->parent->left){         
                Node *u = key->parent->parent->right;
                if(u->color == "RED"){                          
                    key->parent->color = "BLACK";
                    u->color = "BLACK";
                    key->parent->parent->color = "RED";
                    key = key->parent->parent;
                }
                else {                                         
                    if (key == key->parent->right) {             
                        key = key->parent;
                        leftRotate(key);
                    }
                    key->parent->color = "BLACK";               
                    key->parent->parent->color = "RED";
                    rightRotate(key->parent->parent);          
                }
            }
            else{                                                
                Node *u = key->parent->parent->left;
                if(u->color == "RED"){
                    key->parent->color = "BLACK";
                    u->color = "BLACK";
                    key->parent->parent->color = "RED";
                    key = key->parent->parent;
                }
                else{
                    if (key == key->parent->left) {
                        key = key->parent;
                        rightRotate(key);
                    }
                    key->parent->color = "BLACK";
                    key->parent->parent->color = "RED";
                    leftRotate(key->parent->parent);
                }
            }
            if(key == root) break;                             
        }
        root->color = "BLACK";                                
    }

    void Insert(int data){
        Node* new_node = new Node(data);
        new_node->left = NIL;
        new_node->right = NIL;

        Node* parent = nullptr;
        Node* current = root;
        while(current != NIL){
            parent = current;
            if(new_node->data < current->data){
                current = current->left;
            }
            else{
                current = current->right;
            }
        }
        new_node->parent = parent;
        if(parent == nullptr){
            root = new_node;
        }
        else if(new_node->data < parent->data){
            parent->left = new_node;
        }
        else{
            parent->right = new_node;
        }

        if(new_node->parent == nullptr){
            new_node->color = "BLACK";
            return;
        }

        if(new_node->parent->parent == nullptr){
            return;
        }
        fixInsert(new_node);
    }

    Node* Search(Node *node, int data){
        if(node == NIL || data == node->data){
            return node;
        }
        if(data < node->data){
            return Search(node->left, data);
        }
        return Search(node->right, data);
    }
    Node* Search(int data){
        return Search(this->root, data);
    }

    void sibling(Node* u, Node* v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void deleteNode(int data) {
        deleteNode(this->root, data);
    }

    void deleteNode(Node* node, int key) {
        Node* root = NIL;
        Node* x, * y;
        while (node != NIL) {
            if (node->data == key) {
                root = node;
            }

            if (node->data <= key) {
                node = node->right;
            } else {
                node = node->left;
            }
        }

        if (root == NIL) {
            cout << "Khong tim thay node can xoa" << endl;
            return;
        }

        y = root;
        string y_original_color = y->color;
        if (root->left == NIL) {
            x = root->right;
            sibling(root, root->right);
        } else if (root->right == NIL) {
            x = root->left;
            sibling(root, root->left);
        } else {
            y = minimum(root->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == root) {
                x->parent = y;
            } else {
                sibling(y, y->right);
                y->right = root->right;
                y->right->parent = y;
            }

            sibling(root, y);
            y->left = root->left;
            y->left->parent = y;
            y->color = root->color;
        }
        delete root;
        if (y_original_color == "BLACK") {
            fixDelete(x);
        }
    }

    void fixDelete(Node* x) {
        Node* s;
        while (x != root && x->color == "BLACK") {
            if (x == x->parent->left) {
                s = x->parent->right;
                if (s->color == "RED") {
                    s->color = "BLACK";
                    x->parent->color = "RED";
                    leftRotate(x->parent);
                    s = x->parent->right;
                }

                if (s->left->color == "BLACK" && s->right->color == "BLACK") {
                    s->color = "RED";
                    x = x->parent;
                } else {
                    if (s->right->color == "BLACK") {
                        s->left->color = "BLACK";
                        s->color = "RED";
                        rightRotate(s);
                        s = x->parent->right;
                    }

                    s->color = x->parent->color;
                    x->parent->color = "BLACK";
                    s->right->color = "BLACK";
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                s = x->parent->left;
                if (s->color == "RED") {
                    s->color = "BLACK";
                    x->parent->color = "RED";
                    rightRotate(x->parent);
                    s = x->parent->left;
                }

                if (s->left->color == "BLACK" && s->right->color == "BLACK") {
                    s->color = "RED";
                    x = x->parent;
                } else {
                    if (s->left->color == "BLACK") {
                        s->right->color = "BLACK";
                        s->color = "RED";
                        leftRotate(s);
                        s = x->parent->left;
                    }

                    s->color = x->parent->color;
                    x->parent->color = "BLACK";
                    s->left->color = "BLACK";
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = "BLACK";
    }

    Node* minimum(Node* node) {
        while (node->left != NIL) {
            node = node->left;
        }
        return node;
    }

    int height(Node* node) {
        if (node == NIL) {
            return 0;
        }
        int left_height = height(node->left);
        int right_height = height(node->right);
        return max(left_height, right_height) + 1;
    }

    void Output(Node* root, int level) {
        if (root == NIL) return;
        if (level == 1) {
            cout << root->data << "(" << root->color << ")" << " ";
        } else if (level > 1) {
            Output(root->left, level - 1);
            Output(root->right, level - 1);
        }
    }

    void BFS(Node* node) {
        int h = height(node);
        for (int i = 1; i <= h; i++) {
            Output(node, i);
            cout << endl;
        }
    }

    void Output() {
        cout << "BFS: " << endl;
        BFS(this->root);
    }
};


int main(){
    RedBlackTree rbt;
    int a[] = {44, 86, 75, 38, 12, 59, 65, 47, 21, 28, 17, 82, 50, 21, 59};
    for(int x : a){
        rbt.Insert(x);
    }
    rbt.Output();
    Node *node = rbt.Search(12);
    if(node != rbt.NIL){
        cout << "Tim thay: " << node->data <<endl;
    }
    else{
        cout << "Khong tim thay: "<< endl;
    }
    rbt.deleteNode(21);
    rbt.Output();
    rbt.deleteNode(59);
    rbt.Output();
    return 0;
}
