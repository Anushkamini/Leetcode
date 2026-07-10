class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
        vector<pair<int,int>> arr;
        for (int i = 0; i < n; i++)
            arr.push_back({nums[i], i});

        sort(arr.begin(), arr.end());

        vector<int> val(n), pos(n), comp(n);

        for (int i = 0; i < n; i++) {
            val[i] = arr[i].first;
            pos[arr[i].second] = i;
        }

        int cid = 0;
        comp[0] = 0;
        for (int i = 1; i < n; i++) {
            if (val[i] - val[i - 1] > maxDiff)
                cid++;
            comp[i] = cid;
        }

        const int LOG = 18;

        vector<vector<int>> right(LOG, vector<int>(n));
        vector<vector<int>> left(LOG, vector<int>(n));

        int r = 0;
        for (int i = 0; i < n; i++) {
            while (r + 1 < n && val[r + 1] - val[i] <= maxDiff)
                r++;
            right[0][i] = r;
        }

        int l = 0;
        for (int i = 0; i < n; i++) {
            while (val[i] - val[l] > maxDiff)
                l++;
            left[0][i] = l;
        }

        for (int k = 1; k < LOG; k++) {
            for (int i = 0; i < n; i++) {
                right[k][i] = right[k - 1][right[k - 1][i]];
                left[k][i] = left[k - 1][left[k - 1][i]];
            }
        }

        vector<int> ans;

        for (auto &q : queries) {
            int u = pos[q[0]];
            int v = pos[q[1]];

            if (u == v) {
                ans.push_back(0);
                continue;
            }

            if (comp[u] != comp[v]) {
                ans.push_back(-1);
                continue;
            }

            if (u < v) {
                int cur = u;
                int steps = 0;
                for (int k = LOG - 1; k >= 0; k--) {
                    if (right[k][cur] < v) {
                        cur = right[k][cur];
                        steps += (1 << k);
                    }
                }
                ans.push_back(steps + 1);
            } else {
                int cur = u;
                int steps = 0;
                for (int k = LOG - 1; k >= 0; k--) {
                    if (left[k][cur] > v) {
                        cur = left[k][cur];
                        steps += (1 << k);
                    }
                }
                ans.push_back(steps + 1);
            }
        }

        return ans;
    }
};