#include <vector>
#include <random>
#include <iostream>
#include <time.h>

std::vector<int> divideRedPackage(int amount, int people) {
    std::default_random_engine e;
    
    std::vector<int> results;

    int restAmount = amount;
    int restPeople = people;
    for(int i = 0; i < people - 1; ++i) {
        e.seed(time(NULL));
        std::uniform_int_distribution<unsigned> u(0, restAmount / restPeople * 2 - 1);
        int temp = u(e);
        restAmount -= temp;
        restPeople--;
        results.push_back(temp);
    }

    results.push_back(restAmount);
    return results;
} 

int main(int argc, char** argv) {
    std::vector<int> al = divideRedPackage(1000, 10);
    int sum = 0;
    for(auto a : al) {
        std::cout << a << " ";
        sum += a;
    }
    std::cout << std::endl;
    std::cout << "The sum is：" << sum << std::endl;
    return 0;
}