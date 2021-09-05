#include <iostream>
#include <vector>

using namespace std;

void shellSort(vector<int> &nums)
{
    for (int gap = nums.size(); gap > 0; gap /= 2)
    {
        for (int i = gap; i < nums.size(); ++i)
        { // ÐÞ¸Ä£ºnum[j] < num[j + gap]
            for (int j = i - gap; j >= 0 && nums[j] > nums[j + gap]; j -= gap)
            {
                swap(nums[j], nums[j + gap]);
            }
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

    shellSort(nums);
    printNums(nums);

    system("pause");
    return 0;
}