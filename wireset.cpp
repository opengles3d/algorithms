#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <sstream>
#include <fstream>

struct Position{
    int x;
    int y;
};

std::vector<std::vector<int>> grid;

bool findPath(const Position& s, const Position& e, std::vector<Position>& path, int& pathlen) {
    if((s.x == e.x) && (s.y == e.y)) {
        pathlen = 0;
        return true;
    }

    Position DIR[4];
    Position here;
    Position next;

    DIR[0].x = 0;
    DIR[0].y = 1;

    DIR[1].x = 1;
    DIR[1].y = 0;

    DIR[2].x = 0;
    DIR[2].y = -1;

    DIR[3].x = -1;
    DIR[3].y = 0;

    here = s;
    grid[s.x][s.y] = 0;
    std::queue<Position> Q;
    for(;;) {
        for(int i = 0; i < 4; i++) {//right, down, left, up
            next.x = here.x + DIR[i].x;
            next.y = here.y + DIR[i].y;
            if(grid[next.x][next.y] == -1) {//not wired
                grid[next.x][next.y] = grid[here.x][here.y] + 1;
                Q.push(next);
            }

            if((next.x == e.x) && (next.y == e.y)) {
                break;
            }
        }

        if((next.x == e.x) && (next.y == e.y)) {
            break;
        }

        if(Q.empty()) {
            return false;
        } else {
            here = Q.front();
            Q.pop();
        }
    }

    pathlen = grid[e.x][e.y];
    path.resize(pathlen);
    here = e;
    for(int j = pathlen - 1; j >= 0; j--) {
        path[j] = here;
        for(int i = 0; i < 4; i++) {
            next.x = here.x + DIR[i].x;
            next.y = here.y + DIR[i].y;
            if(grid[next.x][next.y] == j) {
                break;
            }
        }

        here = next;
    }

    return true;
}

void init(int m, int n) {
    
    for(int i = 0; i <= m + 1; i++) {
        std::vector<int> row(n+2);
        grid.push_back(row);
    }

    for(int i = 1; i <= m; i++) {
        for(int j = 1; j <= n; j++) {
            grid[i][j] = -1;
        }
    }

    for(int i = 0; i <= n + 1; i++) {//set wall at up & down
        grid[0][i] = grid[m + 1][i] = -2;
    }

    for(int i = 0; i <= m + 1; i++) {//set wall at right & left
        grid[i][0] = grid[i][n + 1] = -2;
    }
}

int main(int argc, char** argv) {
    Position a, b;
    int len, m, n;
    //input m, n
    std::string str;
	std::fstream f("n.txt");
	getline(f, str);
	std::istringstream ss(str);
	ss >> m; //row
	ss >> n; //col
    init(m, n);

    int x = 1;
    int y = 1;
    while(!(x == 0 && y == 0)) {
        getline(f, str);
	    std::istringstream ss2(str);
        ss2 >> x >> y;
        grid[x][y] = -2;
    }

    {
        getline(f, str);
	    std::istringstream ss2(str);
        ss2 >> a.x >> a.y;
    }

    {
        getline(f, str);
	    std::istringstream ss2(str);
        ss2 >> b.x >> b.y;
    }

    std::vector<Position> way;
    if(findPath(a, b, way, len)){
        std::cout << "The shortest path len: " << len << std::endl;
        std::cout << "These points are:" << std::endl;
        for(int i = 0; i < len; i++) {
            std::cout << std::setw(2) << way[i].x << std::setw(2) << way[i].y << std::endl;
        }
    } else {
        std::cout << "No way to go" << std::endl;
    }
    return 0;
}
