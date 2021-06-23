#include <iostream>
#include <random>
#include <vector>
#include <format>
#include <thread>

void swap(int& num1, int& num2) {
	int temp;
	temp = num1;
	num1 = num2;
	num2 = temp;
}

void genRandNum(std::vector<int>& v, const int MIN, const int MAX, bool overlap = true) {
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

void sortVector(std::vector<int>& v, bool up = true) {
	for (int i = 0; i < v.size(); i++) {
		for (int j = i + 1; j < v.size(); j++) {
			if (up == true) {
				if (v[i] > v[j]) {
					swap(v[i], v[j]);
				}
			}
			else {
				if (v[i] < v[j]) {
					swap(v[i], v[j]);
				}
			}
		}
	}
}

void printVector(std::vector<int> v, bool sleep = false, bool nlineSleep = false) {
	for (int i = 0; i < v.size(); i++) {
		std::cout << std::format("{:4} ", v[i]);
		if (sleep == true) {
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		if ((i + 1) % 20 == 0) {
			std::cout << "\n";
			if (nlineSleep == true) {
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
		}
	}
}

int main() {
	std::vector<int> v;
	std::cout << std::format("\n{:-^100}\n\n", "Generate Random Numebers");
	genRandNum(v, 1, 500);
	printVector(v, false, true);
	std::cout << std::format("\n{:-^100}\n\n", "Sort");
	sortVector(v);
	printVector(v, false, true);
}