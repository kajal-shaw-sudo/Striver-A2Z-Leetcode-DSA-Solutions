// problem : https://leetcode.com/problems/climbing-stairs/description/

// recursion
class Solution {
private:
    int helper(int i) {
        if (i <= 1) {
            return 1;
        }

        return helper(i-1) + helper(i-2);
    }
    
public:
    int climbStairs(int n) {
        return helper(n);
    }
};

// memoization
class Solution {
private:
    int helper(int i, vector<int>& dp) {
        if (i <= 1) {
            return 1;
        }

        if (dp[i] != -1) {
            return dp[i];
        }

        return dp[i] = helper(i-1, dp) + helper(i-2, dp);
    }

public:
    int climbStairs(int n) {
        vector<int> dp(n+1, -1);
        return helper(n, dp);
    }
};

// tabulation
class Solution {
public:
    int climbStairs(int n) {
        vector<int> dp(n+1, 0);

        dp[0] = dp[1] = 1;

        for (int i=2; i<=n; i++) {
            dp[i] = dp[i-1] + dp[i-2];
        }

        return dp[n];
    }
};

// space optimization
class Solution {
public:
    int climbStairs(int n) {
        int curr, prev, prev2;

        prev2 = prev = 1;

        for (int i=2; i<=n; i++) {
            curr = prev + prev2;

            prev2 = prev;
            prev = curr;
        }

        return prev;
    }
};