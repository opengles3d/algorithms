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

void init(int m, int n) {
	int total = m + n;
	V.resize(total + 1 + 2);
	for (int i = 0; i <= total; i++) {
		V[i].first = -1;
	}

	pre.resize(total + 1 + 2);
	for (int i = 0; i <= total; i++) {
		pre[i] = -1;
	}

	E.resize(m * n * 4);

	h.resize(total + 1 + 2);
	g.resize(total + 1 + 2);

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

void printflow(int m, int n) {
	std::cout << "------------real flow edge---------------" << std::endl;
	for (int i = 1; i <= m; i++) {
		std::cout << i << "team appoint to desk:";
		for (int j = V[i].first; ~j; j = E[j].next) {
			if (E[j].flow == 1) {
				std::cout << E[j].v - m << "   ";
			}
		}
		std::cout << std::endl;
	}
}

int main(int argc, char** argv) {
	std::string str;
	std::fstream f("u.txt");
	getline(f, str);
	std::istringstream ss(str);
	int m;
	int n;
	ss >> m; //team
	ss >> n; //desk

	init(m, n);

	int total = m + n;
	int sum = 0;

	getline(f, str);
	std::istringstream ss2(str);
	for (int i = 1; i <= m; i++) {
		int w;
		ss2 >> w;
		sum += w;
		add(0, i, w);
	}

	getline(f, str);
	std::istringstream ss3(str);
	for (int i = m + 1; i <= total; i++) {
		int w;
		ss3 >> w;
		add(i, total + 1, w);
	}

	for (int i = 1; i <= m; i++) {
		for (int j = m + 1; j <= total; j++) {
			add(i, j, 1);
		}
	}
	std::cout << std::endl;
	printing(total + 2);
	int maxflow = isap(0, total + 1, total + 2);
	if (sum == maxflow) {
		std::cout << "Succeed:" << std::endl;
		printflow(m, n);
		std::cout << std::endl;
		printing(total + 2);
	}
	else {
		std::cout << "Failed" << std::endl;
	}

	return 0;
}
