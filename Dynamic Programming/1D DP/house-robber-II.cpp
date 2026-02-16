// problem : https://leetcode.com/problems/house-robber-ii/description/

// recursion
class Solution {
private:
    long long helper(vector<long long>& temp, int i) {
        if (i == 0) {
            return temp[0];
        }

        if (i < 0) {
            return 0;
        }

        int notTake = 0 + helper(temp, i-1);
        int take = temp[i] + helper(temp, i-2);

        return max(take, notTake);
    }

    long long maxNonAdjacentSum(vector<long long>& temp) {
        int n = temp.size();

        return helper(temp, n-1);
    }

public:
    int rob(vector<int>& nums) {
        int n = nums.size();

        if (n == 0) {
            return 0;
        }

        if (n == 1) {
            return nums[0];
        }

        vector<long long> temp1, temp2;

        for (int i=0; i<n; i++) {
            if (i != n-1) {
                temp1.push_back(nums[i]);
            }
            if (i != 0) {
                temp2.push_back(nums[i]);
            }
        }

        return max((int)maxNonAdjacentSum(temp1), (int)maxNonAdjacentSum(temp2));
    }
};

// memoization
class Solution {
private:
    long long helper(vector<long long>& temp, int i, vector<long long>& dp) {
        if (i == 0) {
            return temp[0];
        }

        if (i < 0) {
            return 0;
        }

        if (dp[i] != -1) {
            return dp[i];
        }

        int notTake = 0 + helper(temp, i-1, dp);
        int take = temp[i] + helper(temp, i-2, dp);

        return dp[i] = max(take, notTake);
    }

    long long maxNonAdjacentSum(vector<long long>& temp) {
        int n = temp.size();

        vector<long long> dp(n, -1);

        return helper(temp, n-1, dp);
    }

public:
    int rob(vector<int>& nums) {
        int n = nums.size();

        if (n == 0) {
            return 0;
        }

        if (n == 1) {
            return nums[0];
        }

        vector<long long> temp1, temp2;

        for (int i=0; i<n; i++) {
            if (i != n-1) {
                temp1.push_back(nums[i]);
            }
            if (i != 0) {
                temp2.push_back(nums[i]);
            }
        }

        return max((int)maxNonAdjacentSum(temp1), (int)maxNonAdjacentSum(temp2));
    }
};

// tabulation
class Solution {
    long long maxNonAdjacentSum(vector<long long>& temp) {
        int n = temp.size();

        vector<long long> dp(n, 0);

        dp[0] = temp[0];

        for (int i=1; i<n; i++) {
            int notTake = 0 + dp[i-1];
            int take = temp[i];

            if (i > 1) {
                take += dp[i-2];
            }

            dp[i] = max(take, notTake);
        }

        return dp[n-1];
    }

public:
    int rob(vector<int>& nums) {
        int n = nums.size();

        if (n == 0) {
            return 0;
        }

        if (n == 1) {
            return nums[0];
        }

        vector<long long> temp1, temp2;

        for (int i=0; i<n; i++) {
            if (i != n-1) {
                temp1.push_back(nums[i]);
            }
            if (i != 0) {
                temp2.push_back(nums[i]);
            }
        }

        return max((int)maxNonAdjacentSum(temp1), (int)maxNonAdjacentSum(temp2));
    }
};

// space optimization
class Solution {
    long long maxNonAdjacentSum(vector<long long>& temp) {
        int n = temp.size();

        int curr, prev, prev2;

        prev2 = 0, prev = temp[0];

        for (int i=1; i<n; i++) {
            int notTake = 0 + prev;
            int take = temp[i];

            if (i > 1) {
                take += prev2;
            }

            curr = max(take, notTake);

            prev2 = prev;
            prev = curr;
        }

        return prev;
    }

public:
    int rob(vector<int>& nums) {
        int n = nums.size();

        if (n == 0) {
            return 0;
        }

        if (n == 1) {
            return nums[0];
        }

        vector<long long> temp1, temp2;

        for (int i=0; i<n; i++) {
            if (i != n-1) {
                temp1.push_back(nums[i]);
            }
            if (i != 0) {
                temp2.push_back(nums[i]);
            }
        }

        return max((int)maxNonAdjacentSum(temp1), (int)maxNonAdjacentSum(temp2));
    }
};