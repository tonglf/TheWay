#include <iostream>
#include <vector>

using namespace std;

void insertSort(vector<int> &nums)
{
    int i, j;
    for (i = 1; i < nums.size(); ++i)
    {
        int temp = nums[i];
        for (j = i - 1; j >= 0; --j)
        {
            if (temp < nums[j]) // ÐÞ¸Ä£ºtemp > nums[j - 1]
            {
                nums[j + 1] = nums[j];
            }
            else
                break;
        }
        nums[j + 1] = temp;
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