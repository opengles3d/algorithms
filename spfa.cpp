#include <iostream>
#include <queue>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iomanip>

int top;
std::vector<int> dist;
std::vector<int> pre;
std::vector<int> c;
std::vector<bool> vis;
int n;
int m;
int maxflow;

struct Vertex {
	int first;
};

std::vector<Vertex> V;

struct Edge {
	int v;
	int next;
	int cap;
	int flow;
	int cost;
};

std::vector<Edge> E;

void init() {
	V.resize(n + 1);
	for (int i = 0; i <= n; i++) {
		V[i].first = -1;
	}

	pre.resize(n + 1);
	E.resize(2 * (m + 1));

	dist.resize(n + 1);
	c.resize(n + 1);
	vis.resize(n + 1);

	top = 0;
	maxflow = 0;
}

void add_edge(int u, int v, int c, int cost) {
	E[top].v = v;
	E[top].cap = c;
	E[top].flow = 0;
	E[top].cost = cost;
	E[top].next = V[u].first;
	V[u].first = top++;
}

void add(int u, int v, int c, int cost) {
	add_edge(u, v, c, cost);
	add_edge(v, u, 0, -cost);
}

bool SPFA(int s, int t, int n) {
	int i, u, v;
	std::queue<int> Q;

	for (i = 0; i <= n; i++) {
		vis[i] = false;
	}

	for (i = 0; i <= n; i++) {
		c[i] = 0;
	}

	for (i = 1; i <= n; i++) {
		dist[i] = INT_MAX;
	}

	for (i = 0; i <= n; i++) {
		pre[i] = -1;
	}

	vis[s] = true;
	c[s]++;
	dist[s] = 0;
	Q.push(s);
	while (!Q.empty()) {
		u = Q.front();
		Q.pop();
		vis[u] = false;
		for (i = V[u].first; i != -1; i = E[i].next) {
			v = E[i].v;
			if (E[i].cap > E[i].flow && dist[v] > dist[u] + E[i].cost) {
				dist[v] = dist[u] + E[i].cost;
				pre[v] = i;
				if (!vis[v]) {
					c[v]++;
					Q.push(v);
					vis[v] = true;
					if (c[v] > n) {
						return false;
					}
				}
			}
		}
	}

	std::cout << "Shortest path：" << std::endl;
	std::cout << "dist[] = ";
	for (int i = 1; i <= n; i++) {
		std::cout << "  " << dist[i];
	}
	std::cout << std::endl;
	if (dist[t] == INT_MAX) {
		return false;
	}

	return true;
}

int MCMF(int s, int t, int n) {
	int d;
	int i;
	int mincost = 0;
	while (SPFA(s, t, n)) {
		d = INT_MAX;
		std::cout << std::endl;
		std::cout << "Argumenting path:" << t;
		for (i = pre[t]; i != -1; i = pre[E[i ^ 1].v]) {
			d = std::min(d, E[i].cap - E[i].flow);
			std::cout << "---" << E[i ^ 1].v;
		}
        
        std::cout << std::endl;
		std::cout << "add flow:" << d << std::endl;
		std::cout << std::endl;
		maxflow += d;

		for (i = pre[t]; i != -1; i = pre[E[i^1].v]) {
			E[i].flow += d;
			E[i ^ 1].flow -= d;
		}

		mincost += dist[t] * d;
	}

	return mincost;
}

void printing(int n) {
	std::cout << "------------Adjacency table--------\n";
	for (int i = 1; i <= n; i++) {
		std::cout << "v" << i << "  [" << V[i].first;
		for (int j = V[i].first; ~j; j = E[j].next) {
			std::cout << "]---[" << E[j].v << " " << E[j].cap << " " << E[j].flow << "  " << E[j].next;
		}
		std::cout << "]" << std::endl;
	}

	std::cout << std::endl;
}

void printflow(int n) {
	std::cout << "------------real flow edge---------------" << std::endl;
	for (int i = 1; i <= n; i++) {
		for (int j = V[i].first; ~j; j = E[j].next) {
			if (E[j].flow > 0) {
				std::cout << "v" << i << "--" << "v" << E[j].v << "   " << E[j].flow;
				std::cout << std::endl;
			}
		}
	}
}

int main(int argc, char** argv) {
	std::string str;
	std::fstream f("r.txt");
	getline(f, str);
	std::istringstream ss(str);
	ss >> n; //vertex
	ss >> m; //edge

	init();

	for (int i = 1; i <= m; i++) {
		getline(f, str);
		std::istringstream ss2(str);
		int u, v, w, c;
		ss2 >> u >> v >> w >> c;
		add(u, v, w, c);
	}

	std::cout << std::endl;
	printing(n);
	int mincost = MCMF(1, n, n);
	std::cout << "Min cost:" << mincost << std::endl;
	std::cout << "Max flow: " << maxflow << std::endl;
	std::cout << std::endl;
	printing(n);
	printflow(n);

	return 0;
}

