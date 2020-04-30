
#include <iostream>
#include <queue>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>

struct Position {
    int x;
    int y;
};

std::vector<std::vector<int>> grid;
bool findPath(Position s, Position e, Position* &path, int &pathlen)
#if 0
std::vector<std::vector<double>> g;
std::vector<int> bestx;
int n;
int m;
double bestl;

struct Node{
    double cl;
    int id;
    std::vector<int> x;

    Node() {
        x.resize(n + 1);
    }

    Node(double _cl, int _id) : cl(_cl), id(_id) {
        x.resize(n + 1);
    }
};

bool operator < (const Node& a, const Node& b) {
    return a.cl > b.cl;
}

double travelingbfs() {
    int t;
    Node livenode, newnode;
    std::priority_queue<Node> q;
    newnode = Node(0, 2);
    for(int i = 1; i <= n; i++){
        newnode.x[i] = i;
    }

    q.push(newnode);
    while(!q.empty()){
        livenode = q.top();
        q.pop();
        t = livenode.id;
        if(t == n) {
            if(g[livenode.x[n - 1]][livenode.x[n]] != INT_MAX && g[livenode.x[n]][1] != INT_MAX) {
                if(livenode.cl + g[livenode.x[n - 1]][livenode.x[n]] + g[livenode.x[n]][1] < bestl) {
                    bestl = livenode.cl + g[livenode.x[n - 1]][livenode.x[n]] + g[livenode.x[n]][1];
                    for(int i = 1; i <= n; i++) {
                        bestx[i] = livenode.x[i];
                    }
                }
            }
            continue;
        }

        if(livenode.cl >= bestl) {
            continue;
        }

        for(int j = t; j <= n; j++) {
            if(g[livenode.x[t - 1]][livenode.x[j]] != INT_MAX) {
                double cl = livenode.cl + g[livenode.x[t - 1]][livenode.x[j]];
                if(cl < bestl) {
                    newnode = Node(cl, t + 1);
                    for(int i = 1; i <= n; i++) {
                        newnode.x[i] = livenode.x[i];
                    }
                    std::swap(newnode.x[t], newnode.x[j]);
                    q.push(newnode);
                }
            }
        }
    }

    return bestl;
}

void init() {
    bestl = INT_MAX;

    bestx.resize(n + 1);
    for(int i = 0; i <= n; i++) {
        bestx[i] = 0;
    }

    for(int i = 0; i <= n; i++) {
        std::vector<double> row(n + 1);
        g.push_back(row);
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            g[i][j] = g[j][i] = INT_MAX;
        }
    }
}

void print() {
    std::cout << "Shortest path:" << std::endl;
    for(int i = 1; i <= n; i++) {
        std::cout << bestx[i] << "---->";
    }

    std::cout << "1" << std::endl;
    std::cout << "The length of the shortest path:" << bestl;
}

int main(int argc, char *argv[]) {

	std::string str;
	std::fstream f("m.txt");
	getline(f, str);
	std::istringstream ss(str);
	ss >> n; //count
	ss >> m; //edge

    init();

    for(int i = 1; i <= m; i++) {
        int u, v, w;
		getline(f, str);
		std::istringstream ss2(str);
		ss2 >> u >> v >> w;
        g[u][v] = g[v][u] = w;
    }
   
    travelingbfs();
    print();

    return 0;
}
#endif

#if 0
std::vector<bool> bestx;
std::vector<int> w;
std::vector<int> v;

int bestp;
int W;
int n;
int sumw;
int sumv;

struct Node {
	int cp;
	double up;
	int rw;
	int id;
	std::vector<bool> x;
	Node() {
		x.resize(n + 1);
	}
	Node(int _cp, double _up, int _rw, int _id) {
		x.resize(n + 1);
		cp = _cp;
		up = _up;
		rw = _rw;
		id = _id;
	}
};

struct Goods {
	int weight;
	int value;
};

std::vector<Goods> goods;

struct Object {
	int id;
	double d;
};

std::vector<Object> s;

bool operator < (const Node& a, const Node& b) {
	return a.up < b.up;
}

bool cmp(const Object& a1, const Object& a2) {
	return a1.d > a2.d;
}

double bound(const Node& tnode) {
	double maxvalue = tnode.cp;
	int t = tnode.id;
	double left = tnode.rw;
	while (t <= n && w[t] <= left) {
		maxvalue += v[t];
		left -= w[t];
	}

	if (t <= n) {
		maxvalue += 1.0 * v[t] / w[t] * left;
	}

	return maxvalue;
}

int priorbfs() {
	int t;
	int tcp;
	int tup;
	int trw;

	std::priority_queue<Node> q;
	q.push(Node(0, sumv, W, 1));
	while (!q.empty()) {
		Node livenode;
		Node lchild;
		Node rchild;

		livenode = q.top();
		q.pop();
		t = livenode.id;

		if (t > n || livenode.rw == 0) {
			if (livenode.cp >= bestp) {
				for (int i = 1; i <= n; i++) {
					bestx[i] = livenode.x[i];
				}

				bestp = livenode.cp;
			}

			continue;
		}

		if (livenode.up < bestp) {
			continue;
		}

		tcp = livenode.cp;
		trw = livenode.rw;
		if (trw >= w[t]) {//left
			lchild.cp = tcp + v[t];
			lchild.rw = trw - w[t];
			lchild.id = t + 1;

			tup = bound(lchild);

			lchild = Node(lchild.cp, tup, lchild.rw, t + 1);

			for (int i = 1; i < t; i++) {
				lchild.x[i] = livenode.x[i];
			}

			lchild.x[t] = true;

			if (lchild.cp > bestp) {
				bestp = lchild.cp;
			}

			q.push(lchild);
		}

		//right child
		rchild.cp = tcp;
		rchild.rw = trw;
		rchild.id = t + 1;
		tup = bound(rchild);
		if (tup >= bestp) {
			rchild = Node(tcp, tup, trw, t + 1);

			for (int i = 1; i < t; i++) {
				rchild.x[i] = livenode.x[i];
			}
			rchild.x[t] = false;

			q.push(rchild);
		}
	}

	return bestp;
}

int main(int argc, char *argv[]) {
	bestp = 0;
	sumw = 0;
	sumv = 0;

	std::string str;
	std::fstream f("l.txt");
	getline(f, str);
	std::istringstream ss(str);
	ss >> n; //count
	ss >> W; //shopping cart capacity

	bestx.resize(n + 1);
	goods.resize(n + 1);
	s.resize(n + 1);
	w.resize(n + 1);
	v.resize(n + 1);

	getline(f, str);
	std::istringstream ss2(str);

	for (int i = 1; i <= n; i++) {

		ss2 >> goods[i].weight >> goods[i].value;
		sumw += goods[i].weight;
		sumv += goods[i].value;

		s[i - 1].id = i;
		s[i - 1].d = 1.0 * goods[i].value / goods[i].weight;
	}

	if (sumw <= W) {
		bestp = sumv;
		std::cout << "Get all of the goods" << std::endl;
		std::cout << "The best value is " << bestp << std::endl;
		return 0;
	}

	sort(s.begin(), s.end(), cmp);
	std::cout << "Weights and Values after sorted:" << std::endl;
	for (int i = 1; i <= n; i++) {
		w[i] = goods[s[i - 1].id].weight;
		v[i] = goods[s[i - 1].id].value;
		std::cout << w[i] << "  " << v[i] << std::endl;
	}

	priorbfs();

	std::cout << "The best value is " << bestp << std::endl;
	std::cout << "Get all of the goods" << std::endl;
	for (int i = 1; i <= n; i++) {
		if (bestx[i]) {
			std::cout << s[i - 1].id << " ";
		}
	}
	std::cout << std::endl;

	system("PAUSE");
	return 0;
}
#endif

#if 0
struct Node {
    int id;
    int x;
    int y;
};

bool cmp(const Node& a, const Node& b) {
    return std::min(b.x, a.y) >= std::min(b.y, a.x);
}

int main(int argc, char *argv[]) {

    std::vector<Node> T;
    int n;
    int f1;
    int f2;

	std::string s;
	std::fstream f("k.txt");
	getline(f, s);
	std::istringstream ss(s);
    ss >> n;

    T.resize(n);

    int u;
    int v;
	for (int j = 0; j < n; j++) {
        getline(f, s);
        std::istringstream ss2(s);
		ss2 >> T[j].x >> T[j].y;
        T[j].id = j + 1;
 	}

    std::sort(T.begin(), T.end(), cmp);

    f1 = 0;
    f2 = 0;

    for(int i = 0; i < n; i++) {
        f1 += T[i].x;
        f2 = std::max(f1, f2) + T[i].y;
    }

    std::cout << "The best result is:" << std::endl;
    for(int i = 0; i < n; i++) {
        std::cout << T[i].id << " ";
    }
    std::cout << std::endl;
    std::cout << "The best result value is:" << f2 << std::endl;

    system("PAUSE");
    return 0;
}
#endif

#if 0
struct Node {
    int x;
    int y;
};

std::vector<Node> T;
std::vector<int> x;
std::vector<int> bestx;

int n;
int bestf;
int f1;
int f2;

void backtrack(int t) {
    if(t > n) {
        for(int i = 1; i <= n; i++) {
            bestx[i] = x[i];
        }

        bestf = f2;
        return;
    }

    for(int i = t; i <= n; i++) {
        f1 += T[x[i]].x;
        int temp = f2;
        f2 = std::max(f1, f2) + T[x[i]].y;
        if(f2 < bestf) {
            std::swap(x[t], x[i]);
            backtrack(t + 1);
            std::swap(x[t], x[i]);
        }

        f1 -= T[x[i]].x;
        f2 = temp;
    }
}

int main(int argc, char *argv[]) {
	std::string s;
	std::fstream f("k.txt");
	getline(f, s);
	std::istringstream ss(s);
    ss >> n;


    T.resize(n + 1);
    bestx.resize(n + 1);
    x.resize(n + 1);

    int u;
    int v;
	for (int j = 1; j <= n; j++) {
        getline(f, s);
        std::istringstream ss2(s);
		ss2 >> T[j].x >> T[j].y;
        x[j] = j;
 	}

    bestf = INT_MAX;
    f1 = 0;
    f2 = 0;

    backtrack(1);

    std::cout << "The best result is:" << std::endl;
    for(int i = 1; i <= n; i++) {
        std::cout << bestx[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "The best result value is:" << bestf << std::endl;

    system("PAUSE");
    return 0;
}
#endif


#if 0
std::vector<int> x;
int count = 0;
int n;

bool place(int t) {
    bool ok = true;
    for(int j = 1; j < t; j++) {
        if(x[t] == x[j] || t - j == fabs(x[t] - x[j])) {
            ok = false;
            break;
        }
    } 
    return ok;
}

void backtrack(int t) {
    if( t > n) {
        count++;
        std::cout << "The " << count << "th method:";
        for(int j = 1; j <= n; j++) {
            std::cout << x[j] << " ";
        }
        std::cout << std::endl;
        for(int j = 1; j <= n; j++) {
            for(int i = 1; i <= n; i++) {
                if(x[j] == i) {
                    std::cout << "#";
                } else {
                    std::cout << "*";
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        std::cout << "---------------" << std::endl;
    } else {
        for(int  i = 1; i <= n; i++) {
            x[t] = i;
            if(place(t)) {
                backtrack(t + 1);
            }
        }
    }
}


int main(int argc, char *argv[]) {
	std::cout << "Input in the number of queens:";
    std::cin >> n;

    x.resize(n + 1);
    
    backtrack(1);
    std::cout << "Thare are totally " << count << " methods." << std::endl;
    system("PAUSE");
    return 0;
}
#endif

#if 0
std::vector<std::vector<int>> map;
std::vector<int> x;
int sum = 0;
int n;
int m;
int edge;

bool ok(int t) {
    for(int j = 1; j < t; j++) {
        if(map[t][j]) {
            if(x[j] == x[t]) {
                return false;
            }
        }
    } 

    return true;
}

void backtrack(int t) {
    if( t > n) {
        sum++;
        std::cout << "The " << sum << "th method:";
        for(int j = 1; j <= n; j++) {
            std::cout << x[j] << " ";
        }
        std::cout << std::endl;
    } else {
        for(int  i = 1; i <= m; i++) {
            x[t] = i;
            if(ok(t)) {
                backtrack(t + 1);
            }
        }
    }
}


int main(int argc, char *argv[]) {
	std::string s;
	std::fstream f("j.txt");
	getline(f, s);
	std::istringstream ss(s);
    ss >> n;
    ss >> m;
	ss >> edge;

    for(int i = 0; i <= n; i++) {
        std::vector<int> row(n + 1);
        map.push_back(row);
    }

    x.resize(n + 1);

    int u;
    int v;
	for (int j = 0; j < edge; j++) {
        getline(f, s);
	    std::istringstream ss2(s);
        ss2 >> u >> v;
        map[u][v] = map[v][u] = 1;
 	}

    backtrack(1);

    system("PAUSE");
    return 0;
}
#endif

#if 0
std::vector<std::vector<int>> a;
std::vector<bool> x;
std::vector<bool> bestx;
int cn;
int n;
int m;
int bestn;

bool place(int t) {
    bool ok = true;
    for(int j = 1; j < t; j++) {
        if(x[j] && a[t][j] == 0) {
            ok = false;
            break;
        }
    } 

    return ok;
}

void backtrack(int t) {
    if( t > n) {
        for(int j = 1; j <= n; j++) {
            bestx[j] = x[j];
        }
        bestn = cn;
        return;
    }

    if(place(t)) {
        x[t] = true;
        cn++;
        backtrack(t + 1);//left
        cn--;
    }

    if(cn + n - t > bestn) {
        x[t] = false;
        backtrack(t + 1);//right
    }
}


int main(int argc, char *argv[]) {
	std::string s;
	std::fstream f("i.txt");
	getline(f, s);
	std::istringstream ss(s);
	ss >> n;
    ss >> m;

    for(int i = 0; i <= n; i++) {
        std::vector<int> row(n + 1);
        a.push_back(row);
    }
    x.resize(n + 1);
    bestx.resize(n + 1);
    

    int u;
    int v;
	for (int j = 0; j < m; j++) {
        getline(f, s);
	    std::istringstream ss2(s);
        ss2 >> u >> v;
        a[u][v] = a[v][u] = 1;
 	}

    bestn = 0;
    cn = 0;
    backtrack(1);

    std::cout << "Take somting, the best is " << bestn << std::endl;
    std::cout << "Those are:" << std::endl;
    for(int i = 1; i <= n; i ++) {
        if(bestx[i]) {
            std::cout << i << " ";
        }
    }

    std::cout << std::endl;

    system("PAUSE");
    return 0;
}
#endif

#if 0
std::vector<int> v;
std::vector<int> w;
std::vector<bool> x;
std::vector<bool> bestx;
int cp;
int cw;
int n;
int W;
int bestp;

int bound(int i) {
    int rp = 0;
    while(i <= n) {
        rp += v[i];
        i++;
    }

    return cp + rp;
}

void backtrack(int t) {
    if( t > n) {
        for(int j = 1; j <= n; j++) {
            bestx[j] = x[j];
        }
        bestp = cp;
        return;
    }

    if(cw + w[t] <= W) {
        x[t] = true;
        cw += w[t];
        cp += v[t];
        backtrack(t + 1);//left
        cw -= w[t];
        cp -= v[t];
    }

    if(bound(t + 1) > bestp) {
        x[t] = false;
        backtrack(t + 1);//right
    }
}

void knapsack() {
    cw = 0;
    cp = 0;
    bestp = 0;
    int sumw = 0;
    int sumv = 0;
    for(int i = 1; i <= n; i++) {
        sumv += v[i];
        sumw += w[i];
    }

    if(sumw <= W) {
        bestp = sumv;
        std::cout << "Take verything, the best is " << bestp << std::endl;
        return;
    }

    backtrack(1);

    std::cout << "Take somting, the best is " << bestp << std::endl;
    std::cout << "Those are:" << std::endl;
    for(int i = 1; i <= n; i ++) {
        if(bestx[i]) {
            std::cout << i << " ";
        }
    }

    std::cout << std::endl;
}

int main(int argc, char *argv[]) {
	std::string s;
	std::fstream f("h.txt");
	getline(f, s);
	std::istringstream ss(s);
	ss >> n;
    ss >> W;

    v.resize(n + 1);
    w.resize(n + 1);
    x.resize(n + 1);
    bestx.resize(n + 1);
    
    getline(f, s);
	std::istringstream ss2(s);
	for (int j = 1; j <= n; j++) {
        ss2 >> w[j] >> v[j] ;
 	}

    knapsack();

    system("PAUSE");
    return 0;
}
#endif

#if 0
std::vector<std::vector<int>> min;
std::vector<std::vector<int>> max;
std::vector<int> sum;
int n;

int max_cost;
int min_cost;

int straight(std::vector<int>& a, int n) {
	for (int i = 1; i <= n; i++) {
		min[i][i] = 0;
	}

	for (int i = 1; i <= n; i++) {
		max[i][i] = 0;
	}

	sum[0] = 0;
	for (int i = 1; i <= n; i++) {
		sum[i] = sum[i - 1] + a[i];
	}

	for (int v = 2; v <= n; v++) {
		for (int i = 1; i <= n - v + 1; i++) {
			int j = i + v - 1;
			min[i][j] = INT_MAX;
			max[i][j] = -1;
			int temp = sum[j] - sum[i - 1];
			for (int k = i; k < j; k++) {
				min[i][j] = std::min(min[i][j], min[i][k] + min[k + 1][j] + temp);
				max[i][j] = std::max(max[i][j], max[i][k] + max[k + 1][j] + temp);
			}
		}
	}

	min_cost = min[1][n];
	max_cost = max[1][n];

	return 0;
}

int circular(std::vector<int>& a, int n) {
	for (int i = 1; i <= n - 1; i++) {
		a[n + i] = a[i];
	}

	n = 2 * n - 1;

	straight(a, n);

	n = (n + 1) / 2;
	min_cost = min[1][n];
	max_cost = max[1][n];
	for (int i = 2; i <= n; i++) {
		if (min[i][n + i - 1] < min_cost) {
			min_cost = min[i][n + i - 1];
		}

		if (max[i][n + i - 1] > max_cost) {
			max_cost = max[i][n + i - 1];
		}
	}

	return 0;
}

int main(int argc, char *argv[]) {
	std::string s;
	std::fstream f("g.txt");
	getline(f, s);
	std::istringstream ss(s);
	ss >> n;

	std::vector<int> row;
	getline(f, s);
	std::istringstream ss2(s);
	std::vector<int> a(2 * n + 1);
	for (int j = 1; j <= n; j++) {
		int u;
		ss2 >> u;
		a[j] = u;
	}

	for (int i = 0; i <= n; i++) {
		std::vector<int> row(n + 1);
		max.push_back(row);
	}

	for (int i = 0; i <= n; i++) {
		std::vector<int> row(n + 1);
		min.push_back(row);
	}

	sum.resize(n + 1);

	straight(a, n);
	std::cout << "Straight min : " << min_cost << std::endl;
	std::cout << "Straight max : " << max_cost << std::endl;

	max.clear();
	for (int i = 0; i <= 2*n; i++) {
		std::vector<int> row(2*n + 1);
		max.push_back(row);
	}

	min.clear();
	for (int i = 0; i <= 2*n; i++) {
		std::vector<int> row(2*n + 1);
		min.push_back(row);
	}

	sum.resize(2 * n + 1);

	circular(a, n);
	std::cout << "Straight min : " << min_cost << std::endl;
	std::cout << "Straight max : " << max_cost << std::endl;

	system("PAUSE");
	return 0;
}
#endif


#if 0
std::vector<std::vector<int>> g;
std::vector<std::vector<int>> m;
std::vector<std::vector<int>> s;
int n;

void triangulation() {
	for (int i = 0; i <= n; i++) {
		std::vector<int> row(n + 1);
		m.push_back(row);
	}

	for (int i = 0; i <= n; i++) {
		m[i][i] = 0;
	}

	for (int i = 0; i <= n; i++) {
		std::vector<int> row(n + 1);
		s.push_back(row);
	}

	for (int i = 0; i <= n; i++) {
		s[i][i] = 0;
	}

	for (int d = 2; d <= n; d++) {
		for (int i = 1; i <= n - d + 1; i++) {
			int j = i + d - 1;
			m[i][j] = m[i + 1][j] + g[i - 1][i] + g[i][j] + g[i - 1][j];
			s[i][j] = i;
			for (int k = i; k < j; k++) {
				int temp = m[i][k] + m[k + 1][j] + g[i - 1][k] + g[k][j] + g[i - 1][j];
				if (m[i][j] > temp) {
					m[i][j] = temp;
					s[i][j] = k;
				}
			}
		}
	}
}

void print(int i, int j) {
	if (i == j) {
		return;
	}

	if (s[i][j] > i) {
		std::cout << "{v" << i - 1 << ",v" << s[i][j] << "}" << std::endl;
	}

	if (j > s[i][j] + 1) {
		std::cout << "{v" << s[i][j] << ",v" << j << "}" << std::endl;
	}

	print(i, s[i][j]);
	print(s[i][j] + 1, j);
}

int main(int argc, char *argv[]) {
	std::string s;
	std::fstream f("f.txt");
	getline(f, s);
	std::istringstream ss(s);
	ss >> n;
	n--;
	for (int i = 0; i <= n; i++) {
		std::vector<int> row;
		getline(f, s);
		std::istringstream ss(s);
		for (int j = 0; j <= n; j++) {
			int u;
			ss >> u;
			row.push_back(u);
		}

		g.push_back(row);
	}

	triangulation();
	print(1, n);
	std::cout << "\nMinimum value is " << m[1][n] << std::endl;
	system("PAUSE");
	return 0;
}
#endif

#if 0
std::vector<int> p;
std::vector<std::vector<int>> m;
std::vector<std::vector<int>> s;
int n;

void matrixchain() {
	for (int i = 0; i <= n; i++) {
		std::vector<int> rowm(n + 1);
		m.push_back(rowm);

		std::vector<int> rows(n + 1);
		s.push_back(rows);
	}
	int k;
	for (int r = 2; r <= n; r++) {
		for (int i = 1; i <= n - r + 1; i++) {
			int j = r + i - 1;
			m[i][j] = m[i + 1][j] + p[i - 1] * p[i] * p[j];
			s[i][j] = i;

			for (k = i + 1; k < j; k++) {
				int t = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
				if (t < m[i][j]) {
					m[i][j] = t;
					s[i][j] = k;
				}
			}
		}
	}
}

void print(int i, int j) {
	if (i == j) {
		std::cout << "A[" << i << "]";
		return;
	}
	std::cout << "(";
	print(i, s[i][j]);
	print(s[i][j] + 1, j);
	std::cout << ")";
}

int main(int argc, char *argv[]) {
	std::string s;
	//std::cout << "Input the first string:" << std::endl;
	//std::cin >> s1;
	//std::cout << "Input the second string:" << std::endl;
	//std::cin >> s2;
	std::fstream f("e.txt");
	getline(f, s);
	std::istringstream ss(s);
	ss >> n;
	for (int i = 0; i <= n; i++) {
		getline(f, s);
		std::istringstream ss(s);
		int u;
		ss >> u;
		p.push_back(u);
	}

	matrixchain();
	print(1, n);
	std::cout << "\nMinimum value is " << m[1][n] << std::endl;
    return 0;
}
#endif

#if 0
std::vector<std::vector<int>> d;

int min(int a, int b) {
    return a < b ? a : b; 
}

int editdistance(std::string& str1, std::string& str2) {
    int len1 = str1.size();
    int len2 = str2.size();

    for(int i = 0; i <= len1; i++) {
        std::vector<int> row(len2 + 1);
        d.push_back(row);
    }
    for(int i = 0; i <= len1; i++) {
        d[i][0] = i;
    }

    for(int j = 0; j <= len2; j++) {
        d[0][j] = j;
    }

    for(int i = 1; i <= len1; i++) {
        for(int j = 1; j <= len2; j++) {
            int diff;
            if(str1[i - 1] == str2[j - 1]) {
                diff = 0;
            } else {
                diff = 1;
            }

            int temp = min(d[i - 1][j] + 1, d[i][j - 1] + 1);
            d[i][j] = min(temp, d[i - 1][j - 1] + diff);
        }
    }

    return d[len1][len2];
}

int main(int argc, char *argv[]) {
    std::string s1;
    std::string s2;
    //std::cout << "Input the first string:" << std::endl;
    //std::cin >> s1;
    //std::cout << "Input the second string:" << std::endl;
    //std::cin >> s2;

	std::fstream f("d.txt");
	getline(f, s1);
	getline(f, s2);

	int ed = editdistance(s1, s2);
    std::cout << "The edit distance between " << s1 << " and " << s2 << " is " << ed << std::endl;
    return 0;
}
#endif

#if 0
void print(int i, int j, const std::vector<std::vector<int>>& b, const std::string & s1) {
	if (i == 0 || j == 0) {
		return;
	}

	if (b[i][j] == 1) {
		print(i - 1, j - 1, b, s1);
		std::cout << s1[i - 1];
	}
	else if (b[i][j] == 2) {
		print(i, j - 1, b, s1);
	}
	else {
		print(i - 1, j, b, s1);
	}
}

void lcsl(std::string& s1, std::string& s2) {
	size_t len1 = s1.size();
	size_t len2 = s2.size();
	std::vector<std::vector<int>> c;
	for (int i = 0; i < len1 + 1; i++) {
		std::vector<int> row(len2 + 1);
		c.push_back(row);
	}

	std::vector<std::vector<int>> b;
	for (int i = 0; i < len1 + 1; i++) {
		std::vector<int> row(len2 + 1);
		b.push_back(row);
	}

	for (int i = 0; i <= len1; i++) {
		c[i][0] = 0;
	}

	for (int i = 0; i <= len2; i++) {
		c[0][i] = 0;
	}

	for (int i = 1; i <= len1; i++) {
		for (int j = 1; j <= len2; j++) {
			if (s1[i - 1] == s2[j - 1]) {
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = 1;
			}
			else {
				if (c[i][j - 1] > c[i - 1][j]) {
					c[i][j] = c[i][j - 1];
					b[i][j] = 2;
				}
				else {
					c[i][j] = c[i - 1][j];
					b[i][j] = 3;
				}
			}
		}
	}

	std::cout << "Length is:" << c[len1][len2] << std::endl;
	std::cout << "LCSL is:";
	print(len1, len2, b, s1);
}

int main(int argc, char *argv[]) {
    std::string s1;
    std::string s2;
    //std::cout << "Input the first string:" << std::endl;
    //std::cin >> s1;
    //std::cout << "Input the second string:" << std::endl;
    //std::cin >> s2;

	std::fstream f("c.txt");
	getline(f, s1);
	getline(f, s2);

	lcsl(s1, s2);
    return 0;
}
#endif


#if 0
int partition2(std::vector<int>& num, int low, int high) {
    int pivot = num[low];
    int i = low;
    int j = high;
    while(i < j) {
        while(i < j && num[j] > pivot) {
            j--;
        }

        while(i < j && num[i] <= pivot) {
            i++;
        }

        if(i < j) {
            std::swap(num[i++], num[j--]);
        }
    }

    if(num[i] > pivot) {
        std::swap(num[i - 1], num[low]);
        return i - 1;
    }

    std::swap(num[i], num[low]);

    return i;
}

int partition(std::vector<int>& num, int low, int high) {
    int pivot = num[low];
    int i = low;
    int j = high;
    while(i < j) {
        while(i < j && num[j] > pivot) {
            j--;
        }

        if(i < j) {
            std::swap(num[i++], num[j]);
        }

        while(i < j && num[i] <= pivot) {
            i++;
        }

        if(i < j) {
            std::swap(num[i], num[j--]);
        }
    }

    return i;
}

void quicksort(std::vector<int>& num, int low, int high) {
    if(low < high) {
        int mid = partition2(num, low, high);
        quicksort(num, low, mid - 1);
        quicksort(num, mid + 1, high);
    }
}

int main(int argc, char *argv[]) {
	std::fstream f("b.txt");
    std::vector<int> numbers;
    
	while (!f.eof()) {
        std::string s;
		getline(f, s);
		std::istringstream ss(s);
        int u;
		ss >> u;
        numbers.push_back(u);
	}

	quicksort(numbers, 0, numbers.size() - 1);
    for(auto n : numbers) {
        std::cout << n << " ";
    }
    return 0;
}
#endif


#if 0
void merge(std::vector<int>& num, int low, int mid, int high) {
	std::vector<int> B(high - low + 1);
	int i = low;
	int j = mid + 1;
	int k = 0;
	while (i <= mid && j <= high) {
		if (num[i] <= num[j]) {
			B[k++] = num[i++];
		}
		else {
			B[k++] = num[j++];
		}
	}

	while (i <= mid) {
		B[k++] = num[i++];
	}

	while (j <= high) {
		B[k++] = num[j++];
	}

	for (i = low, k = 0; i <= high; i++, k++) {
		num[i] = B[k];
	}
}

void mergesort(std::vector<int>& num, int low, int high) {
	if (low < high) {
		int mid = (low + high) / 2;
		mergesort(num, low, mid);
		mergesort(num, mid + 1, high);
		merge(num, low, mid, high);
	}
}

int main(int argc, char *argv[]) {
	std::fstream f("b.txt");
    std::vector<int> numbers;
    
	while (!f.eof()) {
        std::string s;
		getline(f, s);
		std::istringstream ss(s);
        int u;
		ss >> u;
        numbers.push_back(u);
	}

	mergesort(numbers, 0, numbers.size() - 1);
    for(auto n : numbers) {
        std::cout << n << " ";
    }
    return 0;
}
#endif

# if 0
int binarySearch(const std::vector<int>& n, int a) {
    int low = 0;
    int high = n.size() - 1;
    while(low <= high) {
        int middle = (low + high) / 2;
        if(n[middle] == a) {
            return middle;
        } else if(n[middle] > a) {
            high = middle;
        } else {
            low = middle;
        }
    }

    return -1;
}

int main(int argc, char *argv[]) {
	std::fstream f("b.txt");
    std::vector<int> numbers;
    
	while (!f.eof()) {
        std::string s;
		getline(f, s);
		std::istringstream ss(s);
        int u;
		ss >> u;
        numbers.push_back(u);
	}

	sort(numbers.begin(), numbers.end());
    int a = numbers[10];
	int ans = binarySearch(numbers, a);
	std::cout << a << " is at " << ans << std::endl;
    return 0;
}
#endif

#if 0
std::vector<int> nodeset;

int n, m;

struct Edge {
	int u;
	int v;
	int w;
};

std::vector<Edge> e;

bool comp(const Edge& x, const Edge& y) {
	return x.w < y.w;
}

void init(int n, int m) {
	nodeset.resize(n);
	for (int i = 0; i < n; i++) {
		nodeset[i] = i;
	}

	e.resize(m);
}

bool merge(int a, int b) {
	int p = nodeset[a];
	int q = nodeset[b];
	if (p == q) {
		return false;
	}

	for (int i = 0; i < n; i++) {
		if (nodeset[i] == q) {
			nodeset[i] = p;
		}
	}

	return true;
}

int kruskal(int n, int m) {
	int ans = 0;
	for (int i = 0; i < m; i++) {
		if (merge(e[i].u, e[i].v)) {
			ans += e[i].w;
			n--;
			if (n == 1) {
				return ans;
			}
		}
	}

	return 0;
}

int main(int argc, char *argv[]) {
	std::fstream f("a.txt");

	std::cout << "Input the vertex number n and edge number m: " << std::endl;
	std::string s;
	getline(f, s);
	std::istringstream ss(s);
	ss >> n >> m;
	//std::cin >> n >> m;
	init(n, m);

	std::cout << "Input vertex u, v and edge weight w: " << std::endl;
	int u, v;
	for (int i = 0; i < m; i++) {
		getline(f, s);
		std::istringstream ss(s);
		//std::cin >> e[i].u >> e[i].v >> e[i].w;
		//ss >> e[i].u >> e[i].v >> e[i].w;
		ss >> u >> v >> e[i].w;
		e[i].u = u - 1;
		e[i].v = v - 1;
	}

	sort(e.begin(), e.end(), comp);
	int ans = kruskal(n, m);
	std::cout << "The minimum cost:" << ans << std::endl;
    return 0;
}
#endif

#if 0
constexpr int INF = 0x3fffffff;
constexpr int N = 100;
std::vector<bool> s;
std::vector<int> closest;
std::vector<int> lowcost;
std::vector<std::vector<int>> c;

void Prim(int n, int u0, std::vector<std::vector<int>>& c) {
    s[u0] = true;
    for(int i = 0;  i < n; i++) {
        if(i != u0) {
            lowcost[i] = c[u0][i];
            closest[i] = u0;
            s[i] = false;
        } else {
            lowcost[i] = 0;
        }
    }

    for(int i = 0; i < n; i++) {
        int temp = INF;
        int t = u0;
        for(int j = 0; j < n; j++) {
            if((!s[j]) && (lowcost[j] < temp)) {
                t = j;
                temp = lowcost[j];
            }
        }

        if(t == u0) {
            break;
        }

        s[t] = true;
        for(int j = 0; j < n; j++) {
            if((!s[j]) && (c[t][j] < lowcost[j])) {
                lowcost[j] = c[t][j];
                closest[j] = t;
            }
        }
    }
}

int main(int argc, char** argv) {
    s.resize(N);
    closest.resize(N);
    lowcost.resize(N);
    for(int i = 0; i < N; i++) {
        std::vector<int> row(N);
        c.push_back(row);
    }
    int n, m, u, v, w;
    int u0;
    std::cout << "Input the vertex number n and edge number m:" << std::endl;
    std::cin >> n >> m;
    int sumcost = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            c[i][j] = INF;
        }
    }

    std::cout << "Input the vertex u, v and edge weight w:" << std::endl;
    for(int i = 0; i < m; i++) {
        std::cin >> u >> v >> w;
        c[u - 1][v - 1] = c[v - 1][u - 1] = w;
    }

    std::cout << "Input any vertex u0:" << std::endl;
    std::cin >> u0; u0 -= 1;
    Prim(n, u0, c);
    std::cout << "Array lowcost contents: " << std::endl;
    for(int i = 0; i < n; i++) {
        std::cout << lowcost[i] << " ";
    }
    std::cout << std::endl;

    for(int i = 0; i < n; i++) {
        sumcost += lowcost[i];
    }

    std::cout <<"The minimum cost:" << sumcost << std::endl;

    return 0;
}
#endif

#if 0
constexpr int  MAXBITS = 100;
constexpr double MAXVALUE = 10000;
constexpr int MAXLEAF = 30;
constexpr int MAXNODES = MAXLEAF * 2 - 1;

typedef struct {
    double weight;
    int parent;
    int lchild;
    int rchild;
    char value;
}HNodeType;

typedef struct {
    int bits[MAXBITS];
    int start;
}HCodeType;

std::vector<HNodeType> HuffNodes;
std::vector<HCodeType> HuffCodes;

void HuffmanTree(std::vector<HNodeType>& HuffNodes, int n) {
    for(int i = 0; i < n * 2 - 1; i++) {
        HuffNodes[i].weight = 0;
        HuffNodes[i].parent = -1;
        HuffNodes[i].lchild = -1;
        HuffNodes[i].rchild = -1;
        HuffNodes[i].value = -1;
    }

    for(int i = 0; i < n; i++) {
        std::cout << "Please input value and weightof the node:" << i + 1 << std::endl;
        std::cin >> HuffNodes[i].value >> HuffNodes[i].weight;
    }

    int x1, x2;
    double m1, m2;
    for(int i = 0; i < n - 1; i++) {
        m1 = m2 = MAXVALUE;
        x1 = x2 = 0;

        for(int j = 0; j < n + i; j++) {
            if(HuffNodes[j].weight < m1 && HuffNodes[j].parent == -1) {
                m2 = m1;
                x2 = x1;
                m1 = HuffNodes[j].weight;
                x1 = j;
            } else if(HuffNodes[j].weight < m2 && HuffNodes[j].parent == -1) {
                m2 = HuffNodes[j].weight;
                x2 = j;
            }
        }

        HuffNodes[x1].parent = n + i;
        HuffNodes[x2].parent = n + i;
        HuffNodes[n+i].weight = m1 + m2;
        HuffNodes[n+i].lchild = x1;
        HuffNodes[n+i].rchild = x2;

        std::cout << "x1.weight and x2.weight in round " << i + 1 << "\t" << HuffNodes[x1].weight << "\t" << HuffNodes[x2].weight << std::endl;
    }
}

void HuffmanCode(std::vector<HCodeType>& HuffCodes, int n) {
    HCodeType cd;
    int c, p;
    for(int i = 0; i < n; i++) {
        cd.start = n - 1;
        c = i;
        p = HuffNodes[c].parent;
    
        while(p != -1) {
            if (HuffNodes[p].lchild == c) {
                cd.bits[cd.start] = 0;
            } else {
                cd.bits[cd.start] = 1;
            }

            cd.start--;
            c = p;
            p = HuffNodes[c].parent;
        }

        for(int j = cd.start + 1; j < n; j++) {
            HuffCodes[i].bits[j] = cd.bits[j];
        }

        HuffCodes[i].start = cd.start;
    }
}

int main(int argc, char** argv) { 
    HuffNodes.resize(MAXNODES);
    HuffCodes.resize(MAXLEAF);
    int n;
    std::cout << "Please input n:" << std::endl;
    std::cin >> n;
    HuffmanTree(HuffNodes, n);
    HuffmanCode(HuffCodes, n);

    for(int i = 0; i < n; i++ ) {
        std::cout << HuffNodes[i].value <<": Huffman code is: ";
        for(int j = HuffCodes[i].start + 1; j < n; j++) {
            std::cout << HuffCodes[i].bits[j];
        }
        std::cout << std::endl;
    }
    return 0;
}
#endif

#if 0
template<typename T>
concept interface = requires(T t) {
    {t.foo()} -> void;
};

class A {
public:
    void foo() {
        std::cout << "A:foo()" << std::endl;
    }
};

class B {
public:
    void foo() {
        std::cout << "B:foo()" << std::endl;
    }
};

template<interface T>
class Client{
    T& m_t;
public:
    Client(T& t) : m_t(t) {}

    void bar() {
        m_t.foo();
    }
};

int main(int argc, char** argv) { 
    Client c({A()});
    return 0;
}
#endif

#if 0
#include <iostream>
#include <array>

class spiderman {
public:
    spiderman() = default;

    bool attack(int x, int) {
        std::cout << "Spiderman attack :" << x << std::endl;
        return true;
    }
};

class captain_america {
public:
    captain_america() = default;

    bool attack(int, int y) {
        std::cout << "Captain_america attack :" << y << std::endl;
        return true;
    }
};

bool attack(int x, int y) {
    std::cout << "attack :" << x << "," << y << std::endl;
    return true;
}

template <typename RET, typename...ARGS>
class base {
public:
    virtual ~base() = default;
    virtual RET func(ARGS... args) = 0;
};

template<typename T, typename RET, typename... ARGS>
class wrapper : public base<RET, ARGS...> {
    T m_t{};
    RET (T::*m_func)(ARGS...) const;
public:
    wrapper(RET (T::*func)(ARGS...)) : m_func(func) {}

    RET func(ARGS...args) override {
        return std::invoke(m_func, &m_t, args...);
    }
};

template<typename RET, typename... ARGS>
class delegate {
    std::unique_ptr<base<RET, ARGS...>> m_wrapper;

public:
    template<typename T> delegate(RET (T::*func)(ARGS...)) : m_wrapper{std::make_unique<wrapper<T, RET, ARGS...>>(func)} {}

    RET operator()(ARGS... args) {
        return m_wrapper->func(args...);
    }
};


int main(int argc, char** argv) {
    spiderman s{};
    captain_america c{};
    std::array<delegate<bool, int, int>, 2> heros {
        //delegate(attack),
        delegate(&spiderman::attack),
        delegate(&captain_america::attack)
    };

    for(auto &h : heros) {
        h(0, 42);
    }
    return 0;
}
#endif


#if 0
#include <iostream>
#include <array>

class spiderman {
public:
    spiderman() = default;

    bool attack(int x, int) {
        std::cout << "Spiderman attack :" << x << std::endl;
        return true;
    }
};

class captain_america {
public:
    captain_america() = default;

    bool attack(int, int y) {
        std::cout << "Captain_america attack :" << y << std::endl;
        return true;
    }
};

bool attack(int x, int y) {
    std::cout << "attack :" << x << "," << y << std::endl;
    return true;
}

template <typename RET, typename...ARGS>
class base {
public:
    virtual ~base() = default;
    virtual RET func(ARGS... args) = 0;
};

template<typename T, typename RET, typename... ARGS>
class wrapper : public base<RET, ARGS...> {
    T m_t{};
    RET (T::*m_func)(ARGS...);
public:
    wrapper(RET (T::*func)(ARGS...)) : m_func(func) {}

    RET func(ARGS...args) override {
        return std::invoke(m_func, &m_t, args...);
    }
};

template<typename RET, typename... ARGS>
class delegate {
    std::unique_ptr<base<RET, ARGS...>> m_wrapper;

public:
    template<typename T> delegate(RET (T::*func)(ARGS...)) : m_wrapper{std::make_unique<wrapper<T, RET, ARGS...>>(func)} {}

    RET operator()(ARGS... args) {
        return m_wrapper->func(args...);
    }
};


int main(int argc, char** argv) {
    spiderman s{};
    captain_america c{};
    std::array<delegate<bool, int, int>, 2> heros {
        //delegate(attack),
        delegate(&spiderman::attack),
        delegate(&captain_america::attack)
    };

    for(auto &h : heros) {
        h(0, 42);
    }
    return 0;
}
#endif

#if 0
#include <fstream>

int main(int argc, char** argv) {
    std::fstream file{"111.txt", std::fstream::out};
    return 0;
}
#endif

#if 0
#include <any>
#include <string>
#include <iostream>
#include <variant>

std::variant<int, std::string> data;

int main(int argc, char** argv) {
    data = 35;
    data = std::string("Hello world");

    std::cout << std::get<std::string>(data) << std::endl;
    std::cout << std::get<int>(data) << std::endl;
    return 0;
}
#endif

#if 0
#include <any>
#include <string>
#include <iostream>

std::any data;

int main(int argc, char** argv) {
    data = 35;
    data = std::string("Hello world");

    std::cout << std::any_cast<std::string>(data) << std::endl;

    return 0;
}
#endif

#if 0
#include <thread>
#include <iostream>
#include <future>

void foo(std::promise<int> promise) {
    promise.set_value(40);
    //while(true);
}

int main(int argc, char** argv) {
    std::promise<int> promise;
    auto future = promise.get_future();

    std::thread t{foo, std::move(promise)};

    future.wait();
    std::cout << "The promise is 0: " << future.get() << std::endl;
    t.join();

    std::cout << "The promise is: " << future.get() << std::endl;

    return 0;
}
#endif

#if 0
#include <iostream>
#include <future>
#include <thread>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

constexpr auto size = 100;

int foo() {
    std::srand(std::time(nullptr));
    std::vector<long> numbers(size);
    std::generate(numbers.begin(), numbers.end(), [](){
        return std::rand();
    });
    std::sort(numbers.begin(), numbers.end());
    //for(auto s : numbers) {
    //    std::cout << s << " ";
    //}
    return numbers.back();
}

int main(int argc, char** argv) {
    #if 0
    auto s1 = std::async(std::launch::async, foo);
    auto s2 = std::async(std::launch::async, foo);
    auto s3 = std::async(std::launch::async, foo);
    auto s4 = std::async(std::launch::async, foo);
    #endif

    auto s1 = std::async(std::launch::deferred, foo);
    auto s2 = std::async(std::launch::deferred, foo);
    auto s3 = std::async(std::launch::deferred, foo);
    auto s4 = std::async(std::launch::deferred, foo);

    std::cout << s1.get() << std::endl;
    std::cout << s2.get() << std::endl;
    std::cout << s3.get() << std::endl;
    std::cout << s4.get() << std::endl;

    std::cout << foo() << std::endl;
    std::cout << foo() << std::endl;
    std::cout << foo() << std::endl;
    std::cout << foo() << std::endl;
    return 0;
}
#endif

#if 0
#include <iostream>
#include <thread>
#include <shared_mutex>
#include <mutex>
#include <atomic>

int count{};
std::atomic<int> atomic_count{};

void foo() {
    while(atomic_count < 10000) {
        count++;
        atomic_count++;
    };
}

int main(int argc, char** argv) {
    std::thread t1{foo};
    std::thread t2{foo};

    t1.join();
    t2.join();

    std::cout << "Normal count is: " << count << std::endl;
    std::cout << "Atomic count is: " << atomic_count << std::endl; 
    return 0;
}
#endif

#if 0
#include <iostream>
#include <thread>
#include <shared_mutex>
#include <mutex>


std::timed_mutex m{};

void foo() {
    if(m.try_lock_for(std::chrono::seconds(1))) {
        std::cout << "Locked" << std::endl;
    } else {
        std::cout << "Unlocked" << std::endl;
    }
}

int main(int argc, char** argv) {
    std::thread t1{foo};
    std::thread t2{foo};

    t1.join();
    t2.join();
    return 0;
}
#endif

#if 0
#include <iostream>
#include <thread>
#include <shared_mutex>
#include <mutex>

int count_rw{};

std::shared_mutex m{};

void reader() {

    while(true) {
        std::shared_lock lock(m);
        std::cout << "READ: The answer is:" << count_rw << std::endl;
        if(count_rw > 40) {
            return;
        }
    }
}


void writer() {

    while(true) {
        std::unique_lock lock(m);
        count_rw++;
        std::cout << "WRITE: The answer is:" << count_rw << std::endl;
        if(count_rw == 100) {
            return;
        }
    }
}


int main(int argc, char** argv) {
    std::thread th1{reader};
    std::thread th12{reader};
    std::thread th13{reader};
    std::thread th14{reader};
    std::thread th2{writer};
    th1.join();
    th12.join();
    th13.join();
    th14.join();
    th2.join();
    return 0;
}
#endif

#if 0
#include <iostream>
#include <thread>
#include <mutex>

std::mutex m{};

void foo() {
    std::string msg("The answer is: 42\n");

    while(true) {
        m.lock();
        for(const auto m : msg) {
            std::cout << m;
        }
        m.unlock();
    }
}

int main(int argc, char** argv) {
    std::thread th1{foo};
    std::thread th2{foo};
    th1.join();
    th2.join();
    return 0;
}
#endif

#if 0
#include <iostream>

template<typename T>
struct the_answer {
    the_answer(T t) {
        std::cout << "The answer is: " << t << std::endl;
    }
};

template class the_answer<int>;
template class the_answer<float>;

int main(int argc, char** argv) {
    the_answer{10};
    return 0;
}
#endif

#if 0
#include <iostream>
#include <type_traits>

template<auto answer, std::enable_if_t<std::is_integral_v<decltype(answer)>, int> = 0>
void foo() {
    std::cout << "The answer is: " << answer << std::endl;
}


int main(int argc, char** argv) {
    foo<42.0>();
    return 0;
}
#endif


#if 0
#include <iostream>

template<auto answer>
void foo() {
    std::cout << "The answer is: " << answer << std::endl;
}


int main(int argc, char** argv) {
    foo<42L>();
    return 0;
}
#endif

#if 0
#include <iostream>
#include <vector>


struct suboptimal {
    suboptimal() = default;
    suboptimal(suboptimal &&other) {
        *this = std::move(other);
    }

    suboptimal &operator=(suboptimal &&) {
        std::cout << "move\n";
        return *this;
    }

    suboptimal(const suboptimal &other) {
        *this = other;
    }

    suboptimal &operator=(const suboptimal &) {
        std::cout << "copy\n";
        return *this;
    }
};  

struct optimal {

    optimal() = default;

    optimal(optimal &&other) noexcept {
        *this = std::move(other);
    }

    optimal &operator=(optimal &&) noexcept {
        std::cout << "move\n";
        return *this;
    }

    optimal(const optimal &other) {
        *this = other;
    }

    optimal &operator=(const optimal &) {
        std::cout << "copy\n";
        return *this;
    }
};

template <typename T>
class mock_vector {
public:
    using size_type = std::size_t;

    mock_vector(size_type s) : m_size(s), m_buffer{std::make_unique<T[]>(m_size)} {}

    void resize(size_type size) noexcept(std::is_nothrow_move_constructible_v<T>) {
        auto tmp = std::make_unique<T[]>(size);
        for(size_type i = 0; i < m_size; i++) {
            tmp[i] = std::move_if_noexcept(m_buffer[i]);
        }

        m_size = size;
        m_buffer = std::move(tmp);
    }

private:
    size_type m_size{};
    std::unique_ptr<T[]> m_buffer{};
};


int main(int argc, char** argv) {
    std::vector<optimal> d1(5);
    std::vector<suboptimal> d2(5);
    d1.resize(10);
    std::cout << "--------------\n";
    d2.resize(10);

    return 0;
}
#endif


#if 0
#include <memory>
#include <iostream>
#include <stdexcept>

template <typename T>
class mock_vector {
public:
    using size_type = std::size_t;

    mock_vector(size_type s) : m_size(s), m_buffer{std::make_unique<T[]>(m_size)} {}

    void resize(size_type size) noexcept(std::is_nothrow_move_constructible_v<T>) {
        auto tmp = std::make_unique<T[]>(size);
        for(size_type i = 0; i < m_size; i++) {
            tmp[i] = std::move_if_noexcept(m_buffer[i]);
        }

        m_size = size;
        m_buffer = std::move(tmp);
    }

private:
    size_type m_size{};
    std::unique_ptr<T[]> m_buffer{};
};

int main(int argc, char** argv) {
    mock_vector<int> mv(5);
    mv.resize(10);
    return 0;
}
#endif

#if 0
#include <iostream>

struct the_answer_noexcept{
    the_answer_noexcept() = default;
    the_answer_noexcept(const the_answer_noexcept& is) noexcept {
        std::cout << "l-value" << std::endl;
    }

    the_answer_noexcept(const the_answer_noexcept&& is) noexcept {
        std::cout << "r-value" << std::endl;
    }

};

struct the_answer_can_throw {
    the_answer_can_throw() = default;
    the_answer_can_throw(const the_answer_can_throw& is){
        std::cout << "l-value" << std::endl;
    }

    the_answer_can_throw(the_answer_can_throw&& is) {
        std::cout << "r-value" << std::endl;
    }
};

int main(int argc, char** argv) {
    the_answer_noexcept is1;
    the_answer_can_throw is2;

    std::cout << "noexcept:";
    auto is3 = std::move_if_noexcept(is1);

    std::cout << "can throw:";
    auto is4 = std::move_if_noexcept(is2);

    return 0;
}
#endif

#if 0
#include <iostream>
#include <tuple>
#include <algorithm>

template<
    std::size_t I = 0,
    typename ... Args,
    typename FUNCTION>
constexpr void
for_each(const std::tuple<Args...> &t, FUNCTION &&func)
{
    if constexpr (I < sizeof...(Args)) {
        func(std::get<I>(t));
        for_each<I + 1>(t, std::forward<FUNCTION>(func));
    }
}

template<typename ...Args>
void foo(Args &&... args) {
    std::tuple t(std::forward<Args>(args)...);
    for_each(t, [](const auto args) {
        std::cout << args << std::endl;
    });
}

int main(int argc, char** argv) {
    foo(42, " is the answer");
    return 0;
}
#endif

#if 0
#include <iostream>
#include <tuple>

template<typename ...Args>
void foo(Args &&... args) {
    std::tuple t(std::forward<Args>(args)...);
    std::cout << std::get<0>(t) << std::get<1>(t) << std::endl;
}

int main(int argc, char** argv) {
    foo(42, " is the answer");
    return 0;
}
#endif

#if 0
#include <iostream>
#include <tuple>

int main(int argc, char** argv) {
    std::tuple t("the answer is: ", 42);
    std::cout << std::get<0>(t) << std::get<1>(t) << std::endl;
    return 0;
}
#endif

#if 0
#include <iostream>
#include <iomanip>

template<typename T>
constexpr void foo(T&& t) {
    if constexpr (std::is_floating_point_v<T>) {
        std::cout << std::setprecision(10);
    }
    std::cout << "The answer is:" << t << std::endl;
}

int main(int argc, char** argv) {
    foo(42);
    foo(42.123456789);
    return 0;
}
#endif

#if 0
#include <iostream>

constexpr auto answer = 42;

int main(int argc, char** argv) {
    if constexpr (answer == 42) {
        std::cout << "The answer is: " << answer << std::endl;
    } else {
        std::cout << "The answer is not: " << answer << std::endl;
    }
}
#endif

#if 0
#include <iostream>

struct the_answer {};
void foo2(const the_answer& is, int i) {
    std::cout << "l-value: " << i << std::endl;
}

void foo2(the_answer && is, int i) {
    std::cout << "r-value: " << i << std::endl;
}

template<typename... Args>
void foo1(Args &&... args) {
    foo2(std::forward<Args>(args)...);
}

int main(int argc, char** argv) {
    the_answer is;
    foo1(is, 42);
    foo1(the_answer(), 42);
    return 0;
}
#endif

#if 0
#include <iostream>
struct the_answer {};
void foo2(const the_answer& is) {
    std::cout << "l-value" << std::endl;
}

void foo2(the_answer&& is) {
    std::cout << "r-value" << std::endl;
}

template<typename T>
void foo1(T &&t) {
    foo2(std::forward<T>(t));
}

int main(int argc, char** argv) {
    the_answer is;
    foo1(is);
    foo1(the_answer());
    return 0;
}
#endif

#if 0
#include <iostream>
#include <type_traits>
#include <iomanip>

template<typename T>
std::enable_if_t<std::is_integral_v<T>>
the_answer(T is) {
    std::cout << "The answer is: " << is << std::endl;
}


template<typename T>
std::enable_if_t<std::is_floating_point_v<T>>
the_answer(T is) {
    std::cout << std::setprecision(10);
    std::cout << "The answer is: " << is << std::endl;
}

int main(int argc, char** argv) {
    the_answer(42.057756886);
    return 0;
}
#endif

#if 0
#include <iostream>
#include <type_traits>

template<typename T, std::enable_if_t<std::is_integral_v<T>>* = nullptr>
void the_answer(T is) {
    std::cout << "The answer is: " << is << std::endl;
}

int main(int argc, char** argv) {
    the_answer(42);
    return 0;
}
#endif

#if 0
#include <iostream>
#include <type_traits>

template<typename T>
constexpr auto is_int() {
    return false;
}

template<>
constexpr auto is_int<int>() {
    return true;
}

template<typename T, std::enable_if_t<is_int<T>(), int> = 0>
void the_answer(T is) {
    std::cout << "The answer is: " << is << std::endl;
}

int main(int argc, char** argv) {
    the_answer(42);
    return 0;
}
#endif

#if 0
#include <iostream>
struct the_answer {
    using type = unsigned;
};

template<typename T>
void foo(typename T::type t) {
    std::cout << "The answer is not: " << t << std::endl;
}

template <typename T>
void foo(T t) {
    std::cout << "The answer is: " << t << std::endl;
}

int main(int argc, char** argv) {
    foo<the_answer>(23);
    foo<int>(42);
    return 0;
}
#endif

#if 0
#include <iostream>
class the_answer {
public:
    the_answer() = default;
    ~the_answer() = default;
    void foo() & { 
        std::cout << "The answer is: 42" << std::endl;
    }

    void foo() && {
        std::cout << "The answer is not: 0" << std::endl;
    }

    the_answer(the_answer && other) noexcept = default;
    the_answer& operator=(the_answer && other) noexcept = default;

    the_answer(const the_answer& other) = default;
    the_answer& operator=(const the_answer& other) = default;
};

int main(int argc, char** argv) {
    the_answer is;
    is.foo();

    std::move(is).foo();
    the_answer{}.foo();
}
#endif

#if 0
#include <iostream>
#include <memory>

class the_answer {
    std::unique_ptr<int> m_answer;
public:
    explicit the_answer(int answer) : m_answer{std::make_unique<int>(answer)} {}

    ~the_answer() {
        if(m_answer) {
            std::cout << "The answer is: " << *m_answer << std::endl;
        } else {
            std::cout << "The answer is unknown." << std::endl;
        }
    }

    the_answer(the_answer&& other) noexcept {
        *this = std::move(other);
    }

    the_answer& operator=(the_answer&& other) noexcept {
        m_answer = std::move(other.m_answer);
        return *this;
    }
};

int main(int argc, char** argv) {
    the_answer is_42{42};
    the_answer is = std::move(is_42);
    return 0;
}
#endif

#if 0
#include <iostream>

class the_answer {
private:
    int m_answer{42};
public:
    the_answer() = default;
    
    explicit the_answer(int answer) : m_answer(answer) { }

    virtual ~the_answer() {
        if(m_answer != 0) {
            std::cout << "The answer is: " << m_answer << std::endl;
        }
    }

    the_answer(the_answer &&other) noexcept {
        *this = std::move(other);
    }

    the_answer& operator=(the_answer &&other) noexcept {
        if(&other == this) {
            return *this;
        }
        m_answer = std::exchange(other.m_answer, 10);
        return *this;
    }

    the_answer(const the_answer& ) = default;
    the_answer& operator=(const the_answer& ) = default;
};

int main(int argc, char** argv) {
    {
        the_answer is{23};
        the_answer is_42{42};
        is = is_42;
    }
    std::cout << '\n';
    {
        the_answer is{23};
        the_answer is_42{42};
        is = std::move(is_42);
    }
    return 0;
}
#endif

#if 0
#include <iostream>
#include <stdexcept>

class nested {
public:
    ~nested() {
        std::cout << "# exceptions: " << std::uncaught_exceptions() << std::endl;
    }
};

class the_answer {
public:
    ~the_answer() {
        try {
            nested n;
            throw std::runtime_error("42");
        } catch (const std::exception& e) {
            std::cout << "1. The answer is: " << e.what() << std::endl;
        }
    } 
};

int main(int argc, char** argv) {
    try {
        the_answer is;
        throw std::runtime_error("always 42");
    } catch (const std::exception& e) {
            std::cout << "2. The answer is: " << e.what() << std::endl;
    }
}
#endif

#if 0
#include <iostream>
#include <stdexcept>

void foo() noexcept {
    std::cout << "The answer is 42." << std::endl; 
}

int main(int argc, char** argv) {
    std::cout << std::boolalpha << std::endl;
    std::cout << "could foo throw: " << !noexcept(foo()) << std::endl;
    return 0;
}
#endif

#if 0
#include <iostream>
#include <stdexcept>
#include <limits>

template<typename T>
uint64_t foo(T val) noexcept(sizeof(T) <= 4) {
   if constexpr(sizeof(T) <= 4) {
       return static_cast<uint64_t>(val) << 32;
   }
   
    throw std::runtime_error("Runtime error");
}

int main(int argc, char** argv) {
     try {
         uint32_t val1 = std::numeric_limits<uint32_t>::max();
         std::cout << "foo: " << foo(val1) << std::endl;

         uint64_t val2 = std::numeric_limits<uint64_t>::max();
         std::cout << "foo: " << foo(val2) << std::endl;
    } catch(std::runtime_error& re) {
        std::cout << re.what() << std::endl;
    }
}
#endif

#if 0
#include "ad.h"

#include <iostream>
int main(int argc, char** argv) {
    using namespace lib_ad;
    std::cout << "The answer is:" << my_api() << std::endl;
    return 0;
}
#endif