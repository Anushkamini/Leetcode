class Solution {
public:
    int maximumLengthSubstring(string s) {
       int charCount[26] = {0};
        int maxLength = 0;
        int left = 0;

        for (int right = 0; right < s.length(); ++right) {
            int currentCharIndex = s[right] - 'a';
            ++charCount[currentCharIndex];
            while (charCount[currentCharIndex] > 2) {
                int leftCharIndex = s[left] - 'a';
                --charCount[leftCharIndex];
                ++left;
            }
            int currentWindowSize = right - left + 1;
            maxLength = max(maxLength, currentWindowSize);
        }  
        return maxLength;  
    }
};