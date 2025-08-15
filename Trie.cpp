#include<bits/stdc++.h>
using namespace std;
class Node{
public:
    bool flag;
    array<Node*, 26> children;
    Node(){
        flag=false;
        children.fill(nullptr);
    }
};
class Trie {
private:
    Node *root=nullptr;
    void deleteNodes(Node* node) {
        if (node == nullptr) {
            return;
        }
        for (int i = 0; i < 26; ++i) {
            deleteNodes(node->children[i]);
        }
        delete node;
    }
public:
    Trie() {
        root=new Node();
    }
    ~Trie() {
        deleteNodes(root);
    }
    
    void insert(string word) {
        Node * node=root;
        for(auto ch:word){
            int id=ch-'a';
            if(node->children[id]==nullptr){
                node->children[id]=new Node();
            }
            node=node->children[id];
        }
        node->flag=true;
    }
    
    bool search(string word) {
        Node *node=root;
        for(auto ch:word){
            int id=ch-'a';
            if(node->children[id]==nullptr)return false;
            node=node->children[id];
        }
        return node->flag;
    }
    
    bool startsWith(string prefix) {
        Node *node=root;
        for(auto ch:prefix){
            int id=ch-'a';
            if(node->children[id]==nullptr)return false;
            node=node->children[id];
        }
        return true;
    }
};