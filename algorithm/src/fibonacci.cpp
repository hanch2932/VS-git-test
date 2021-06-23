#include <iostream>
#include <format>

int main() {
	double x = 0, y = 1;

	std::cout << std::format("{:^30}\n{:^30}\n", x, y);
	for (int i = 2; i < 100; i++) {
		double sum;
		sum = x + y;
		x = y;
		y = sum;
		std::cout << std::format("{:^30}\n", sum);
	}
}