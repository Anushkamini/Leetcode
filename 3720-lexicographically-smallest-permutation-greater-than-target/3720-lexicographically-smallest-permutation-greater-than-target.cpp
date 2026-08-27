class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
       int n = s.size();

        int cnt[26] = {};
        for (char c : s) {
            cnt[c - 'a']++;
        }

        string ans;

        for (int i = 0; i < n; i++) {

            // Try to keep the character equal to target[i]
            int x = target[i] - 'a';

            if (cnt[x] > 0) {
                ans += target[i];
                cnt[x]--;
                continue;
            }

            // Cannot match target[i].
            // Try to make the current position greater.
            for (int c = x + 1; c < 26; c++) {

                if (cnt[c] > 0) {
                    ans += char('a' + c);
                    cnt[c]--;

                    // Fill remaining positions with
                    // smallest possible characters.
                    for (int j = 0; j < 26; j++) {
                        while (cnt[j] > 0) {
                            ans += char('a' + j);
                            cnt[j]--;
                        }
                    }

                    return ans;
                }
            }

            // No greater character at this position.
            // Backtrack.
            while (!ans.empty()) {

                char last = ans.back();
                ans.pop_back();
                cnt[last - 'a']++;

                int pos = ans.size();

                int targetChar = target[pos] - 'a';

                // Try a character greater than target[pos]
                for (int c = targetChar + 1; c < 26; c++) {

                    if (cnt[c] > 0) {
                        ans += char('a' + c);
                        cnt[c]--;

                        // Fill the rest in increasing order.
                        for (int j = 0; j < 26; j++) {
                            while (cnt[j] > 0) {
                                ans += char('a' + j);
                                cnt[j]--;
                            }
                        }

                        return ans;
                    }
                }
            }

            return "";
        }

        // We matched target exactly.
        // Need a strictly greater permutation.
        while (!ans.empty()) {

            char last = ans.back();
            ans.pop_back();
            cnt[last - 'a']++;

            int pos = ans.size();
            int targetChar = target[pos] - 'a';

            for (int c = targetChar + 1; c < 26; c++) {

                if (cnt[c] > 0) {
                    ans += char('a' + c);
                    cnt[c]--;

                    for (int j = 0; j < 26; j++) {
                        while (cnt[j] > 0) {
                            ans += char('a' + j);
                            cnt[j]--;
                        }
                    }

                    return ans;
                }
            }
        }

        return "";
    }
};