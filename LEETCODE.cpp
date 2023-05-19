#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
        vector<int> newNums;
        for (int i=0; i<nums.size()-1; i++){
            int count = 0;
            for (int j=i+1; j<nums.size();j++){
                if (nums[i] > nums[j]){
                    count++;
                }
            }
            newNums.push_back(count);
        }
        newNums.push_back(0);
        return newNums;
    }

// vector<int> quickSort(vector<int>& nums);

// vector<int> smallerNumbersThanCurrent(vector<int> &nums)
// {
//     nums = quickSort(nums);
//     int initialSize = nums.size();
    
//     for (int i: nums){
//          nums.push_back(nums.size() - i);
//     }
//     nums.erase(nums.begin(),nums.begin()+initialSize);
//     cout << endl;
    
//     return nums;
// }

// vector<int> quickSort(vector<int>& nums){
//     if (nums.size() <= 1) {
//         return nums;
//     }
    
//     vector<int> less;
//     vector<int> more;
//     int pivot = nums[0];
    
//     for (int i = 1; i < nums.size(); i++){
//         if (nums[i] < pivot) {
//             less.push_back(nums[i]);
//         } else {
//             more.push_back(nums[i]);
//         }
//     }
    
//     vector<int> sortedLess = quickSort(less);
//     vector<int> sortedMore = quickSort(more);
//     sortedLess.push_back(pivot);
//     sortedLess.insert(sortedLess.end(), sortedMore.begin(), sortedMore.end());
    
//     return sortedLess;
// }

int main()
{
    vector<int> ints = {5,2,6,1};
    for (int i:smallerNumbersThanCurrent(ints)){
        cout << i << " ";
    }

    
//     vector<int> result = smallerNumbersThanCurrent(ints);
    
//     for (int i: result){
//         cout << i << " ";
//     }
//     cout << endl;
}
