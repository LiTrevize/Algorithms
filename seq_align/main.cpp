#include <iostream>
#include <fstream>

using namespace std;

int OPT[1000][1000];

void seq_align(char *x, char *y, int n, int m, int gap_cost, int mismatch[128][128]) {
    for (int i = 0; i <= n; ++i) {
        OPT[i][0] = i * gap_cost;
    }
    for (int j = 0; j <= m; ++j) {
        OPT[0][j] = j * gap_cost;
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            int a, b, c;
            a = mismatch[x[i - 1]][y[j - 1]] + OPT[i - 1][j - 1];
            b = gap_cost + OPT[i - 1][j];
            c = gap_cost + OPT[i][j - 1];
            if (a < b && a < c)
                OPT[i][j] = a;
            else if (b < c)
                OPT[i][j] = b;
            else
                OPT[i][j] = c;
        }
    }
}

int main() {
    int gap_cost = 1;
    int n, m;
    char x[1000], y[1000];
    int mismatch[128][128];
    for (int i = 0; i < 128; ++i) {
        for (int j = 0; j < 128; ++j) {
            if (i == j) mismatch[i][j] = 0;
            else mismatch[i][j] = 1;
        }
    }

    ifstream infile;
    ofstream outfile;
    infile.open("test.in");
    outfile.open("test.out");

    infile >> n >> m;
    for (int i = 0; i < n; ++i) {
        infile >> x[i];
    }
    for (int j = 0; j < m; ++j) {
        infile >> y[j];
    }

    seq_align(x, y, n, m, gap_cost, mismatch);

    outfile << OPT[n][m];

    infile.close();
    outfile.close();

    return 0;
}