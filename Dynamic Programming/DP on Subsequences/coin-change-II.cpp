// problem : https://leetcode.com/problems/coin-change-ii/description/

// recursion
class Solution {
private:
    int helper(vector<int>& coins, int i, int target) {
        if (i == 0) {
            return (target % coins[0] == 0 ? 1 : 0);
        }

        int notTake = helper(coins, i-1, target);
        int take = 0;

        if (coins[i] <= target) {
            take = helper(coins, i, target - coins[i]);
        }

        return take + notTake;
    }

public:
    int change(int amount, vector<int>& coins) {
        int n = coins.size();

        return helper(coins, n-1, amount);
    }
};

// memoization
class Solution {
private:
    int helper(vector<int>& coins, int i, int target, vector<vector<int>>& dp) {
        if (i == 0) {
            return (target % coins[0] == 0 ? 1 : 0);
        }

        if (dp[i][target] != -1) {
            return dp[i][target];
        }

        int notTake = helper(coins, i-1, target, dp);
        int take = 0;

        if (coins[i] <= target) {
            take = helper(coins, i, target - coins[i], dp);
        }

        return dp[i][target] = take + notTake;
    }

public:
    int change(int amount, vector<int>& coins) {
        int n = coins.size();

        vector<vector<int>> dp(n, vector<int>(amount+1, -1));

        return helper(coins, n-1, amount, dp);
    }
};

// tabulation
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        int n = coins.size();

        vector<vector<int>> dp(n+1, vector<int>(amount+1, 0));

        for (int target=0; target<=amount; target++) {
            if (target % coins[0] == 0) {
                dp[0][target] = 1;
            }
            else {
                dp[0][target] = 0;
            }
        }

        for (int i=1; i<n; i++) {
            for (int target=0; target<=amount; target++) {
                long long notTake = dp[i-1][target];
                long long take = 0;

                if (coins[i] <= target) {
                    take = dp[i][target - coins[i]];
                }

                dp[i][target] = take + notTake;
            }
        }

        return dp[n-1][amount];
    }
};

// space optimization
class Solution {
public:
    int change(int amount, vector<int>& coins) {
        int n = coins.size();

        vector<int> curr(amount+1, 0), prev(amount+1, 0);

        for (int target=0; target<=amount; target++) {
            if (target % coins[0] == 0) {
                prev[target] = 1;
            }
            else {
                prev[target] = 0;
            }
        }

        for (int i=1; i<n; i++) {
            for (int target=0; target<=amount; target++) {
                long long notTake = prev[target];
                long long take = 0;

                if (coins[i] <= target) {
                    take = curr[target - coins[i]];
                }

                curr[target] = take + notTake;
            }

            prev = curr;
        }

        return prev[amount];
    }
};