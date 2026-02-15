// problem : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/description/

// recursion
class Solution {
private:
    int helper(vector<int>& prices, int i, int buy, int k, int n) { // k = transactions
        if (i == n || k == 0) {
            return 0;
        }

        int profit = 0;

        if (buy == 0) {
            profit = max(0 + helper(prices, i+1, 0, k, n), -prices[i] + helper(prices, i+1, 1, k, n));
        }

        if (buy == 1) {
            profit = max(0 + helper(prices, i+1, 1, k, n), prices[i] + helper(prices, i+1, 0, k-1, n));
        }

        return profit;
    }

public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();

        if (n == 0) {
            return 0;
        }

        return helper(prices, 0, 0, 2, n);
    }
};

// memoization
class Solution {
private:
    int helper(vector<int>& prices, int i, int buy, int k, int n, vector<vector<vector<int>>>& dp) { // k = transactions
        if (i == n || k == 0) {
            return 0;
        }

        if (dp[i][buy][k] != -1) {
            return dp[i][buy][k];
        }

        int profit = 0;

        if (buy == 0) {
            profit = max(0 + helper(prices, i+1, 0, k, n, dp), -prices[i] + helper(prices, i+1, 1, k, n, dp));
        }

        if (buy == 1) {
            profit = max(0 + helper(prices, i+1, 1, k, n, dp), prices[i] + helper(prices, i+1, 0, k-1, n, dp));
        }

        return dp[i][buy][k] = profit;
    }

public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();

        if (n == 0) {
            return 0;
        }

        vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(3, -1))); // k can be 0, 1, 2 so k size = 3

        return helper(prices, 0, 0, 2, n, dp);
    }
};

// tabulation
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();

        if (n == 0) {
            return 0;
        }

        vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(2, vector<int>(3, 0))); // k can be 0, 1, 2 so k size = 3

        for (int buy=0; buy<=1; buy++) {
            for (int k=0; k<=2; k++) {
                dp[n][buy][k] = 0;
            }
        }

        int profit = 0;

        for (int i=n-1; i>=0; i--) {
            for (int buy=0; buy<=1; buy++) {
                for (int k=0; k<2; k++) {
                    if (buy == 0) {
                        profit = max(0 + dp[i+1][0][k], -prices[i] + dp[i+1][1][k]);
                    }

                    if (buy == 1) {
                        profit = max(0 + dp[i+1][1][k], prices[i] + dp[i+1][0][k+1]);
                    }

                    dp[i][buy][k] = profit;
                }
            }
        }

        return dp[0][0][0];
    }
};

// space optimization
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();

        if (n == 0) {
            return 0;
        }

        vector<vector<int>> curr(2, vector<int>(3, 0)), front(2, vector<int>(3, 0));
        // k can be 0, 1, 2 so k size = 3

        for (int buy=0; buy<=1; buy++) {
            for (int k=0; k<=2; k++) {
                curr[buy][k] = front[buy][k] = 0;
            }
        }

        int profit = 0;

        for (int i=n-1; i>=0; i--) {
            for (int buy=0; buy<=1; buy++) {
                for (int k=0; k<2; k++) {
                    if (buy == 0) {
                        profit = max(0 + front[0][k], -prices[i] + front[1][k]);
                    }

                    if (buy == 1) {
                        profit = max(0 + front[1][k], prices[i] + front[0][k+1]);
                    }

                    curr[buy][k] = profit;
                }
            }

            front = curr;
        }

        return curr[0][0];
    }
};