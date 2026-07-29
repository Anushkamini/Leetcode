class Solution {
public:
    const long long LIMIT = 1000001;
    vector<long long> C[5005];

    long long comb(int n, int r) {
        if (r < 0 || r > n) return 0;
        if (r == 0 || r == n) return 1;
        if (C[n].empty()) C[n].assign(r + 1, -1);
        if (r >= (int)C[n].size()) C[n].resize(r + 1, -1);
        if (C[n][r] != -1) return C[n][r];

        __int128 ans = 1;
        for (int i = 1; i <= r; i++) {
            ans = ans * (n - r + i) / i;
            if (ans > LIMIT) return C[n][r] = LIMIT;
        }
        return C[n][r] = min((long long)ans, LIMIT);
    }

    long long ways(vector<int>& cnt) {
        int rem = 0;
        for (int x : cnt) rem += x;

        long long ans = 1;
        int left = rem;

        for (int x : cnt) {
            if (x == 0) continue;
            ans *= comb(left, x);
            if (ans > LIMIT) ans = LIMIT;
            left -= x;
        }
        return ans;
    }

    string smallestPalindrome(string s, int k) {
        vector<int> freq(26), half(26);
        string mid = "";

        for (char c : s) freq[c - 'a']++;

        for (int i = 0; i < 26; i++) {
            half[i] = freq[i] / 2;
            if (freq[i] & 1) mid += char('a' + i);
        }

        if (ways(half) < k) return "";

        string first = "";
        int len = 0;
        for (int x : half) len += x;

        for (int pos = 0; pos < len; pos++) {
            for (int c = 0; c < 26; c++) {
                if (half[c] == 0) continue;

                half[c]--;
                long long cnt = ways(half);

                if (cnt >= k) {
                    first += char('a' + c);
                    break;
                }

                k -= cnt;
                half[c]++;
            }
        }

        string second = first;
        reverse(second.begin(), second.end());
        return first + mid + second;
    }
};