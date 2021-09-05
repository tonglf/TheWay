#include <iostream>
#include <vector>

using namespace std;

void selectSort(vector<int> &nums)
{
    int index; // 记录每次遍历最小值的索引
    for (int i = 0; i < nums.size(); ++i)
    {
        index = i;
        for (int j = i + 1; j < nums.size(); ++j)
        {
            if (nums[j] < nums[index]) // 修改：nums[j] > nums[index]
            {
                index = j;
            }
        }
        swap(nums[i], nums[index]);
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

    selectSort(nums);
    printNums(nums);

    system("pause");
    return 0;
}