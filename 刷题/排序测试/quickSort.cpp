#include <iostream>
#include <vector>

using namespace std;

void quickSort(vector<int> &nums, int l, int r) // ����ҿ���д��
{
    if (l + 1 >= r)
        return;

    int first = l, last = r - 1, key = nums[first];

    while (first < last)
    {
        while (first < last && nums[last] >= key) // �޸ģ�nums[last] <= key
            --last;

        nums[first] = nums[last];

        while (first < last && nums[first] <= key) // �޸ģ�nums[first] >= key
            ++first;

        nums[last] = nums[first];
    }

    nums[first] = key;

    quickSort(nums, l, first);
    quickSort(nums, first + 1, r);
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

    quickSort(nums, 0, nums.size());
    printNums(nums);

    system("pause");
    return 0;
}