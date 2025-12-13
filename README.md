# AVL-Trees in C++  
**A fast, generic, self-balancing AVL Tree implementation with a practical dictionary demo**

![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Data Structures](https://img.shields.io/badge/Data_Structures-AVL_Tree-blue)
![License](https://img.shields.io/github/license/c0rRupT9/AVL-Trees)

This repository provides a **templated AVL Tree** class in modern C++ that supports key-value storage, efficient operations, and extra features tailored for real-world use (like case-insensitive string handling).

It's not just a basic textbook example — it includes:
- Proper memory management (recursive destructor — many similar repos leak memory!)
- Insertion, deletion (with full rebalancing), search, prefix search
- Case-insensitive operations for strings
- Pretty ASCII tree printing with height display
- Interactive dictionary application loading ~34k entries

## Features

- **Generic template** — Works with any comparable key type and any value type
- **O(log n) guaranteed** — Insert, search, delete thanks to AVL balancing
- **All four rotations** — LL, RR, LR, RL handled correctly
- **String-specialized functions** — Case-insensitive search & deletion, prefix matching (great for autocomplete/dictionaries)
- **Memory safe** — Full recursive destructor
- **Tree visualization** — Pretty-print the tree structure in ASCII (with optional depth limit)
- **Performance analysis** — Built-in stats comparing height/leaves to theoretical ideals
- **Interactive demo** — Loads a dictionary file and lets you search, prefix-search, delete, and print

## Performance Example (on ~34k dictionary entries)

![Analysis](https://i.ibb.co/27xB8Vp5/image.png)

textSearches are **O(log n)** — much faster than linear scan on a vector!

## Quick Start

```bash
git clone https://github.com/c0rRupT9/AVL-Trees.git
cd AVL-Trees/src
g++ main.cpp -o dictionary
./dictionary
You'll see the interactive menu:
```

Search words (case-insensitive)

Prefix search (e.g., all words starting with "neuro")

Delete entries

Print tree visualization

Note: Update the path variable in main.cpp to point to your dictionary.txt file (a standard English wordlist works great). You can use any text dictionary file with the format:  word    definition.
Usage as a Library
Include ``tree.hpp`` and use like:
```bash
C++#include "tree.hpp"

int main() {
    tree<std::string, std::string> dict;
    dict.insert("hello", "A greeting");
    dict.insert("Hello", "Updated definition");  // Duplicates update value

    dict.searchWord("Hello");  // Case-insensitive lookup
    auto prefixes = dict.vectorWithPrefix("hel");

    for (const auto& word : prefixes) {
        std::cout << word << std::endl;
    }
}
```
## **Sample Output**

### Tree Visualization (partial)
![visual](https://i.ibb.co/Lz75s5vH/image-1.png)

You can even print the whole tree! 

## Interactive Menu
![Menu](https://i.ibb.co/ynzq8ZKt/image-2.png)

## Performance vs. std::map (Red-Black Tree) – Integers (Release Mode)

Benchmarks on 100,000 random integers (12-core CPU):

| Operation   | AVL Tree                  | std::map (Red-Black)      | Winner                  |
|-------------|---------------------------|---------------------------|-------------------------|
| Insert      | ~254 ns per operation     | ~205 ns per operation     | Red-Black (~20% faster) |
| Search      | **~50 ns per operation**  | ~138 ns per operation     | **AVL** (~176% faster)  |

![Menu](https://i.ibb.co/HD1m277f/Benchmark.png)

**AVL shines in search-heavy scenarios** thanks to tighter height bounds (≈1.44 log₂ n vs up to 2 log₂ n).

## **Contributing**
Found a bug? Have an improvement? Feel free to:

Open an issue

Submit a pull request

All contributions and feedback are welcome!
If you find this project useful, please give it a ⭐ — it helps others discover it!

## **License**
MIT License
 
