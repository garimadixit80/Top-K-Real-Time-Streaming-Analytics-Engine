#ifndef TOP_K_MANAGER_H
#define TOP_K_MANAGER_H

#include <bits/stdc++.h>
using namespace std;

struct Node {
    string key;
    int freq;
};

struct Compare {
    bool operator()(const Node& a, const Node& b) {
        return a.freq > b.freq; // min-heap
    }
};

class TopKManager {
private:
    int K;
    priority_queue<Node, vector<Node>, Compare> minHeap;
    unordered_map<string, int> inHeap;

public:
    TopKManager(int k);
    void process(const string& key, int freq);
    vector<Node> getTopK();
};

#endif
