#include <iostream>
#include <vector>
#include <random>
#include <format>
#include <thread>

void swap(int& num1, int& num2) {
	int temp = 0; 
	temp = num1;
	num1 = num2;
	num2 = temp;
}
// 백터 오름차순 정렬
int sortVector(std::vector<int>& v) {
	int count = 0;
	for (int i = 0; i < v.size(); i++) {
		for (int j = i + 1; j < v.size(); j++) {
			if (v[i] > v[j]) {
				swap(v[i], v[j]);
				count++;
			}
		}
	}
	return count;
}
// 백터 출력
void printVector(std::vector<int> v, bool sleep, bool sleepNewLine) {
	for (int i = 0; i < v.size(); i++) {
		std::cout << std::format("{:4} ", v[i]);
		if (sleep == true) {
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		if ((i + 1) % 20 == 0) {
			std::cout << "\n";
			if (sleepNewLine == true) {
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
		}
	}
}
// 난수 생성, 중복 여부 확인
void genRandomNum(std::vector<int>& v, const int MIN, const int MAX, bool overlap) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(MIN, MAX);

	for (int i = 0; i < MAX - MIN + 1; i++) {
		v.push_back(dis(gen));
		if (overlap == false) {
			for (int j = 0; j < i; j++) {
				if (v[i] == v[j]) {
					v.erase(v.begin() + i);
					i--;
					break;
				}
			}
		}
	}
}

int main() {
	std::vector<int> v;
	int sortCount = 0;

	genRandomNum(v, 1, 1000, true);

	std::cout << std::format("\n{:-^100}\n\n", "GENERATE RANDOM NUMBER");
	printVector(v, false, true);
	sortCount = sortVector(v);
	std::cout << "\n";
	std::cout << std::format("{:-^100}\n", "SORT");
	std::cout << "\n";
	printVector(v, true, false);
	std::cout << std::format("\nCOUNT SWAP : {}\n", sortCount);
}