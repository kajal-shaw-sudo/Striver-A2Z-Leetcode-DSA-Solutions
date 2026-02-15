// problem : https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/description/

// recursion
class Solution {
private:
    int helper(vector<int>& prices, int i, int buy, int n) {
        if (i == n) {
            return 0;
        }

        int maxProfit = 0;

        // we can buy the stock
        if (buy == 0) {
            maxProfit = max(0 + helper(prices, i+1, 0, n), -prices[i] + helper(prices, i+1, 1, n));
        }
        
        if (buy == 1) {
            maxProfit = max(0 + helper(prices, i+1, 1, n), prices[i] + helper(prices, i+1, 0, n));
        }

        return maxProfit;
    }

public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();

        if (n == 0) {
            return 0;
        }

        return helper(prices, 0, 0, n);
    }
};

// memoization
class Solution {
private:
    int helper(vector<int>& prices, int i, int buy, int n, vector<vector<int>>& dp) {
        if (i == n) {
            return 0;
        }

        if (dp[i][buy] != -1) {
            return dp[i][buy];
        }

        int maxProfit = 0;

        // we can buy the stock
        if (buy == 0) {
            maxProfit = max(0 + helper(prices, i+1, 0, n, dp), -prices[i] + helper(prices, i+1, 1, n, dp));
        }
        
        if (buy == 1) {
            maxProfit = max(0 + helper(prices, i+1, 1, n, dp), prices[i] + helper(prices, i+1, 0, n, dp));
        }

        return dp[i][buy] = maxProfit;
    }

public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();

        if (n == 0) {
            return 0;
        }

        vector<vector<int>> dp(n, vector<int>(2, -1));

        return helper(prices, 0, 0, n, dp);
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

        vector<vector<int>> dp(n+1, vector<int>(2, 0));

        // when no stocks left, profit is 0
        dp[n][0] = dp[n][1] = 0;

        int profit = 0;

        for (int i=n-1; i>=0; i--) {
            for (int buy=0; buy<=1; buy++) {
                if (buy == 0) {
                    profit = max(0 + dp[i+1][0], -prices[i] + dp[i+1][1]);
                }

                if (buy == 1) {
                    profit = max(0 + dp[i+1][1], prices[i] + dp[i+1][0]);
                }

                dp[i][buy] = profit;
            }
        }

        return dp[0][0];
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

        vector<int> curr(2, 0), front(2, 0);

        // when no stocks left, profit is 0
        front[0] = front[1] = 0;

        int profit = 0;

        for (int i=n-1; i>=0; i--) {
            for (int buy=0; buy<=1; buy++) {
                if (buy == 0) {
                    profit = max(0 + front[0], -prices[i] + front[1]);
                }

                if (buy == 1) {
                    profit = max(0 + front[1], prices[i] + front[0]);
                }

                curr[buy] = profit;
            }

            front = curr;
        }

        return curr[0];
    }
};