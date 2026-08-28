class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();

        // Count characters
        vector<int> cnt(26, 0);
        for (char c : s)
            cnt[c - 'a']++;

        // Check whether a palindrome is possible
        int odd = 0;
        char mid = 0;

        for (int i = 0; i < 26; i++) {
            if (cnt[i] % 2) {
                odd++;
                mid = char('a' + i);
            }
        }

        if (odd > 1)
            return "";

        int m = n / 2;

        // half[c] = number of c's available in left half
        vector<int> half(26);

        for (int i = 0; i < 26; i++)
            half[i] = cnt[i] / 2;

        /*
         * First check whether target's first half can be used
         * exactly.
         */
        vector<int> rem = half;
        bool possible = true;

        for (int i = 0; i < m; i++) {
            int c = target[i] - 'a';

            if (rem[c] == 0) {
                possible = false;
                break;
            }

            rem[c]--;
        }

        /*
         * If we can use target's first half exactly,
         * construct the palindrome and check it.
         */
        if (possible) {
            string left = target.substr(0, m);

            string ans = left;

            if (n % 2)
                ans += mid;

            string right = left;
            reverse(right.begin(), right.end());

            ans += right;

            if (ans > target)
                return ans;
        }

        /*
         * Now find the rightmost position where we can
         * increase target[i].
         *
         * For every i, we check whether target[0...i-1]
         * can be kept unchanged.
         */
        for (int i = m - 1; i >= 0; i--) {

            // Rebuild remaining counts after using prefix [0..i-1]
            rem = half;

            bool ok = true;

            for (int j = 0; j < i; j++) {
                int c = target[j] - 'a';

                if (rem[c] == 0) {
                    ok = false;
                    break;
                }

                rem[c]--;
            }

            if (!ok)
                continue;

            int cur = target[i] - 'a';

            // Try the smallest character greater than target[i]
            for (int c = cur + 1; c < 26; c++) {

                if (rem[c] == 0)
                    continue;

                // Put c at position i
                rem[c]--;

                string left = target.substr(0, i);
                left += char('a' + c);

                // Fill remaining positions with smallest chars
                for (int x = 0; x < 26; x++) {
                    while (rem[x] > 0) {
                        left += char('a' + x);
                        rem[x]--;
                    }
                }

                // Build palindrome
                string right = left;
                reverse(right.begin(), right.end());

                string ans = left;

                if (n % 2)
                    ans += mid;

                ans += right;

                return ans;
            }
        }

        return "";
    }
};