#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void countSort(vector<int> &nums)
{
    int minVal = *min_element(nums.begin(), nums.end());
    int maxVal = *max_element(nums.begin(), nums.end());

    vector<int> vecCount(maxVal - minVal + 1, 0);
    for (int i = 0; i < nums.size(); ++i)
    {
        vecCount[nums[i] - minVal]++;
    }

    int index;
    for (int i = 0; i < vecCount.size(); ++i)
    {
        while (vecCount[i]--)
        {
            nums[index++] = i + minVal;
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
    vector<int> nums{10001, 10005, 10003, 10001, 10002, 10002, 10003, 10002, 10003, 10005};
    printNums(nums);

    countSort(nums);
    printNums(nums);

    system("pause");
    return 0;
}