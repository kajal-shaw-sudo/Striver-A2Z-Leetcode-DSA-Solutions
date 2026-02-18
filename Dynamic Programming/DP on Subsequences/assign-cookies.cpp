// problem : https://leetcode.com/problems/assign-cookies/description/

// greedy approach : sort the greed factor and the cookie size, then use two pointers to assign cookies to children
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());

        int n = g.size(), m = s.size();

        int i = 0, j = 0;  // child - i, cookie - j
        int count = 0;

        while (i < n && j < m) {
            if (g[i] <= s[j]) {
                count++;
                i++;
            }

            j++;
        }

        return count;
    }
};

// recursion
class Solution {
private:
    int helper(vector<int>& g, int i, vector<int>& s, int j) {
        if (i >= g.size() || j >= s.size()) {
            return 0;
        }

        int notTake = 0 + helper(g, i, s, j+1);
        int take = 0;

        if (g[i] <= s[j]) {
            take = 1 + helper(g, i+1, s, j+1);
        }

        return max(take, notTake);
    }
    
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());

        int n = g.size(), m = s.size();

        return helper(g, 0, s, 0);
    }
};

// memoization
class Solution {
private:
    int helper(vector<int>& g, int i, vector<int>& s, int j, vector<vector<int>>& dp) {
        if (i >= g.size() || j >= s.size()) {
            return 0;
        }

        if (dp[i][j] != -1) {
            return dp[i][j];
        }

        int notTake = 0 + helper(g, i, s, j+1, dp);
        int take = 0;

        if (g[i] <= s[j]) {
            take = 1 + helper(g, i+1, s, j+1, dp);
        }

        return dp[i][j] = max(take, notTake);
    }

public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());

        int n = g.size(), m = s.size();

        vector<vector<int>> dp(n, vector<int> (m, -1));

        return helper(g, 0, s, 0, dp);
    }
};

// tabulation
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());

        int n = g.size(), m = s.size();

        vector<vector<int>> dp(n+1, vector<int> (m+1, 0));

        for (int i=n-1;i>=0; i--) {
            for (int j=m-1; j>=0; j--) {

                if (g[i] <= s[j]) {
                    dp[i][j] = max(1 + dp[i+1][j+1], dp[i][j+1]);
                }
                else {
                    dp[i][j] = dp[i][j+1];
                }
            }
        }

        return dp[0][0];
    }
};

// space optimization
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());

        int n = g.size(), m = s.size();

        vector<int> curr(m+1, 0), front(m+1, 0);

        for (int i=n-1;i>=0; i--) {
            for (int j=m-1; j>=0; j--) {

                if (g[i] <= s[j]) {
                    curr[j] = max(1 + front[j+1], curr[j+1]);
                }
                else {
                    curr[j] = curr[j+1];
                }
            }

            front = curr;
        }

        return curr[0];
    }
};