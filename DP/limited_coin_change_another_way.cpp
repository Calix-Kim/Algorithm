#include <iostream>
#include <vector>

// Get an idea from "https://www.careercup.com/question?id=5692261441470464"

void changeCount2(std::vector<int> coins, std::vector<int> counts, int amount) {

	int coin_num = coins.size();

	// Vector for saving the number of ways to make coin change during Dynamic Programming
	std::vector<std::vector<int>> dp(coin_num + 1, std::vector<int>(amount + 1));
	std::vector<std::vector<std::vector<int>>> lastComb(amount + 1);	// Vector to be used to update curComb
	std::vector<std::vector<std::vector<int>>> curComb(amount + 1);	// Vector for updating combinations of coins

	// Catch the exception
	try {
		if (amount < 0 || amount > 100)
			throw std::out_of_range("Please input the number between 0 and 100.");
	}
	catch (std::out_of_range& e) {
		std::cout << e.what() << std::endl;
		return;
	}

	dp[0][0] = 1;
	lastComb[0].push_back(std::vector<int>(coin_num, 0));	// Push first {0, 0, 0, 0}

	for (int i = 1; i <= coin_num; i++) {
		// Initialize value and copy the combination vector from last one to current one.
		for (int j = 0; j <= amount; j++) {
			dp[i][j] = dp[i - 1][j];
		}
		std::copy(lastComb.begin(), lastComb.end(), curComb.begin());

		// Update dp and combination vector
		for (int k = 1; k <= counts[i - 1]; k++) {
			int start = coins[i - 1] * k;	// Setting start offset.
			for (int j = start; j <= amount; j++) {	// Update value from start offset to the amount of change
				dp[i][j] += dp[i - 1][j - start];

				std::vector<std::vector<int>> temp_v = lastComb.at(j - start);	// Get the combinations
				for (int m = 0; m < temp_v.size(); m++) {
					temp_v[m][i - 1] += k;	// Update vector after addiing k coins on the combination 
					curComb[j].push_back(temp_v[m]);
				}
			}
		}

		// Update lastComb vector
		std::copy(curComb.begin(), curComb.end(), lastComb.begin());
	}

	std::cout << "Available Count : " << dp[coin_num][amount] << std::endl;

	// Print the combination that you saved
	for (int j = 0; j < curComb[amount].size(); j++) {
		for (int k = 0; k < curComb[amount][j].size(); k++) {
			std::cout << curComb[amount][j][k];
			if (k != curComb[amount][j].size() - 1)
				std::cout << ",";
		}
		std::cout << std::endl;
	}
}