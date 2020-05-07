#include <iostream>

int gcd(int a, int b) {
    if(a == b) {
        return a;
    }

    if((a & 1) == 0 && (b & 1) == 0) {
        return gcd(a >> 1, b >> 1) << 1;
    } else if((a & 1) == 0 && (b & 1) != 0) {
        return gcd(a >> 1, b);
    } else if((a & 1) != 0 && (b & 1) == 0) {
        return gcd(a, b >> 1);
    } else {
        int big = a > b ? a : b;
        int small = a < b ? a : b;
        return gcd(big - small, small);
    }
}

int main(int argc, char* argv[]) {
    while(true) {
        std::cout << "Input two numbers to get gcd for them and two zeros for an end." << std::endl;
        int a;
        int b;
        std::cin >> a >> b;
        if(a == 0 || b == 0) {
            break;
        }
        int g = gcd(a, b);
        std::cout << "gcd of " << a << " and " << b << " is " << g << std::endl;
        //std::cout << "gcd of "; std::cout << a ; std::cout << " and " ; std::cout << b ; std::cout << " is " ; std::cout << g; std::cout << std::endl;
    }
}