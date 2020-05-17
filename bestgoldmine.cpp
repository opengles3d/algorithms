#include <iostream>
#include <vector>
#include <algorithm>

int bestGoldMining(int w, int n, std::vector<int>& p, std::vector<int>& g) {
    std::vector<std::vector<int>> rt;
    for(int i = 0; i <= g.size() + 1; i++) {
        std::vector<int> r (w + 1);
        rt.push_back(r);
    }

    for(int i = 1; i <= g.size(); i++) {
        for(int j = 1; j <= w; j++) {
            if (j < p[i - 1]) {
                rt[i][j] = rt[i - 1][j];
            } else {
                rt[i][j] = std::max(rt[i - 1][j], rt[i - 1][j - p[i - 1]] + g[i - 1]);
            }
        }
    }

    return rt[g.size()][w];
} 

int main(int argc, char** argv) {
    int w = 10;
    std::vector<int> p {5, 5, 3, 4, 3};
    std::vector<int> g {400, 500, 200, 300, 350};

    std::cout << bestGoldMining(w, g.size(), p, g);
}