#include <iostream>
#include <vector>

using Value = double;
using namespace std;

struct Cell {
    Value value = 0;
    bool exist = false;
};


vector <Value> losers;
vector <Value> winners;
Cell tree[7];


void add_to_win_or_los() {
    if (winners.empty() || tree[0].value >= winners.back() && tree[0].exist) {
        winners.push_back(tree[0].value);
    }
    else if (tree[0].exist) {
        losers.push_back(tree[0].value);
    }
    tree[0].exist = false;
}


void tree_sort(int pos, vector<Value>& vec) {
    int left = pos * 2 + 1;
    int right = pos * 2 + 2;
    int mini;
    if ((tree[left].value > tree[right].value || !tree[left].exist) && tree[right].exist) {
        mini = right;
    }
    else if (tree[left].exist) {
        mini = left;
    }
    else {
        if (pos == 0) {
            add_to_win_or_los();
        }
        return;
    }

    swap(tree[pos], tree[mini]);
    if (pos == 0) {
        tree_sort(mini, vec);
        if ((tree[pos].value > tree[mini].value) && tree[mini].exist) {
            swap(tree[pos], tree[mini]);
        }
        add_to_win_or_los();
    }
    else {
        if (!vec.empty()) {
            tree[mini].value = vec[0];
            tree[mini].exist = true;
            vec.erase(vec.begin());
            if (tree[mini].value < tree[pos].value) {
                swap(tree[mini].value, tree[pos].value);
            }
        }
        else {
            tree[mini].exist = false;
        }
    }
}

vector<Value>& tournament_sort(vector<Value>& vec) {
    tree_sort(1, vec);
    tree_sort(2, vec);
    while(tree[0].exist || tree[1].exist || tree[2].exist) {
        tree_sort(0, vec);
    }
    return vec;
}


void fill_tree(vector<Value>& vec) {
    for (int i = 0; i < 3; ++i) {
        Cell el;
        tree[i] = el;
    }
    for (int i = 3; i < 7; ++i) {
        Cell el;
        el.value = vec[0];
        el.exist = true;
        vec.erase(vec.begin());
        tree[i] = el;
    }
}



int main() {
    vector<Value> vec = {76, 90, 79, 51, 79, 59, 0, 89, 0, 75, 34, 20, 48, 50, 2, 72, 3, 0, 16, 22, 84, 8, 82, 84,
                         93, 3, 87, 27, 58, 93, 84, 96, 10, 48, 66, 78, 66, 17, 54, 27, 87, 7, 89, 54, 39, 78, 38,
                         40, 54, 19, 39, 25, 63, 62, 80, 88, 16, 43, 13, 87, 61, 74, 74, 46, 58, 20, 10, 97, 72, 35,
                         85, 26, 18, 10, 26, 50, 8, 49, 24, 48, 29, 1, 40, 38, 66, 85, 43, 72, 77, 22, 61, 92, 1, 87,
                         83, 69, 82, 86, 92, 5, 92, 27, 54, 13, 53, 21, 56, 85, 11, 52, 55};
    while(true) {
        tournament_sort(vec);
        vec.insert(vec.end(), losers.begin(), losers.end());
        vec.insert(vec.end(), winners.begin(), winners.end());
        if (losers.empty() && winners.size() == vec.size()) {
            break;
        }
        winners.clear();
        losers.clear();
        fill_tree(vec);
    }
    for (auto &&item: vec) {
        cout << item << " ";
    }
    return 0;
}
