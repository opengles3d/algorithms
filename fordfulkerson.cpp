#include <iostream>
#include <queue>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iomanip>

std::vector<std::vector<int>> gn;//residual net
std::vector<std::vector<int>> fn;//real flow net
std::vector<int> pre;
std::vector<bool> vis;

int n, m;//vertex and edge

bool bfs(int s, int t) {

    for(int i = 0; i <= n; i++) {
        pre[i] = -1;
    }
    
    for(int i = 0; i <= n; i++) {
        vis[i] = false;
    }

    std::queue<int> q;
    vis[s] = true;
    q.push(s);

    while(!q.empty()) {
        int now = q.front();
        q.pop();
        for(int i = 1; i <= n; i++) {
            if(!vis[i] && gn[now][i] > 0) {
                vis[i] = true;
                pre[i] = now;
                if( i == t) {
                    return true;//find one
                }

                q.push(i);
            }
        }
    }

    return false;
}

int ek(int s, int t) {
    int v, w, d, maxflow;
    maxflow = 0;

    while(bfs(s, t)) {
        v = t;
        d = INT_MAX;

        while(v != s) {
            w = pre[v];
            if(d > gn[w][v]) {
                d = gn[w][v];
            }

            v = w;
        }

        maxflow += d;
        v = t;

        while(v != s) {
            w = pre[v];
            gn[w][v] -= d;
            gn[v][w] += d;

            if(fn[v][w] > 0) {
                fn[v][w] -= d;
            } else {
                fn[w][v] += d;
            }

            v = w;
        }
    }

    return maxflow;
}

void print() {
    std::cout << std::endl;
    std::cout << "------Real flow net ----------" << std::endl;
    std::cout << "   ";
    for(int i = 1; i <= n; i++) {
        std::cout << std::setw(7) << "v" << i;
    }

    std::cout << std::endl;

    for(int i = 1; i <= n; i++) {
        std::cout << "v" << i;
        for(int j = 1; j <= n; j++) {
            std::cout << std::setw(7) << fn[i][j] << "   ";
        }

        std::cout << std::endl;
    }
}

int main(int argc, char** argv) {
    std::string str;
	std::fstream f("p.txt");
	getline(f, str);
	std::istringstream ss(str);
	ss >> n; //vertex
    ss >> m; //edge

    pre.resize(n + 1);
    for(int i = 0; i <= n; i++) {
        pre[i] = -1;
    }
    vis.resize(n + 1);
    for(int i = 0; i <= n; i++) {
        vis[i] = false;
    }

    for(int i = 0; i <= n; i++) {
        std::vector<int> row(n + 1);
        gn.push_back(row);
    }

    for(int i = 0; i <= n; i++) {
        std::vector<int> row(n + 1);
        fn.push_back(row);
    }

    for(int i = 1; i <= m; i++) {
        getline(f, str);
	    std::istringstream ss2(str);
        int u, v, w;
        ss2 >> u >> v >> w;
        gn[u][v] += w;
    }

    std::cout << "Max flow: " << ek(1, n) << std::endl;

    print();

    return 0;
}