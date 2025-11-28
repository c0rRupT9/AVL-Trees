#include <iostream>
#include <random>
#include <chrono>
#include "tree.hpp"
const int MAX_VAL = 400;

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
//insert values upto MAX_VAL 400 times
// Test for Random unsequenced insertion 0-399 
// the loop is run 800 times since random number generator can have duplications
// causing the tree to not exactly have 400 nodes
for (int i = 0; i < 800; i++)
{
    Tree.insert(number(MAX_VAL));
}

//Results: 
/*Obtained values:
Nodes: 351
Leaves: 155
Height: 10
Root: 249

Expected values:
Leaves: 176
Height: 11.8595
Root: 200

Divergence:
Leaves divergence: 11.9318 %
Height divergence: 15.6792 %
Root divergence: 24.5 %

Total loss: 18.5272 %*/


// Test for sequential linear insertion set
// for(int i = 0; i < 400; i++)
//     Tree.insert(i);

// Results: 
/*Obtained values:
Nodes: 400
Leaves: 200
Height: 9
Root: 255

Expected values:
Leaves: 200.5
Height: 12.1295
Root: 200

Divergence:
Leaves divergence: 0.249377 %
Height divergence: 25.8008 %
Root divergence: 27.5 %

Total loss: 14.2088 %*/
    Tree.print();
    int N = Tree.numberOfNodes();
    int obtainedNodes = Tree.numberOfNodes();
    int obtainedLeaves = Tree.numberOfLeaves();
    int obtainedHeight = Tree.treeHeight();
    int obtainedRoot = Tree.rootValue();

    // ---- Expected values (theoretical for balanced AVL) ----
    double expectedLeaves = (N + 1) / 2.0;           // leaves half nodes
    double expectedHeight = 1.44 * log2(N + 2) - 0.328; // AVL max height
    double expectedRoot = MAX_VAL / 2.0;               // median-ish for uniform random

    // ---- Compute divergence ----
    double leavesDivergence = std::abs(expectedLeaves - obtainedLeaves);
    double heightDivergence = std::abs(expectedHeight - obtainedHeight);
    double rootDivergence = std::abs(expectedRoot - obtainedRoot);

    double totalLoss = leavesDivergence + heightDivergence + rootDivergence;
    double idealTotal = expectedHeight + expectedLeaves + expectedRoot;

    // ---- Output ----
    std::cout << "Obtained values:\n";
    std::cout << "Nodes: " << obtainedNodes << "\n";
    std::cout << "Leaves: " << obtainedLeaves << "\n";
    std::cout << "Height: " << obtainedHeight << "\n";
    std::cout << "Root: " << obtainedRoot << "\n\n";

    std::cout << "Expected values:\n";
    std::cout << "Leaves: " << expectedLeaves << "\n";
    std::cout << "Height: " << expectedHeight << "\n";
    std::cout << "Root: " << expectedRoot << "\n\n";

    std::cout << "Divergence:\n";
    std::cout << "Leaves divergence: " << (leavesDivergence/expectedLeaves)*100 <<" %" << "\n";
    std::cout << "Height divergence: " << (heightDivergence/expectedHeight)*100 <<" %" << "\n";
    std::cout << "Root divergence: " << (rootDivergence/expectedRoot)*100 <<" %" << "\n\n";

    std::cout << "Total loss: " << (totalLoss/idealTotal)*100 << " %" << "\n";




    return 0;

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
}