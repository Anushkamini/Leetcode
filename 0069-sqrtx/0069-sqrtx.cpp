class Solution {
public:
    int mySqrt(int x) {
          if (x < 2) // check  for 0 and 1
            return x;

        int left = 1, right = x / 2;
        int ans = 0;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if ((long long)mid * mid == x)
                return mid;

            if ((long long)mid * mid < x) {
                ans = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        return ans; 
    }
};