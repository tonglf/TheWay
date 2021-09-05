#include <iostream>
#include <vector>

using namespace std;

void bubbleSort(vector<int> &nums)
{
    bool swapped; // ÓÅ»¯
    for (int i = 0; i < nums.size(); ++i)
    {
        swapped = false;
        for (int j = 0; j < nums.size() - i - 1; ++j)
        {
            if (nums[j] > nums[j + 1]) // ÐÞ¸Ä£ºnums[j] < nums[j - 1]
            {
                swap(nums[j], nums[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
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

    bubbleSort(nums);
    printNums(nums);

    system("pause");
    return 0;
}