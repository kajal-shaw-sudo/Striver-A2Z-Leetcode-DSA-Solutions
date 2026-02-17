// problem : https://leetcode.com/problems/unique-paths-ii/description/

// recursion
class Solution {
private:
    int helper(vector<vector<int>>& obstacleGrid, int i, int j) {
        if (i >=0 && j >=0 && obstacleGrid[i][j] == 1) {
            return 0;
        }

        if (i == 0 && j == 0) {
            return 1;
        }

        if (i < 0 || j < 0) {
            return 0;
        }

        int up = helper(obstacleGrid, i-1, j);
        int left = helper(obstacleGrid, i, j-1);

        return up + left;
    }
    
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int n = obstacleGrid.size(), m = obstacleGrid[0].size();

        return helper(obstacleGrid, n-1, m-1);
    }
};

// memoization
class Solution {
private:
    int helper(vector<vector<int>>& obstacleGrid, int i, int j, vector<vector<int>>& dp) {
        if (i >=0 && j >=0 && obstacleGrid[i][j] == 1) {
            return 0;
        }

        if (i == 0 && j == 0) {
            return 1;
        }

        if (i < 0 || j < 0) {
            return 0;
        }

        if (dp[i][j] != -1) {
            return dp[i][j];
        }

        int up = helper(obstacleGrid, i-1, j, dp);
        int left = helper(obstacleGrid, i, j-1, dp);

        return dp[i][j] = up + left;
    }

public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int n = obstacleGrid.size(), m = obstacleGrid[0].size();

        vector<vector<int>> dp(n, vector<int> (m, -1));

        return helper(obstacleGrid, n-1, m-1, dp);
    }
};

// tabulation
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int n = obstacleGrid.size(), m = obstacleGrid[0].size();

        vector<vector<int>> dp(n+1, vector<int> (m+1, 0));

        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) {
                if (i >= 0 && j >=0 && obstacleGrid[i][j] == 1) {
                    dp[i][j] = 0;
                }
                else if (i == 0 && j == 0) {
                    dp[i][j] = 1;
                }
                else {
                    int up = 0, left = 0;

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

        return dp[n-1][m-1];
    }
};

// space optimization
class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
        int n = obstacleGrid.size(), m = obstacleGrid[0].size();

        vector<int> curr(m+1, 0), prev(m+1, 0);

        for (int i=0; i<n; i++) {
            for (int j=0; j<m; j++) {
                if (i >= 0 && j >=0 && obstacleGrid[i][j] == 1) {
                    curr[j] = 0;
                }
                else if (i == 0 && j == 0) {
                    curr[j] = 1;
                }
                else {
                    int up = 0, left = 0;

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

        return prev[m-1];
    }
};