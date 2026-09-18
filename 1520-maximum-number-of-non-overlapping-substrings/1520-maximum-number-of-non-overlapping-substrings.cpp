class Solution {
public:
    vector<string> maxNumOfSubstrings(string s) {

        int n = s.size();

        vector<int> first(26, n);
        vector<int> last(26, -1);

        // Step 1: Find first and last occurrence
        for (int i = 0; i < n; i++) {

            int c = s[i] - 'a';

            first[c] = min(first[c], i);
            last[c] = i;
        }

        vector<pair<int, int>> intervals;

        // Step 2: Find valid intervals
        for (int c = 0; c < 26; c++) {

            if (last[c] == -1)
                continue;

            int l = first[c];
            int r = last[c];

            bool valid = true;

            for (int i = l; i <= r; i++) {

                int current = s[i] - 'a';

                // Character appeared before l
                if (first[current] < l) {
                    valid = false;
                    break;
                }

                // Expand interval
                r = max(r, last[current]);
            }

            if (valid) {
                intervals.push_back({l, r});
            }
        }

        // Step 3: Sort intervals by ending position
        sort(intervals.begin(), intervals.end(),
             [](pair<int, int> a, pair<int, int> b) {

                 return a.second < b.second;
             });

        vector<string> ans;

        int prevEnd = -1;

        // Step 4: Greedy selection
        for (auto interval : intervals) {

            int l = interval.first;
            int r = interval.second;

            if (l > prevEnd) {

                ans.push_back(s.substr(l, r - l + 1));

                prevEnd = r;
            }
        }

        return ans;
    }
};