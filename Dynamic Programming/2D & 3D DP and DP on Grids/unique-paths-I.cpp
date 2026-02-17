// problem : https://leetcode.com/problems/unique-paths/description/

// recursion
class Solution {
private:
    int helper(int i, int j) {
        if (i == 0 && j == 0) {
            return 1;
        }

        if (i < 0 || j < 0) {
            return 0;
        }

        int up = helper(i-1, j);
        int left = helper(i, j-1);

        return up + left;
    }
    
public:
    int uniquePaths(int m, int n) {
        return helper(m-1, n-1);
    }
};

// memoization
class Solution {
private:
    int helper(int i, int j, vector<vector<int>>& dp) {
        if (i == 0 && j == 0) {
            return 1;
        }

        if (i < 0 || j < 0) {
            return 0;
        }

        if (dp[i][j] != -1) {
            return dp[i][j];
        }

        int up = helper(i-1, j, dp);
        int left = helper(i, j-1, dp);

        return dp[i][j] = up + left;
    }

public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m, vector<int> (n, -1));

        return helper(m-1, n-1, dp);
    }
};

// tabulation
class Solution {
private:
    int helper(int i, int j, vector<vector<int>>& dp) {
        if (i == 0 && j == 0) {
            return 1;
        }

        if (i < 0 || j < 0) {
            return 0;
        }

        if (dp[i][j] != -1) {
            return dp[i][j];
        }

        int up = helper(i-1, j, dp);
        int left = helper(i, j-1, dp);

        return dp[i][j] = up + left;
    }

public:
    int uniquePaths(int m, int n) {
        vector<vector<int>> dp(m+1, vector<int> (n+1, 0));

        dp[0][0] = 1;

        for (int i=0; i<m; i++) {
            for (int j=0; j<n; j++) {
                if (i == 0 && j == 0) {
                    dp[i][j] = 1;
                }
                else {
                    int left = 0, up = 0;

                    if (i > 0) {
                        up = dp[i-1][j];
                    }

                    if (j > 0) {
                        left = dp[i][j-1];
                    }

                    dp[i][j] = up + left;
                }
            }
        }

        return dp[m-1][n-1];
    }
};

// space optimization
class Solution {
public:
    int uniquePaths(int m, int n) {
        vector<int> curr(n+1, 0), prev(n+1, 0);

        prev[0] = 1;

        for (int i=0; i<m; i++) {
            for (int j=0; j<n; j++) {
                if (i == 0 && j == 0) {
                    curr[j] = 1;
                }
                else {
                    int left = 0, up = 0;

                    if (i > 0) {
                        up = prev[j];
                    }

                    if (j > 0) {
                        left = curr[j-1];
                    }

                    curr[j] = up + left;
                }
            }

            prev = curr;
        }

        return prev[n-1];
    }
};