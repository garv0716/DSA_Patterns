#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxChVal(const vector<int>& ch) {
        int maxi = 0;

        for (int x : ch) {
            maxi = max(maxi, x);
        }

        return maxi;
    }

    int characterReplacement(string s, int k) {
        int low = 0;
        int res = 0;

        vector<int> count(26, 0);

        for (int high = 0; high < s.size(); high++) {

            // Include current character in the window
            count[s[high] - 'A']++;

            int len = high - low + 1;
            int maxCount = maxChVal(count);
            int diff = len - maxCount;

            // Shrink window if replacements needed exceed k
            while (diff > k) {
                count[s[low] - 'A']--;
                low++;

                len = high - low + 1;
                maxCount = maxChVal(count);
                diff = len - maxCount;
            }

            // Update answer
            res = max(res, len);
        }

        return res;
    }
};

int main() {
    Solution sol;

    string s1 = "ABAB";
    int k1 = 2;

    cout << "Output: "
         << sol.characterReplacement(s1, k1)
         << endl;   // 4

    string s2 = "AABABBA";
    int k2 = 1;

    cout << "Output: "
         << sol.characterReplacement(s2, k2)
         << endl;   // 4

    return 0;
}