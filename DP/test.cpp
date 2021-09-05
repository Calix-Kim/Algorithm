#include <iostream>
#include <vector>

void changeCount(std::vector<int> coins, std::vector<int> counts, int n);
void changeCount2(std::vector<int> coins, std::vector<int> counts, int amount);

int main(void) {

	// Initialize what coins you have and how many each
	std::vector<int> coins = { 1, 5, 10, 50 };
	std::vector<int> counts = { 9, 9, 9, 9 };

	for (int i = 0; i <= 10; i++) {
		std::cout << "n = " << i << "\n";
		changeCount(coins, counts, i);
		//changeCount2(coins, counts, i);
		std::cout << "----------------------------------------------------" << "\n\n\n";
	}

	return 0;
}