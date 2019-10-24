#include <iostream>
#include <vector>

using namespace std;

void subset(int *S, int n) {
    int i, j, idx;

    for (i = 0; i < (1 << n); ++i) {
        j = i;
        idx = 0;
        while (j > 0) {
            if (j & 1)
                cout << S[idx] << ' ';
            idx++;
            j >>= 1;
        }
        cout << endl;
    }
}

vector<vector<int>> subset_vec(int *S, int n) {
    vector<vector<int>> res;
    int curlen;
    if (n >= 1) {
        res.push_back(vector<int>());
        res.push_back(vector<int>(1, S[0]));
    }
    for (int i = 1; i < n; ++i) {
        curlen = res.size();
        for (int j = 0; j < curlen; ++j) {
            vector<int> tmp(res[j]);
            tmp.push_back(S[i]);
            res.push_back(tmp);
        }
    }
    return res;
}

int main() {
    int n = 3;
    int S[20];
    vector<vector<int>> res;
    for (int i = 0; i < n; ++i) {
        S[i] = i + 1;
    }
    cout << "Method 1" << endl;
    subset(S, n);

    cout << "Method 2" << endl;
    res = subset_vec(S, n);
    for (int i = 0; i < res.size(); ++i) {
        for (int j = 0; j < res[i].size(); ++j) {
            cout << res[i][j] << ' ';
        }
        cout << endl;
    }
    return 0;
}