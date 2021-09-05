#include <iostream>
#include <vector>

using namespace std;

void mergeSort(vector<int> &nums, int l, int r, vector<int> &temp)
{
    if (l + 1 >= r)
        return;

    int m = l + (r - l) / 2;

    mergeSort(nums, l, m, temp);
    mergeSort(nums, m, r, temp);

    int p = l, q = m, i = l;
    while (p < m || q < r)
    {
        if (q >= r || (p < m && nums[p] >= nums[q])) // ÐÞ¸Ä£ºnums[p] >= nums[q]
            temp[i++] = nums[p++];
        else
            temp[i++] = nums[q++];
    }

    for (i = l; i < r; ++i)
        nums[i] = temp[i];
}

void printNums(const vector<int> &nums)
{
    for (int i = 0; i < nums.size(); ++i)
    {
        std::cout << nums[i] << "  ";
    }
    std::cout << std::endl;
}

int main()
{
    vector<int> nums{5, 7, 3, 9, 1, 0, 6, 4, 8, 2};
    printNums(nums);

    vector<int> temp(nums.size());
    mergeSort(nums, 0, nums.size(), temp);
    printNums(nums);

    system("pause");
    return 0;
}