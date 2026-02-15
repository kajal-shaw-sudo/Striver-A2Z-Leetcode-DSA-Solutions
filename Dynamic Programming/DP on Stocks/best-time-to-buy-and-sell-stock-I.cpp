// problem : https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/

// brute
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();

        int maxProfit = 0;

        for (int i=0; i<n; i++) {
            for (int j=i+1; j<n; j++) {
                int profit = prices[j] - prices[i];
                maxProfit = max(maxProfit, profit);
            }
        }

        return maxProfit;
    }
};


// optimal
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();

        int maxProfit = 0;

        int minPrice = prices[0];

        for (int i=1; i<n; i++) {
            int profit = prices[i] - minPrice;
            maxProfit = max(maxProfit, profit);
            minPrice = min(minPrice, prices[i]);
        }

        return maxProfit;
    }
};