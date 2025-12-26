#include <bits/stdc++.h>
#include <thread>
using namespace std;

vector<string> generateStream(int n) {
    vector<string> events = {
        "login", "search", "logout", "click", "purchase",
        "scroll", "view", "share"
    };

    vector<string> stream;
    srand(time(0));

    for (int i = 0; i < n; i++) {
        stream.push_back(events[rand() % events.size()]);
    }
    return stream;
}
