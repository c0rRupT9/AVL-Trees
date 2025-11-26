#include <iostream>
#include "tree.hpp"


int main()
{
    tree<int> Tree;
    int input;

    // while(1)
    // {
    //             Tree.print();
    //     std::cout << "Enter: " << std::endl;
    //     std::cin >> input;
    //     if(input == 6112)
    //         return 0;
    //     if(input == 6181)
    //     {
    //         std::cin >> input;
    //         Tree.deleteNode(input);
    //         continue;
    //     }
    //     Tree.insert(input);

    // }

    Tree.insert(1);Tree.insert(2);Tree.insert(3);Tree.insert(4);Tree.insert(5);Tree.insert(6);Tree.insert(7);Tree.insert(8);
    Tree.print();
    Tree.deleteNode(5);
    Tree.print();
    Tree.deleteNode(4);
    Tree.print();
    
    return 0;
}