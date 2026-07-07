class Solution {
public:
    long long sumAndMultiply(int n) {
        int x = 0;      // Concatenated non-zero number
        int sum = 0;    // Sum of non-zero digits
        int p = 1;      // Current place value

        while (n > 0) {
            int digit = n % 10;

            sum += digit;

            if (digit != 0) {
                x += digit * p;
                p *= 10;
            }

            n /= 10;
        }

        return 1LL * x * sum;
    }
};