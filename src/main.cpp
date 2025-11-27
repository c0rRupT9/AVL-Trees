#include <iostream>
#include <random>
#include <chrono>
#include "tree.hpp"

int number(int num)
{
    int seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 mt(seed);
    std::uniform_int_distribution distance (0, num -1);
    return distance(mt);
}

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



// Tree.insert(50);
// Tree.insert(30);
// Tree.insert(20);
// Tree.insert(40);
// Tree.insert(70);
// Tree.insert(60);
// Tree.insert(80);

// Tree.insert(5);
// Tree.insert(2);
// Tree.insert(8);
// Tree.insert(1);
// Tree.insert(3);
// Tree.insert(7);
// Tree.insert(9);

// Tree.insert(50);
// Tree.insert(30);
// Tree.insert(70);
// Tree.insert(20);
// Tree.insert(40);
// Tree.insert(60);
// Tree.insert(80);
// Tree.insert(10);
// Tree.insert(25);
// Tree.insert(35);
// Tree.insert(45);
// Tree.insert(55);
// Tree.insert(65);
// Tree.insert(75);
// Tree.insert(85);

// Tree.insert(10);
// Tree.insert(5);
// Tree.insert(7);
// Tree.insert(10);
// Tree.insert(5);
// Tree.insert(3);

// Tree.insert(10);
// Tree.insert(8);
// Tree.insert(9);
    
// Tree.insert(1);
// Tree.insert(2);
// Tree.insert(3);
// Tree.insert(4);
// Tree.insert(5);
// Tree.insert(6);
// Tree.insert(7);
// Tree.insert(8);
// Tree.print();
// Tree.deleteNode(5);
// Tree.print();
// Tree.deleteNode(4);
// Tree.print();

for (int i = 0; i < 400; i++)
{
    Tree.insert(number(10000));
}
Tree.print();
std::cout << "Number of nodes " << Tree.numberOfNodes() << std::endl;
std::cout << "Number of leaves " << Tree.numberOfLeaves() << std::endl;



    return 0;
}