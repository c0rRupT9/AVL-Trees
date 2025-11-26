#include <iostream>
#include "tree.hpp"


int main()
{
    tree<int> Tree;
    int input, i=0;

    while(i < 10)
    {
        Tree.insert(i);
        Tree.print();
        i++;
    }
    
    return 0;
}