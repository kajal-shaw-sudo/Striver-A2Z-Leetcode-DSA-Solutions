// problem : https://leetcode.com/problems/house-robber/description/

// recursion
class Solution {
private:
    int helper(vector<int>& nums, int i) {
        if (i == 0) {
            return nums[0];
        }

        if (i < 0) {
            return 0;
        }
        
        int notTake = 0 + helper(nums, i-1);
        int take = nums[i] + helper(nums, i-2);

        return max(take, notTake);
    }

public:
    int rob(vector<int>& nums) {
        int n = nums.size();

        return helper(nums, n-1);
    }
};

// memoization
class Solution {
private:
    int helper(vector<int>& nums, int i, vector<int>& dp) {
        if (i == 0) {
            return nums[0];
        }

        if (i < 0) {
            return 0;
        }

        if (dp[i] != -1) {
            return dp[i];
        }
        
        int notTake = 0 + helper(nums, i-1, dp);
        int take = nums[i] + helper(nums, i-2, dp);

        return dp[i] = max(take, notTake);
    }

public:
    int rob(vector<int>& nums) {
        int n = nums.size();

        vector<int> dp(n, -1);

        return helper(nums, n-1, dp);
    }
};

// tabulation
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();

        vector<int> dp(n, 0);

        dp[0] = nums[0];

        for (int i=1; i<n; i++) {
            int notTake = 0 + dp[i-1];
            int take = nums[i];

            if (i > 1) {
                take += dp[i-2];
            }

            dp[i] = max(take, notTake);
        }

        return dp[n-1];
    }
};

// space optimization
class Solution {
public:
    int rob(vector<int>& nums) {
        int n = nums.size();

        int curr, prev, prev2;

        prev2 = 0, prev = nums[0];

        for (int i=1; i<n; i++) {
            int notTake = 0 + prev;
            int take = nums[i];

            if (i > 1) {
                take += prev2;
            }

            curr = max(take, notTake);

            prev2 = prev;
            prev = curr;
        }

        return prev;
    }
};