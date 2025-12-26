#include "TopKManager.h"

TopKManager::TopKManager(int k) : K(k) {}

void TopKManager::process(const string& key, int freq) {
    if (inHeap.count(key)) {
        // Lazy update: insert new value
        minHeap.push({key, freq});
        inHeap[key] = freq;
        return;
    }

    if ((int)minHeap.size() < K) {
        minHeap.push({key, freq});
        inHeap[key] = freq;
    } 
    else if (freq > minHeap.top().freq) {
        inHeap.erase(minHeap.top().key);
        minHeap.pop();
        minHeap.push({key, freq});
        inHeap[key] = freq;
    }
}

vector<Node> TopKManager::getTopK() {
    vector<Node> result;
    unordered_set<string> seen;

    while (!minHeap.empty() && result.size() < K) {
        Node cur = minHeap.top();
        minHeap.pop();

        // Accept only the latest valid frequency for each key
        if (!seen.count(cur.key) && inHeap[cur.key] == cur.freq) {
            seen.insert(cur.key);
            result.push_back(cur);
        }
    }

    reverse(result.begin(), result.end());
    return result;
}
