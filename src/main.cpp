// To report bugs mail me at corrupt.dev.git@gmail.com
#include "../include/tree.hpp"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <chrono>
#include <cmath>

// Vector was used here to compare speeds only
// If you want to speed the code up directly input the key and vlaue into the tree


std::vector<std::pair<std::string, std::string>> dict;
std::string path = "../documents/dictionary.txt"; // please change it according to your needs

bool isWordChar(char c) { return std::isalpha(static_cast<unsigned char>(c)) || c == '-'; }

bool isNewEntry(const std::string &line)
{
    if (line.empty()) return false;
    if (!std::isalpha((unsigned char)(line[0]))) return false;

    size_t i = 0;
    while (i < line.size() && isWordChar(line[i])) ++i;

    if (i == line.size()) return true;
    if (line[i] == ' ') return true;
    if (std::ispunct((unsigned char)(line[i]))) return true;
    return false;
}

void readFile()
{
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << path << "\n";
        return;
    }

    std::string line;
    std::string currentKey, currentValue;

    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        if (isNewEntry(line))
        {
            if (!currentKey.empty()) dict.emplace_back(currentKey, currentValue);

            std::istringstream ss(line);
            ss >> currentKey;
            std::string rest;
            std::getline(ss, rest);
            if (!rest.empty() && rest.front() == ' ') rest.erase(0,1);
            currentValue = rest;
        }
        else
        {
            if (!currentKey.empty())
            {
                if (!currentValue.empty()) currentValue += ' ';
                currentValue += line;
            }
        }
    }

    if (!currentKey.empty()) dict.emplace_back(currentKey, currentValue);
    file.close();
}

void insertToTree(const std::vector<std::pair<std::string, std::string>>& keys, tree<std::string, std::string>& object)
{
    for (const auto &p : keys) object.insert(p.first, p.second);
}



int main()
{
    tree<std::string, std::string> Tree;

    std::cout << "Getting things ready! \n Initializing...\n Starting Phase 1 (reading the file)\n";
    auto start = std::chrono::high_resolution_clock::now();

    readFile();

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> timeToInit = end - start;
    std::cout << "Phase 1 completed in " << timeToInit.count() << " seconds\n";
    std::cout << "Entries parsed: " << dict.size() << "\n";

    std::cout << "Starting Phase 2 (inserting values into the tree)\n";
    start = std::chrono::high_resolution_clock::now();
    insertToTree(dict, Tree);
    end = std::chrono::high_resolution_clock::now();
    timeToInit = end - start;
    std::cout << "Phase 2 completed in " << timeToInit.count() << " seconds\n\n";

    int N = Tree.numberOfNodes();
    int obtainedNodes = N;
    int obtainedLeaves = Tree.numberOfLeaves();
    int obtainedHeight = Tree.treeHeight();
    std::string obtainedRoot = Tree.rootValue();

    double expectedLeaves = (N + 1) / 2.0;
    double expectedHeight = N > 0 ?  std::log2(N): 0.0;
    std::string expectedRoot = dict[(N/2)].first;

    double leavesDivergence = std::abs(expectedLeaves - obtainedLeaves);
    double heightDivergence = std::abs(expectedHeight - obtainedHeight);

    double totalLoss = leavesDivergence + heightDivergence;
    double idealTotal = expectedHeight + expectedLeaves;


    std::cout << "\n AVL Performance Analysis \n";
    std::cout << "Obtained values:\n";
    std::cout << "Nodes: " << obtainedNodes 
    << "\nLeaves: " << obtainedLeaves 
    << "\nHeight: " << obtainedHeight 
    << "\nRoot: " << obtainedRoot << "\n\n";

    std::cout << "Expected values:\nLeaves: " << expectedLeaves << "\nHeight: " << expectedHeight << "\nRoot: " << expectedRoot << "\n\n";

    if (expectedLeaves > 0)
        std::cout << "Leaves divergence: " << (leavesDivergence/expectedLeaves)*100 <<" %\n";
    if (expectedHeight > 0)
        std::cout << "Height divergence: " << (heightDivergence/expectedHeight)*100 <<" %\n\n";

    if (idealTotal > 0)
        std::cout << "Total loss: " << (totalLoss/idealTotal)*100 << " %\n";

    std::cout << "Estimated search iterations (log2 nodes): " << (obtainedNodes>0 ? std::log2(obtainedNodes) : 0) << "\n";
    std::cout << "Real iterations can range from " << 1 << " to " << obtainedHeight <<  "\n\n";

    std::string value = "";
    int input;
    std::vector<std::string> nodes;
    // To print the complete Tree use 
    //Tree.print();
    // Please avoid it, can cause bottlenecks. 
    while(true)
    {

        
        std::cout << "\n=====================================\n";
        std::cout << "       AVL TREE BASED DICTIONARY         \n";
        std::cout << "=====================================\n";

        
        std::cout << "Please select an option (enter the integer):\n";
        std::cout << " 1. Search a Value\n";
        std::cout << " 2. Search with a Specific Prefix\n";
        std::cout << " 3. Delete a Node\n";
        std::cout << " 4. (Debug) Print the Tree, to specific depth(n)\n";
        std::cout << " 5. Exit\n\n";


        
        
        std::cout << "-------------------------------------\n";
        std::cout << "Enter choice: ";

        if(!(std::cin >> input))
        { 
            std::cout << "Please!\n";
            break;
        }
        switch (input)
        {
        case 1:
            while(true)
            {
                std::cout << "Please enter the word to search for (Exit: quit()): ";
                if (!(std::cin >> value)) break;
                if (value == "quit()") break;
                Tree.searchWord(value);
            }
            break;
        case 2:
            std::cout << "Please enter the prefix: ";
            if(!(std::cin >> value)) break;
            nodes = Tree.vectorWithPrefix(value);
            for(auto &a: nodes) std::cout << a << " ";
            std::cout << std::endl;
            break;

        case 3:
            std::cout << "please enter The word: ";
            if(!(std::cin >> value)) break;
            Tree.deleteNode(value);
            break;

        case 5:
            std::cout << "Exitting. Thankyou...\n";
            return 0;
            break;
        case 4:
            int n;
            std::cout << "Please enter the value of n: enter -1 to print full tree: ";
            std::cin >> n;    
            Tree.print(n);
            break;
        default:
            std::cout << "Please enter a valid value!" << std::endl;
            break;
        }

    }
    return 0;
}