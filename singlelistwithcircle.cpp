#include <iostream>

struct Node {
	int data;
	Node* next;

	Node(int d) : data(d), next(nullptr) {}
};

Node* makeUpData() {
	Node* pHead = new Node(1);
	Node* pD = pHead;
	Node* p = nullptr;
	for (int i = 2; i <= 5; i++) {
		p = new Node(i);
		pD->next = p;
		pD = p;
	}

	Node* p2 = nullptr;
	for (int i = 6; i <= 7; i++) {
		p2 = new Node(i);
		pD->next = p2;
		pD = p2;
	}

	pD->next = p;//make a circle

	return pHead;
}

bool checkCircle(Node* pHead, int& circlelength, Node*& pStart) {
	if (pHead == nullptr) {
		return false;
	}

	Node* pP = pHead;
	Node* pP2 = pHead;
	Node* pP3 = nullptr;

	bool hasCircle = false;

	while (pP != nullptr && pP2->next != nullptr) {
		pP = pP->next;
		pP2 = pP2->next->next;

		if (pP == pP2) {
			if (!hasCircle) {
				pP3 = pP;
                std::cout << "The first meet point" << pP->data << std::endl;
				hasCircle = true;
			}

			if (circlelength > 0) {
				break;
			}
		}

		if (hasCircle) {
			circlelength++;
		}
	}

	//get start node;
	pP = pHead; 
	while (pP != nullptr && pP3 != nullptr) {
		pP = pP->next;
		pP3 = pP3->next;
		if (pP == pP3) {
			pStart = pP;
			break;
		}
	}

	return hasCircle;
}

int main(int argc, char* argv[]) {
	//make up data
	Node* pData = makeUpData();
	int circlelength = 0;
	Node* pStart = nullptr;
	bool hasCircle = checkCircle(pData, circlelength, pStart);
	if (hasCircle) {
		std::cout << "This list has a circle" << std::endl;
		std::cout << "The length of circle:" << circlelength << std::endl;
		std::cout << "The start of circle:" << pStart->data << std::endl;
	}
	else {
		std::cout << "This list has no circle" << std::endl;
	}

	//system("PAUSE");
}
