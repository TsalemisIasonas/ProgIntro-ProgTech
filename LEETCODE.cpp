#include <string>
#include <vector>
#include <iostream>

using namespace std;
int search(vector<int> &nums, int target)
{
    return binarySearch(nums, target, 0, nums.size() - 1);
}
int binarySearch(vector<int> &nums, int target, int start, int end)
{
    if (start > end)
    {
        return -1;
    }

    int mid = start + (end - start) / 2;

    if (nums[mid] == target)
        return mid;
    else if (nums[mid] > target)
    {
        return binarySearch(nums, target, start, mid - 1);
    }
    else if (nums[mid] < target)
    {
        return binarySearch(nums, target, mid + 1, end);
    }
}

int main()
{
    vector<int> ints = {1, 2, 3, 4, 5};
    cout << search(ints, 7);
}
