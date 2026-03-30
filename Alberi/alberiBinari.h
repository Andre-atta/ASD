//
// Created by Andrea on 16/03/2026.
//

#ifndef ASD_ALBERIBINARI_H
#define ASD_ALBERIBINARI_H

#include "vector"
using namespace std;

struct Node
{
    int val;
    Node* sx;
    Node* dx;
    Node* p; // Puntatore al padre
    Node(int v) : val(v), sx(nullptr), dx(nullptr), p(nullptr) {}
};
typedef Node* Pnode;


class alberoBinario
{
    struct Tree {
        Node* root;
        Tree(Node* r = nullptr) : root{r} {}
    };
    Tree tree;

    void deleteTree(Pnode node) {
        if (node == nullptr) return;
        deleteTree(node->sx);
        deleteTree(node->dx);
        delete node;
    }

    Pnode copyTree(Pnode node) {
        if (node == nullptr) return nullptr;
        Node* newNode = new Node(node->val);
        newNode->sx = copyTree(node->sx);
        newNode->dx = copyTree(node->dx);

        if (newNode->sx) newNode->sx->p = newNode;
        if (newNode->dx) newNode->dx->p = newNode;
        return newNode;
    }

    bool insertAtDepth(Pnode node, int val, int depth) {
        if (!node) return false;

        if (depth == 0) {
            if (!node->sx) {
                node->sx = new Node(val);
                node->sx->p = node;
                return true;
            }
            if (!node->dx) {
                node->dx = new Node(val);
                node->dx->p = node;
                return true;
            }
            return false;
        }

        // Prima sinistra poi destra => riempimento sx -> dx
        if (insertAtDepth(node->sx, val, depth - 1)) return true;
        return insertAtDepth(node->dx, val, depth - 1);
    }

public:
    alberoBinario() = default;

    alberoBinario(int val) {
        tree.root = new Node(val);
    }

    ~alberoBinario() {
        deleteTree(tree.root);
        tree.root = nullptr;
    }

    alberoBinario(const alberoBinario& other) {
        tree.root = copyTree(other.tree.root);
    }

    Pnode getRoot() const {
        return tree.root;
    }

    void insert(int val) {
        if (!tree.root) {
            tree.root = new Node(val);
            return;
        }

        for (int d = 0; ; ++d)
            if (insertAtDepth(tree.root, val, d)) return;

    }
};


#endif //ASD_ALBERIBINARI_H