class Solution {
public:
    static const int MOD = 1000000007;

    vector<int> sumAndMultiply(string s, vector<vector<int>>& queries) {
        int n = s.size();

        vector<int> pos, digit;

        // Store positions and values of non-zero digits
        for (int i = 0; i < n; i++) {
            if (s[i] != '0') {
                pos.push_back(i);
                digit.push_back(s[i] - '0');
            }
        }

        int k = digit.size();

        // Powers of 10 modulo MOD
        vector<long long> power10(k + 1, 1);
        for (int i = 1; i <= k; i++) {
            power10[i] = (power10[i - 1] * 10) % MOD;
        }

        // Prefix concatenated number
        vector<long long> prefixNum(k + 1, 0);
        for (int i = 0; i < k; i++) {
            prefixNum[i + 1] = (prefixNum[i] * 10 + digit[i]) % MOD;
        }

        // Prefix sum of digits
        vector<long long> prefixSum(k + 1, 0);
        for (int i = 0; i < k; i++) {
            prefixSum[i + 1] = prefixSum[i] + digit[i];
        }

        vector<int> ans;

        for (auto &q : queries) {
            int l = q[0];
            int r = q[1];

            int L = lower_bound(pos.begin(), pos.end(), l) - pos.begin();
            int R = upper_bound(pos.begin(), pos.end(), r) - pos.begin() - 1;

            if (L > R) {
                ans.push_back(0);
                continue;
            }

            int len = R - L + 1;

            long long x = (prefixNum[R + 1]
                          - (prefixNum[L] * power10[len]) % MOD
                          + MOD) % MOD;

            long long sum = prefixSum[R + 1] - prefixSum[L];

            ans.push_back((x * (sum % MOD)) % MOD);
        }

        return ans;
    }
};