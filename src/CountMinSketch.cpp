#include "CountMinSketch.h"

CountMinSketch::CountMinSketch(int d, int w)
    : depth(d), width(w) {
    table.assign(depth, vector<int>(width, 0));

    // Generate random seeds
    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    for (int i = 0; i < depth; i++) {
        hashSeeds.push_back(rng());
    }
}

uint64_t CountMinSketch::hashKey(const string& key, uint64_t seed) const {
    uint64_t h = hash<string>{}(key);
    return (h ^ seed) % width;
}

void CountMinSketch::update(const string& key) {
    for (int i = 0; i < depth; i++) {
        int idx = hashKey(key, hashSeeds[i]);
        table[i][idx]++;
    }
}

int CountMinSketch::query(const string& key) const {
    int result = INT_MAX;
    for (int i = 0; i < depth; i++) {
        int idx = hashKey(key, hashSeeds[i]);
        result = min(result, table[i][idx]);
    }
    return result;
}
