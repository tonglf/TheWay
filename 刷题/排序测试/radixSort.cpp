#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void radixSort(vector<int> &nums)
{
    int maxVal = *max_element(nums.begin(), nums.end());
    int count = 0;
    while (maxVal)
    {
        count++;
        maxVal /= 10;
    }

    vector<int> bucket(10, 0);
    vector<int> temp(nums.size());

    int radix = 1;
    for (int i = 0; i < count; ++i)
    {
        for (auto &buck : bucket)
        {
            buck = 0;
        }

        for (int j = 0; j < nums.size(); ++j)
        {
            int index = (nums[j] / radix) % 10;
            bucket[index]++;
        }

        for (int k = 1; k < bucket.size(); ++k)
        {
            bucket[k] += bucket[k - 1];
        }

        for (int m = nums.size() - 1; m >= 0; --m)
        {
            int index = (nums[m] / radix) % 10;
            temp[bucket[index] - 1] = nums[m];
            bucket[index]--;
        }

        nums = temp;
        radix *= 10;
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
    vector<int> nums{65, 7, 233, 19, 1, 40, 566, 674, 98, 52};
    printNums(nums);

    radixSort(nums);
    printNums(nums);

    system("pause");
    return 0;
}