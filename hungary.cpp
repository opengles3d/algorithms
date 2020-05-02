#include <iostream>
#include <queue>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iomanip>

std::vector<int> match;
std::vector<bool> vis;
int top;

struct Vertex{
    int first;
};

std::vector<Vertex> V;

struct Edge{
    int v;
    int next;
};

std::vector<Edge> E;

void init(int n, int m) {
    int total = m + n;
    V.resize(total + 1);
    for(int i = 0; i <= total; i++) {
        V[i].first = -1;
    }

    match.resize(total + 1);
    for(int i = 0; i <= total; i++) {
        match[i] = 0;
    }

    vis.resize(total + 1);
    E.resize(m * n * 2);

    top = 0;
}

void add(int u, int v) {
    E[top].v = v;
    E[top].next = V[u].first;
    V[u].first = top++;
}

void printg(int n) {
    std::cout << "------------Adjacency table--------\n";
	for (int i = 1; i <= n; i++) {
		std::cout << "v" << i << "  [" << V[i].first;
		for (int j = V[i].first; ~j; j = E[j].next) {
			std::cout << "]---[" << E[j].v << " " << E[j].next;
		}
		std::cout << "]" << std::endl;
	}
}

void printing(int n) {
    std::cout << "------------Matched as below:-------------" << std::endl;
    for(int i = 1; i<= n; i++) {
        if(match[i]) {
            std::cout << i << "--" << match[i] << std::endl;
        }
    }
}

bool maxmatch(int u) {
    int v;
    for(int j = V[u].first; ~j; j = E[j].next) {
        v = E[j].v;
        if(!vis[v]) {
            vis[v] = true;
            if(!match[v] || maxmatch(match[v])) {
                match[u] = v;
                match[v] = u;
                return true;
            }
        }
    }

    return false;
}

int main(int argc, char** argv) {

	std::string str;
	std::fstream f("t.txt");
	getline(f, str);
	std::istringstream ss(str);
    int n;
    int m;
	ss >> m; //female
	ss >> n; //male
    init(m, n);
    int total = m + n;

    int u = 0, v = 0;
	while (true) {
		getline(f, str);
		std::istringstream ss2(str);
		ss2 >> u >> v;
		if (u == -1 && v == -1) {
			break;
		}
		add(u, v);
        add(v, u);
	}

    std::cout << std::endl;
    printg(total);

    int num = 0;
    for(int i = 1; i <= m; i++) {
        for(int j = 0; j <= total; j++) {
            vis[j] = false; 
        }

        if(maxmatch(i)) {
            num++;
        }
    }

    std::cout << "Max match number:" << num << std::endl;
    
    printing(m);

    return 0;
}