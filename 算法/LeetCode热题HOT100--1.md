# LeetCode 热题 HOT 100 -- 1

## 1、两数之和

给定一个整数数组 nums 和一个整数目标值 target，请你在该数组中找出 和为目标值 target  的那 两个 整数，并返回它们的数组下标。

你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。

你可以按任意顺序返回答案。

示例 1：

```cpp
输入：nums = [2,7,11,15], target = 9
输出：[0,1]
解释：因为 nums[0] + nums[1] == 9 ，返回 [0, 1] 。
```

示例 2：

```cpp
输入：nums = [3,2,4], target = 6
输出：[1,2]
```


示例 3：

```c++
输入：nums = [3,3], target = 6
输出：[0,1]
```

**题解：哈希表**

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> HashMap;
        for (int i = 0; i < nums.size(); ++i)
        {
            int n = target - nums[i];
            if (HashMap.find(n) != Map.end())
            {
                return {HashMap[n] ,i};
            }
            HashMap.insert(pair<int, int>(nums[i], i));
        }
        return {};
    }
};
```

- **时间复杂度：O(N)**

- **空间复杂度：O(N)**

## 2、两数相加

给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序 的方式存储的，并且每个节点只能存储 一位 数字。

请你将两个数相加，并以相同形式返回一个表示和的链表。

你可以假设除了数字 0 之外，这两个数都不会以 0 开头。

示例1

```cpp
输入：l1 = [2,4,3], l2 = [5,6,4]
输出：[7,0,8]
解释：342 + 465 = 807.
```


示例 2：

```cpp
输入：l1 = [0], l2 = [0]
输出：[0]
```


示例 3：

```c++
输入：l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
输出：[8,9,9,9,0,0,0,1]
```

**题解：**

```cpp
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
{
    ListNode *head = nullptr, *tail = nullptr;	// 需要初始化
    int carry = 0;
    while (l1 || l2)
    {
        int n1 = l1 ? l1->val : 0;
        int n2 = l2 ? l2->val : 0;        
        sum = n1 + n2 + carry;
        if (!head)
            head = tail = new ListNode(sum % 10);
        else
        {
            tail->next = new ListNode(sum % 10);
            tail = tail->next;
        }
        carry = sum / 10;
        if (l1)
            l1 = l1->next;
        if (l2)
            l2 = l2->next;
    }
    if (carry > 0)
        tail->next = new ListNode(carry);
    return head;
}
```

- **时间复杂度：O(N)**，N 为链表 l1 、 l2 的最大长度。

- **空间复杂度：O(1)**

## 3.无重复字符的最长子串

给定一个字符串，请你找出其中不含有重复字符的 **最长子串** 的长度。

示例 1:

```cpp
输入: s = "abcabcbb"
输出: 3 
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
```


示例 2:

```cpp
输入: s = "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
```


示例 3:

```c++
输入: s = "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。
```


示例 4:

```c++
输入: s = ""
输出: 0
```

**题解：滑动窗口**

```cpp
int lengthOfLongestSubstring(string s) 
{
    unordered_set<char> occ;			// 哈希集合，记录每个字符是否出现过
    int rk = -1, ans = 0;				// 右指针，初始值为 -1，相当于我们在字符串的左边界的左侧，还没有开始移动
    for (int i = 0; i < s.size(); ++i)
    {
        if (i != 0)
            occ.erase(s[i - 1]);		// 左指针向右移动一格，移除一个字符
        while (rk + 1 < s.size() && !occ.count(s[rk + 1]))
        {
            occ.insert(s[rk + 1]);		// 不断地移动右指针
            rk++;
        }
        ans = max(ans, rk - i + 1);		// 第 i 到 rk 个字符是一个极长的无重复字符子串
    }
    return ans;
}
```

- **时间复杂度：O(N)**

- **空间复杂度：O(Σ)**，其中 Σ 表示字符集（即字符串中可以出现的字符）

## 4.寻找俩个正序数组的中位数

给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和 nums2。请你找出并返回这两个正序数组的中位数 。

示例 1：

```cpp
输入：nums1 = [1,3], nums2 = [2]
输出：2.00000
解释：合并数组 = [1,2,3] ，中位数 2
```


示例 2：

```cpp
输入：nums1 = [1,2], nums2 = [3,4]
输出：2.50000
解释：合并数组 = [1,2,3,4] ，中位数 (2 + 3) / 2 = 2.5
```


示例 3：

```cpp
输入：nums1 = [0,0], nums2 = [0,0]
输出：0.00000
```


示例 4：

```cpp
输入：nums1 = [], nums2 = [1]
输出：1.00000
```

**题解：二分法**

```cpp
double findMedianSortedArrays(int[] nums1, int[] nums2) 
{
	int length1 = nums1.size(), length2 = nums2.size();
	int totalLength = length1 + length2;
	if (totalLength % 2 == 1) 
    {
        int midIndex = totalLength / 2;
        double median = getKthElement(nums1, nums2, midIndex + 1);
        return median;
    } 
    else 
    {
        int midIndex1 = totalLength / 2 - 1, midIndex2 = totalLength / 2;
        double median = (getKthElement(nums1, nums2, midIndex1 + 1) 
                         + getKthElement(nums1, nums2, midIndex2 + 1)) / 2.0;
        return median;
    }
}

int getKthElement(int[] nums1, int[] nums2, int k) 
{
    int length1 = nums1.size(), length2 = nums2.size();
    int index1 = 0, index2 = 0;
    int kthElement = 0;
	while (true) 
    {
        // 边界情况
        if (index1 == length1) 
        {
            return nums2[index2 + k - 1];
        }
        if (index2 == length2) 
        {
            return nums1[index1 + k - 1];
        }
        if (k == 1) 
        {
            return Math.min(nums1[index1], nums2[index2]);
        }
            
        // 正常情况
        int half = k / 2;
        int newIndex1 = Math.min(index1 + half, length1) - 1;
        int newIndex2 = Math.min(index2 + half, length2) - 1;
        int pivot1 = nums1[newIndex1], pivot2 = nums2[newIndex2];
        if (pivot1 <= pivot2) 
        {
            k -= (newIndex1 - index1 + 1);
            index1 = newIndex1 + 1;
        } 
        else
        {    
         	k -= (newIndex2 - index2 + 1);
            index2 = newIndex2 + 1;
        }
    }
}
```

- **时间复杂度：O(log(m+n))**

- **空间复杂度：O(1)O(1)**

## 5.最长回文子串

给你一个字符串 `s`，找到 `s` 中最长的回文子串。

示例 1：

```c++
输入：s = "babad"
输出："bab"
解释："aba" 同样是符合题意的答案。
```


示例 2：

```cpp
输入：s = "cbbd"
输出："bb"
```


示例 3：

```c++
输入：s = "a"
输出："a"
```


示例 4：

```c++
输入：s = "ac"
输出："a"
```

**方法一：中心扩展法**

```cpp
string longestPalindrome(string s)
{
    int end = 0, start = 0;
    int left1, right1;
    int left2, right2;    
    for (int i = 0; i < s.size(); ++i)
    {
        auto [left1, right1] = extend(s, i, i, s.size());
        auto [left2, right2] = extend(s, i, i + 1, s.size());
        if (left1 - right1 > end - start)
        {
            start = left1;
            end = right1;
        }
        if (left2 - right2 > end - start)
        {
            start = left2;
            end = right2;
        }
    }
    return s.substr(start, (e))
}

pair<int, int> extend(const string s, int i, int j, int n)
{
    while (i >= 0 && j < n && s[i] == s[j])
    {
        i--;
        j++;
    }
    return {i + 1, j - 1};
}
```



**方法二：动态规划**

```cpp

```

## 10.正则表达式匹配

给你一个字符串 s 和一个字符规律 p，请你来实现一个支持 '.' 和 '*' 的正则表达式匹配。

'.' 匹配任意单个字符
'*' 匹配零个或多个前面的那一个元素
所谓匹配，是要涵盖整个字符串 s 的，而不是部分字符串。

示例 1：

```cpp
输入：s = "aa" p = "a"
输出：false
解释："a" 无法匹配 "aa" 整个字符串。
```


示例 2:

```cpp
输入：s = "aa" p = "a*"
输出：true
解释：因为 '*' 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 'a'。因此，字符串 "aa" 可被视为 'a' 重复了一次。
```


示例 3：

```cpp
输入：s = "ab" p = ".*"
输出：true
解释：".*" 表示可匹配零个或多个（'*'）任意字符（'.'）。
```

示例 4：

```c++
输入：s = "aab" p = "c*a*b"
输出：true
解释：因为 '*' 表示零个或多个，这里 'c' 为 0 个, 'a' 被重复一次。因此可以匹配字符串 "aab"。
```


示例 5：

```c++
输入：s = "mississippi" p = "mis*is*p*."
输出：false
```







## 11.盛最多水的容器

给你 n 个非负整数 a1，a2，...，an，每个数代表坐标中的一个点 (i, ai) 。在坐标内画 n 条垂直线，垂直线 i 的两个端点分别为 (i, ai) 和 (i, 0) 。找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。

说明：你不能倾斜容器。

示例 1：

![img](https://aliyun-lc-upload.oss-cn-hangzhou.aliyuncs.com/aliyun-lc-upload/uploads/2018/07/25/question_11.jpg)

```cpp
输入：[1,8,6,2,5,4,8,3,7]
输出：49 
解释：图中垂直线代表输入数组 [1,8,6,2,5,4,8,3,7]。在此情况下，容器能够容纳水（表示为蓝色部分）的最大值为 49。
```


示例 2：

```cpp
输入：height = [1,1]
输出：1
```


示例 3：

```cpp
输入：height = [4,3,2,1,4]
输出：16
```


示例 4：

```cpp
输入：height = [1,2,1]
输出：2
```







## 15.三数之和

给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？请你找出所有和为 0 且不重复的三元组。

注意：答案中不可以包含重复的三元组。

示例 1：

```cpp
输入：nums = [-1,0,1,2,-1,-4]
输出：[[-1,-1,2],[-1,0,1]]
```


示例 2：

```cpp
输入：nums = []
输出：[]
```


示例 3：

```cpp
输入：nums = [0]
输出：[]
```







## 17.电话号码的字母组合

给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。

给出数字到字母的映射如下（与电话按键相同）。注意 1 不对应任何字母。

<img src="https://assets.leetcode-cn.com/aliyun-lc-upload/original_images/17_telephone_keypad.png" alt="img" style="zoom: 33%;" />

示例 1：

```cpp
输入：digits = "23"
输出：["ad","ae","af","bd","be","bf","cd","ce","cf"]
```


示例 2：

```c++
输入：digits = ""
输出：[]
```


示例 3：

```cpp
输入：digits = "2"
输出：["a","b","c"]
```





## 19.删除链表的倒数第 N 个结点

给你一个链表，删除链表的倒数第 `n` 个结点，并且返回链表的头结点。

**进阶：**你能尝试使用一趟扫描实现吗？

示例 1：

```cpp
输入：head = [1,2,3,4,5], n = 2
输出：[1,2,3,5]
```


示例 2：

```c++
输入：head = [1], n = 1
输出：[]
```


示例 3：

```c++
输入：head = [1,2], n = 1
输出：[1]
```







## 20.有效的括号

给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。

有效字符串需满足：

左括号必须用相同类型的右括号闭合。
左括号必须以正确的顺序闭合。

示例 1：

```cpp
输入：s = "()"
输出：true
```


示例 2：

```cpp
输入：s = "()[]{}"
输出：true
```


示例 3：

```cpp
输入：s = "(]"
输出：false
```


示例 4：

```cpp
输入：s = "([)]"
输出：false
```


示例 5：

```cpp
输入：s = "{[]}"
输出：true
```







## 21.合并两个有序数组

将两个升序链表合并为一个新的 **升序** 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。 

示例 1：

![img](https://assets.leetcode.com/uploads/2020/10/03/merge_ex1.jpg)

```cpp
输入：l1 = [1,2,4], l2 = [1,3,4]
输出：[1,1,2,3,4,4]
```


示例 2：

```cpp
输入：l1 = [], l2 = []
输出：[]
```


示例 3：

```cpp
输入：l1 = [], l2 = [0]
输出：[0]
```







## 22.括号生成

数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的 括号组合。

示例 1：

```cpp
输入：n = 3
输出：["((()))","(()())","(())()","()(())","()()()"]
```

示例 2：

```c++
输入：n = 1
输出：["()"]
```





## 23.合并 K 个升序链表

给你一个链表数组，每个链表都已经按升序排列。

请你将所有链表合并到一个升序链表中，返回合并后的链表。

 

示例 1：

```cpp
输入：lists = [[1,4,5],[1,3,4],[2,6]]
输出：[1,1,2,3,4,4,5,6]
解释：链表数组如下：
[
  1->4->5,
  1->3->4,
  2->6
]
将它们合并到一个有序链表中得到。
1->1->2->3->4->4->5->6
```


示例 2：

```cpp
输入：lists = []
输出：[]
```


示例 3：

```cpp
输入：lists = [[]]
输出：[]
```







## 31.下一个排列

实现获取 下一个排列 的函数，算法需要将给定数字序列重新排列成字典序中下一个更大的排列。

如果不存在下一个更大的排列，则将数字重新排列成最小的排列（即升序排列）。

必须 原地 修改，只允许使用额外常数空间。

示例 1：

```cpp
输入：nums = [1,2,3]
输出：[1,3,2]
```


示例 2：

```cpp
输入：nums = [3,2,1]
输出：[1,2,3]
```


示例 3：

```cpp
输入：nums = [1,1,5]
输出：[1,5,1]
```

示例 4：

```c#
输入：nums = [1]
输出：[1]
```





## 



## 33.搜索旋转排序数组

整数数组 nums 按升序排列，数组中的值 互不相同 。

在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了 旋转，使数组变为 [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]（下标 从 0 开始 计数）。例如， [0,1,2,4,5,6,7] 在下标 3 处经旋转后可能变为 [4,5,6,7,0,1,2] 。

给你 旋转后 的数组 nums 和一个整数 target ，如果 nums 中存在这个目标值 target ，则返回它的下标，否则返回 -1 。

示例 1：

```cpp
输入：nums = [4,5,6,7,0,1,2], target = 0
输出：4
```


示例 2：

```cpp
输入：nums = [4,5,6,7,0,1,2], target = 3
输出：-1
```


示例 3：

```cpp
输入：nums = [1], target = 0
输出：-1
```







## 34.在排序数组中查找元素的第一个和最后一个位置

给定一个按照升序排列的整数数组 nums，和一个目标值 target。找出给定目标值在数组中的开始位置和结束位置。

如果数组中不存在目标值 target，返回 [-1, -1]。

进阶：

你可以设计并实现时间复杂度为 O(log n) 的算法解决此问题吗？

示例 1：

```cpp
输入：nums = [5,7,7,8,8,10], target = 8
输出：[3,4]
```


示例 2：

```cpp
输入：nums = [5,7,7,8,8,10], target = 6
输出：[-1,-1]
```


示例 3：

```cpp
输入：nums = [], target = 0
输出：[-1,-1]
```







## 39.组合求和

给定一个无重复元素的数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。

candidates 中的数字可以无限制重复被选取。

说明：

所有数字（包括 target）都是正整数。
解集不能包含重复的组合。 
示例 1：

```cpp
输入：candidates = [2,3,6,7], target = 7,
所求解集为：
[
  [7],
  [2,2,3]
]
```

示例 2：

```cpp
输入：candidates = [2,3,5], target = 8,
所求解集为：
[
  [2,2,2,2],
  [2,3,3],
  [3,5]
]
```







## 42.接雨水

给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。 

示例 1：

![img](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/10/22/rainwatertrap.png)

```c++
输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]
输出：6
解释：上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接 6 个单位的雨水（蓝色部分表示雨水）。 
```


示例 2：

```cpp
输入：height = [4,2,0,3,2,5]
输出：9
```

