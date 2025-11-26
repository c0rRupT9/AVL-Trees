#include <iostream>
#include "tree.cpp"


int main()
{
    tree<int> Tree;

    Tree.insert(5);
    Tree.insert(10);
    Tree.insert(7);
    Tree.insert(8);

    if(Tree.search(10))
    {
        std::cout << "Found";
    }
    if(!Tree.search(11))
    {
        std::cout << "Not Found";
    }
    
    return 0;
}