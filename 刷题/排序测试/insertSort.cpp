#include <iostream>
#include <vector>

using namespace std;

void insertSort(vector<int> &nums)
{
    for (int i = 1; i < nums.size(); ++i)
    {
        for (int j = i; j > 0 && nums[j] < nums[j - 1]; --j) // ÐÞ¸Ä£ºnums[j] > nums[j - 1]
        {
            swap(nums[j], nums[j - 1]);
        }
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

    insertSort(nums);
    printNums(nums);

    system("pause");
    return 0;
}