#include <iostream>
#include <vector>

void changeCount(std::vector<int> coins, std::vector<int> counts, int n) {

	// Vector for saving the number of ways to make coin change during Dynamic Programming
	std::vector<int> dp(n + 1);
	std::vector<int> dpLast(n + 1);
	std::vector<std::vector<std::vector<int>>> comb_v(n + 1);

	int coin_num = coins.size();

	// Catch the exception
	try {
		if (n < 0 || n > 100)
			throw std::out_of_range("Please input the number between 0 and 100.");
	}
	catch (std::out_of_range& e) {
		std::cout << e.what() << std::endl;
		return;
	}

	dp[0] = 1;
	dpLast[0] = 1;
	comb_v[0].push_back(std::vector<int>(coin_num, 0));	// Push first {0, 0, 0, 0}

	for (int i = 0; i < coin_num; i++) {
		for (int j = coins[i]; j <= n; j++) {

			// Update dp vector following Dynamic Prgramming Process
			if (j < coins[i] * (counts[i] + 1))
				dp[j] += dp[j - coins[i]];
			else
				dp[j] += (dp[j - coins[i]] - dpLast[j - coins[i] * (counts[i] + 1)]);

			//Update combination vector
			std::vector<std::vector<int>> temp_v = comb_v.at(j - coins[i]);
			for (int k = 0; k < temp_v.size(); k++) {
				temp_v[k][i]++;
				if (temp_v[k][i] > counts[i])
					temp_v.erase(temp_v.begin() + k);
				else
					comb_v[j].push_back(temp_v[k]);
			}

			std::cout << dp[j] << " ";
		}

		// Update the last dp vector
		std::copy(dp.begin(), dp.end(), dpLast.begin());
		std::cout << std::endl;
	}

	std::cout << "Available Count : " << dp[n] << std::endl;

	// Print the combination that you saved
	for (int j = 0; j < comb_v[n].size(); j++) {
		for (int k = 0; k < comb_v[n][j].size(); k++) {
			std::cout << comb_v[n][j][k];
			if (k != comb_v[n][j].size() - 1)
				std::cout << ",";
		}
		std::cout << std::endl;
	}
}