class Solution {
public:
    vector<int> frequencySort(vector<int>& nums) {
        unordered_map<int, int> freq;

        // Count frequency
        for (int x : nums) {
            freq[x]++;
        }

        // Sort
        sort(nums.begin(), nums.end(), [&](int a, int b) {
            if (freq[a] != freq[b])
                return freq[a] < freq[b];

            return a > b;   // larger value first
        });

        return nums;
    }
};