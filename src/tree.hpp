#pragma once
#include <iostream>
#include <algorithm>

template <class T>
class tree
{
private:
    struct Node
    {
        T data;
        int height;          
        Node* left;
        Node* right;

        Node(const T& data)
            : data(data), height(1), left(nullptr), right(nullptr) {}
    };

    Node* root;  

public:
    tree() : root(nullptr) {}

    
    void insert(const T& data)
    {
        root = addToTree(root, data);
    }

    
    bool search(const T& item)
    {
        return searchNode(root, item);
    }

    void print()
    {
        printTree(root, "", true);
    }

private:

    int getBalance(Node* node)
    {
        return (getHeight(node->left) - getHeight(node->right));
    }

    Node* rotateLeft(Node *z)
    {
                //       z                               y
                //      / \                       ->ls /   \
                //     T1   y     left Rotate         z      x
                //         / \   - - - - - - - ->   / \ <-rs   / \
                //      T2    X                     T1  T2 T3  T4
                //           / \ 
                //          T3  T4
    Node* y = z->right;
    Node* T2 = y->left;

    y->left = z;
    z->right = T2;


    z->height = 1 + std::max(getHeight(z->left), getHeight(z->right));
    y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));

    return y; 
    }

    Node* rotateRight(Node *z)
    {
                //       z                               y
                //      / \                            /    \ <-right side
                //     y   T4     Right Rotate       x        z
                //    / \       - - - - - - - ->    / \ ls-> / \
                //   x   T3                        T1  T2 T3  T4
                //  / \
                // T1  T2
    Node* y = z->left;
    Node* T3 = y->right;

    y->right = z;
    z->left = T3;

    
    z->height = 1 + std::max(getHeight(z->left), getHeight(z->right));
    y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));

    return y; 
    }
    void printTree(Node* node, std::string indent, bool last) {
        if (node != nullptr) {
            std::cout << indent;

            if (last) {
                std::cout << "R----";
                indent += "     ";
            } else {
                std::cout << "L----";
                indent += "|    ";
            }

            std::cout << node->data << "(h=" << node->height << ")" << std::endl;

            printTree(node->left, indent, false);
            printTree(node->right, indent, true);
        }
    }


    int getHeight(Node* node)
    {
        return node ? node->height : 0;
    }

    Node* createNode(const T& data)
    {
        return new Node(data);
    }


    Node* addToTree(Node* node, T data)
    {
        if (!node)
            return createNode(data);

        if (data < node->data)
            node->left = addToTree(node->left, data);

        else if (data > node->data)
            node->right = addToTree(node->right, data);

        else
            return node; 

    
        node->height = 1 + std::max(getHeight(node->left),
                                    getHeight(node->right));
        //LL left side of left branch
        if(getBalance(node) > 1 && data < node -> left -> data)
        {
            return rotateRight(node);

        }
        // RR right side of right branch
        if(getBalance(node) < -1 && data > node -> right -> data)
        {
            return rotateLeft(node);
        }

        //LR left side of right branch
        if(getBalance(node) > 1 && data > node -> left -> data)
        {
            node -> left = rotateLeft(node);
            return rotateRight(node);
        }

        // RL right side of right branch
        if(getBalance(node) < -1 && data < node -> right -> data)
        {
            node -> right = rotateRight(node);
            return rotateLeft(node);
        }


         return node;
    }

    
    bool searchNode(Node* node, const T& item)
    {
        if (!node)
            return false;

        if (node->data == item)
            return true;

        if (item < node->data)
            return searchNode(node->left, item);
        else
            return searchNode(node->right, item);
    }
};
