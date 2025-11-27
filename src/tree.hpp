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
        Node *left;
        Node *right;

        Node(const T &data) : data(data), height(1), left(nullptr), right(nullptr) {}
    };

    Node *root;

public:

    tree() : root(nullptr) {}
    ~tree() { deleteTree(root); }

    int numberOfLeaves()
    {
        return countLeaves(root);
    }
    int numberOfNodes()
    {
        return countNodes(root);
    }
    T findMax()
    {
        Node *temp = root;
        while(temp -> right)
        temp = temp -> right;
        return temp -> data;
    }
    T findMin()
    {
        Node* temp = root;
        while(temp -> left)
        temp = temp -> left;
        return temp -> data;
    }

    void insert(const T &data)
    {
        root = addToTree(root, data);
    }

    bool search(const T &item)
    {
        return searchNode(root, item);
    }

    void print()
    {
        printTree(root, "", true);
    }

    void deleteNode(T data)
    {
        root = delete_entry(root, data);
    }

private:

    void deleteTree(Node* node)
    {
        if(!node) return;
        
        deleteTree(temp -> right);
        deleteTree(temp -> left);
        delete node;
    }
    int getBalance(Node *node)
    {
        return (getHeight(node->left) - getHeight(node->right));
    }
    int countLeaves(Node *node)
    {
        if(!node) return 0;
        else if(!node -> right && !node -> left) return 1;
        return countLeaves(node -> right) + countLeaves(node -> left);
    }
    int countNodes(Node* node)
    {
        if(!node) return 0;
        return 1 + countNodes(node -> right) + countNodes(node -> left);
    }

    Node *rotateLeft(Node *z)
    {
        //                z                               y
        //               / \                       ->ls  / \
                //     T1   y     left Rotate          z    x
        //                 / \   - - - - - - - ->   / \ <-rs/ \
                //      T2    X                     T1  T2 T3  T4
        //                   / \ 
                //          T3  T4
        Node *y = z->right;
        Node *T2 = y->left;

        y->left = z;
        z->right = T2;

        z->height = 1 + std::max(getHeight(z->left), getHeight(z->right));
        y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));

        return y;
    }

    Node *rotateRight(Node *z)
    {
        //       z                               y
        //      / \                            /    \ <-right side
        //     y   T4     Right Rotate       x        z
        //    / \       - - - - - - - ->    / \ ls-> / \
        //   x   T3                        T1  T2 T3  T4
        //  / \
        // T1  T2
        Node *y = z->left;
        Node *T3 = y->right;

        y->right = z;
        z->left = T3;

        z->height = 1 + std::max(getHeight(z->left), getHeight(z->right));
        y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));

        return y;
    }

    Node *AVL(Node *node)
    {
        // //LL left side of left branch
        // if(getBalance(node) > 1 && data < node -> left -> data)
        // {
        //     return rotateRight(node);

        // }
        // // RR right side of right branch
        // if(getBalance(node) < -1 && data > node -> right -> data)
        // {
        //     return rotateLeft(node);
        // }

        // //LR left side of right branch
        // if(getBalance(node) > 1 && data > node -> left -> data)
        // {
        //     node -> left = rotateLeft(node);
        //     return rotateRight(node);
        // }

        // // RL right side of right branch
        // if(getBalance(node) < -1 && data < node -> right -> data)
        // {
        //     node -> right = rotateRight(node);
        //     return rotateLeft(node);
        // }

        // return node;

        // Above code can cause crashes due fragile cases of checking data inputs

        if (!node)
            return node;

        int balance = getBalance(node);

        // Left heavy
        if (balance > 1)
        {
            // LL
            if (getBalance(node->left) >= 0)
                return rotateRight(node);
            // LR
            else
            {
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
        }

        // Right heavy
        if (balance < -1)
        {
            // RR
            if (getBalance(node->right) <= 0)
                return rotateLeft(node);
            // RL
            else
            {
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
        }

        return node;
    }
    void printTree(Node *node, std::string indent, bool last)
    {
        if (node != nullptr)
        {
            std::cout << indent;

            if (last)
            {
                std::cout << "R----";
                indent += "     ";
            }
            else
            {
                std::cout << "L----";
                indent += "|    ";
            }

            std::cout << node->data << "(h=" << node->height << ")" << std::endl;

            printTree(node->left, indent, false);
            printTree(node->right, indent, true);
        }
    }

    int getHeight(Node *node)
    {
        return node ? node->height : 0;
    }

    Node *createNode(const T &data)
    {
        return new Node(data);
    }

    Node *addToTree(Node *node, T data)
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

        return AVL(node);
    }

    bool searchNode(Node *node, const T &item)
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

    Node *delete_entry(Node *node, T data)
    {
        if (!node)
            return node;

        if (data < node->data)
            node->left = delete_entry(node->left, data);

        else if (data > node->data)
            node->right = delete_entry(node->right, data);

        else
        {
            // if(!node -> right || !node -> left) //check if node has 0 or 1 child
            // {
            //     Node *temp = node -> right? node -> right : node -> left; //assign temp that node to replace later

            //     if(!temp) // In case no children are there temp si `nullptr` "Node is a leaf node"
            //     {
            //         temp = node;
            //         node = nullptr;
            //     }

            //     else
            //         node = temp; // this copies the contents or the single child we assigned temp in line 210

            //     delete temp; // Discard temp
            // }
            // If you can fix above code please do so
            if (!node->left) // only right chld or no child
            {
                Node *temp = node->right;
                delete node;
                return temp;
            }
            else if (!node->right) // only left child
            {
                Node *temp = node->left;
                delete node;
                return temp;
            }
            else // The node has two child nodes
            {
                Node *temp = node->right;

                while (temp->left) // find the succesor of the node
                    temp = temp->left;

                node->data = temp->data;
                node->right = delete_entry(node->right, temp->data);
            }
        }
        if (!node)
            return node;

        node->height = 1 + std::max(getHeight(node->right), getHeight(node->left));

        // return after applying AVL
        return AVL(node);
        // return AVL(node, node->data); working without AVL
    }
};
