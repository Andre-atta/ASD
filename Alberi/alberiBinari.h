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
protected:
    struct Tree {
        Node* root;
        Tree(Node* r = nullptr) : root{r} {}
    };
    Tree tree;

private:
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

    Pnode insert(Pnode parent, int val, bool asLeft) {
        if (!parent) {
            if (!tree.root) {
                tree.root = new Node(val);
                return tree.root;
            }
            return nullptr;
        }

        if (asLeft) {
            if (!parent->sx) {
                parent->sx = new Node(val);
                parent->sx->p = parent;
            } else {
                parent->sx->val = val;
            }
            return parent->sx;
        } else {
            if (!parent->dx) {
                parent->dx = new Node(val);
                parent->dx->p = parent;
            } else {
                parent->dx->val = val;
            }
            return parent->dx;
        }
    }
};


#endif //ASD_ALBERIBINARI_H