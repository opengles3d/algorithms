#include <iostream>
#include <queue>
#include <vector>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iomanip>

std::vector<std::vector<float>> kernel;
std::vector<char> FJL;
std::vector<char> JL;
int n, m, i, j; 

void print() {
    std::cout << std::endl;
    std::cout << "---------------simplex----------------------" << std::endl;
    std::cout << "   ";
    std::cout << std::setw(7) << "b ";
    for(int i = 1; i <= n; i++) {
        std::cout << std::setw(7) << "x" << FJL[i];
    }
    std::cout << std::endl;

    std::cout << "C ";

    for(int i = 0; i <= n; i++) {
        if(i >= 1) {
            std::cout <<"x" << JL[i];
        }

        for(int j = 0; j <= m; j++) {
            std::cout << std::setw(7) << kernel[i][j] << "  ";
        }

        std::cout << std::endl;
    }
}

void DCXA() {
    float max1;
    float max2;
    int e = -1;
    int k = -1;

    float min;

    while(true) {
        max1 = 0;
        max2 = 0;
        min = 1000000000;

        for(int j = 1; j <= m; j++) {
            if(max1 < kernel[0][j]) {
                max1 = kernel[0][j];
                e = j;
            }
        }

        if(max1 <= 0) {//find the result
            std::cout << std::endl;
            std::cout << "Got the optimized solution: " << kernel[0][0] << std::endl;
            print();
            break;
        }

        for(int i = 1; i <= n; i++) {
            if(max2 < kernel[i][e]) {
                max2 = kernel[i][e];
            }

            float temp = kernel[i][0] / kernel[i][e];
            if(temp > 0 && temp < min) {
                min = temp;
                k = i;
            }
        }

        std::cout << "Base column variables:" << FJL[e] << " ";
        std::cout << "Li base variables:" << JL[k] << std::endl;

        if(max2 == 0) {
            std::cout << "No solution" << std::endl;
            break;
        }

        char temp = FJL[e];
        FJL[e] = JL[k];
        JL[k] = temp;
        //std::swap(FJL[e], JL[k]);
        for(int i = 0; i <= n; i++) {
            if( i != k ) {
                for(int j = 0; j <= m; j++) {
                    if( j != e ) {
                        if(i == 0 && j == 0) {
                            kernel[i][j] = kernel[i][j] + kernel[i][e] * kernel[k][j] / kernel[k][e];
                        } else {
                            kernel[i][j] = kernel[i][j] - kernel[i][e] * kernel[k][j] / kernel[k][e];
                        }
                    }
                }
            }
        }

        for(int i = 0; i <= n; i++) {
            if( i != k) {
                kernel[i][e] = -kernel[i][e] / kernel[k][e];
            }
        }

        for(int j = 0; j <= m; j++) {
            if(j != e) {
                kernel[k][j] = kernel[k][j] / kernel[k][e];
            }
        }

        kernel[k][e] = 1 / kernel[k][e];
        print();
    }
}

int main(int argc, char** argv) {
    std::string str;
	std::fstream f("o.txt");
	getline(f, str);
	std::istringstream ss(str);
	ss >> m; //row

    getline(f, str);
	std::istringstream ss2(str);
    FJL.resize(m + 1);
    for(int i = 1; i <= m; i++) {
        ss2 >> FJL[i];
    }

    getline(f, str);
	std::istringstream ss3(str);
	ss3 >> n; //row
    getline(f, str);
	std::istringstream ss4(str);
    JL.resize(n + 1);
    for(int i = 1; i <= n; i++) {
        ss4 >> JL[i];
    }

    for(int i = 0; i <= n; i++) {
        std::vector<float> row(m + 1);
        kernel.push_back(row);
    }

    for(int i = 0; i <= n; i++) {
        getline(f, str);
	    std::istringstream ss5(str);
        for(int j = 0; j <= m; j++) {
            ss5 >> kernel[i][j];
        }
    }

    print();
    DCXA();
    return 0;
}