#include <bits/stdc++.h>
#include <windows.h>
#include <chrono>
#include "CountMinSketch.h"
#include "TopKManager.h"

using namespace std;

// Forward declaration
vector<string> generateStream(int n);

int main()
{
    CountMinSketch cms(4, 1000);
    TopKManager topk(3);

    vector<string> stream = generateStream(50);

    // 🔹 ADDITION: exact frequency counter (ground truth)
    unordered_map<string, int> actualCount;

    for (const string &event : stream)
    {
        // 🔹 ADDITION: update exact count
        actualCount[event]++;

        cms.update(event);
        int freq = cms.query(event);
        topk.process(event, freq);

        Sleep(50);
    }

    cout << "\nTop-K Events (CMS Estimate):\n";
    auto result = topk.getTopK();
    for (auto &node : result)
    {
        cout << node.key << " -> " << node.freq << endl;
    }

    // 🔹 ADDITION: print actual frequencies
    cout << "\nActual Frequencies:\n";
    for (auto &p : actualCount)
    {
        cout << p.first << " -> " << p.second << endl;
    }

    return 0;
}
