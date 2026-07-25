class Solution {
public:
    int maxProduct(int n) {
           // Initialize variables to track the two largest digits
        int largestDigit = 0;      // Stores the largest digit found
        int secondLargestDigit = 0; // Stores the second largest digit found
      
        // Process each digit of the number from right to left
        while (n > 0) {
            // Extract the rightmost digit
            int currentDigit = n % 10;
          
            // Update the two largest digits based on current digit
            if (currentDigit > largestDigit) {
                // Current digit becomes the new largest
                // Previous largest becomes second largest
                secondLargestDigit = largestDigit;
                largestDigit = currentDigit;
            } else if (currentDigit > secondLargestDigit) {
                // Current digit is not the largest but is larger than second largest
                secondLargestDigit = currentDigit;
            }
       
            n /= 10;
        }
        return largestDigit * secondLargestDigit;
    }
};