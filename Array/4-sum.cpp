// problem: https://leetcode.com/problems/4sum/description/

// brute
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int n = nums.size();

        set<vector<int>> st;

        for (int i=0; i<n; i++) {
            for (int j=i+1; j<n; j++) {
                for (int k=j+1; k<n; k++) {
                    for (int l=k+1; l<n; l++) {
                        long long sum = (long long)nums[i] + nums[j] + nums[k] + nums[l];

                        if ((int)sum == target) {
                            vector<int> temp = {nums[i], nums[j], nums[k], nums[l]};
                            sort(temp.begin(), temp.end());
                            st.insert(temp);
                        }
                    }
                }
            }
        }

        return vector<vector<int>> (st.begin(), st.end());
    }
};

// better
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int n = nums.size();

        set<vector<int>> st;

        for (int i=0; i<n; i++) {
            for (int j=i+1; j<n; j++) {
                unordered_set<int> hash;
                for (int k=j+1; k<n; k++) {
                    long long fourth = 1LL * target - nums[i] - nums[j] - nums[k];

                    if (fourth > INT_MAX || fourth < INT_MIN) {
                        continue;
                    }
                    
                    if (hash.find(fourth) != hash.end()) {
                        vector<int> temp = {nums[i], nums[j], nums[k], (int)fourth};
                        sort(temp.begin(), temp.end());
                        st.insert(temp);
                    }

                    hash.insert(nums[k]);
                }
            }
        }

        return vector<vector<int>> (st.begin(), st.end());
    }
};

// optimal
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        int n = nums.size();

        sort(nums.begin(), nums.end());

        vector<vector<int>> ans;

        for (int i=0; i<n; i++) {
            if (i > 0 && nums[i] == nums[i-1]) {
                continue;
            }

            for (int j=i+1; j<n; j++) {
                if (j > i+1 && nums[j] == nums[j-1]) {
                    continue;
                }

                int k = j+1, l = n-1;

                while (k < l) {
                    long long sum = (long long) nums[i] + nums[j] + nums[k] + nums[l];

                    if (sum == target) {
                        ans.push_back({nums[i], nums[j], nums[k], nums[l]});
                        k++, l--;

                        while (k < l && nums[k] == nums[k-1]) {
                            k++;
                        }

                        while (k < l && nums[l] == nums[l+1]) {
                            l--;
                        }
                    }
                    else if (sum < target) {
                        k++;
                    }
                    else {
                        l--;
                    }
                }
            }
        }

        return ans;
    }
};