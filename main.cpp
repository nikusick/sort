#include <iostream>
#include <vector>
#include <conio.h>

using Value = double;
using namespace std;

vector <Value> losers;
vector <Value> winners;
Value tree[7];


void tree_sort(int pos, vector<Value>& vec) {
    int left = pos * 2 + 1;
    int right = pos * 2 + 2;
    if (tree[right] < tree[left]) {
        tree[pos] = tree[right];
        if (pos != 0) {
            if (!vec.empty()) {
                tree[right] = vec[0];
                vec.erase(vec.begin());
            }
        }
        else {
            tree_sort(2, vec);
            if (tree[pos] > tree[right]) {
                swap(tree[pos], tree[right]);
            }
            if (winners.empty() || tree[pos] >= winners.back()) {
                winners.push_back(tree[pos]);
            }
            else {
                losers.push_back(tree[pos]);
            }
        }
    }
    else {
        tree[pos] = tree[left];
        if (pos != 0) {
            if (!vec.empty()) {
                tree[left] = vec[0];
                vec.erase(vec.begin());
            }
        }
        else {
            tree_sort(1, vec);
            if (tree[pos] > tree[left]) {
                swap(tree[pos], tree[left]);
            }
            if (winners.empty() || tree[pos] >= winners.back()) {
                winners.push_back(tree[pos]);
            }
            else {
                losers.push_back(tree[pos]);
            }
        }
    }
}

vector<Value>& tournament_sort(vector<Value>& vec) {
    tree_sort(1, vec);
    tree_sort(2, vec);
    tree_sort(0, vec);
    return vec;
}



int main() {
    vector<Value> vec = {5, 4, 3, 2, 1, 0, -1};
    for (int i = 3; i < 7; ++i) {
        tree[i] = vec[i - 3];
    }
    vec.erase(vec.begin());
    vec.erase(vec.begin());
    vec.erase(vec.begin());
    vec.erase(vec.begin());
    while (true) {
        while (!vec.empty()) {
            tournament_sort(vec);
            for (auto &&item: winners) {
                cout << item << " ";
            }
            cout << endl;
            for (auto &&item: losers) {
                cout << item << " ";
            }
        }
        vec.insert(vec.end(), winners.begin(), winners.end());
        vec.insert(vec.end(), losers.begin(), losers.end());
        for (auto &&item: vec) {
            cout << item << " ";
        }
        if (winners.size() != vec.size()) {
            break;
        }
        winners.clear();
        losers.clear();

    }
    for (auto &&item: vec) {
        cout << item << " ";
    }
    return 0;
}
