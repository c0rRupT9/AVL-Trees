#pragma once

#include <iostream>
#include <vector>

template <class T, class F>
class tree
{
private:
    struct Node
    {
        T data;
        F value;
        int height = 1;
        Node *left = nullptr;
        Node *right = nullptr;

        Node(const T &data, const F &value) : data(data), value(value) {}
    };

    Node *root;

public:
    tree() : root(nullptr) {}
    ~tree() { deleteTree(root); }

    int treeHeight() const { return root ? root->height : 0; }
    T rootValue() const { return root ? root->data : T(); }
    int numberOfLeaves() const { return countLeaves(root); }
    int numberOfNodes() const { return countNodes(root); }

    T findMax() const
    {
        Node *temp = root;
        if (!temp)
            return T();
        while (temp->right)
            temp = temp->right;
        return temp->data;
    }
    T findMin() const
    {
        Node *temp = root;
        if (!temp)
            return T();
        while (temp->left)
            temp = temp->left;
        return temp->data;
    }

    void insert(const T &data, const F &value)
    {
        root = addToTree(root, data, value);
    }

    bool search(const T &item) const
    {
        return searchNodeBool(root, item);
    }

    // print tree
    void print(int n) const
    {
        printTree(root, "", true, n);
    }

    void deleteNode(const T &data)
    {
        int nodes = numberOfNodes();
        root = delete_entry(root, data);

        if (numberOfNodes() < nodes)
            std::cout << "Operation Sucessful\n";
        else
            std::cout << "Node not found!\n";
    }

    void searchWord(const T &key) const
    {

        Node *n;
        if constexpr (std::is_same<T, std::string>::value)
        {
            n = searchNodeString(root, key);
        }
        else
            n = searchNode(root, key);
        if (n)
            std::cout << "\n"
                      << n->data << " : " << n->value << std::endl;
        else
            std::cout << "\nNot found: " << key << std::endl;
    }

    // This function is only available for trees with type tree<std::string, any>
    typename std::enable_if<std::is_same<T, std::string>::value, std::vector<std::string>>::type
    vectorWithPrefix(std::string prefix) const
    {
        std::vector<std::string> nodes;
        collectWithPrefix(root, prefix, nodes);
        return nodes;
    }

private:
    // This function discards the rules of BST with complexity of O(n)
    void collectWithPrefix(Node *node, const std::string prefix, std::vector<std::string> &arr) const
    {
        if (!node)
            return;
        collectWithPrefix(node->left, prefix, arr);
        if (!node->data.empty() && lowerCase(node->data).compare(0, prefix.size(), lowerCase(prefix)) == 0)
            arr.push_back(node->data);
        collectWithPrefix(node->right, prefix, arr);
    }

    Node *searchNode(Node *node, const T &key) const
    {
        if (!node)
            return nullptr;
        if (key == node->data)
            return node;
        if (key < node->data)
            return searchNode(node->left, key);
        return searchNode(node->right, key);
    }
    std::string lowerCase(const std::string &input) const
    {
        std::string output;
        for (char c : input)
            output += (tolower((unsigned char)c));
        return output;
    }

    typename std::enable_if<std::is_same<T, std::string>::value, Node *>::type
    searchNodeString(Node *node, const std::string &key) const
    {
        if (!node)
            return nullptr;
        std::string lowerKey = lowerCase(key);
        std::string lowerData = lowerCase(node->data);
        if (lowerData == lowerKey)
            return node;
        if (lowerKey > lowerData)
            return searchNodeString(node->right, key);

        return searchNodeString(node->left, key);
    }

    bool searchNodeBool(Node *node, const T &item) const
    {
        return searchNode(node, item) != nullptr;
    }

    void deleteTree(Node *node)
    {
        if (!node)
            return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

    int getBalance(Node *node) const
    {
        return node ? (getHeight(node->left) - getHeight(node->right)) : 0;
    }

    int countLeaves(Node *node) const
    {
        if (!node)
            return 0;
        if (!node->left && !node->right)
            return 1;
        return countLeaves(node->left) + countLeaves(node->right);
    }
    int countNodes(Node *node) const
    {
        if (!node)
            return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    Node *rotateLeft(Node *z)
    {
        Node *y = z->right;
        Node *C2 = y->left;
        /*
                    z
                   / \                      y
                  C1  y                   /   \
                     / \    ----->       z     x
                    C2  x               / \   / \
                       / \             C1 C2 C3 C4
                      C3 C4

        */

        y->left = z;
        z->right = C2;

        z->height = 1 + ((getHeight(z->left) > getHeight(z->right)) ? getHeight(z->left) : getHeight(z->right));
        y->height = 1 + ((getHeight(z->left) > getHeight(z->right)) ? getHeight(z->left) : getHeight(z->right));

        return y;
    }

    Node *rotateRight(Node *z)
    {
        Node *y = z->left;
        Node *C2 = y->right;
        /*
                    z
                   / \
                  y  C1                  y
                 / \    --------->     /   \
                x  C2                 x     z
               / \                   / \   / \
              C3 C4                 C3 C4 C2 C1
        */

        y->right = z;
        z->left = C2;

        z->height = 1 + ((getHeight(z->left) > getHeight(z->right)) ? getHeight(z->left) : getHeight(z->right));
        y->height = 1 + ((getHeight(z->left) > getHeight(z->right)) ? getHeight(z->left) : getHeight(z->right));

        return y;
    }

    Node *AVL(Node *node)
    {
        if (!node)
            return node;
        int balanceFactor = getBalance(node);

        // Left Heavy case
        if (balanceFactor > 1)
        {
            // if left heavy is right heavy too LR case
            if (getBalance(node->left) < 0)
                node->left = rotateLeft(node->left);
            // The function has too do a left rotation in anycase so its left open to reduce lines
            return rotateRight(node);
        }
        // Right Heavy
        if (balanceFactor < -1)
        {
            // RL case
            if (getBalance(node->right) > 0)
                node->right = rotateRight(node->right);
            // RR case
            return rotateLeft(node);
        }
        return node;
    }

    void printTree(Node *node, std::string indent, bool last, int depth) const
    {
        if (node == nullptr)
            return;

        if (depth == 0)
            return;

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

        std::cout << node->data << " (h=" << node->height << ")\n";

        printTree(node->left, indent, false, depth - 1);
        printTree(node->right, indent, true, depth - 1);
    }

    int getHeight(Node *node) const
    {
        return node ? node->height : 0;
    }

    Node *createNode(const T &data, const F &value)
    {
        return new Node(data, value);
    }

    Node *addToTree(Node *node, const T &data, const F &value)
    {
        if (!node)
            return createNode(data, value);

        if (data < node->data)
            node->left = addToTree(node->left, data, value);
        else if (data > node->data)
            node->right = addToTree(node->right, data, value);
        else
        {
            // duplicate key: update value (The program was aborting prematurely, DUMP files indicated this point) where we return node with dup val
            // before
            node->value = value;
            return node;
        }

        node->height = 1 + ((getHeight(node->left) > getHeight(node->right)) ? getHeight(node->left) : getHeight(node->right));
        return AVL(node);
    }

    Node *delete_entry(Node *node, const T &data)
    {
        // Only compiled when T is std::string
        if constexpr (std::is_same<T, std::string>::value)
        {
            if (!node)
                return nullptr;
            std::string lowerKey = lowerCase(data);
            std::string lowerData = lowerCase(node->data);
            if (lowerKey < lowerData)
                node->left = delete_entry(node->left, data);
            else if (lowerKey > lowerData)
                node->right = delete_entry(node->right, data);
            else
            {
                // Check if node has no child or one child
                if (!node->left || !node->right)
                {
                    Node *temp = node->left ? node->left : node->right;
                    delete node;
                    return temp;
                }
                // If it has both childern then find the succesor to the node
                else
                {
                    Node *temp = node->right;
                    // The next successor will be the left most node to the right subtree of node
                    while (temp->left)
                        temp = temp->left;
                    node->data = temp->data;
                    node->value = temp->value;
                    // delete the left most node in right subtree of node ie. succesor
                    node->right = delete_entry(node->right, temp->data);
                }
            }

            node->height = 1 + ((getHeight(node->left) > getHeight(node->right)) ? getHeight(node->left) : getHeight(node->right));
            return AVL(node);
        }
        else
        {
            if (!node)
                return nullptr;

            if (data < node->data)
                node->left = delete_entry(node->left, data);
            else if (data > node->data)
                node->right = delete_entry(node->right, data);
            else
            {
                if (!node->left || !node->right)
                {
                    Node *temp = node->left ? node->left : node->right;
                    delete node;
                    return temp;
                }
                else
                {
                    Node *temp = node->right;
                    while (temp->left)
                        temp = temp->left;
                    node->data = temp->data;
                    node->value = temp->value;
                    node->right = delete_entry(node->right, temp->data);
                }
            }

            node->height = 1 + ((getHeight(node->left) > getHeight(node->right)) ? getHeight(node->left) : getHeight(node->right));
            return AVL(node);
        }
    }
};
