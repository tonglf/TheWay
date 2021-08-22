# LeetCode 热题 HOT 100 -- 5

## 337.打家劫舍 III

在上次打劫完一条街道之后和一圈房屋后，小偷又发现了一个新的可行窃的地区。这个地区只有一个入口，我们称之为“根”。 除了“根”之外，每栋房子有且只有一个“父“房子与之相连。一番侦察之后，聪明的小偷意识到“这个地方的所有房屋的排列类似于一棵二叉树”。 如果两个直接相连的房子在同一天晚上被打劫，房屋将自动报警。

计算在不触动警报的情况下，小偷一晚能够盗取的最高金额。

示例 1:

    输入: [3,2,3,null,3,null,1]
    	 3
    	/ \
       2   3
        \   \ 
         3   1
    输出: 7 
    解释: 小偷一晚能够盗取的最高金额 = 3 + 3 + 1 = 7.     

示例 2:

    输入: [3,4,5,1,3,null,1]
    	 3
    	/ \
       4   5
      / \   \ 
     1   3   1
    输出: 9
    解释: 小偷一晚能够盗取的最高金额 = 4 + 5 = 9. 

**题解：动态规划**

```cpp
class Solution {
public:
    int rob(TreeNode* root) 
    {
        vector<int> result = robTree(root);
        return max(result[0], result[1]);
    }
    // 长度为2的数组，0：不偷，1：偷
    vector<int> robTree(TreeNode* cur) 
    {
        if (cur == NULL) 
            return vector<int>{0, 0};
        vector<int> left = robTree(cur->left);
        vector<int> right = robTree(cur->right);
        // 偷cur
        int val1 = cur->val + left[0] + right[0];
        // 不偷cur
        int val2 = max(left[0], left[1]) + max(right[0], right[1]);
        return {val2, val1};
    }
};
```

**时间复杂度：O(n)** 

**空间复杂度：O(logn)**


## 338.比特位计数

给定一个非负整数 num。对于 0 ≤ i ≤ num 范围中的每个数字 i ，计算其二进制数中的 1 的数目并将它们作为数组返回。

示例 1:

```cpp
输入: 2
输出: [0,1,1]
```


示例 2:

```cpp
输入: 5
输出: [0,1,1,2,1,2]
```


进阶:

给出时间复杂度为O(n*sizeof(integer))的解答非常容易。但你可以在线性时间O(n)内用一趟扫描做到吗？
要求算法的空间复杂度为O(n)。
你能进一步完善解法吗？要求在C++或任何其他语言中不使用任何内置函数（如 C++ 中的 __builtin_popcount）来执行此操作。

**题解：**

```cpp
class Solution {
public:
    vector<int> countBits(int n) 
    {
        vector<int> result(n + 1);
        for (int i = 0; i <= n; ++i)
        {
            int count = 0;
            int num = i;
            while (num)
            {
                num &= (num - 1);
                count++;
            }
            result[i] = count;
        }
        return result;
    }
};
```

**时间复杂度：O(logn)** 

**空间复杂度：O(1)**

**题解二：动态规划**

```cpp
class Solution {
public:
    vector<int> countBits(int n) {
        vector<int> bits(n + 1);
        for (int i = 1; i <= n; i++) 
        {
            bits[i] = bits[i & (i - 1)] + 1;
        }
        return bits;
    }
};
```

**时间复杂度：O(n)** 

**空间复杂度：O(1)**

## 347.前 K 个高频元素

给你一个整数数组 nums 和一个整数 k ，请你返回其中出现频率前 k 高的元素。你可以按 任意顺序 返回答案。

示例 1:

```cpp
输入: nums = [1,1,1,2,2,3], k = 2
输出: [1,2]
```

示例 2:

```cpp
输入: nums = [1], k = 1
输出: [1]
```

**题解：堆**

```cpp
class Solution {
public:
    // 小顶堆
    class mycomparison {
    public:
        bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs) 
        {
            return lhs.second > rhs.second;
        }
    };
    
    vector<int> topKFrequent(vector<int>& nums, int k) 
    {
        // 要统计元素出现频率
        unordered_map<int, int> map; // map<nums[i],对应出现的次数>
        for (int i = 0; i < nums.size(); i++) 
        {
            map[nums[i]]++;
        }

        // 对频率排序
        // 定义一个小顶堆，大小为 k
        priority_queue<pair<int, int>, vector<pair<int, int>>, mycomparison> pri_que;

        // 用固定大小为k的小顶堆，扫面所有频率的数值
        for (unordered_map<int, int>::iterator it = map.begin(); it != map.end(); it++) 
        {
            pri_que.push(*it);
            if (pri_que.size() > k) 	// 如果堆的大小大于了K，则队列弹出，保证堆的大小一直为k
            { 
                pri_que.pop();
            }
        }

        // 找出前K个高频元素，因为小顶堆先弹出的是最小的，所以倒叙来输出到数组
        vector<int> result(k);
        for (int i = k - 1; i >= 0; i--) 
        {
            result[i] = pri_que.top().first;
            pri_que.pop();
        }
        return result;
    }
};
```

**时间复杂度：O(nlogk)**
**空间复杂度：O(n)**

## 394.字符串解码

给定一个经过编码的字符串，返回它解码后的字符串。

编码规则为: k[encoded_string]，表示其中方括号内部的 encoded_string 正好重复 k 次。注意 k 保证为正整数。

你可以认为输入字符串总是有效的；输入字符串中没有额外的空格，且输入的方括号总是符合格式要求的。

此外，你可以认为原始数据不包含数字，所有的数字只表示重复的次数 k ，例如不会出现像 3a 或 2[4] 的输入。

示例 1：

```cpp
输入：s = "3[a]2[bc]"
输出："aaabcbc"
```


示例 2：

```cpp
输入：s = "3[a2[c]]"
输出："accaccacc"
```


示例 3：

```cpp
输入：s = "2[abc]3[cd]ef"
输出："abcabccdcdcdef"
```


示例 4：

```cpp
输入：s = "abc3[cd]xyz"
输出："abccdcdcdxyz"
```

**题解：栈**

```cpp
class Solution {
public:
    string getDigits(string &s, size_t &ptr) 
    {
        string ret = "";
        while (isdigit(s[ptr])) 
        {
            ret.push_back(s[ptr++]);
        }
        return ret;
    }

    string getString(vector<string> &v) 
    {
        string ret;
        for (const auto &s: v) 
        {
            ret += s;
        }
        return ret;
    }

    string decodeString(string s) 
    {
        vector<string> stk;
        size_t ptr = 0;

        while (ptr < s.size()) 
        {
            char cur = s[ptr];
            if (isdigit(cur)) 
            {
                // 获取一个数字并进栈
                string digits = getDigits(s, ptr);
                stk.push_back(digits);
            } 
            else if (isalpha(cur) || cur == '[') 
            {
                // 获取一个字母并进栈
                stk.push_back(string(1, s[ptr++])); 
            } 
            else 
            {
                ++ptr;
                vector <string> sub;
                while (stk.back() != "[") 
                {
                    sub.push_back(stk.back());
                    stk.pop_back();
                }
                reverse(sub.begin(), sub.end());
                // 左括号出栈
                stk.pop_back();
                // 此时栈顶为当前 sub 对应的字符串应该出现的次数
                int repTime = stoi(stk.back()); 
                stk.pop_back();
                string t, o = getString(sub);
                // 构造字符串
                while (repTime--) 
                    t += o; 
                // 将构造好的字符串入栈
                stk.push_back(t);
            }
        }
        return getString(stk);
    }
};
```

**时间复杂度：O(n)**
**空间复杂度：O(n)**

## 399.除法求值

给你一个变量对数组 equations 和一个实数值数组 values 作为已知条件，其中 equations[i] = [Ai, Bi] 和 values[i] 共同表示等式 Ai / Bi = values[i] 。每个 Ai 或 Bi 是一个表示单个变量的字符串。

另有一些以数组 queries 表示的问题，其中 queries[j] = [Cj, Dj] 表示第 j 个问题，请你根据已知条件找出 Cj / Dj = ? 的结果作为答案。

返回 所有问题的答案 。如果存在某个无法确定的答案，则用 -1.0 替代这个答案。如果问题中出现了给定的已知条件中没有出现的字符串，也需要用 -1.0 替代这个答案。

注意：输入总是有效的。你可以假设除法运算中不会出现除数为 0 的情况，且不存在任何矛盾的结果。

示例 1：

```c++
输入：equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
输出：[6.00000,0.50000,-1.00000,1.00000,-1.00000]
解释：
条件：a / b = 2.0, b / c = 3.0
问题：a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ?
结果：[6.0, 0.5, -1.0, 1.0, -1.0 ]
```


示例 2：

```c++
输入：equations = [["a","b"],["b","c"],["bc","cd"]], values = [1.5,2.5,5.0], queries = [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
输出：[3.75000,0.40000,5.00000,0.20000]
```


示例 3：

```c++
输入：equations = [["a","b"]], values = [0.5], queries = [["a","b"],["b","a"],["a","c"],["x","y"]]
输出：[0.50000,2.00000,-1.00000,-1.00000]
```

**题解：并查集**

```cpp
```





## 406.根据身高重建队列

假设有打乱顺序的一群人站成一个队列，数组 people 表示队列中一些人的属性（不一定按顺序）。每个 people[i] = [hi, ki] 表示第 i 个人的身高为 hi ，前面 正好 有 ki 个身高大于或等于 hi 的人。

请你重新构造并返回输入数组 people 所表示的队列。返回的队列应该格式化为数组 queue ，其中 queue[j] = [hj, kj] 是队列中第 j 个人的属性（queue[0] 是排在队列前面的人）。

示例 1：

```cpp
输入：people = [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]
输出：[[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]
解释：
编号为 0 的人身高为 5 ，没有身高更高或者相同的人排在他前面。
编号为 1 的人身高为 7 ，没有身高更高或者相同的人排在他前面。
编号为 2 的人身高为 5 ，有 2 个身高更高或者相同的人排在他前面，即编号为 0 和 1 的人。
编号为 3 的人身高为 6 ，有 1 个身高更高或者相同的人排在他前面，即编号为 1 的人。
编号为 4 的人身高为 4 ，有 4 个身高更高或者相同的人排在他前面，即编号为 0、1、2、3 的人。
编号为 5 的人身高为 7 ，有 1 个身高更高或者相同的人排在他前面，即编号为 1 的人。
因此 [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]] 是重新构造后的队列。
示例 2：

输入：people = [[6,0],[5,0],[4,0],[3,2],[2,2],[1,4]]
输出：[[4,0],[5,0],[2,2],[3,2],[1,4],[6,0]]
```

**题解：贪心**

```cpp
class Solution {
public:
    static bool cmp(const vector<int> a, const vector<int> b) 
    {
        if (a[0] == b[0]) return a[1] < b[1];
        return a[0] > b[0];
    }
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) 
    {
        sort (people.begin(), people.end(), cmp);
        vector<vector<int>> que;
        for (int i = 0; i < people.size(); i++) 
        {
            int position = people[i][1];
            que.insert(que.begin() + position, people[i]);
        }
        return que;
    }
};
```

**时间复杂度O(nlogn + n^2)**

**空间复杂度O(n)**

## 416.分割等和子集

给你一个 只包含正整数 的 非空 数组 nums 。请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。

示例 1：

```cpp
输入：nums = [1,5,11,5]
输出：true
解释：数组可以分割成 [1, 5, 5] 和 [11] 。
```


示例 2：

```cpp
输入：nums = [1,2,3,5]
输出：false
解释：数组不能分割成两个元素和相等的子集。
```

**题解：动态规划——01背包**

```cpp
class Solution {
public:
    bool canPartition(vector<int>& nums) 
    {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum % 2)
        {
            return false;
        }
        int mid = sum / 2;
        vector<int> dp(mid + 1, 0);
        for (int i = 0; i < nums.size(); ++i)
        {
            for (int j = mid; j >= nums[i]; --j)
            {
                dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]);
            }
        }
        return dp[mid] == mid;
    }
};
```

**时间复杂度O(n^2)**

**空间复杂度O(n)**

## 437.路径总和 III

给定一个二叉树，它的每个结点都存放着一个整数值。

找出路径和等于给定数值的路径总数。

路径不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。

二叉树不超过1000个节点，且节点数值范围是 [-1000000,1000000] 的整数。

示例：

<img src="./Image/437_leetcode.jpg" style="zoom: 67%;" />

```cpp
root = [10,5,-3,3,2,null,11,3,-2,null,1], sum = 8
      10
     /  \
    5   -3
   / \    \
  3   2   11
 / \   \
3  -2   1

返回 3。和等于 8 的路径有:

1.  5 -> 3
2.  5 -> 2 -> 1
3.  -3 -> 11
```

**题解：回溯**

```cpp
class Solution {
private:
    unordered_map<int, int> prefix;         // <前缀和，其出现次数>
    void dfs(TreeNode* root, int sum, int cur_sum, int& res)
    {
        if (!root) 
            return;
        cur_sum += root->val;               // 更新前缀和
        // 当前路径中存在以当前节点为终点的和为sum的子路径
        if (prefix.find(cur_sum - sum) != prefix.end())
            res += prefix[cur_sum - sum];
        
        prefix[cur_sum]++;                  // 将当前节点加入路径
        dfs(root->left, sum, cur_sum, res); // 在其左子树中递归寻找
        dfs(root->right, sum, cur_sum, res);// 在其右子树中递归寻找
        prefix[cur_sum]--;                  // 回溯
    }
public:
    int pathSum(TreeNode* root, int sum) 
    {
        int res = 0;    // 满足条件的路径数量
        prefix[0] = 1;  // 前缀和为0的路径只有一条：哪个节点都不选
        dfs(root, sum, 0, res);
        return res;
    }
};
```

**时间复杂度O(n)**

**空间复杂度O(n)**


## 438.找到字符串中所有字母异或位词

给定一个字符串 s 和一个非空字符串 p，找到 s 中所有是 p 的字母异位词的子串，返回这些子串的起始索引。

字符串只包含小写英文字母，并且字符串 s 和 p 的长度都不超过 20100。

说明：

字母异位词指字母相同，但排列不同的字符串。
不考虑答案输出的顺序。
示例 1:

```cpp
输入:
s: "cbaebabacd" p: "abc"

输出:
[0, 6]

解释:
起始索引等于 0 的子串是 "cba", 它是 "abc" 的字母异位词。
起始索引等于 6 的子串是 "bac", 它是 "abc" 的字母异位词。
```

示例 2:

```cpp
输入:
s: "abab" p: "ab"

输出:
[0, 1, 2]

解释:
起始索引等于 0 的子串是 "ab", 它是 "ab" 的字母异位词。
起始索引等于 1 的子串是 "ba", 它是 "ab" 的字母异位词。
起始索引等于 2 的子串是 "ab", 它是 "ab" 的字母异位词。
```

**题解：滑动窗口**

```cpp
class Solution {
public:
    vector<int> findAnagrams(string s, string p) 
    {
        int n = s.size(), m = p.size();
        if(m > n)
            return {};
        vector<int> ans, cnt_s(26), cnt_p(26);
        int i;
        for(i = 0; i < m; i++)
        {
            cnt_p[p[i] - 'a']++;
            cnt_s[s[i] - 'a']++;
        }
        if(cnt_p == cnt_s)
            ans.push_back(0);
        for( ; i < n; i++)
        {
            cnt_s[s[i] - 'a']++;
            cnt_s[s[i - m] - 'a']--;
            if(cnt_p == cnt_s)
                ans.push_back(i - m + 1);
        }
        return ans;
    }
};
```

**时间复杂度O(n)**

**空间复杂度O(n)**

## 448.找到所有数组中消失的数字

给你一个含 n 个整数的数组 nums ，其中 nums[i] 在区间 [1, n] 内。请你找出所有在 [1, n] 范围内但没有出现在 nums 中的数字，并以数组的形式返回结果。

示例 1：

```cpp
输入：nums = [4,3,2,7,8,2,3,1]
输出：[5,6]
示例 2：

输入：nums = [1,1]
输出：[2]
```

**题解：**

```cpp
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        int n = nums.size();
        for (auto& num : nums) 
        {
            int x = (num - 1) % n;
            nums[x] += n;
        }
        vector<int> ret;
        for (int i = 0; i < n; i++) 
        {
            if (nums[i] <= n) 
            {
                ret.push_back(i + 1);
            }
        }
        return ret;
    }
};
```

**时间复杂度O(n)**

**空间复杂度O(1)**

## 461.汉明距离

两个整数之间的 汉明距离 指的是这两个数字对应二进制位不同的位置的数目。

给你两个整数 x 和 y，计算并返回它们之间的汉明距离。

示例 1：

```cpp
输入：x = 1, y = 4
输出：2
解释：
1   (0 0 0 1)
4   (0 1 0 0)
       ↑   ↑
上面的箭头指出了对应二进制位不同的位置。
示例 2：

输入：x = 3, y = 1
输出：1
```

**题解：**

```cpp
class Solution {
public:
    int hammingDistance(int x, int y) 
    {
        int n = x ^ y;		// 异或
        int count = 0;
        while (n)
        {
            n &= (n - 1);	// 与
            count++;
        }
        return count;
    }
};
```

**时间复杂度：*O*(log*N*)**

**空间复杂度：*O*(1)**

## 494.目标和

给你一个整数数组 nums 和一个整数 target 。

向数组中的每个整数前添加 '+' 或 '-' ，然后串联起所有整数，可以构造一个 表达式 ：

例如，nums = [2, 1] ，可以在 2 之前添加 '+' ，在 1 之前添加 '-' ，然后串联起来得到表达式 "+2-1" 。
返回可以通过上述方法构造的、运算结果等于 target 的不同 表达式 的数目。

示例 1：

```cpp
输入：nums = [1,1,1,1,1], target = 3
输出：5
解释：一共有 5 种方法让最终目标和为 3 。
-1 + 1 + 1 + 1 + 1 = 3
+1 - 1 + 1 + 1 + 1 = 3
+1 + 1 - 1 + 1 + 1 = 3
+1 + 1 + 1 - 1 + 1 = 3
+1 + 1 + 1 + 1 - 1 = 3
示例 2：

输入：nums = [1], target = 1
输出：1
```

**题解：**

```cpp
class Solution {
public:
    int findTargetSumWays(vector<int>& nums, int target) 
    {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum < target) 
            return 0;
        if ((sum + target) % 2 == 1)
            return 0;
        int bagsize = (sum + target ) / 2;
        vector<int> dp(bagsize + 1, 0);
        dp[0] = 1;
        for (int i = 0; i < nums.size(); ++i)
        {
            for (int j = bagsize; j >= nums[i]; --j)
            {
                dp[j] += dp[j - nums[i]];
            }
        }
        return dp[bagsize];
    }
};
```

**时间复杂度O(n * m)**

**空间复杂度：O(m)**

## 538.把二叉搜素树转换为累加树

给出二叉 搜索 树的根节点，该树的节点值各不相同，请你将其转换为累加树（Greater Sum Tree），使每个节点 node 的新值等于原树中大于或等于 node.val 的值之和。

提醒一下，二叉搜索树满足下列约束条件：

节点的左子树仅包含键 小于 节点键的节点。
节点的右子树仅包含键 大于 节点键的节点。
左右子树也必须是二叉搜索树。
注意：本题和 1038: https://leetcode-cn.com/problems/binary-search-tree-to-greater-sum-tree/ 相同

示例 1：

```cpp
输入：[4,1,6,0,2,5,7,null,null,null,3,null,null,null,8]
输出：[30,36,21,36,35,26,15,null,null,null,33,null,null,null,8]
```


示例 2：

```cpp
输入：root = [0,null,1]
输出：[1,null,1]
```


示例 3：

```c++
输入：root = [1,0,2]
输出：[3,3,2]
```


示例 4：

```cpp
输入：root = [3,2,4,1]
输出：[7,9,4,10]
```

**题解：保存前一个指针**

```cpp
class Solution {
public:
    TreeNode* convertBST(TreeNode* root) 
    {
        if (root == nullptr)
            return root;
        TreeNode* cur = root;
        TreeNode* pre =nullptr;
        stack<TreeNode*> s;
        while (!s.empty() || cur)
        {
            if (cur)
            {
                s.push(cur);
                cur = cur->right;
            }
            else
            {
                cur = s.top();
                s.pop();
                if (pre)
                {
                    cur->val += pre->val;
                }
                pre = cur;
                cur = cur->left;
            }
        }
        return root;
    }
};
```

**时间复杂度O(n)**

**空间复杂度O(n)**

## 543.二叉树的直径

给定一棵二叉树，你需要计算它的直径长度。一棵二叉树的直径长度是任意两个结点路径长度中的最大值。这条路径可能穿过也可能不穿过根结点。

示例 :

```cpp
给定二叉树
	  1
     / \
    2   3
   / \     
  4   5    
```
返回 3, 它的长度是路径 [4,2,1,3] 或者 [5,2,1,3]。

**题解：**

```cpp
class Solution {
    int ans;
    int depth(TreeNode* rt)
    {
        if (rt == NULL) 
        {
            return 0; 	// 访问到空节点了，返回 0
        }
        int L = depth(rt->left); 		// 左儿子为根的子树的深度
        int R = depth(rt->right); 		// 右儿子为根的子树的深度
        ans = max(ans, L + R + 1); 		// 计算 d_node 即 L+R+1 并更新 ans
        return max(L, R) + 1; 			// 返回该节点为根的子树的深度
    }
public:
    int diameterOfBinaryTree(TreeNode* root) {
        ans = 1;
        depth(root);
        return ans - 1;
    }
};
```

**时间复杂度：*O*(*N*)**

**空间复杂度：O(Height)**

## 560.和为 K 的子数组

给定一个整数数组和一个整数 k，你需要找到该数组中和为 k 的连续的子数组的个数。

示例 1 :

```cpp
输入:nums = [1,1,1], k = 2
输出: 2 , [1,1] 与 [1,1] 为两种不同的情况。
```

**题解：**

```cpp
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) 
    {
        unordered_map<int, int> mp;
        mp[0] = 1;
        int count = 0, pre = 0;
        for (auto& x : nums) 
        {
            pre += x;
            if (mp.find(pre - k) != mp.end()) 
            {
                count += mp[pre - k];
            }
            mp[pre]++;
        }
        return count;
    }
};
```

**时间复杂度：*O*(*N*)**

**空间复杂度：*O*(*N*)**

## 581.最短无序连续子数组

给你一个整数数组 nums ，你需要找出一个 连续子数组 ，如果对这个子数组进行升序排序，那么整个数组都会变为升序排序。

请你找出符合题意的 最短 子数组，并输出它的长度。

 示例 1：

```c++
输入：nums = [2,6,4,8,10,9,15]
输出：5
解释：你只需要对 [6, 4, 8, 10, 9] 进行升序排序，那么整个表都会变为升序排序。
```


示例 2：

```cpp
输入：nums = [1,2,3,4]
输出：0
```


示例 3：

```cpp
输入：nums = [1]
输出：0
```

**题解：**

```cpp
class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) 
    {
        if (is_sorted(nums.begin(), nums.end()))
        {
            return 0;
        }
        vector<int> numsSorted(nums);
        sort(numsSorted.begin(), numsSorted.end());
        int left = 0;
        while (nums[left] == numsSorted[left])
        {
            left++;
        }
        int right = nums.size() - 1;
        while (nums[right] == numsSorted[right])
        {
            right--;
        }
        return right - left + 1;
    }
};
```

**时间复杂度：*O*(log*N*)**

**空间复杂度：*O*(N)**

## 617.合并二叉树

给定两个二叉树，想象当你将它们中的一个覆盖到另一个上时，两个二叉树的一些节点便会重叠。

你需要将他们合并为一个新的二叉树。合并的规则是如果两个节点重叠，那么将他们的值相加作为节点合并后的新值，否则不为 NULL 的节点将直接作为新二叉树的节点。

示例 1:

```cpp
输入: 
	Tree 1                     Tree 2                  
          1                         2                             
         / \                       / \                            
        3   2                     1   3                        
       /                           \   \                      
      5                             4   7                  
输出: 
合并后的树:
	     3
	    / \
	   4   5
	  / \   \ 
	 5   4   7
```

**题解：递归**

```cpp
class Solution {
public:
    TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) 
    {
        if (root1 == nullptr)
            return root2;
        if (root2 == nullptr)
            return root1;
        
        root1->val += root2->val;
        root1->left = mergeTrees(root1->left, root2->left);
        root1->right = mergeTrees(root1->right, root2->right);
        
        return root1;
    }
};
```

**时间复杂度：*O*(min(*m*,*n*))**

**空间复杂度：*O*(min(*m*,*n*))**

## 621.任务调度器

给你一个用字符数组 tasks 表示的 CPU 需要执行的任务列表。其中每个字母表示一种不同种类的任务。任务可以以任意顺序执行，并且每个任务都可以在 1 个单位时间内执行完。在任何一个单位时间，CPU 可以完成一个任务，或者处于待命状态。

然而，两个 相同种类 的任务之间必须有长度为整数 n 的冷却时间，因此至少有连续 n 个单位时间内 CPU 在执行不同的任务，或者在待命状态。

你需要计算完成所有任务所需要的 最短时间 。

 示例 1：

```cpp
输入：tasks = ["A","A","A","B","B","B"], n = 2
输出：8
解释：A -> B -> (待命) -> A -> B -> (待命) -> A -> B
     在本示例中，两个相同类型任务之间必须间隔长度为 n = 2 的冷却时间，而执行一个任务只需要一个单位时间，所以中间出现了（待命）状态。 
```

示例 2：

```cpp
输入：tasks = ["A","A","A","B","B","B"], n = 0
输出：6
解释：在这种情况下，任何大小为 6 的排列都可以满足要求，因为 n = 0
["A","A","A","B","B","B"]
["A","B","A","B","A","B"]
["B","B","B","A","A","A"]
...
诸如此类
```


示例 3：

```cpp
输入：tasks = ["A","A","A","A","A","A","B","C","D","E","F","G"], n = 2
输出：16
解释：一种可能的解决方案是：
     A -> B -> C -> A -> D -> E -> A -> F -> G -> A -> (待命) -> (待命) -> A -> (待命) -> (待命) -> A
```

**题解：**

```cpp
```



## 647.回文子串

给定一个字符串，你的任务是计算这个字符串中有多少个回文子串。

具有不同开始位置或结束位置的子串，即使是由相同的字符组成，也会被视作不同的子串。

 示例 1：

```cpp
输入："abc"
输出：3
解释：三个回文子串: "a", "b", "c"
```


示例 2：

```cpp
输入："aaa"
输出：6
解释：6个回文子串: "a", "a", "a", "aa", "aa", "aaa"
```

**题解一：动态规划**

```cpp
class Solution {
public:
    int countSubstrings(string s) 
    {
        vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), false));
        int result = 0;
        for (int i = s.size() - 1; i >= 0; i--) 
        {
            for (int j = i; j < s.size(); j++) 
            {
                if (s[i] == s[j] && (j - i <= 1 || dp[i + 1][j - 1])) 
                {
                    result++;
                    dp[i][j] = true;
                }
            }
        }
        return result;
    }
};
```

**时间复杂度：O(n^2)**

**空间复杂度：O(n^2)**

**题解二：双指针**

```cpp
class Solution {
public:
    int countSubstrings(string s) 
    {
        int result = 0;
        for (int i = 0; i < s.size(); i++) 
        {
            result += extend(s, i, i, s.size()); // 以i为中心
            result += extend(s, i, i + 1, s.size()); // 以i和i+1为中心
        }
        return result;
    }
    
    int extend(const string& s, int i, int j, int n) 
    {
        int res = 0;
        while (i >= 0 && j < n && s[i] == s[j]) 
        {
            i--;
            j++;
            res++;
        }
        return res;
    }
};
```

**时间复杂度：O(n^2)**

**空间复杂度：O(n^2)**

## 739.每日温度

请根据每日 气温 列表，重新生成一个列表。对应位置的输出为：要想观测到更高的气温，至少需要等待的天数。如果气温在这之后都不会升高，请在该位置用 0 来代替。

例如，给定一个列表 temperatures = [73, 74, 75, 71, 69, 72, 76, 73]，你的输出应该是 [1, 1, 4, 2, 1, 1, 0, 0]。

提示：气温 列表长度的范围是 [1, 30000]。每个气温的值的均为华氏度，都是在 [30, 100] 范围内的整数。

**题解：单调栈**

```cpp
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) 
    {
        int n = temperatures.size();
        vector<int> ans(n);
        stack<int> s;
        for (int i = 0; i < n; ++i) 
        {
            while (!s.empty() && temperatures[i] > temperatures[s.top()]) 
            {
                int previousIndex = s.top();
                ans[previousIndex] = i - previousIndex;
                s.pop();
            }
            s.push(i);
        }
        return ans;
    }
};
```

**时间复杂度：O(n)**

**空间复杂度：O(n)**
