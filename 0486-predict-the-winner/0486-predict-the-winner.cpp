class Solution {
public:
    bool predictTheWinner(vector<int>& nums) {
        int n = nums.size();
        // dp[i][j] represents the maximum score difference (current player - opponent)
        // when playing optimally on subarray nums[i...j]
        vector<vector<int>> dp(n, vector<int>(n));
      
        // Recursive function with memoization to calculate optimal score difference
        auto calculateScoreDifference = [&](this auto&& calculateScoreDifference, int left, int right) -> int {
            // Base case: no elements left to choose
            if (left > right) {
                return 0;
            }
          
            // Return memoized result if already computed
            if (dp[left][right] != 0) {
                return dp[left][right];
            }
          
            // Current player has two choices:
            // 1. Take nums[left]: gain nums[left] points, opponent plays optimally on [left+1, right]
            int takeLeft = nums[left] - calculateScoreDifference(left + 1, right);
          
            // 2. Take nums[right]: gain nums[right] points, opponent plays optimally on [left, right-1]
            int takeRight = nums[right] - calculateScoreDifference(left, right - 1);
          
            // Store and return the maximum score difference achievable
            return dp[left][right] = max(takeLeft, takeRight);
        };
      
        // Player 1 wins if their score difference is non-negative
        return calculateScoreDifference(0, n - 1) >= 0;
    }
};