// problem : https://leetcode.com/problems/minimum-path-sum/description/

// recursion
class Solution {
private:
    int helper(vector<vector<int>>& grid, int i, int j) {
        if (i == 0 && j == 0) {
            return grid[0][0];
        }

        if (i < 0 || j < 0) {
            return 1e9;
        }

        int up = grid[i][j] + helper(grid, i-1, j);
        int left = grid[i][j] + helper(grid, i, j-1);

        return min(up, left);
    }

public:
    int minPathSum(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();

        return helper(grid, n-1, m-1);
    }
};

// memoization
class Solution {
private:
    int helper(vector<vector<int>>& grid, int i, int j, vector<vector<int>>& dp) {
        if (i == 0 && j == 0) {
            return grid[0][0];
        }

        if (i < 0 || j < 0) {
            return 1e9;
        }

        if (dp[i][j] != -1) {
            return dp[i][j];
        }

        int up = grid[i][j] + helper(grid, i-1, j, dp);
        int left = grid[i][j] + helper(grid, i, j-1, dp);

        return dp[i][j] = min(up, left);
    }

public:
    int minPathSum(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();

        vector<vector<int>> dp(n, vector<int> (m, -1));

        return helper(grid, n-1, m-1, dp);
    }
};

// tabulation
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();

        vector<vector<int>> dp(n+1, vector<int> (m+1, 0));

        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) {
                if (i == 0 && j == 0) {
                    dp[i][j] = grid[i][j];
                }
                else {
                    int up = 0, left = 0;

                    if (i > 0) {
                        up = grid[i][j] + dp[i-1][j];
                    }
                    else {
                        up = 1e9;
                    }

                    if (j > 0) {
                        left = grid[i][j] + dp[i][j-1];
                    }
                    else {
                        left = 1e9;
                    }

                    dp[i][j] = min(up, left);
                }
            }
        }

        return dp[n-1][m-1];
    }
};

// space optimization
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();

        vector<int> curr(m+1, 0), prev(m+1, 0);

        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) {
                if (i == 0 && j == 0) {
                    curr[j] = grid[i][j];
                }
                else {
                    int up = 0, left = 0;

                    if (i > 0) {
                        up = grid[i][j] + prev[j];
                    }
                    else {
                        up = 1e9;
                    }

                    if (j > 0) {
                        left = grid[i][j] + curr[j-1];
                    }
                    else {
                        left = 1e9;
                    }

                    curr[j] = min(up, left);
                }
            }

            prev = curr;
        }

        return prev[m-1];
    }
};