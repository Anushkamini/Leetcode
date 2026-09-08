class Solution {
public:
    int countCommas(int n) {
         long long ans = 0;
        for (long long x = 1000; x <= n; x *= 1000) {
            ans += n - x + 1;
        }
        return ans;
    }
};