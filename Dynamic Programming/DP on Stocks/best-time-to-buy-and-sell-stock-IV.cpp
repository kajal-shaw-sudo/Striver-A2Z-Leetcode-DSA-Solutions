// problem : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/description/

// recursion
class Solution {
private:
    int helper(vector<int>& prices, int i, int buy, int k, int n) {
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
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();

        if (n == 0) {
            return 0;
        }

        return helper(prices, 0, 0, k, n);
    }
};

// memoization
class Solution {
private:
    int helper(vector<int>& prices, int i, int buy, int k, int n, vector<vector<vector<int>>>& dp) {
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

        return profit;
    }
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();

        if (n == 0) {
            return 0;
        }

        vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(k+1, -1))); // k can be 0, 1, 2 so k size = 3

        return helper(prices, 0, 0, k, n, dp);
    }
};

// tabulation
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
int n = prices.size();

        if (n == 0) {
            return 0;
        }

        vector<vector<vector<int>>> dp(n+1, vector<vector<int>>(2, vector<int>(k+1, 0)));

        for (int buy=0; buy<=1; buy++) {
            for (int cap=0; cap<=k; cap++) {
                dp[n][buy][cap] = 0;
            }
        }

        int profit = 0;

        for (int i=n-1; i>=0; i--) {
            for (int buy=0; buy<=1; buy++) {
                for (int cap=0; cap<k; cap++) {
                    if (buy == 0) {
                        profit = max(0 + dp[i+1][0][cap], -prices[i] + dp[i+1][1][cap]);
                    }

                    if (buy == 1) {
                        profit = max(0 + dp[i+1][1][cap], prices[i] + dp[i+1][0][cap+1]);
                    }

                    dp[i][buy][cap] = profit;
                }
            }
        }

        return dp[0][0][0];
    }
};

// space optimization
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
    int n = prices.size();

        if (n == 0) {
            return 0;
        }

        vector<vector<int>> curr(2, vector<int>(k+1, 0)), front(2, vector<int>(k+1, 0));
        // k can be 0, 1, 2 so k size = 3

        for (int buy=0; buy<=1; buy++) {
            for (int cap=0; cap<=k; cap++) {
                curr[buy][cap] = front[buy][cap] = 0;
            }
        }

        int profit = 0;

        for (int i=n-1; i>=0; i--) {
            for (int buy=0; buy<=1; buy++) {
                for (int cap=0; cap<k; cap++) {
                    if (buy == 0) {
                        profit = max(0 + front[0][cap], -prices[i] + front[1][cap]);
                    }

                    if (buy == 1) {
                        profit = max(0 + front[1][cap], prices[i] + front[0][cap+1]);
                    }

                    curr[buy][cap] = profit;
                }
            }

            front = curr;
        }

        return curr[0][0];
    }
};