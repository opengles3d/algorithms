#include <iostream>

bool is_power_of_2(int a) {
    if(a <= 1) {
        return false;
    }
    return (a & (a - 1)) == 0;
}

int main(int argc, char** argv) {
    for(int i = 1; i < 300; i++) {
        if(is_power_of_2(i)) {
            std::cout << i << " is power of 2." << std::endl;
        }
    }
}