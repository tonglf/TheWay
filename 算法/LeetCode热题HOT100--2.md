# LeetCode 热题 HOT 100 -- 2

## 46.全排列

给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案。

 示例 1：

```cpp
输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
```

示例 2：

```cpp
输入：nums = [0,1]
输出：[[0,1],[1,0]]
```

示例 3：

```cpp
输入：nums = [1]
输出：[[1]]
```

**题解：回溯法**

```cpp
class Solution {
    vector<vector<int>> result;
    vector<int> path;
public:
    vector<vector<int>> permute(vector<int>& nums) 
    {
        vector<bool> used(nums.size(), false);
        backTracking(nums, used);
        return result;
    }

    void backTracking(const vector<int>& nums, vector<bool>& used)
    {
        if (path.size() == nums.size())
        {
            result.push_back(path);
            return ;
        }

        for (int i = 0; i < nums.size(); ++i)
        {
            if (used[i] == true)
            {
                continue;
            }
            used[i] = true;
            path.push_back(nums[i]);
            backTracking(nums, used);
            path.pop_back();
            used[i] = false;
        }
    }
};
```

**时间复杂度：O*(*n *×* n!)**

**空间复杂度：O*(*n)**

## 48.旋转图像

给定一个 n × n 的二维矩阵 matrix 表示一个图像。请你将图像顺时针旋转 90 度。

你必须在 原地 旋转图像，这意味着你需要直接修改输入的二维矩阵。请不要 使用另一个矩阵来旋转图像。

示例 1：

<img src="./Image/48_leetcode_1.jpg" alt="img" style="zoom:67%;" />

```c++
输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
输出：[[7,4,1],[8,5,2],[9,6,3]]
```


示例 2：

<img src="./Image/48_leetcode_2.jpg" alt="img" style="zoom: 67%;" />

```cpp
输入：matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
输出：[[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]
```

示例 3：

```cpp
输入：matrix = [[1]]
输出：[[1]]
```

示例 4：

```cpp
输入：matrix = [[1,2],[3,4]]
输出：[[3,1],[4,2]]
```

**题解：两次对折**

```cpp
class Solution {
public:
    void rotate(vector<vector<int>>& matrix) 
    {
        for (int i = 0; i < matrix.size() - 1; ++i)				// 沿副对角线对折
        {
            for (int j = 0; j < matrix.size() - i - 1; ++j)
            {
                swap(matrix[i][j], matrix[matrix.size() - 1 - j][matrix.size() - 1 -i]);
            }
        }

        for (int i = 0; i < matrix.size() / 2; ++i)				// 上下对折
        {
            for (int j = 0; j < matrix.size(); ++j)
            {
                swap(matrix[i][j], matrix[matrix.size() - 1 - i][j]);
            }
        }

        return ;
    }
};
```

**时间复杂度：O(N^2)**

**空间复杂度：O(1)**

## 49.字母异位词分组

给定一个字符串数组，将字母异位词组合在一起。字母异位词指字母相同，但排列不同的字符串。

示例:

```cpp
输入: ["eat", "tea", "tan", "ate", "nat", "bat"]
输出:
[
  ["ate","eat","tea"],
  ["nat","tan"],
  ["bat"]
]
```

**题解：排序**

```cpp
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> mp;
        for (string& str: strs) 
        {
            string key = str;
            sort(key.begin(), key.end());
            mp[key].emplace_back(str);			// push_back 也可
        }
        vector<vector<string>> ans;
        for (auto it = mp.begin(); it != mp.end(); ++it) 
        {
            ans.emplace_back(it->second);		// push_back 也可
        }
        return ans;
    }
};
```

**时间复杂度：O*(*n**k *log* k）

**空间复杂度：O*(*n k)**

## 53.最大子序和

给定一个整数数组 nums ，找到一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。 

示例 1：

```cpp
输入：nums = [-2,1,-3,4,-1,2,1,-5,4]
输出：6
解释：连续子数组 [4,-1,2,1] 的和最大，为 6 。
```

示例 2：

```cpp
输入：nums = [1]
输出：1
```

示例 3：

```c++
输入：nums = [0]
输出：0
```

示例 4：

```cpp
输入：nums = [-1]
输出：-1
```

示例 5：

```cpp
输入：nums = [-100000]
输出：-100000
```

**题解一：遍历**

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) 
    {
        int sum = 0;
        int ans = INT_MIN;
        for (int i = 0; i < nums.size(); ++i)
        {
            sum += nums[i];
            ans = max(sum, ans);
            if (sum < 0)
            {
                sum = 0;
            }
        }
        return ans;
    }
};
```

**时间复杂度：O(n）**

**空间复杂度：O*(*1)**

**题解二：动态规划**

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) 
    {
        int pre = 0, maxAns = nums[0];
        for (const auto &x: nums) 
        {
            pre = max(pre + x, x);
            maxAns = max(maxAns, pre);
        }
        return maxAns;
    }
};
```

**时间复杂度：O(n）**

**空间复杂度：O*(*1)**

## 55.跳跃游戏

给定一个非负整数数组 nums ，你最初位于数组的 第一个下标 。

数组中的每个元素代表你在该位置可以跳跃的最大长度。

判断你是否能够到达最后一个下标。

示例 1：

```cpp
输入：nums = [2,3,1,1,4]
输出：true
解释：可以先跳 1 步，从下标 0 到达下标 1, 然后再从下标 1 跳 3 步到达最后一个下标。
```


示例 2：

```cpp
输入：nums = [3,2,1,0,4]
输出：false
解释：无论怎样，总会到达下标为 3 的位置。但该下标的最大跳跃长度是 0 ， 所以永远不可能到达最后一个下标。
```

**题解：贪心**

```cpp
class Solution {
public:
    bool canJump(vector<int>& nums) 
    {
        int cover = 0;
        for (int i = 0; i <= cover; i++) 		// 注意这里是小于等于cover
        { 
            cover = max(i + nums[i], cover);
            if (cover >= nums.size() - 1) 		// 说明可以覆盖到终点了
            {
                return true; 
            }    
        }
        return false;
    }
};
```

**时间复杂度：O(n）**

**空间复杂度：O*(*1)**

## 56.合并区间

以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti, endi] 。请你合并所有重叠的区间，并返回一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间。 

示例 1：

```cpp
输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
输出：[[1,6],[8,10],[15,18]]
解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].
```

示例 2：

```cpp
输入：intervals = [[1,4],[4,5]]
输出：[[1,5]]
解释：区间 [1,4] 和 [4,5] 可被视为重叠区间。
```

**题解：贪心**

```cpp
class Solution {
    static bool mycmp(const vector<int>& a, const vector<int>& b)	// 值传递与引用传递性能差别巨大
    {
        return a[0] < b[0];
    }
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) 
    {
        sort(intervals.begin(), intervals.end(), mycmp);
        vector<vector<int>> ans;
        ans.push_back(intervals[0]);
        for (int i = 1; i < intervals.size(); ++i)
        {
            if (intervals[i][0] <= ans.back()[1])
            {
                ans.back()[1] = max(intervals[i][1], ans.back()[1]);
            }
            else
            {
                ans.push_back(intervals[i]);
            }
        }
        return ans;
    }
};
```

**时间复杂度：O(n log(n)）**（快排）

**空间复杂度：O*(*1)**

## 62.不同路径

一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。

机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish” ）。

问总共有多少条不同的路径？

示例 1：

![img](./Image/62_leetcode.png)

```cpp
输入：m = 3, n = 7
输出：28
```


示例 2：

```cpp
输入：m = 3, n = 2
输出：3
解释：
从左上角开始，总共有 3 条路径可以到达右下角。

1. 向右 -> 向下 -> 向下
2. 向下 -> 向下 -> 向右
3. 向下 -> 向右 -> 向下
```

示例 3：

```cpp
输入：m = 7, n = 3
输出：28
```


示例 4：

```cpp
输入：m = 3, n = 3
输出：6
```

**题解：动态规划**

```cpp
class Solution {
public:
    int uniquePaths(int m, int n) 
    {
        vector<vector<int>> dp(m, vector<int>(n, 0));
        for (int i = 0; i < m; ++i)
        {
            dp[i][0] = 1;
        }
        for (int i = 1; i < n; ++i)
        {
            dp[0][i] = 1;
        }

        for (int i = 1; i < m; ++i)
        {
            for (int j = 1; j < n; ++j)
            {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
        return dp[m - 1][n - 1];
    }
};
```

**时间复杂度：O*(*m*n)**

**空间复杂度：O*(*m*n)**

## 64.最小路径和

给定一个包含非负整数的 m x n 网格 grid ，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。

说明：每次只能向下或者向右移动一步。

示例 1：

![img](./Image/64_leetcode.jpg)

```cpp
输入：grid = [[1,3,1],[1,5,1],[4,2,1]]
输出：7
解释：因为路径 1→3→1→1→1 的总和最小。
```

示例 2：

```c++
输入：grid = [[1,2,3],[4,5,6]]
输出：12
```

**题解：动态规划**

```cpp
class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) 
    {
        int rows = grid.size();
        int cols = grid[0].size();
        vector<vector<int>> dp(rows, vector<int>(cols, 0));
        dp[0][0] = grid[0][0];
        for (int i = 1; i < rows; ++i)
        {
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        }
        for (int j = 1; j < cols; ++j)
        {
            dp[0][j] = dp[0][j - 1] + grid[0][j];
        }

        for (int i = 1; i < rows; ++i)
        {
            for (int j = 1; j < cols; ++j)
            {
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
            }
        }

        return dp[rows - 1][cols - 1];
    }
};
```

**时间复杂度：O*(*m*n)**

**空间复杂度：O*(*m*n)**

## 70.爬楼梯

假设你正在爬楼梯。需要 n 阶你才能到达楼顶。

每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？

注意：给定 n 是一个正整数。

示例 1：

```cpp
输入： 2
输出： 2
解释： 有两种方法可以爬到楼顶。

1.  1 阶 + 1 阶
2.  2 阶
```

示例 2：

```cpp
输入： 3
输出： 3
解释： 有三种方法可以爬到楼顶。

1.  1 阶 + 1 阶 + 1 阶
2.  1 阶 + 2 阶
3.  2 阶 + 1 阶
```

**题解：动态规划**

```cpp
class Solution {
public:
    int climbStairs(int n) {
        if (n < 3)
            return n;
        vector<int> dp(n + 1, 0);
        dp[1] = 1;
        dp[2] = 2;
        for (int i = 3; i <= n; ++i)
        {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return dp[n];
    }
};
```

**时间复杂度：O(n)**

**空间复杂度：O(1)**

## 72.编辑距离

给你两个单词 word1 和 word2，请你计算出将 word1 转换成 word2 所使用的最少操作数 。

你可以对一个单词进行如下三种操作：

插入一个字符
删除一个字符
替换一个字符

示例 1：

```cpp
输入：word1 = "horse", word2 = "ros"
输出：3
解释：
horse -> rorse (将 'h' 替换为 'r')
rorse -> rose (删除 'r')
rose -> ros (删除 'e')
```

示例 2：

```cpp
输入：word1 = "intention", word2 = "execution"
输出：5
解释：
intention -> inention (删除 't')
inention -> enention (将 'i' 替换为 'e')
enention -> exention (将 'n' 替换为 'x')
exention -> exection (将 'n' 替换为 'c')
exection -> execution (插入 'u')
```

**题解：动态规划**

```cpp
class Solution {
public:
    int minDistance(string word1, string word2) {
        vector<vector<int>> dp(word1.size() + 1, vector<int>(word2.size() + 1, 0));
        for (int i = 0; i <= word1.size(); i++) 
            dp[i][0] = i;
        for (int j = 0; j <= word2.size(); j++) 
            dp[0][j] = j;
        
        for (int i = 1; i <= word1.size(); i++) 
        {
            for (int j = 1; j <= word2.size(); j++) 
            {
                if (word1[i - 1] == word2[j - 1]) 
                {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else 
                {
                    dp[i][j] = min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]}) + 1;
                }
            }
        }
        return dp[word1.size()][word2.size()];
    }
};
```

**时间复杂度：O*(*m*n)**

**空间复杂度：O*(*m*n)**

## 75.颜色分类

给定一个包含红色、白色和蓝色，一共 n 个元素的数组，原地对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。

此题中，我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。

示例 1：

```cpp
输入：nums = [2,0,2,1,1,0]
输出：[0,0,1,1,2,2]
```

示例 2：

```cpp
输入：nums = [2,0,1]
输出：[0,1,2]
```

示例 3：

````cpp
输入：nums = [0]
输出：[0]
````


示例 4：

```cpp
输入：nums = [1]
输出：[1]
```

**题解：双指针**

```cpp
class Solution {
public:
    void sortColors(vector<int>& nums) 
    {
        int n = nums.size();
        int p0 = 0, p1 = 0;
        for (int i = 0; i < n; ++i) 
        {
            if (nums[i] == 1) 
            {
                swap(nums[i], nums[p1]);
                ++p1;
            } 
            else if (nums[i] == 0) 
            {
                swap(nums[i], nums[p0]);
                if (p0 < p1) 
                {
                    swap(nums[i], nums[p1]);
                }
                ++p0;
                ++p1;
            }
        }
    }
};
```

**时间复杂度：O(n)**

**空间复杂度：O(1)**

## 76.最小覆盖子串

给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。

注意：如果 s 中存在这样的子串，我们保证它是唯一的答案。

示例 1：

```c++
输入：s = "ADOBECODEBANC", t = "ABC"
输出："BANC"
```


示例 2：

```cpp
输入：s = "a", t = "a"
输出："a"
```

**题解：滑动窗口**

```cpp
class Solution {
public:
    unordered_map<char, int> ori, cnt;

    bool check() 
    {
        for (const auto &p: ori) 
        {
            if (cnt[p.first] < p.second) 
            {
                return false;
            }
        }
        return true;
    }

    string minWindow(string s, string t) 
    {
        for (const auto &c: t) 
        {
            ++ori[c];
        }

        int l = 0, r = -1;
        int len = INT_MAX, ansL = -1, ansR = -1;

        while (r < s.size()) 
        {
            if (ori.find(s[++r]) != ori.end()) 
            {
                ++cnt[s[r]];
            }
            while (check() && l <= r) 
            {
                if (r - l + 1 < len) 
                {
                    len = r - l + 1;
                    ansL = l;
                }
                if (ori.find(s[l]) != ori.end()) 
                {
                    --cnt[s[l]];
                }
                ++l;
            }
        }
        return ansL == -1 ? string() : s.substr(ansL, len);
    }
};
```

## 78.子集

给你一个整数数组 nums ，数组中的元素 互不相同 。返回该数组所有可能的子集（幂集）。

解集 不能 包含重复的子集。你可以按 任意顺序 返回解集。

示例 1：

```cpp
输入：nums = [1,2,3]
输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]
```

示例 2：

```cpp
输入：nums = [0]
输出：[[],[0]]
```

**题解：回溯法**

```cpp
class Solution {
    vector<vector<int>> result;
    vector<int> path;
public:
    vector<vector<int>> subsets(vector<int>& nums) 
    {
        backTracking(nums, 0);
        return result;
    }

    void backTracking(const vector<int>& nums, int index)
    {
        result.push_back(path);

        for (int i = index; i < nums.size(); ++i)
        {
            path.push_back(nums[i]);
            backTracking(nums, i + 1);
            path.pop_back();
        }
    }
};
```

**时间复杂度：O*(*n×2^n)**

**空间复杂度：O*(*n)**

## 79.单词搜索

给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word 存在于网格中，返回 true ；否则，返回 false 。

单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。

示例 1：

![img](./Image/79_leetcode_1.jpg)

```cpp
输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
输出：true
```


示例 2：

![img](./Image/79_leetcode_2.jpg)

```cpp
输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
输出：true
```


示例 3：

![img](./Image/79_leetcode_3.jpg)

```cpp
输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
输出：false
```

**题解：回溯法**

```cpp
class Solution {
public:
    bool check(vector<vector<char>>& board, vector<vector<int>>& visited, int i, int j, string& s, int k) {
        if (board[i][j] != s[k]) 
        {
            return false;
        } 
        else if (k == s.length() - 1) 
        {
            return true;
        }
        visited[i][j] = true;
        vector<pair<int, int>> directions{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        bool result = false;
        for (const auto& dir: directions) 
        {
            int newi = i + dir.first, newj = j + dir.second;
            if (newi >= 0 && newi < board.size() && newj >= 0 && newj < board[0].size()) 
            {
                if (!visited[newi][newj]) 
                {
                    bool flag = check(board, visited, newi, newj, s, k + 1);
                    if (flag) 
                    {
                        result = true;
                        break;
                    }
                }
            }
        }
        visited[i][j] = false;
        return result;
    }

    bool exist(vector<vector<char>>& board, string word) 
    {
        int h = board.size(), w = board[0].size();
        vector<vector<int>> visited(h, vector<int>(w));
        for (int i = 0; i < h; i++) 
        {
            for (int j = 0; j < w; j++) 
            {
                bool flag = check(board, visited, i, j, word, 0);
                if (flag) 
                {
                    return true;
                }
            }
        }
        return false;
    }
};
```

## 84.柱状图中最大的矩形

给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。

求在该柱状图中，能够勾勒出来的矩形的最大面积。

 ![img](./Image/84_leetcode_1.jpg)

以上是柱状图的示例，其中每个柱子的宽度为 1，给定的高度为 [2,1,5,6,2,3]。

 ![img](./Image/84_leetcode_2.jpg)

图中阴影部分为所能勾勒出的最大矩形面积，其面积为 10 个单位。

示例:

```cpp
输入: [2,1,5,6,2,3]
输出: 10
```

**题解：栈**

```cpp
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) 
    {
        int n = heights.size();
        vector<int> left(n), right(n);
        
        stack<int> mono_stack;
        for (int i = 0; i < n; ++i) 
        {
            while (!mono_stack.empty() && heights[mono_stack.top()] >= heights[i]) 
            {
                mono_stack.pop();
            }
            left[i] = (mono_stack.empty() ? -1 : mono_stack.top());
            mono_stack.push(i);
        }

        mono_stack = stack<int>();
        for (int i = n - 1; i >= 0; --i) 
        {
            while (!mono_stack.empty() && heights[mono_stack.top()] >= heights[i]) 
            {
                mono_stack.pop();
            }
            right[i] = (mono_stack.empty() ? n : mono_stack.top());
            mono_stack.push(i);
        }
        
        int ans = 0;
        for (int i = 0; i < n; ++i) 
        {
            ans = max(ans, (right[i] - left[i] - 1) * heights[i]);
        }
        return ans;
    }
};
```

**时间复杂度：O*(*n)**

**空间复杂度：O*(*n)**

## 85.最大矩形

给定一个仅包含 0 和 1 、大小为 rows x cols 的二维二进制矩阵，找出只包含 1 的最大矩形，并返回其面积。

示例 1：

![img](./Image/85_leetcode.jpg)

```c++
输入：matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
输出：6
解释：最大矩形如上图所示。
```

示例 2：

```c++
输入：matrix = []
输出：0
```

示例 3：

```cpp
输入：matrix = [["0"]]
输出：0
```

示例 4：

```c++
输入：matrix = [["1"]]
输出：1
```


示例 5：

```cpp
输入：matrix = [["0","0"]]
输出：0
```



```cpp
```





## 94.二叉树的中序遍历

给定一个二叉树的根节点 `root` ，返回它的 **中序** 遍历。

**题解一：递归**

```cpp
class Solution {
public:
    void inorderTraversal(TreeNode* root,  vector<int>& vec)
    {
		if (root)
        {
            inorderTraversal(root->left, vec);
            vec.push_back(root->val);
            inorderTraversal(root->right, vec);
        }
    }
    
    vector<int> inorderTraversal(TreeNode* root) 
    {
		vector<int> result;
        inorderTraversal(root, result);
        return result;
    }
};
```

**题解二：迭代**

```cpp
class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) 
    {
        vector<int> result;
        stack<TreeNode*> s;
        TreeNode* cur = root;
        while (!s.empty() || cur != nullptr)
        {
            if (cur != nullptr)
            {
                s.push(cur);
                cur = cur->left;					// 进入最左侧节点
            }
            else
            {
                cur = s.top();
                result.push_back(cur->val);			// 输出节点值
                s.pop();
                cur = cur->right;					// 转移至右节点
            }
        }
        return result;
    }
};
```

**时间复杂度：O*(*n)**

**空间复杂度：O*(*n)**

## 96.不同的二叉搜索树

给你一个整数 `n` ，求恰由 `n` 个节点组成且节点值从 `1` 到 `n` 互不相同的 **二叉搜索树** 有多少种？返回满足题意的二叉搜索树的种数。

**示例 1：**

![img](./Image/96_leetcode.jpg)

```cpp
输入：n = 3
输出：5
```

**示例 2：**

```cpp
输入：n = 1
输出：1
```

**题解：动态规划**

```cpp
class Solution {
public:
    int numTrees(int n) 
    {
        vector<int> G(n + 1, 0);
        G[0] = 1;
        G[1] = 1;

        for (int i = 2; i <= n; ++i) 
        {
            for (int j = 1; j <= i; ++j) 
            {
                G[i] += G[j - 1] * G[i - j];
            }
        }
        return G[n];
    }
};
```

**时间复杂度 : O(n^2)**

**空间复杂度：O*(*n)**

## 98.验证二叉搜索树

给定一个二叉树，判断其是否是一个有效的二叉搜索树。

假设一个二叉搜索树具有如下特征：

节点的左子树只包含小于当前节点的数。
节点的右子树只包含大于当前节点的数。
所有左子树和右子树自身必须也是二叉搜索树。
示例 1:

```cpp
输入:
    2
   / \
  1   3
输出: true
```

示例 2:

```c++
输入:
    5
   / \
  1   4
     / \
    3   6
输出: false
解释: 输入为: [5,1,4,null,null,3,6]。
     根节点的值为 5 ，但是其右子节点值为 4 。
```

**题解：中序遍历**

```cpp
class Solution {
public:
    bool isValidBST(TreeNode* root) 
    {
        stack<TreeNode*> s;
        TreeNode* cur = root;
        TreeNode* pre = nullptr;
        while (!s.empty() || cur)
        {
            if (cur)
            {
                s.push(cur);
                cur = cur->left;
            }
            else
            {
                cur = s.top();
                s.pop();
                if (pre && pre->val >= cur->val)
                {
                    return false;
                }
                pre = cur;
                cur = cur->right;
            }
        }
        return true;
    }
};
```

**时间复杂度 : O(n)**

**空间复杂度：O*(*n)**

## 101.对称二叉树

给定一个二叉树，检查它是否是镜像对称的。

例如，二叉树 [1,2,2,3,4,4,3] 是对称的。

```cpp
	1
   / \
  2   2
 / \ / \
3  4 4  3
```

但是下面这个 [1,2,2,null,3,null,3] 则不是镜像对称的:

```cpp
   1
  / \
  2   2
   \   \
   3    3
```

**题解一：递归**

```cpp
class Solution {
public:
    bool compare(TreeNode* left, TreeNode* right) 
    {
        if (left == NULL && right != NULL) 
            return false;
        else if (left != NULL && right == NULL) 
            return false;
        else if (left == NULL && right == NULL) 
            return true;
        else if (left->val != right->val) 
            return false;
        else 
            return compare(left->left, right->right) && compare(left->right, right->left);
    }
    bool isSymmetric(TreeNode* root) 
    {
        if (root == NULL) return true;
        return compare(root->left, root->right);
    }
};
```

**题解一：迭代**

```cpp
class Solution {
public:
    bool isSymmetric(TreeNode* root) 
    {
        if (root == NULL) 
            return true;
        stack<TreeNode*> st; 
        st.push(root->left);
        st.push(root->right);
        
        while (!st.empty()) 
        {
            TreeNode* leftNode = st.top(); 
            st.pop();
            TreeNode* rightNode = st.top(); 
            st.pop();
            
            if (!leftNode && !rightNode) 
            {
                continue;
            }
            if ((!leftNode || !rightNode || (leftNode->val != rightNode->val))) 
            {
                return false;
            }
            st.push(leftNode->left);
            st.push(rightNode->right);
            st.push(leftNode->right);
            st.push(rightNode->left);
        }
        return true;
    }
};
```

**时间复杂度 : O(n)**

**空间复杂度：O*(*n)**
