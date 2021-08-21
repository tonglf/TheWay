# LeetCode 热题 HOT 100 -- 4

## 207.课程表

你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1 。

在选修某些课程之前需要一些先修课程。 先修课程按数组 prerequisites 给出，其中 prerequisites[i] = [ai, bi] ，表示如果要学习课程 ai 则 必须 先学习课程  bi 。

例如，先修课程对 [0, 1] 表示：想要学习课程 0 ，你需要先完成课程 1 。
请你判断是否可能完成所有课程的学习？如果可以，返回 true ；否则，返回 false 。

示例 1：

```cpp
输入：numCourses = 2, prerequisites = [[1,0]]
输出：true
解释：总共有 2 门课程。学习课程 1 之前，你需要完成课程 0 。这是可能的。
```

示例 2：

```cpp
输入：numCourses = 2, prerequisites = [[1,0],[0,1]]
输出：false
解释：总共有 2 门课程。学习课程 1 之前，你需要先完成课程 0 ；并且学习课程 0 之前，你还应先完成课程 1 。这是不可能的。
```

**题解：广度优先搜索**

```cpp
class Solution {
private:
    vector<vector<int>> edges;
    vector<int> indeg;

public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) 
    {
        edges.resize(numCourses);
        indeg.resize(numCourses);
        for (const auto& info: prerequisites) 
        {
            edges[info[1]].push_back(info[0]);
            ++indeg[info[0]];
        }

        queue<int> q;
        for (int i = 0; i < numCourses; ++i) 
        {
            if (indeg[i] == 0) 
            {
                q.push(i);
            }
        }

        int visited = 0;
        while (!q.empty()) 
        {
            ++visited;
            int u = q.front();
            q.pop();
            for (int v: edges[u]) 
            {
                --indeg[v];
                if (indeg[v] == 0) 
                {
                    q.push(v);
                }
            }
        }

        return visited == numCourses;
    }
};
```

**时间复杂度: O*(*n*+*m)**

**空间复杂度: *O*(*n*+*m*)**

## 208.实现 Trie （前缀树）

Trie（发音类似 "try"）或者说 前缀树 是一种树形数据结构，用于高效地存储和检索字符串数据集中的键。这一数据结构有相当多的应用情景，例如自动补完和拼写检查。

请你实现 Trie 类：

Trie() 初始化前缀树对象。
void insert(String word) 向前缀树中插入字符串 word 。
boolean search(String word) 如果字符串 word 在前缀树中，返回 true（即，在检索之前已经插入）；否则，返回 false 。
boolean startsWith(String prefix) 如果之前已经插入的字符串 word 的前缀之一为 prefix ，返回 true ；否则，返回 false 。

示例：

```c++
输入
["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
[[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
输出
[null, null, true, false, true, null, true]

解释
Trie trie = new Trie();
trie.insert("apple");
trie.search("apple");   // 返回 True
trie.search("app");     // 返回 False
trie.startsWith("app"); // 返回 True
trie.insert("app");
trie.search("app");     // 返回 True
```

**题解：字典树**

```cpp
class Trie {
private:
    vector<Trie*> children;
    bool isEnd;

    Trie* searchPrefix(string prefix) 
    {
        Trie* node = this;
        for (char ch : prefix) 
        {
            ch -= 'a';
            if (node->children[ch] == nullptr) 
            {
                return nullptr;
            }
            node = node->children[ch];
        }
        return node;
    }

public:
    Trie() : children(26), isEnd(false) {}

    void insert(string word) 
    {
        Trie* node = this;
        for (char ch : word) 
        {
            ch -= 'a';
            if (node->children[ch] == nullptr) 
            {
                node->children[ch] = new Trie();
            }
            node = node->children[ch];
        }
        node->isEnd = true;
    }

    bool search(string word) 
    {
        Trie* node = this->searchPrefix(word);
        return node != nullptr && node->isEnd;
    }

    bool startsWith(string prefix) 
    {
        return this->searchPrefix(prefix) != nullptr;
    }
};
```

## 215.数组中的第 K 个最大元素

给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。

请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。

示例 1:

```cpp
输入: [3,2,1,5,6,4] 和 k = 2
输出: 5
```

示例 2:

```c++
输入: [3,2,3,1,2,4,5,5,6] 和 k = 4
输出: 4
```

**题解一：基于快速排序的选择方法**

```cpp
class Solution {
public:
    int quickSelect(vector<int>& a, int l, int r, int index) 
    {
        int q = randomPartition(a, l, r);
        if (q == index) 
        {
            return a[q];
        } 
        else 
        {
            return q < index ? quickSelect(a, q + 1, r, index) : quickSelect(a, l, q - 1, index);
        }
    }

    inline int randomPartition(vector<int>& a, int l, int r) 
    {
        int i = rand() % (r - l + 1) + l;
        swap(a[i], a[r]);
        return partition(a, l, r);
    }

    inline int partition(vector<int>& a, int l, int r) 
    {
        int x = a[r], i = l - 1;
        for (int j = l; j < r; ++j) 
        {
            if (a[j] <= x) 
            {
                swap(a[++i], a[j]);
            }
        }
        swap(a[i + 1], a[r]);
        return i + 1;
    }

    int findKthLargest(vector<int>& nums, int k) 
    {
        srand(time(0));
        return quickSelect(nums, 0, nums.size() - 1, nums.size() - k);
    }
};
```

**时间复杂度：*O*(*n*)**

**空间复杂度：*O*(log*n*)**

**题解二：基于堆排序的选择方法**

```cpp
class Solution {
public:
    void maxHeapify(vector<int>& a, int i, int heapSize) 
    {
        int l = i * 2 + 1, r = i * 2 + 2, largest = i;
        if (l < heapSize && a[l] > a[largest]) 
        {
            largest = l;
        } 
        if (r < heapSize && a[r] > a[largest]) 
        {
            largest = r;
        }
        if (largest != i) 
        {
            swap(a[i], a[largest]);
            maxHeapify(a, largest, heapSize);
        }
    }

    void buildMaxHeap(vector<int>& a, int heapSize) 
    {
        for (int i = heapSize / 2; i >= 0; --i) 
        {
            maxHeapify(a, i, heapSize);
        } 
    }

    int findKthLargest(vector<int>& nums, int k) 
    {
        int heapSize = nums.size();
        buildMaxHeap(nums, heapSize);
        for (int i = nums.size() - 1; i >= nums.size() - k + 1; --i) 
        {
            swap(nums[0], nums[i]);
            --heapSize;
            maxHeapify(nums, 0, heapSize);
        }
        return nums[0];
    }
};
```

**时间复杂度：*O*(*n*log*n*)**  建堆的时间代价是 O(n)，删除的总代价是 O(klogn)，因为 k<n，故渐进时间复杂为 O(n+klogn)=O(nlogn)。
**空间复杂度：O(logn)**，即递归使用栈空间的空间代价。

## 221.最大正方形

在一个由 '0' 和 '1' 组成的二维矩阵内，找到只包含 '1' 的最大正方形，并返回其面积。

示例 1：

![img](https://assets.leetcode.com/uploads/2020/11/26/max1grid.jpg)

```cpp
输入：matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
输出：4
```


示例 2：

![img](https://assets.leetcode.com/uploads/2020/11/26/max2grid.jpg)

```cpp
输入：matrix = [["0","1"],["1","0"]]
输出：1
```

示例 3：

```c++
输入：matrix = [["0"]]
输出：0
```





## 226.翻转二叉树

翻转一棵二叉树。

示例：

输入：

     	  4
        /   \
      2      7
     / \    / \
    1   3  6   9

输出：

     	  4
        /   \
      7      2
     / \    / \
    9   6  3   1

**题解：递归**

```cpp
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) 
    {
        if (root == nullptr) 
        {
            return nullptr;
        }
        TreeNode* left = invertTree(root->left);
        TreeNode* right = invertTree(root->right);
        
        root->left = right;
        root->right = left;
        
        return root;
    }
};
```

**时间复杂度：*O*(*N*)**

**空间复杂度：*O*(*N*)**


## 234.回文链表

请判断一个链表是否为回文链表。

示例 1:

```cpp
输入: 1->2
输出: false
```

示例 2:

```cpp
输入: 1->2->2->1
输出: true
```

进阶：
你能否用 O(n) 时间复杂度和 O(1) 空间复杂度解决此题？

**题解：快慢指针——翻转后半部分的链表**

```cpp
class Solution {
public:
    bool isPalindrome(ListNode* head) 
    {
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast && fast->next)
        {
            fast = fast->next->next;
            slow = slow->next;
        }
        ListNode* p1 = head;
        ListNode* p2 = reverseList(slow);

        while (p1 && p2)
        {
            if (p1->val != p2->val)
            {
                return false;
            }
            p1 = p1->next;
            p2 = p2->next;
        }
        return true;
    }

    ListNode* reverseList(ListNode* head)
    {
        ListNode* cur = head;
        ListNode* pre = nullptr;
        ListNode* next = nullptr;
        while (cur)
        {
            next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        return pre;
    }
};
```

**时间复杂度：*O*(*N*)**

**空间复杂度：*O*(*1*)**

## 236.二叉树的最近公共祖先

给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

百度百科中最近公共祖先的定义为：“对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

示例 1：

![img](./Image/236_leetcode.png)

```c++
输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
输出：3
解释：节点 5 和节点 1 的最近公共祖先是节点 3 。
```

示例 2：

```cpp
输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
输出：5
解释：节点 5 和节点 4 的最近公共祖先是节点 5 。因为根据定义最近公共祖先节点可以为节点本身。
```


示例 3：

```cpp
输入：root = [1,2], p = 1, q = 2
输出：1
```

**题解：递归**

```cpp
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) 
    {
        if (root == q || root == p || root == NULL) 
            return root;
        
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);
        
        if (left != NULL && right != NULL) 
            return root;
        if (left == NULL) 
            return right;
        return left;
    }
};
```

**时间复杂度：*O*(*N*)**

**空间复杂度：*O*(*N*)**

## 238.除自身以外数组的乘积

给你一个长度为 n 的整数数组 nums，其中 n > 1，返回输出数组 output ，其中 output[i] 等于 nums 中除 nums[i] 之外其余各元素的乘积。

示例:

```cpp
输入: [1,2,3,4]
输出: [24,12,8,6]
```


提示：题目数据保证数组之中任意元素的全部前缀元素和后缀（甚至是整个数组）的乘积都在 32 位整数范围内。

说明: 请不要使用除法，且在 O(n) 时间复杂度内完成此题。

进阶：
你可以在常数空间复杂度内完成这个题目吗？（ 出于对空间复杂度分析的目的，输出数组不被视为额外空间。）

**题解：**

```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) 
    {
        int length = nums.size();
        vector<int> answer(length);

        // answer[i] 表示索引 i 左侧所有元素的乘积
        // 因为索引为 '0' 的元素左侧没有元素， 所以 answer[0] = 1
        answer[0] = 1;
        for (int i = 1; i < length; i++) 
        {
            answer[i] = nums[i - 1] * answer[i - 1];
        }

        // R 为右侧所有元素的乘积
        // 刚开始右边没有元素，所以 R = 1
        int R = 1;
        for (int i = length - 1; i >= 0; i--) 
        {
            // 对于索引 i，左边的乘积为 answer[i]，右边的乘积为 R
            answer[i] = answer[i] * R;
            // R 需要包含右边所有的乘积，所以计算下一个结果时需要将当前值乘到 R 上
            R *= nums[i];
        }
        return answer;
    }
};
```

**时间复杂度：*O*(*N*)**

**空间复杂度：*O*(*1*)**

## 239.滑动窗口最大值

给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。

返回滑动窗口中的最大值。 

示例 1：

```cpp
输入：nums = [1,3,-1,-3,5,3,6,7], k = 3
输出：[3,3,5,5,6,7]
解释：
滑动窗口的位置                   最大值

[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
```


示例 2：

```cpp
输入：nums = [1], k = 1
输出：[1]
```


示例 3：

```cpp
输入：nums = [1,-1], k = 1
输出：[1,-1]
```


示例 4：

```cpp
输入：nums = [9,11], k = 2
输出：[11]
```


示例 5：

```cpp
输入：nums = [4,-2], k = 2
输出：[4]
```

**题解：单调栈**

```cpp
class Solution {
private:
    class MyQueue { //单调队列（从大到小）
    public:
        deque<int> que; // 使用deque来实现单调队列
        // 每次弹出的时候，比较当前要弹出的数值是否等于队列出口元素的数值，如果相等则弹出。
        // 同时pop之前判断队列当前是否为空。
        void pop(int value) 
        {
            if (!que.empty() && value == que.front()) 
            {
                que.pop_front();
            }
        }
        // 如果push的数值大于入口元素的数值，那么就将队列后端的数值弹出，直到push的数值小于等于队列入口元素的数值为止。
        // 这样就保持了队列里的数值是单调从大到小的了。
        void push(int value) 
        {
            while (!que.empty() && value > que.back()) 
            {
                que.pop_back();
            }
            que.push_back(value);

        }
        // 查询当前队列里的最大值 直接返回队列前端也就是front就可以了。
        int front() 
        {
            return que.front();
        }
    };
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) 
    {
        MyQueue que;
        vector<int> result;
        for (int i = 0; i < k; i++) 	// 先将前k的元素放进队列
        { 
            que.push(nums[i]);
        }
        result.push_back(que.front()); // result 记录前k的元素的最大值
        for (int i = k; i < nums.size(); i++) 
        {
            que.pop(nums[i - k]); 		// 滑动窗口移除最前面元素
            que.push(nums[i]); 			// 滑动窗口前加入最后面的元素
            result.push_back(que.front()); // 记录对应的最大值
        }
        return result;
    }
};
```

**时间复杂度：*O*(*N*)**

**空间复杂度：*O*(*K*)**

## 240.搜索二维矩阵 II

编写一个高效的算法来搜索 m x n 矩阵 matrix 中的一个目标值 target 。该矩阵具有以下特性：

每行的元素从左到右升序排列。
每列的元素从上到下升序排列。

示例 1：

![img](./Image/240_leetcode_1.jpg)

```cpp
输入：matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 5
输出：true
```


示例 2：

```cpp
输入：matrix = [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]], target = 20
输出：false
```

**题解：**

```cpp
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) 
    {
        int m = matrix.size();
        int n = matrix[0].size();

        int i = 0, j = n - 1;
        while (i < m && j >= 0)
        {
            if (target == matrix[i][j])
            {
                return true;
            }
            else if (target > matrix[i][j])
            {
                i++;
            }
            else
            {
                j--;
            }
        }
        return false;
    }
};
```

**时间复杂度：*O*(*N* + *M*)**

**空间复杂度：*O*(*1*)**

## 253.会议室 II

给你一个会议时间安排的数组 intervals ，每个会议时间都会包括开始和结束的时间 intervals[i] = [starti, endi] ，为避免会议冲突，同时要考虑充分利用会议室资源，请你计算至少需要多少间会议室，才能满足这些会议安排。

示例 1：

```cpp
输入：intervals = [[0,30],[5,10],[15,20]]
输出：2
```


示例 2：

```cpp
输入：intervals = [[7,10],[2,4]]
输出：1
```



```cpp
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) 
    {
    	if (intervals.size() == 0) 
        {
      		return 0;
    	}

    	vector<int> start(intervals.size());
    	vector<int> end(intervals.size());

    	for (int i = 0; i < intervals.size(); i++) 
    	{
      		start[i] = intervals[i][0];
      		end[i] = intervals[i][1];
    	}

 		sort(start.begin(), start.end());
 		sort(end.begin(), end.end());

    	int startPointer = 0, endPointer = 0;
    	int usedRooms = 0;

    	while (startPointer < intervals.size()) 
        {
      		if (start[startPointer] >= end[endPointer]) 
        	{
        		usedRooms -= 1;
        		endPointer += 1;
      		}
      		usedRooms += 1;
      		startPointer += 1;
    	}
    	return usedRooms;
	}
};
```

**时间复杂度: *O*(*N* log*N*)** 

**时间复杂度: *O*(*N*)** 

## 279.完全平方数

给定正整数 n，找到若干个完全平方数（比如 1, 4, 9, 16, ...）使得它们的和等于 n。你需要让组成和的完全平方数的个数最少。

给你一个整数 n ，返回和为 n 的完全平方数的 最少数量 。

完全平方数 是一个整数，其值等于另一个整数的平方；换句话说，其值等于一个整数自乘的积。例如，1、4、9 和 16 都是完全平方数，而 3 和 11 不是。

示例 1：

```cpp
输入：n = 12
输出：3 
解释：12 = 4 + 4 + 4
```

示例 2：

```c++
输入：n = 13
输出：2
解释：13 = 4 + 9
```

**题解：动态规划——完全背包**

```cpp
class Solution {
public:
    int numSquares(int n) 
    {
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 0; i <= n; i++) 			// 遍历背包
        { 
            for (int j = 1; j * j <= i; j++) 	// 遍历物品
            { 
                dp[i] = min(dp[i - j * j] + 1, dp[i]);
            }
        }
        return dp[n];
    }
};
```

**时间复杂度:  O( n sqrt{n} )**

**时间复杂度: *O*(*N*)** 

## 283.移动零

给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。

示例:

```c++
输入: [0,1,0,3,12]
输出: [1,3,12,0,0]
```


说明:

必须在原数组上操作，不能拷贝额外的数组。
尽量减少操作次数。

**题解：双指针**

```cpp
class Solution {
public:
    void moveZeroes(vector<int>& nums) 
    {
        int n = nums.size(), left = 0, right = 0;
        while (right < n) 
        {
            if (nums[right]) 
            {
                swap(nums[left], nums[right]);
                left++;
            }
            right++;
        }
    }
};
```

**时间复杂度：*O*(*N*)**

**空间复杂度：*O*(*1*)**

## 287.寻找重复数

给定一个包含 n + 1 个整数的数组 nums ，其数字都在 1 到 n 之间（包括 1 和 n），可知至少存在一个重复的整数。

假设 nums 只有 一个重复的整数 ，找出 这个重复的数 。

你设计的解决方案必须不修改数组 nums 且只用常量级 O(1) 的额外空间。

示例 1：

```cpp
输入：nums = [1,3,4,2,2]
输出：2
```


示例 2：

```cpp
输入：nums = [3,1,3,4,2]
输出：3
```


示例 3：

```cpp
输入：nums = [1,1]
输出：1
```


示例 4：

```cpp
输入：nums = [1,1,2]
输出：1
```

**题解：二分查找**

```cpp
class Solution {
public:
    int findDuplicate(vector<int>& nums) 
    {
        int n = nums.size();
        int l = 1, r = n - 1, ans = -1;
        while (l <= r) 
        {
            int mid = (l + r) >> 1;
            int cnt = 0;
            for (int i = 0; i < n; ++i) 
            {
                cnt += nums[i] <= mid;
            }
            if (cnt <= mid) 
            {
                l = mid + 1;
            } 
            else 
            {
                r = mid - 1;
                ans = mid;
            }
        }
        return ans;
    }
};
```

**时间复杂度：*O*(*N*)**

**空间复杂度：*O*(*1*)**

## 297.二叉树的序列化与反序列化

序列化是将一个数据结构或者对象转换为连续的比特位的操作，进而可以将转换后的数据存储在一个文件或者内存中，同时也可以通过网络传输到另一个计算机环境，采取相反方式重构得到原数据。

请设计一个算法来实现二叉树的序列化与反序列化。这里不限定你的序列 / 反序列化算法执行逻辑，你只需要保证一个二叉树可以被序列化为一个字符串并且将这个字符串反序列化为原始的树结构。

提示: 输入输出格式与 LeetCode 目前使用的方式一致，详情请参阅 LeetCode 序列化二叉树的格式。你并非必须采取这种方式，你也可以采用其他的方法解决这个问题。

示例 1：

<img src="./Image/297_leetcode.jpg" alt="img" style="zoom:50%;" />

```cpp
输入：root = [1,2,3,null,null,4,5]
输出：[1,2,3,null,null,4,5]
```

示例 2：

```cpp
输入：root = []
输出：[]
```


示例 3：

```cpp
输入：root = [1]
输出：[1]
```


示例 4：

```cpp
输入：root = [1,2]
输出：[1,2]
```

**题解：深度优先搜索**

```cpp
class Codec {
public:
    void rserialize(TreeNode* root, string& str) 
    {
        if (root == nullptr) {
            str += "None,";
        } 
        else 
        {
            str += to_string(root->val) + ",";
            rserialize(root->left, str);
            rserialize(root->right, str);
        }
    }

    string serialize(TreeNode* root) 
    {
        string ret;
        rserialize(root, ret);
        return ret;
    }

    TreeNode* rdeserialize(list<string>& dataArray) 
    {
        if (dataArray.front() == "None") 
        {
            dataArray.erase(dataArray.begin());
            return nullptr;
        }

        TreeNode* root = new TreeNode(stoi(dataArray.front()));
        dataArray.erase(dataArray.begin());
        root->left = rdeserialize(dataArray);
        root->right = rdeserialize(dataArray);
        return root;
    }

    TreeNode* deserialize(string data) 
    {
        list<string> dataArray;
        string str;
        for (auto& ch : data) 
        {
            if (ch == ',') 
            {
                dataArray.push_back(str);
                str.clear();
            } 
            else 
            {
                str.push_back(ch);
            }
        }
        if (!str.empty()) 
        {
            dataArray.push_back(str);
            str.clear();
        }
        return rdeserialize(dataArray);
    }
};
```

**时间复杂度：*O*(*N*)**

**空间复杂度：*O*(*N*)**

## 300.最长递增子序列

给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。

子序列是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。例如，[3,6,2,7] 是数组 [0,3,1,6,2,2,7] 的子序列。

示例 1：

```c++
输入：nums = [10,9,2,5,3,7,101,18]
输出：4
解释：最长递增子序列是 [2,3,7,101]，因此长度为 4 。
```

示例 2：

```cpp
输入：nums = [0,1,0,3,2,3]
输出：4
```


示例 3：

```cpp
输入：nums = [7,7,7,7,7,7,7]
输出：1
```

**题解：动态规划**

```cpp
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) 
    {
        vector<int> dp(nums.size(), 1);
        for (int i = 1; i < nums.size(); ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                if (nums[j] < nums[i])
                {
                    dp[i] = max(dp[i], dp[j] + 1);                    
                }
            }
        }
        return *max_element(dp.begin(), dp.end());
    }
};
```

**时间复杂度：O(N^2)**

**空间复杂度：*O*(*N*)**

## 301.删除无效的括号

给你一个由若干括号和字母组成的字符串 s ，删除最小数量的无效括号，使得输入的字符串有效。

返回所有可能的结果。答案可以按 任意顺序 返回。

示例 1：

```cpp
输入：s = "()())()"
输出：["(())()","()()()"]
```

示例 2：

```cpp
输入：s = "(a)())()"
输出：["(a())()","(a)()()"]
```


示例 3：

```c++
输入：s = ")("
输出：[""]
```

**题解：回溯**

```cpp
public class Solution {
private 
    int len;
    char[] charArray;
    Set<String> validExpressions = new HashSet<>();
    
    void dfs(int index, int leftCount, int rightCount, 
             int leftRemove, int rightRemove, StringBuilder path) 
    {
        if (index == len) 
        {
            if (leftRemove == 0 && rightRemove == 0) 
            {
                validExpressions.add(path.toString());
            }
            return;
        }

        char character = charArray[index];
        // 可能的操作 1：删除当前遍历到的字符
        if (character == '(' && leftRemove > 0) 
        {
            // 由于 leftRemove > 0，并且当前遇到的是左括号，因此可以尝试删除当前遇到的左括号
            dfs(index + 1, leftCount, rightCount, leftRemove - 1, rightRemove, path);
        }
        if (character == ')' && rightRemove > 0) 
        {
            // 由于 rightRemove > 0，并且当前遇到的是右括号，因此可以尝试删除当前遇到的右括号
            dfs(index + 1, leftCount, rightCount, leftRemove, rightRemove - 1, path);
        }

        // 可能的操作 2：保留当前遍历到的字符
        path.append(character);
        if (character != '(' && character != ')') 
        {
            // 如果不是括号，继续深度优先遍历
            dfs(index + 1, leftCount, rightCount, leftRemove, rightRemove, path);
        } 
        else if (character == '(') 
        {
            // 考虑左括号
            dfs(index + 1, leftCount + 1, rightCount, leftRemove, rightRemove, path);
        } 
        else if (rightCount < leftCount) 
        {
            // 考虑右括号
            dfs(index + 1, leftCount, rightCount + 1, leftRemove, rightRemove, path);
        }
        path.deleteCharAt(path.length() - 1);
    }
    
public:
    List<String> removeInvalidParentheses(String s) {
        this.len = s.length();
        this.charArray = s.toCharArray();

        // 第 1 步：遍历一次，计算多余的左右括号
        int leftRemove = 0;
        int rightRemove = 0;
        for (int i = 0; i < len; i++) 
        {
            if (charArray[i] == '(') 
            {
                leftRemove++;
            } 
            else if (charArray[i] == ')') 
            {
                // 遇到右括号的时候，须要根据已经存在的左括号数量决定
                if (leftRemove == 0) 
                {
                    rightRemove++;
                }
                if (leftRemove > 0) 
                {
                    // 关键：一个右括号出现可以抵销之前遇到的左括号
                    leftRemove--;
                }
            }
        }

        // 第 2 步：回溯算法，尝试每一种可能的删除操作
        StringBuilder path = new StringBuilder();
        dfs(0, 0, 0, leftRemove, rightRemove, path);
        return new ArrayList<>(this.validExpressions);
    }
};
```

## 309.最佳买卖股票时机含冷冻期

给定一个整数数组，其中第 i 个元素代表了第 i 天的股票价格 。

设计一个算法计算出最大利润。在满足以下约束条件下，你可以尽可能地完成更多的交易（多次买卖一支股票）:

你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
卖出股票后，你无法在第二天买入股票 (即冷冻期为 1 天)。
示例:

```c++
输入: [1,2,3,0,2]
输出: 3 
解释: 对应的交易状态为: [买入, 卖出, 冷冻期, 买入, 卖出]
```

**题解：动态规划**

```cpp
public:
    int maxProfit(vector<int>& prices) 
    {
        int n = prices.size();
        vector<vector<int>> dp(n, vector<int>(4, 0));
        dp[0][0] -= prices[0]; // 持股票
        for (int i = 1; i < n; i++) 
        {
            dp[i][0] = max(dp[i - 1][0], max(dp[i - 1][3], dp[i - 1][1]) - prices[i]);	// 买入
            dp[i][1] = max(dp[i - 1][1], dp[i - 1][3]); // 不买不卖
            dp[i][2] = dp[i - 1][0] + prices[i];	// 卖出
            dp[i][3] = dp[i - 1][2];				// 冷冻期
        }
        return max(dp[n - 1][3],max(dp[n - 1][1], dp[n - 1][2]));
    }
};
```

**时间复杂度：O(N)**

**空间复杂度：*O*(*N*)**

## 312.戳气球

有 n 个气球，编号为0 到 n - 1，每个气球上都标有一个数字，这些数字存在数组 nums 中。

现在要求你戳破所有的气球。戳破第 i 个气球，你可以获得 nums[i - 1] * nums[i] * nums[i + 1] 枚硬币。 这里的 i - 1 和 i + 1 代表和 i 相邻的两个气球的序号。如果 i - 1或 i + 1 超出了数组的边界，那么就当它是一个数字为 1 的气球。

求所能获得硬币的最大数量。

 示例 1：

```cpp
输入：nums = [3,1,5,8]
输出：167
解释：
nums = [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
coins =  3*1*5    +   3*5*8   +  1*3*8  + 1*8*1 = 167
```


示例 2：

```cpp
输入：nums = [1,5]
输出：10
```

**题解：动态规划**

```cpp
class Solution {
public:
    int maxCoins(vector<int>& nums) 
    {
        int n = nums.size();
        vector<vector<int>> rec(n + 2, vector<int>(n + 2));
        vector<int> val(n + 2);
        val[0] = val[n + 1] = 1;
        for (int i = 1; i <= n; i++) 
        {
            val[i] = nums[i - 1];
        }
        for (int i = n - 1; i >= 0; i--) 
        {
            for (int j = i + 2; j <= n + 1; j++) 
            {
                for (int k = i + 1; k < j; k++) 
                {
                    int sum = val[i] * val[k] * val[j];
                    sum += rec[i][k] + rec[k][j];
                    rec[i][j] = max(rec[i][j], sum);
                }
            }
        }
        return rec[0][n + 1];
    }
};
```

**时间复杂度：O(N^3)**

**空间复杂度：*O*(*N*^2)**

## 322.零钱兑换

给定不同面额的硬币 coins 和一个总金额 amount。编写一个函数来计算可以凑成总金额所需的最少的硬币个数。如果没有任何一种硬币组合能组成总金额，返回 -1。

你可以认为每种硬币的数量是无限的。

示例 1：

```cpp
输入：coins = [1, 2, 5], amount = 11
输出：3 
解释：11 = 5 + 5 + 1
```

示例 2：

```cpp
输入：coins = [2], amount = 3
输出：-1
```

示例 3：

```cpp
输入：coins = [1], amount = 0
输出：0
```

示例 4：

```cpp
输入：coins = [1], amount = 1
输出：1
```

示例 5：

```c++
输入：coins = [1], amount = 2
输出：2
```

**题解：动态规划——完全背包**

```cpp
lass Solution {
public:
    int coinChange(vector<int>& coins, int amount) 
    {
        vector<int> dp(amount + 1, INT_MAX);
        dp[0] = 0;
        for (int i = 1; i <= amount; i++) 			// 遍历背包
        {  
            for (int j = 0; j < coins.size(); j++) 	// 遍历物品
            { 
                if (i - coins[j] >= 0 && dp[i - coins[j]] != INT_MAX ) 
                {
                    dp[i] = min(dp[i - coins[j]] + 1, dp[i]);
                }
            }
        }
        if (dp[amount] == INT_MAX) 
            return -1;
        return dp[amount];
    }
};
```

**时间复杂度：*O*(Sn)**		S : amount       n : coins.size()

**空间复杂度：*O*(*S*)**

