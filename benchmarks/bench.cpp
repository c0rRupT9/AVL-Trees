#include <benchmark/benchmark.h>
#include <random>
#include <map>
#include "tree.hpp"  // AVL Header

static constexpr size_t N = 100'000;  // 100k elements
static constexpr size_t NUM_SEARCHES = 10'000;  // For search benchmarks

std::vector<int> generate_keys() {
    std::vector<int> keys(N);
    for (size_t i = 0; i < N; ++i) keys[i] = static_cast<int>(i);
    std::mt19937 gen(42);
    std::shuffle(keys.begin(), keys.end(), gen);
    return keys;
}

static const auto keys = generate_keys();
static std::vector<int> search_keys = []() {
    std::vector<int> sk(N);
    for (size_t i = 0; i < N; ++i) sk[i] = static_cast<int>(i);
    std::mt19937 gen(123);
    std::shuffle(sk.begin(), sk.end(), gen);
    sk.resize(NUM_SEARCHES);
    return sk;
}();

// AVL Insertion
static void BM_AVL_Int_Insert(benchmark::State& state) {
    for (auto _ : state) {
        tree<int, int> avl;
        for (size_t i = 0; i < N; ++i) {
            avl.insert(keys[i], keys[i]);  // key and value same for simplicity
        }
        benchmark::DoNotOptimize(avl);
    }
}

// std::map (Red-Black) Insertion
static void BM_RB_Int_Insert(benchmark::State& state) {
    for (auto _ : state) {
        std::map<int, int> rb;
        for (size_t i = 0; i < N; ++i) {
            rb[keys[i]] = keys[i];
        }
        benchmark::DoNotOptimize(rb);
    }
}

// AVL Search (use a fast public method - add this if needed, see below)
static void BM_AVL_Int_Search(benchmark::State& state) {
    tree<int, int> avl;
    for (size_t i = 0; i < N; ++i) avl.insert(keys[i], keys[i]);

    for (auto _ : state) {
        for (int key : search_keys) {
            auto val = avl.benchmarkFind(key);  // Fast non-printing lookup
            benchmark::DoNotOptimize(val);
        }
    }
    state.SetItemsProcessed(state.iterations() * NUM_SEARCHES);
}

// std::map Search
static void BM_RB_Int_Search(benchmark::State& state) {
    std::map<int, int> rb;
    for (size_t i = 0; i < N; ++i) rb[keys[i]] = keys[i];

    for (auto _ : state) {
        for (int key : search_keys) {
            auto it = rb.find(key);
            benchmark::DoNotOptimize(it);
        }
    }
    state.SetItemsProcessed(state.iterations() * NUM_SEARCHES);
}

BENCHMARK(BM_AVL_Int_Insert);
BENCHMARK(BM_RB_Int_Insert);
BENCHMARK(BM_AVL_Int_Search);
BENCHMARK(BM_RB_Int_Search);