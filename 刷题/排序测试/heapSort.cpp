#include <iostream>
#include <vector>

using namespace std;

void heapAdjust(vector<int> &nums, int low, int high)
{
    int pivotKey = nums[low - 1];
    for (int i = 2 * low; i <= high; i *= 2)
    {
        if (i < high && nums[i - 1] < nums[i])
        {
            i++; // i 指向较大值
        }

        if (pivotKey >= nums[i - 1])
        {
            break;
        }

        nums[low - 1] = nums[i - 1];
        low = i;
    }
    nums[low - 1] = pivotKey;
}

void heapSort(vector<int> &nums)
{
    for (int i = nums.size() / 2; i > 0; i--)
    {
        heapAdjust(nums, i, nums.size());
    }

    for (int i = nums.size(); i > 1; i--)
    {
        swap(nums[0], nums[i - 1]);
        heapAdjust(nums, 1, i - 1);
    }
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

    heapSort(nums);
    printNums(nums);

    system("pause");
    return 0;
}