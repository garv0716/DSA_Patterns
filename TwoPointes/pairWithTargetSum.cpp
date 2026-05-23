#include<iostream>
#include<vector>
using namespace std;

vector<int> twoSum(vector<int>& numbers, int target) {
        int n = numbers.size() - 1;
        int start = 0;
        int end = n;

        while(start < end){
            if (numbers[start] + numbers[end] == target){
                return {start + 1 , end + 1};
            }
            else if (numbers[start] + numbers[end] < target){
                start ++;
            }
            else if(numbers[start]+numbers[end] > target){
                end --;
            }
        }
        return {};
}
int main(){
    vector<int>numbers{2,7,11,15};
    int target = 9;
    twoSum(numbers, target);
    return 0;
}