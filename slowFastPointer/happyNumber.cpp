#include <iostream>
using namespace std;

class Solution {
public:
    int sqSum(int n) {
        int sum = 0;

        while (n > 0) {
            int d = n % 10;
            n = n / 10;
            sum = sum + d * d;
        }

        return sum;
    }

    bool isHappy(int n) {
        int slow = n;
        int fast = n;

        slow = sqSum(slow);
        fast = sqSum(sqSum(fast));

        while (slow != fast) {
            slow = sqSum(slow);
            fast = sqSum(sqSum(fast));
        }

        return slow == 1;
    }
};

int main() {
    Solution obj;

    int n;
    cout << "Enter a number: ";
    cin >> n;

    if (obj.isHappy(n)) {
        cout << n << " is a Happy Number" << endl;
    } else {
        cout << n << " is NOT a Happy Number" << endl;
    }

    return 0;
}