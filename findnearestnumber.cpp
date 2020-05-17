#include <iostream>
#include <vector>

int findTransferPoint(std::vector<int>& numbers) {
	for (int i = numbers.size() - 1; i > 0; i--) {
		if (numbers[i] > numbers[i - 1]) {
			return i;
		}
	}

	return 0;
}

std::vector<int> exchangeHead(std::vector<int>& numbers, int index) {
	int head = numbers[index - 1];
	for (int i = numbers.size() - 1; i > 0; i--) {
		if (head < numbers[i]) {
			numbers[index - 1] = numbers[i];
			numbers[i] = head;
			break;
		}
	}

	return numbers;
}

std::vector<int> reverse(std::vector<int>& numbers, int index) {
	for (int i = index, j = numbers.size() - 1; i < j; i++, j--) {
		int temp = numbers[i];
		numbers[i] = numbers[j];
		numbers[j] = temp;
	}

	return numbers;
}

std::vector<int> findNearestNumbers(std::vector<int>& numbers) {
	int index = findTransferPoint(numbers);
	if (index == 0) {
		std::vector<int> results;
		return results;
	}
	std::vector<int> copys = numbers;
	exchangeHead(copys, index);
	reverse(copys, index);
	return copys;
}

void output(std::vector<int> numbers) {
	std::cout << std::endl;
	for (auto i : numbers) {
		std::cout << i << " ";
	}
	std::cout << std::endl;
}

int main(int argc, char** argv) {
	std::vector<int> numbers{ 1, 2, 3, 4, 5 };
	for (int i = 0; i < 10; i++) {
		numbers = findNearestNumbers(numbers);
		output(numbers);
	}

	system("PAUSE");
}
