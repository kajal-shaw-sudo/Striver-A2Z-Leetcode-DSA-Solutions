// problem : https://leetcode.com/problems/coin-change/description/

// recursion
class Solution {
private:
    int helper(vector<int>& coins, int i, int amount) {
        if (i == 0) {
            if (amount % coins[i] == 0) {
                return amount / coins[i];
            }
            else {
                return 1e9;
            }
        }

        int notTake = 0 + helper(coins, i-1, amount);
        int take = 1e9;

        if (coins[i] <= amount) {
            take = 1 + helper(coins, i, amount - coins[i]);
        }

        return min(take, notTake);
    }

public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();

        int ans = 1e9;

        ans = helper(coins, n-1, amount);

        if (ans >= 1e9) {
            ans = -1;
        }

        return ans;
    }
};

// memoization
class Solution {
private:
    int helper(vector<int>& coins, int i, int target, vector<vector<int>>& dp) {
        if (i == 0) {
            if (target % coins[i] == 0) {
                return target / coins[i];
            }
            else {
                return 1e9;
            }
        }

        if (dp[i][target] != -1) {
            return dp[i][target];
        }

        int notTake = 0 + helper(coins, i-1, target, dp);
        int take = 1e9;

        if (coins[i] <= target) {
            take = 1 + helper(coins, i, target - coins[i], dp);
        }

        return dp[i][target] = min(take, notTake);
    }

public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();

        vector<vector<int>> dp(n, vector<int>(amount+1, -1));

        int ans = 1e9;

        ans = helper(coins, n-1, amount, dp);

        if (ans >= 1e9) {
            ans = -1;
        }

        return ans;
    }
};

// tabulation
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();

        vector<vector<int>> dp(n+1, vector<int>(amount+1, 0));

        for (int target=0; target<=amount; target++) {
            if (target % coins[0] == 0) {
                dp[0][target] = target / coins[0];
            }
            else {
                dp[0][target] = 1e9;
            }
        }

        for (int i=1; i<n; i++) {
            for (int target=0; target<=amount; target++) {
                int notTake = 0 + dp[i-1][target];
                int take = 1e9;

                if (coins[i] <= target) {
                    take = 1 + dp[i][target - coins[i]];
                }

                dp[i][target] = min(take, notTake);
            }
        }

        int ans = dp[n-1][amount];

        if (ans >= 1e9) {
            ans = -1;
        }

        return ans;
    }
};

// space optimization
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        int n = coins.size();

        vector<int> curr(amount+1, 0), prev(amount+1, 0);

        for (int target=0; target<=amount; target++) {
            if (target % coins[0] == 0) {
                prev[target] = target / coins[0];
            }
            else {
                prev[target] = 1e9;
            }
        }

        for (int i=1; i<n; i++) {
            for (int target=0; target<=amount; target++) {
                int notTake = 0 + prev[target];
                int take = 1e9;

                if (coins[i] <= target) {
                    take = 1 + curr[target - coins[i]];
                }

                curr[target] = min(take, notTake);
            }

            prev = curr;
        }

        int ans = prev[amount];

        if (ans >= 1e9) {
            ans = -1;
        }

        return ans;
    }
};