class Solution {
public:
    int largestInteger(vector<int>& nums, int k) {
        int n = nums.size();
        int count[51] = {};

        // Count how many k-sized subarrays contain each number
        for (int i = 0; i <= n - k; i++) {
            bool present[51] = {};

            for (int j = i; j < i + k; j++) {
                present[nums[j]] = true;
            }

            for (int x = 0; x <= 50; x++) {
                if (present[x]) {
                    count[x]++;
                }
            }
        }

        // Find the largest number appearing in exactly one window
        int ans = -1;

        for (int x = 0; x <= 50; x++) {
            if (count[x] == 1) {
                ans = x;
            }
        }

        return ans;
    }
};