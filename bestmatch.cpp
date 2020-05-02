#include <iostream>
#include <queue>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iomanip>

int top;
std::vector<int> h;
std::vector<int> pre;
std::vector<int> g;
int n;
int m;

struct Vertex {
	int first;
};

std::vector<Vertex> V;

struct Edge {
	int v;
	int next;
	int cap;
	int flow;
};

std::vector<Edge> E;

void init() {
	V.resize(m + n + 1 + 1 + 1);
	for (int i = 0; i <= m + n; i++) {
		V[i].first = -1;
	}

	pre.resize(m + n + 1 + 1 + 1);

	E.resize(m + n + (m * n));

	h.resize(m + n + 1 + 1 + 1);
	g.resize(m + n + 1 + 1 + 1);

	top = 0;
}

void add_edge(int u, int v, int c) {
	E[top].v = v;
	E[top].cap = c;
	E[top].flow = 0;
	E[top].next = V[u].first;
	V[u].first = top++;
}

void add(int u, int v, int c) {
	add_edge(u, v, c);
	add_edge(v, u, 0);
}

void set_h(int t, int n) {
	std::queue<int> Q;
	for (int i = 0; i <= n; i++) {
		h[i] = -1;
	}

	for (int i = 0; i <= n; i++) {
		g[i] = 0;
	}

	h[t] = 0;
	Q.push(t);
	while (!Q.empty()) {
		int v = Q.front();
		Q.pop();
		++g[h[v]];
		for (int i = V[v].first; ~i; i = E[i].next) {
			int u = E[i].v;
			if (h[u] == -1) {
				h[u] = h[v] + 1;
				Q.push(u);
			}
		}
	}

	std::cout << "Init height" << std::endl;
	std::cout << "h[] = ";
	for (int i = 1; i <= n; i++) {
		std::cout << "  " << h[i];
	}
	std::cout << std::endl;
}

int isap(int s, int t, int n) {
	set_h(t, n);
	int ans = 0;
	int u = s;
	int d;
	while (h[s] < n) {
		int i = V[u].first;
		if (u == s) {
			d = INT_MAX;
		}

		for (; ~i; i = E[i].next) {
			int v = E[i].v;
			if (E[i].cap > E[i].flow && h[u] == h[v] + 1) {
				u = v;
				pre[v] = i;
				d = std::min(d, E[i].cap - E[i].flow);
				if (u == t) {
					std::cout << std::endl;
					std::cout << "augmenting path:" << t;
					while (u != s) {
						int j = pre[u];
						E[j].flow += d;
						E[j ^ 1].flow -= d;
						u = E[j ^ 1].v;
						std::cout << "----" << u;
					}

					std::cout << "Augmenting flow:" << d << std::endl;
					ans += d;
					d = INT_MAX;
				}

				break;
			}
		}

		if (i == -1) {
			if (--g[h[u]] == 0) {
				break;
			}

			int hmin = n - 1;
			for (int j = V[u].first; ~j; j = E[j].next) {
				if (E[j].cap > E[j].flow) {
					hmin = std::min(hmin, h[E[j].v]);
				}
			}

			h[u] = hmin + 1;
			std::cout << "Relabel height" << std::endl;
			std::cout << "h[] = ";
			for (int i = 1; i <= n; i++) {
				std::cout << "  " << h[i];
			}

			std::cout << std::endl;

			++g[h[u]];
			if (u != s) {
				u = E[pre[u] ^ 1].v;
			}
		}
	}


	return ans;
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
}

void printflow(int n) {
	std::cout << "------------real flow edge---------------" << std::endl;
	for (int i = 1; i <= n; i++) {
		for (int j = V[i].first; ~j; j = E[j].next) {
			if (E[j].flow > 0) {
				std::cout << "v" << i << "--" << "v" << E[j].v/* << "   " << E[j].flow*/;
				std::cout << std::endl;
			}
		}
	}
}

int main(int argc, char** argv) {
	std::string str;
	std::fstream f("s.txt");
	getline(f, str);
	std::istringstream ss(str);
	ss >> n; //female
	ss >> m; //male

	init();
	int total = m + n;
	for (int i = 1; i <= m; i++) {
		add(0, i, 1);
	}

	for (int i = m + 1; i <= total; i++) {
		add(i, total + 1, 1);
	}

	int u = 0, v = 0;
	while (true) {
		getline(f, str);
		std::istringstream ss2(str);
		ss2 >> u >> v;
		if (u == -1 && v == -1) {
			break;
		}
		add(u, v, 1);
	}

	std::cout << std::endl;
	printing(total + 2);
	int maxflow = isap(0, total + 1, total + 2);
	std::cout << "Max flow: " << maxflow << std::endl;
	std::cout << std::endl;
	printing(total + 2);
	printflow(m);

	//system("PAUSE");

	return 0;
}

