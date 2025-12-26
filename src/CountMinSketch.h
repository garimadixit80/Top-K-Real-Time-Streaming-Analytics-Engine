#ifndef COUNT_MIN_SKETCH_H
#define COUNT_MIN_SKETCH_H

#include <bits/stdc++.h>
using namespace std;

class CountMinSketch {
private:
    int depth;
    int width;
    vector<vector<int>> table;
    vector<uint64_t> hashSeeds;

    uint64_t hashKey(const string& key, uint64_t seed) const;

public:
    CountMinSketch(int d, int w);
    void update(const string& key);
    int query(const string& key) const;
};

#endif
