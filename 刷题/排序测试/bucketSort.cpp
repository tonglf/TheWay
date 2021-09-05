#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void bucketSort(vector<int> &nums)
{
    vector<vector<int>> buckets(5); // 以数值都在 0~50 为例

    for (int i = 0; i < nums.size(); ++i)
    {
        int bucket = nums[i] / 10;
        buckets[bucket].push_back(nums[i]);
    }

    int index = 0;
    for (int i = 0; i < buckets.size(); ++i)
    {
        sort(buckets[i].begin(), buckets[i].end());
        for (int j = 0; j < buckets[i].size(); ++j)
        {
            nums[index++] = buckets[i][j];
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
    vector<int> nums{1, 8, 7, 44, 42, 46, 38, 34, 33, 17, 15, 16, 27, 28, 24};
    printNums(nums);

    bucketSort(nums);
    printNums(nums);

    system("pause");
    return 0;
}