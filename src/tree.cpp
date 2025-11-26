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

private:

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
