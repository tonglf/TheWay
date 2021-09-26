# 剑指 offer

## 分类

### 重点题目

- [ ] No17、树的子结构
- [ ] No19、顺时针打印矩阵
- [ ] No21、栈的压入弹出序列
- [ ] No31、整数中 1 出现的次数（ 从 1 到 n 中 1 出现的次数 ）
- [ ] No35、数组中的逆排序
- [ ] No40、数组中只出现一次的数字
- [ ] No46、孩子们的游戏（圆圈中最后剩下的数）
- [ ] No49、字符串转化为整数
- [ ] No52、正则表达式匹配
- [ ] No53、表示数值的字符串
- [ ] No57、二叉树的下一个结点
- [ ] No61、序列化二叉树
- [ ] No63、数据流中的中位数
- [ ] No65、矩阵中的路径
- [ ] No66、机器人的运动范围

### 数组

- [ ] 1、6、13、19、28、32、35、37、40、50、51、63

### 字符串

- [ ] 2、27、34、43、44、49、53、54

### 链表

- [x] 3、14、15、16、25、36、55、56

### 树

- [ ] 4、17、18、22、23、24、26、38、39、57、58、59、60、61、62

### 栈、队列

- [ ] 5、20、21、52

### 动态规划

- [ ] 7、8、9、10、30、64、65、66

### 回溯

- [ ] 65、66

### 其他

- [ ] 11、12、29、31、33、41、42、45、46、47、48、6

## No1、二维数组中的查找

**题目描述**

在一个二维数组中（每个一维数组的长度相同），每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。

```cpp
[
 [1,2,8,9],
 [2,4,9,12],
 [4,7,10,13],
 [6,8,11,15]
]
```

给定 target = 7，返回 true。

给定 target = 3，返回 false。

**示例1**

**输入**

```cpp
7,[[1,2,8,9],[2,4,9,12],[4,7,10,13],[6,8,11,15]]
```

**返回值**

```cpp
true
```

说明

```cpp
存在 7 ，返回 true
```

**示例2**

**输入**

```cpp
3,[[1,2,8,9],[2,4,9,12],[4,7,10,13],[6,8,11,15]]
```

**返回值**

```cpp
false
```

**说明**

```cpp
不存在3，返回 false
```

**题解：**

**右上角**逐渐逼近**左下角** 很好

- 如果当前位置元素比 target 小，则 row++
- 如果当前位置元素比 target 大，则 col--
- 如果相等，返回 true
- 如果越界了还没找到，说明不存在，返回 false

```cpp
bool Find(int target, vector<vector<int>> array) 
{
    if (array.empty() || array[0].empty()) 
        return false;
       
    int i = 0;		// 表示行
    int j = array[0].size() - 1;	// 表示列
    while (i < array.size() && j >= 0)	// 保证不越界
    {
    	if (array[i][j] == target)
            return true;
            
        else if (array[i][j] > target)	// 右上角的值大于 target 则去左边列找
            j--;

        else				// 右上角的值小于 target 则去下一行去找
            i++;
    }
    return false;    
}
```

注：从左下角往右上角逼近也可以。

## No2、替换空格

**题目描述**

请实现一个函数，将一个字符串中的每个空格替换成“%20”。例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy。

**1、首先统计出长度，然后从后向前替换**

```cpp
class Solution {
public:
    string replaceSpace(string s) 
    {
        int count = 0;
        int n = s.size();
        for (int i = 0; i < n; ++i)
        {
            if (s[i] == ' ')
                count++;
        }
        s.resize(n + count * 2);		// 重点
        int index1 = n - 1;
        int index2 = s.size() - 1;
        while (index1 >= 0)
        {
            if (s[index1] == ' ')
            {
                s[index2--] = '0';
                s[index2--] = '2';
                s[index2--] = '%';
                index1--;
            }
            else
            {
                s[index2--] = s[index1--];
            }
        }
        return s;
    }
};
```

## No3、从尾到头打印链表

**题目描述**

输入一个链表，按链表从尾到头的顺序返回一个 ArrayList。

- 方法一：顺序遍历存入 vector ，然后使用 reverse 取反，或者返回尾迭代器，核心代码如下

```cpp
reverse(result.begin(),result.end());	
	return result;
// 或
return vector<int>(result.rbegin(),result.rend());
```

- 方法二：使用栈结构，将链表中的值顺序压入栈中，然后依次出栈，完成从尾到头打印链表。

```cpp
s.push(node->val);
std::cout << s.top() << " ";
a.pop();
```

- 方法三：使用递归

```cpp
class Solution {
public:
    vector<int> reversePrint(ListNode* head) 
    {
        vector<int> result;
        reversePrint(head, result);
        return result;
    }

    void reversePrint(ListNode* head, vector<int>& result)
    {
        if (head)
        {
            reversePrint(head->next, result);
            result.push_back(head->val);
        }
    }
};
```

## No4、重建二叉树

**题目描述**

输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。例如输入前序遍历序列 {1,2,4,7,3,5,6,8} 和中序遍历序列 {4,7,2,1,5,3,8,6}，则重建二叉树并返回。

重建二叉树可以使用前序遍历与中序遍历或者中序遍历与后序遍历，前序遍历不能重建成唯一的一棵二叉树。

- **前序遍历**与**中序遍历**重建二叉树

```cpp
class Solution {
public:
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) 
    {
        return buildTree(preorder.begin(), preorder.end(), inorder.begin(), inorder.end());
    }

    using Itor = vector<int>::iterator;
    TreeNode* buildTree(Itor preFirst, Itor preLast, Itor inFirst, Itor inLast)
    {
        if (preFirst >= preLast || inFirst >= inLast)
        {
            return nullptr;
        }

        TreeNode* root = new TreeNode(*preFirst);
        auto postion = find(inFirst, inLast, *preFirst);
        int dis = distance(inFirst, postion);

        root->left = buildTree(preFirst + 1, preFirst + dis + 1, inFirst, inFirst + dis);
        root->right = buildTree(preFirst + dis + 1, preLast, inFirst + dis + 1, inLast);

        return root;
    }
};
```

- **中序遍历**与**后序遍历**重建二叉树

```cpp
class Solution {
public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) 
    {
        return buildTree(inorder.begin(), inorder.end(), postorder.begin(), postorder.end());
    }

    using Itor = vector<int>::iterator;
    TreeNode* buildTree(Itor inFirst, Itor inLast, Itor postFirst, Itor postLast)
    {
        if (inFirst >= inLast || postFirst >= postLast)
        {
            return nullptr;
        }

        TreeNode* root = new TreeNode(*prev(postLast));
        auto postion = find(inFirst, inLast, *prev(postLast));
        int dis = distance(inFirst, postion);

        root->left = buildTree(inFirst, inFirst + dis, postFirst, postFirst + dis);
        root->right = buildTree(inFirst + dis + 1, inLast, postFirst + dis, prev(postLast));

        return root;
    }
};
```

**1008、前序遍历构造二叉搜索树**

返回与给定前序遍历 `preorder` 相匹配的二叉搜索树（binary **search** tree）的根结点。

**示例：**

```cpp
输入：[8,5,1,7,10,12]
输出：[8,5,10,1,7,null,12]
```

**题解：**

```cpp
class Solution {
public:
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        vector<int> inorder(preorder);
        sort(inorder.begin(), inorder.end());
        return buildTree(preorder.begin(), preorder.end(), inorder.begin(), inorder.end());
    }

    using Itor = vector<int>::iterator;
    TreeNode* buildTree(Itor preFirst, Itor preLast, Itor inFirst, Itor inLast)
    {
        if (preFirst >= preLast || inFirst >= inLast)
        {
            return nullptr;
        }

        TreeNode* root = new TreeNode(*preFirst);
        auto postion = find(inFirst, inLast, *preFirst);
        int dis = distance(inFirst, postion);

        root->left = buildTree(preFirst + 1, preFirst + dis + 1, inFirst, inFirst + dis);
        root->right = buildTree(preFirst + dis + 1, preLast, inFirst + dis + 1, inLast);

        return root;
    }
};
```

**889、根据前序和后序遍历构造二叉树**

返回与给定的前序和后序遍历匹配的任何二叉树。

 pre 和 post 遍历中的值是不同的正整数。

示例：

```cpp
输入：pre = [1,2,4,5,3,6,7], post = [4,5,2,6,7,3,1]
输出：[1,2,3,4,5,6,7]
```

**题解：**

```cpp
class Solution {
public:
    TreeNode* constructFromPrePost(vector<int>& pre, vector<int>& post) 
    {
        return helper(pre, post, 0, pre.size() - 1, 0, post.size() - 1);
    }

    TreeNode* helper(vector<int>& pre, vector<int>& post, int prestart, int preend, int poststart, int postend) 
    {
        if (prestart > preend) 
        {
            return nullptr;
        }
        TreeNode* root = new TreeNode(pre[prestart]);
        if (prestart == preend) 
        { 
            return root;
        }
        int i = poststart; 
        while (i < postend && post[i] != pre[prestart + 1])  // 确定分界点，左子树的根节点
        {
            i++; 
        }
        int len = i - poststart + 1; 		// 左子树长度
        root->left = helper(pre, post, prestart + 1, prestart + len, poststart, i);
        root->right = helper(pre, post, prestart + 1 + len, preend, i + 1, postend - 1);
        return root;
    }
};
```

## No5、用两个栈来实现一个队列

**题目描述**

完成队列的 Push 和 Pop 操作。 队列中的元素为 int 类型。

```cpp
class Solution {
public:
    void push(int node) 
    {
        stack1.push(node);
    }

    int pop() 
    {
        while(stack1.size() != 1)		// stack1 留一个栈底元素用于删除
        {
            stack2.push(stack1.top());
            stack1.pop();

        }
        
        int value = stack1.top();
        stack1.pop();
        
        while(!stack2.empty())		// 将 stack2 的元素搬到 stack1 中
        {
            stack1.push(stack2.top());
            stack2.pop();
        }
        return value;        
    }
private:
    stack<int> stack1;		// 保存元素
    stack<int> stack2;		// 辅助栈
};
```

## No6、旋转数组

**题目描述**

把一个数组最开始的若干个元素搬到数组的末尾，我们称之为数组的旋转。

输入一个非递减排序的数组的一个旋转，输出旋转数组的最小元素。例如数组 {3,4,5,1,2} 为 {1,2,3,4,5} 的一个旋转，该数组的最小值为1。

NOTE：给出的所有元素都大于0，若数组大小为0，请返回0。

**1、常规做法**

```cpp
int minNumberInRotateArray(vector<int> rotateArray) 
{
    if (rotateArray.size() == 0) 
        return 0;
    int  len = rotateArray.size();
    for (int i = 0; i < len-1; ++i) 
    {
        if (rotateArray[i] > rotateArray[i+1]) 	// 找到了旋转的节点
            return rotateArray[i+1];
    }
    return rotateArray[0];		// 未找到，即没有旋转数组，返回第一个数
}
```

**2、二分法**

```cpp
class Solution {
public:
    int minArray(vector<int>& numbers) {
        int l = 0;
        int r = numbers.size() - 1;
        while (l < r)
        {
            int mid = (l + r) / 2;
            if (numbers[mid] > numbers[r])
            {
                l = mid + 1;
            }
            else if (numbers[mid] < numbers[r])
            {
                r = mid;
            }
            else
            {
                r--;
            }
        }
        return numbers[l];
    }
};
```

## No7、斐波那契数列

**题目描述**

斐波那契数列，现在要求输入一个整数n，请你输出斐波那契数列的第n项（从0开始，第0项为0，第1项是1）。

**题解一：动态规划**

```cpp
int Fibonacci(int n) 
{
    if (n <= 1) 
        return n;		//0、1、1、2、3、5、8、13、21、34

    int F[2];
    F[0] = 0;
    F[1] = 1;
    int ret = 0;
    for (int i = 2; i <= n; ++i) 
    {
        ret = F[0] + F[1];
        F[0] = F[1];
        F[1] = ret;
    }
    return ret;
}
```

**题解二：递归**

```cpp
int Fibonacci(int n) 
{
    if(n <= 1) 
        return n;
    return Fibonacci( n - 1 ) + Fibonacci( n - 2 );
}
```

## No8、跳台阶

**题目描述**

一只青蛙一次可以跳上1级台阶，也可以跳上2级。求该青蛙跳上一个n级的台阶总共有多少种跳法（先后次序不同算不同的结果）。

**题解一：递归**

```cpp
int jumpFloor(int number) 
{
    if (number < 2)
        return 1;

    return jumpFloor(number - 1) + jumpFloor(number - 2);
}
```

**题解二：动态规划**

```cpp
class Solution {
public:
    int numWays(int n) {
        if (n < 2)
            return 1;
        int a = 1;
        int b = 1;
        int c = 1;
        for (int i = 2; i <= n; ++i)
        {
            c = (a + b) % 1000000007;
            a = b;
            b = c;
        }
        return c;
    }
};
```

## No9、变态跳台阶

**题目描述**

一只青蛙一次可以跳上1级台阶，也可以跳上2级……它也可以跳上n级。求该青蛙跳上一个n级的台阶总共有多少种跳法。

**题解一：递归**

因为 n 级台阶，第一步有 n 种跳法：跳1级、跳2级、到跳 n 级 跳1级，剩下n-1级，则剩下跳法是f(n-1) 跳2级，剩下n-2级，则剩下跳法是f(n-2) 所以 f(n) = f(n-1) + f(n-2) +...+f(1) 因为 f(n-1) = f(n-2) + f(n-3) + ... + f(1) 所以 f(n) = 2 * f(n-1)

```cpp
int jumpFloorII(int number) 
{
    if(number <= 2) 
        return number;
    return 2 * jumpFloorII(number - 1);
}
```

**题解二：**

```cpp
int jumpFloorII(int number) 
{
	if(number <= 2) 
        return number;
    int count = 0, a = 2;
    for(int i = 3;i <= number; ++i)
    {
        count = a * 2;
        a = count;
    }
    return count;
}
```

**题解三：动态规划**

```cpp
int jumpFloorII(int number) 
{
    vector<int> dp(number + 1);
    dp[0] = 1;
    for (int i = 1; i <= number; ++i)
    {
		for (int j = 0; j < i; ++j)
        {
            dp[i] += dp[j];
        }
    }
	return dp[number];
}
```

## No10、矩阵覆盖

**题目描述**

我们可以用 2*1 的小矩形横着或者竖着去覆盖更大的矩形。

请问用 n 个 2\*1 的小矩形无重叠地覆盖一个 2*n 的大矩形，总共有多少种方法？

比如 n=3 时，2*3 的矩形块有3种覆盖方法：

![img](https://uploadfiles.nowcoder.com/images/20201028/59_1603852524038_7FBC41C976CACE07CB222C3B890A0995)

**题解：与斐波那契数列一样**

```cpp
int rectCover(int number) 
{
    if (number <= 2) 
        return number;  
     
    return rectCover(number - 1) + rectCover(number - 2);
}
```

## No11、二进制中1的个数

**题目描述**

输入一个整数，输出该数 32 位二进制表示中1的个数。其中负数用补码表示。

**示例1**

**输入**

```c
10
```

**返回值**

```c
2
```

**题解：位运算**

```cpp
 int NumberOf1(int n) 
 {
     int count = 0;
     while (n)
     {
         count++;
         n = n & (n - 1);
     }
     return count;
}
```

如果一个整数不为 0，那么这个整数至少有一位是 1。如果我们把这个整数减 1，那么原来处在整数最右边的 1 就会变为 0，原来在 1后面的所有的 0 都会变成 1 (如果最右边的 1 后面还有0的话)。其余所有位将不会受到影响。

**举例**：以一个二进制数 1100 为例，手写一下。

## No12、数值的整数次方

**题目描述**

给定一个 double 类型的浮点数 base 和 int 类型的整数 exponent。求 base 的 exponent 次方。

保证 base 和 exponent 不同时为 0。不得使用库函数，同时不需要考虑大数问题，也不用考虑小数点后面 0 的位数。

**示例1**

**输入**

```
2.00000,3
```

**返回值**

```
8.00000
```

**示例2**

**输入**

```
2.10000,3
```

**返回值**

```
9.26100
```

**示例3**

**输入**

```
2.00000,-2
```

**返回值**

```cpp
0.25000		// 2 的 -2 次方等于 1/4 = 0.25
```

**题解：二分法**

```cpp
class Solution {
public:
    double myPow(double x, long n) 
    {
        if (!n) 
            return 1;
        
        if (n < 0) 
        {
            n = -n;
            x = 1 / x;  
        }
        double result = 1.0;
        while (n > 0) 
        {
            if (n % 2 == 1) 
            {
                result *= x;
            }
            x *= x;
            n /= 2;
        }
        return result;
    }
};
```

## No13、调整数组顺序使奇数位于偶数前面

**题目描述**

输入一个整数数组，实现一个函数来调整该数组中数字的顺序，使得所有的奇数位于数组的前半部分，所有的偶数位于数组的后半部分

**题解：双指针**

```cpp
class Solution {
public:
    vector<int> exchange(vector<int>& nums) 
    {
        int l = 0, r = nums.size() - 1;
        while (l < r)
        {
            while (l < r && !isEven(nums[l]))		// 是奇数
            {
                l++;
            }
            while (l < r && isEven(nums[r]))		// 是偶数
            {
                r--;
            }
            if (l < r)
            {
                swap(nums[l], nums[r]);
            }
        }
        return nums;
    }

    bool isEven(int n)
    {
        return (n & 1) == 0;
    }
};
```

## No14、 链表中倒数第k个结点

**题目描述**

输入一个链表，输出该链表中倒数第k个结点。

**快慢指针**

```cpp
class Solution {
public:
    ListNode* FindKthToTail(ListNode* pListHead, int k) 
    {
        if (!pListHead || k <= 0) 
            return nullptr;
        ListNode* slow = pListHead;
        ListNode* fast = pListHead;
 
        while (k--) 
        {
            if (fast)
                fast = fast->next;
            else
                return nullptr; 	// 如果单链表长度 < K,直接返回
        }
        while (fast) 
        {
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }
};
```

## No15、反转链表

**题目描述**

输入一个链表，反转链表后，输出新链表的表头。

**题解**

```cpp
ListNode* reverseList(ListNode* head) 
{
    ListNode* temp = nullptr; 			// 保存cur的下一个节点
    ListNode* cur = head;
	ListNode* pre = nullptr;
    while(cur) 
    {
        temp = cur->next;  		// 保存一下 cur的下一个节点，因为接下来要改变cur->next
        cur->next = pre; 		// 翻转操作          
        pre = cur;				// 更新pre 和 cur指针
        cur = temp;
    }
    return pre;
}
```

## No16、合并两个有序链表

**题目描述**

输入两个单调递增的链表，输出两个链表合成后的链表，当然我们需要合成后的链表满足单调不减规则。

**题解一：迭代**

```cpp
class Solution {
public:
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2) 
    {
        if (pHead1 == nullptr)
            return pHead2;
        if (pHead2 == nullptr)
            return pHead1;
        ListNode *dummy = new ListNode(-1);
        ListNode *p = dummy;
        
        while (pHead1 && pHead2)
        {
            if (pHead1->val < pHead2->val)
            {
                p->next = pHead1;
                p = p->next;
                pHead1 = pHead1->next;
            }
            else 
            {
                p->next = pHead2;
                p = p->next;
                pHead2 = pHead2->next;
            }
        }
        if (pHead1)
        {
            p->next = pHead1;
        }
        if (pHead2)
        {
            p->next = pHead2;
        }
        return dummy->next;
    }
};
```

**2、递归**

```cpp
ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
{
	if (pHead1 == nullptr) 
        return pHead2;
    if (pHead2 == nullptr) 
        return pHead1;

    if (pHead1->val <= pHead2->val) 
    {
        pHead1->next = Merge(pHead1->next, pHead2);
        return pHead1;
    }
    else 
    {
        pHead2->next = Merge(pHead1, pHead2->next);
        return pHead2;
    }
}
```

## No17、树的子结构

**题目描述**

输入两棵二叉树 A，B，判断 B 是不是 A 的子结构。（ps：我们约定空树不是任意一个树的子结构）

**示例1**

**输入**

```
{8,8,#,9,#,2,#,5},{8,9,#,2}
```

**返回值**

```cpp
true
```

**题解：递归**

```cpp
bool HasSubtreeCore(TreeNode* pRoot1, TreeNode* pRoot2)			// 对比函数
{
    if (pRoot2 == nullptr)  
        return true;
    if (pRoot1 == nullptr) 
        return false;
    
    if (pRoot1->val == pRoot2->val)
    {
        return HasSubtreeCore(pRoot1->left, pRoot2->left) 
        	&& HasSubtreeCore(pRoot1->right, pRoot2->right);
    }
    else
        return false;
}
bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
{
   if (pRoot1 == nullptr || pRoot2 == nullptr)
       return false;
    
   return HasSubtree(pRoot1->left,pRoot2) || HasSubtree(pRoot1->right,pRoot2) 
       			|| HasSubtreeCore(pRoot1, pRoot2);
}
```

## No18、二叉树的镜像

**题目描述**

操作给定的二叉树，将其变换为源二叉树的镜像。

**输入描述:** 二叉树的镜像定义：源二叉树

```cpp
            8
           /  \
          6   10
         / \  / \
        5  7 9 11
        镜像二叉树
            8
           /  \
          10   6
         / \  / \
        11  9 7  5                
```

**题解一：递归**

```cpp
void Mirror(TreeNode *pRoot) 
{
    if (pRoot == nullptr) 
        return;
    TreeNode* temp = pRoot->left;
    pRoot->left = pRoot->right;
    pRoot->right = temp;
    Mirror(pRoot->right);
    Mirror(pRoot->left);
}
```

**题解二：队列**

```cpp
void Mirror(TreeNode* pRoot) 
{
    if (pRoot == nullptr) 
        return;
    queue<TreeNode*> q;
    q.push(pRoot);
    while (!q.empty()) 
    {
        TreeNode* node = q.front();
        q.pop();
        if (node)
        {
            q.push(node->left);
            q.push(node->right);
            swap(node->left, node->right);
        }
    }
}
```

**题解三：栈**

```cpp
void Mirror(TreeNode* pRoot) 
{
    if (pRoot == nullptr) 
        return;
    stack<TreeNode*> s;
    s.push(pRoot);
    while (!s.empty()) 
    {
        TreeNode* node = s.top();
        s.pop();
        if (node) 
        {
            s.push(node->left);
            s.push(node->right);
            swap(node->left, node->right);
        }
    }
}
```

## No19、顺时针打印矩阵

**题目描述**

输入一个矩阵，按照从外向里以顺时针的顺序依次打印出每一个数字，例如，如果输入如下4 X 4矩阵： 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 则依次打印出数字1,2,3,4,8,12,16,15,14,13,9,5,6,7,11,10.

注意：矩阵非方阵，可能为行矩阵也可能为列矩阵。

```cpp
class Solution {
public:
	vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector <int> res;
        if(matrix.empty()) 
            return res;
        int rl = 0, rh = matrix.size() - 1;    // 记录待打印的矩阵上下边缘
        int cl = 0, ch = matrix[0].size() - 1; // 记录待打印的矩阵左右边缘
        while (1)
        {
            for (int i = cl; i <= ch; i++) 
                res.push_back(matrix[rl][i]);	// 从左往右
            if (++rl > rh) 
                break; 		// 若超出边界，退出
            
            for (int i = rl; i <= rh; i++) 
                res.push_back(matrix[i][ch]);	// 从上往下
            if (--ch < cl) 
                break;
            
            for (int i = ch; i >= cl; i--) 
                res.push_back(matrix[rh][i]);	// 从右往左
            if (--rh < rl) 
                break;
            
            for (int i = rh; i >= rl; i--) 
                res.push_back(matrix[i][cl]);	// 从下往上
            if (++cl > ch) 
                break;
        }
        return res;
    }
};
```

## No20、包含min函数的栈

**题目描述**

定义栈的数据结构，请在该类型中实现一个能够得到栈中所含最小元素的 min 函数（时间复杂度应为O(1)）。

**1、用两个栈：一个记录数值，一个记录最小值**

```cpp
class Solution {
	stack<int> minSt;
    stack<int> st;
public:
    void push(int value) 
    {
        if(st.size() == 0) 
        {
            st.push(value);
            minSt.push(value);
        }
        else
        {
            st.push(value);
            if(value < minSt.top())
                minSt.push(value);            
            else
                minSt.push(minSt.top());
        }
    }
    
    void pop() 
    {
        st.pop();
        minSt.pop();
    }
    
    int top() 
    {
        return st.top();
    }
    
    int min() 
    {
        return minSt.top();
    }
};
```

**2、只用一个栈**

```cpp
class Solution {
    int minNum = INT_MAX;
    stack<int> st;
public:
    void push(int value) 
    {
        minNum = std::min(value, minNum);//注意当前类中也有一个min函数，
        //所以我们需要明确此时的min函数是哪个函数
        st.push(minNum);
        st.push(value);
    }
    
    void pop() 
    {
        st.pop();		// pop掉当前值
        st.pop();		// pop掉当前最小值
        int temp = st.top();
        st.pop();
        if(minNum < st.top())	// 更新最小值
        {
            minNum = st.top();
            st.pop();
            st.push(minNum);	// 最小值入栈
        }
        st.push(temp);
    }
    
    int top() 
    {
        return st.top();
    }
    
    int min() 
    {
        return minNum;
    }
};
```

## No21、栈的压入弹出序列

**题目描述** 输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否可能为该栈的弹出顺序。假设压入栈的所有数字均不相等。例如序列1,2,3,4,5是某栈的压入顺序，序列4,5,3,2,1是该压栈序列对应的一个弹出序列，但4,3,5,1,2就不可能是该压栈序列的弹出序列。（注意：这两个序列的长度是相等的）

**示例1**

**输入**

```臭屁屁
[1,2,3,4,5],[4,3,5,1,2]
```

**返回值**

```cpp
false
```

**题解：存储用vector、stack均可**

```cpp
class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) 
    {
	vector<int> v;
    for(int i = 0, j = 0; i < pushed.size();)
    {
        v.push_back(pushed[i++]);
        while (j < popped.size() && !v.empty() && v.back() == popped[j])
        {
            v.pop_back();
            j++;
    	}      
    }
	return v.empty();
    }
};
```

## No22、从上往下打印二叉树

**题目描述**

从上往下打印出二叉树的每个节点，同层节点从左至右打印。层次打印二叉树

**题解：层次遍历，借助队列**

```cpp
vector<int> PrintFromTopToBottom(TreeNode* root) 
{
    vector<int> result;
    if (root == nullptr) 
        return result;
    queue<TreeNode*>  q;
    q.push(root);
    TreeNode* node;
    while (!q.empty()) 
    {
        node = q.front();
        q.pop();
        result.push_back(node->val);
        if (node->left) 
            q.push(node->left);
        if (node->right) 
            q.push(node->right);        
    }
    return result;
}
```

## No23、二叉搜索树的后序遍历序列

**题目描述**

输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。如果是则返回true,否则返回false。假设输入的数组的任意两个数字都互不相同。（ps：我们约定空树不是二叉搜索树）

**题解：递归**

```cpp
bool VerifySquenceOfBST(vector<int> sequence) 
{
    return VerifySquenceOfBSTCore(sequence, 0, sequence.size() - 1);
}

bool VerifySquenceOfBSTCore(vector<int>& sequence, int start, int end) 
{
    if (start >= end) 
        return true;
    
    int low = start;
    while (low < end && sequence[low] < sequence[end])  // end 为根节点
        ++low;

    for (int i = low; i < end; ++i) 			// [low, end-1] 为二叉搜索树的右子树，都需要大于根节点
    {
        if (sequence[i] <= sequence[end]) 
            return false;
    }

    return VerifySquenceOfBSTCore(sequence, start,low - 1) 
        && VerifySquenceOfBSTCore(sequence, low,end - 1);
}
```

## No24、二叉树中和为某一值的路径

**题目描述**

输入一颗二叉树的根节点和一个整数，按字典序打印出二叉树中结点值的和为输入整数的所有路径。路径定义为从树的根结点开始往下一直到叶结点所经过的结点形成一条路径。

**示例1**

**输入**

```cpp
{10,5,12,4,7},22
```

**返回值**

```cpp
[[10,5,7],[10,12]]
```

**示例2**

**输入**

```cpp
{10,5,12,4,7},15
```

**返回值**

```cpp
[]
```

**题解：回溯**

```cpp
class Solution {
    vector<vector<int>> result;
    vector<int> path;
public:
    vector<vector<int>> pathSum(TreeNode* root, int target) {
        if (root == nullptr)
            return result;
        traversal(root, target);
        return result;
    }

    void traversal(TreeNode* cur, int target)
    {
        path.push_back(cur->val);
        if (cur->left == nullptr && cur->right == nullptr)
        {
            if (accumulate(path.begin(), path.end(), 0) == target)
            {
                result.push_back(path);
            }
            return ;
        }
        if (cur->left)
        {
            traversal(cur->left, target);
            path.pop_back();
        }
        if (cur->right)
        {
            traversal(cur->right, target);
            path.pop_back();
        }
    }
};
```

## No25、复杂链表的复制

**题目描述** 输入一个复杂链表（每个节点中有节点值，以及两个指针，一个指向下一个节点，另一个特殊指针random指向一个随机节点），请对此链表进行深拷贝，并返回拷贝后的头结点。（注意，输出结果中请不要返回参数中的节点引用，否则判题程序会直接返回空）

**示例1**

**输入**

```
{10,5,12,4,7},22
```

**返回值**

```
[[10,5,7],[10,12]]
```

**示例2** **输入**

```
{10,5,12,4,7},15
```

**返回值**

```
[]
```

**题解：**

```cpp
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

class Solution {
public:
    Node* copyRandomList(Node* head) {
        Node* p = head;
        while (p)								// 在原本链表后面添加节点
        {
            Node * node = new Node(p->val);
            node->next = p->next;
            p->next = node;
            p = p->next->next;
        }
        p = head;
        while (p)								// 对节点的随机指针赋值，注意为空的情况
        {
            p->next->random = p->random == nullptr ? nullptr : p->random->next;
            p = p->next->next;
        }

        Node* headCopy = new Node(-1);
        Node* p2 = headCopy;
        p = head;
        while (p)								// 一个链表拆分为两个链表
        {
            p2->next = p->next;
            p->next = p->next->next;
            p = p->next;
            p2 = p2->next;
        }
        return headCopy->next;
    }
};
```

## No26、二叉搜索树与双向（循环）链表

**题目描述**

输入一棵二叉搜索树，将该二叉搜索树转换成一个排序的双向链表。要求不能创建任何新的结点，只能调整树中结点指针的指向。

**题解：迭代**

```cpp
class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        if (root == nullptr)
            return root;
        Node* pHead = nullptr;
        Node* pre = nullptr;
        stack<Node*> s;
        while (root || !s.empty())
        {
            if (root)
            {
                s.push(root);
                root = root->left;
            }
            else
            {
                root = s.top();
                s.pop();
                if (pre != nullptr)
                {
                    pre->right = root;
                    root->left = pre;  
                }
                else
                {
                    pHead = root;
                }
                pre = root;
                root = root->right;
            }
        }
        
        pre->right = pHead;			// 双向循环链表，加入这两个语句
        pHead->left = pre;
        
        return pHead;
    }
};
```

## No27、字符串的排列

**题目描述**

输入一个字符串,按字典序打印出该字符串中字符的所有排列。例如输入字符串abc,则打印出由字符a,b,c所能排列出来的所有字符串abc,acb,bac,bca,cab和cba。

**输入描述:**

```
输入一个字符串,长度不超过9(可能有字符重复),字符只包括大小写字母。
```

**示例1**

**输入**

```cpp
"ab"
```

**返回值**

```cpp
["ab","ba"]
```

**题解：回溯**

```cpp
class Solution {
vector<string> result;
string str;
public:
    vector<string> permutation(string s) 
    {
        vector<bool> used(s.size(), false);
        sort(s.begin(), s.end());
        backtracking(s, used);
        return result;
    }
    void backtracking(const string& s, vector<bool>& used)
    {
        if (str.size() == s.size())
        {
            result.push_back(str);
            return ;
        }

        for (int i = 0; i < s.size(); ++i)
        {
            if (i > 0 && s[i] == s[i - 1] && used[i - 1] == false)
                continue;
            if (used[i] == true)
                continue;
            str.push_back(s[i]);
            used[i] = true;
            backtracking(s, used);
            used[i] = false;
            str.pop_back();
        }
    }
};
```

## No28、数组中出现次数超过一半的数字

**题目描述**

数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。例如输入一个长度为9的数组{1,2,3,2,2,2,2,5,4}。由于数字2在数组中出现了5次，超过数组长度的一半，因此输出2。如果不存在则输出0。

**示例1**

**输入**

```
[1,2,3,2,2,2,5,4,2]
```

**返回值**

```
2
```

**题解**

```cpp
class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int result = nums[0];
        int times = 1;
        for (int i = 1; i < nums.size(); ++i)
        {
            if (result == nums[i])
            {
                times++;
            }
            else
            {
                if (times == 0)
                {
                    times = 1;
                    result = nums[i];
                }
                else
                {
                    times--;
                }
            }
        }
        return result;
    }
};
```

## No29、最小的K个数

**题目描述**

输入n个整数，找出其中最小的K个数。例如输入4,5,1,6,2,7,3,8这8个数字，则最小的4个数字是1,2,3,4,。

**示例1** **输入**

```
[4,5,1,6,2,7,3,8],4
```

**返回值**

```
[1,2,3,4]
```

**题解：优先队列**

priority_queue<int,vector<int>,less<int>>

```cpp
// class Solution {
// public:
//     vector<int> getLeastNumbers(vector<int>& arr, int k) {
//         priority_queue<int, vector<int>, greater<int>> pq;
//         for (auto a : arr)
//         {
//             pq.push(a);
//         }
//         vector<int> result;
//         while (k--)
//         {
//             result.push_back(pq.top());
//             pq.pop();
//         }
//         return result;
//     }
// };

class Solution {
public:
    vector<int> getLeastNumbers(vector<int>& arr, int k) {
        //priority_queue<int, vector<int>, greater<int>> pq;	// 这样不行啊
        priority_queue<int> pq;	
        vector<int> result;
        if (k == 0)
            return result;

        for (auto a : arr)
        {
            if (pq.size() < k)
            {
                pq.push(a);
            }
            else
            {
                if (a < pq.top())
                {
                    pq.pop();
                    pq.push(a);
                }
            }
        }

        while (k--)
        {
            result.push_back(pq.top());
            pq.pop();
        }
        return result;
    }
};
```

## No30、连续子数组的最大和

**示例1**

**输入**

```
[1,-2,3,10,-4,7,2,-5]
```

**返回值**

```
18
```

**说明** 输入的数组为{1, -2, 3, 10, -4, 7, 2, -5}，和最大的子数组为{3, 10, -4, 7, 2}，因此输出为该子数组的和 18。

**题解：动态规划**

```cpp
class Solution {
public:
    int maxSubArray(vector<int>& nums) 
    {
        int maxVal = nums[0];
        vector<int> dp(nums.size());
        dp[0] = nums[0];
        for (int i = 1; i < nums.size(); ++i)
        {
            dp[i] = max(dp[i - 1] + nums[i], nums[i]);
            maxVal = max(dp[i], maxVal);
        }
        return maxVal;
    }
};
```

## No31、整数中 1 出现的次数（ 从 1 到 n 中 1 出现的次数 ）

**题目描述**

求出1-13的整数中1出现的次数,并算出100-1300的整数中1出现的次数？

为此他特别数了一下1~13中包含1的数字有1、10、11、12、13因此共出现6次,但是对于后面问题他就没辙了。

ACMer希望你们帮帮他,并把问题更加普遍化,可以很快的求出任意非负整数区间中1出现的次数（从1 到 n 中1出现的次数）。

**输入**

```
13
```

**返回值**

```
6
```

**题解：**

分两种情况，例如：1234和2234，high为最高位，pow为最高位权重 在每种情况下都将数分段处理，即0-999，1000-1999，...，剩余部分

case1：最高位是1，则最高位的1的次数为last+1（1000-1234） 每阶段即0-999的1的个数1*countDigitOne(pow-1) 剩余部分1的个数为countDigitOne(last)--最高位已单独计算了

case2：最高位不是1，则最高位的1的次数为pow（1000-1999） 每阶段除去最高位即0-999，1000-1999中1的次数为high*countDigitOne(pow-1) 剩余部分1的个数为countDigitOne(last) 发现两种情况仅差别在最高位的1的个数，因此单独计算最高位的1（cnt），合并处理两种情况

```cpp
class Solution {
public:
    int countDigitOne(int n) 
    {
        if (n <= 0)
            return 0;
        if (n < 10)
            return 1;
        int high = n, pow = 1;
        while (high >= 10)
        {
            high /= 10;
            pow *= 10;
        }
        int last = n - high * pow;
        int cnt = high == 1 ? last + 1 : pow;
        return cnt + high * countDigitOne(pow - 1) + countDigitOne(last);
    }
};
```

## No32、把数组排成最小的数

**题目描述**

输入一个正整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。例如输入数组{3，32，321}，则打印出这三个数字能排成的最小数字为321323。

**示例1**

**输入**

```
[3,32,321]
```

**返回值**

```
"321323"
```

**题解：**

```cpp
string minNumber(vector<int>& nums) 
{
    vector<string> temp;
    for (auto num : nums) 
    {
        temp.push_back(to_string(num));
    }
    sort(temp.begin(), temp.end(), [](const string& a, const string& b) { return a + b < b + a; });
    string str;
    for (auto& s : temp) 
    {
        str += s;
    }
    return str;
}
```

## No33、第N个丑数

我们把只包含质因子 2、3 和 5 的数称作丑数（Ugly Number）。求按从小到大的顺序的第 n 个丑数。

**示例:**

```cpp
输入: n = 10
输出: 12
解释: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 是前 10 个丑数。
```

**题解：**

```cpp
class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> dp(n + 1);
        dp[1] = 1;
        int p2 = 1, p3 = 1, p5 = 1;
        for (int i = 2; i <= n; i++) 
        {
            int num2 = dp[p2] * 2, num3 = dp[p3] * 3, num5 = dp[p5] * 5;
            dp[i] = min(min(num2, num3), num5);
            if (dp[i] == num2) 
                p2++;
            if (dp[i] == num3) 
                p3++;
            if (dp[i] == num5) 
                p5++;
        }
        return dp[n];
    }
};
```

## No34、第一个只出现一次的字符

在字符串 s 中找出第一个只出现一次的字符。如果没有，返回一个单空格。 s 只包含小写字母。

示例 1:

```cpp
输入：s = "abaccdeff"
输出：'b'
```


示例 2:

```cpp
输入：s = "" 
输出：' '
```

**题解：**

```cpp
class Solution {
public:
    char firstUniqChar(string s) {
        unordered_map<char, int> map;
        for (int i = 0; i < s.size(); ++i)
        {
            map[s[i]]++;
        }
        for (int i = 0; i < s.size(); ++i)
        {
            if (map[s[i]] == 1)
            {
                return s[i];
            }
        }
        return ' ';
    }
};
```

## No35、数组中的逆排序

**题目描述**

在数组中的两个数字，如果前面一个数字大于后面的数字，则这两个数字组成一个逆序对。输入一个数组，求出这个数组中的逆序对的总数。

**示例 1:**

```cpp
输入: [7,5,6,4]
输出: 5
```

**限制：**

```cpp
0 <= 数组长度 <= 50000
```

**题解：归并**

```cpp
class Solution {
public:
    int mergeSort(vector<int>& nums, vector<int>& tmp, int l, int r) {
        if (l >= r) 
        {
            return 0;
        }

        int mid = (l + r) / 2;
        int inv_count = mergeSort(nums, tmp, l, mid) + mergeSort(nums, tmp, mid + 1, r);
        
        int i = l, j = mid + 1, pos = l;
        while (i <= mid && j <= r) 
        {
            if (nums[i] <= nums[j]) 
            {
                tmp[pos] = nums[i];
                ++i;
                inv_count += (j - (mid + 1));
            }
            else 
            {
                tmp[pos] = nums[j];
                ++j;
            }
            ++pos;
        }
        for (int k = i; k <= mid; ++k) 
        {
            tmp[pos++] = nums[k];
            inv_count += (j - (mid + 1));
        }
        for (int k = j; k <= r; ++k) 
        {
            tmp[pos++] = nums[k];
        }
        copy(tmp.begin() + l, tmp.begin() + r + 1, nums.begin() + l);
        return inv_count;
    }

    int reversePairs(vector<int>& nums) 
    {
        int n = nums.size();
        vector<int> tmp(n);
        return mergeSort(nums, tmp, 0, n - 1);
    }
};
```

## No36、返回两个链表中的第一个公共节点

**题目描述**

输入两个链表，找出它们的第一个公共结点。（注意因为传入数据是链表，所以错误测试数据的提示是用其他方式显示的，保证传入数据是正确的）

**题解一：长度较长的链表先走，之后同步走**

```cpp
class Solution {
protected:
    int LensList(ListNode *head)
    {
        int n = 0;
        ListNode* p = head;
        while (p)
        {
            p = p->next;
            n++;
        }
        return n;
    }

public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) 
    {
        ListNode* pA = headA;
        ListNode* pB = headB;

        int lengthA = LensList(pA);
        int lengthB = LensList(pB);

        if (lengthA > lengthB)
        {
            int dis = lengthA - lengthB;
            while (dis--)
            {
                pA = pA->next;
            }
        }
        else
        {
            int dis = lengthB - lengthA;
            while (dis--)
            {
                pB = pB->next;
            }
        }

        while (pA && pA != pB)
        {
            pA = pA->next;
            pB = pB->next;
        }
        return pA;
    }
};
```

**题解二：**

a.长度相同的：1. 有公共结点的，第一次就遍历到；2. 没有公共结点的，走到尾部NULL相遇，返回NULL； b.长度不同的：1. 有公共结点的，第一遍差值就出来了，第二遍就会一起到公共结点；2. 没有公共结点的，第二次遍历一起到结尾NULL。

```cpp
//定义两个指针, 第一轮让两个到达末尾的节点指向另一个链表的头部, 最后如果相遇则为交点(在第一轮移动中恰好抹除了长度差)
//        两个指针等于移动了相同的距离, 有交点就返回, 无交点就是各走了两条指针的长度
ListNode* FindFirstCommonNode(ListNode* pHead1, ListNode* pHead2) 
{
    if (pHead1 == NULL || pHead2 == NULL) 
        return NULL;
    ListNode* p1 = pHead1;
    ListNode* p2 = pHead2;
    while (p1 != p2) 
    {
        p1 = (p1 == NULL ? pHead2 : p1->next);
        p2 = (p2 == NULL ? pHead1 : p2->next);
    }
    return p1;
}
```

## No37、 统计一个数字在排序数组中出现的次数

**题目描述**

统计一个数字在升序数组中出现的次数。

**示例1**

**输入**

```
[1,2,3,3,3,3,4,5],3
```

**返回值**

```
4
```

**1、STL中取巧的一种写法，直接调equal_range() 方法**

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        auto pos = equal_range(nums.begin(), nums.end(), target);
        return pos.second - pos.first;
    }
};
```

**2、二分法，找到第一次出现的位置和最后一次出现的位置**

```cpp
class Solution {
public:
    int getFirstK(vector<int>& nums, int target)
    {
        int l = 0, r = nums.size();
        while (l < r)
        {
            int mid = l + (r - l) / 2;
            if (nums[mid] == target)
            {
                if (mid == 0 || nums[mid - 1] != target)		// 找到第一个出现元素的位置
                    return mid;
                else
                    r = mid;
            }
            else if (nums[mid] > target)
            {
                r = mid;
            }
            else
                l = mid + 1;
        }
        return -1;
    }

    int getLastK(vector<int>& nums, int target)
    {
        int l = 0, r = nums.size();
        while (l < r)
        {
            int mid = l + (r - l) / 2;
            if (nums[mid] == target)
            {
                if (mid == nums.size() - 1 || nums[mid + 1] != target)	// 找到最后一个出现元素的位置
                    return mid;
                else
                    l = mid + 1;
            }
            else if (nums[mid] > target)
            {
                r = mid;
            }
            else
                l = mid + 1;
        }
        return -1;
    }

    int search(vector<int>& nums, int target) {
        int first = getFirstK(nums, target);
        int last = getLastK(nums, target);
        if (first == -1)
            return 0;
        return last - first + 1;
    }
};
```

## No38、二叉树的深度

**题目描述**

输入一棵二叉树，求该树的深度。从根结点到叶结点依次经过的结点（含根、叶结点）形成树的一条路径，最长路径的长度为树的深度。

**示例1**

**输入**

```cpp
{1,2,3,4,5,#,6,#,#,7}
```

**返回值**

```cpp
4
```

**题解一：层次遍历，看看有多少层**

```cpp
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == NULL)
            return 0;
        queue<TreeNode*> q;
        q.push(root);
        int k = 0;
        while (!q.empty())
        {
            int size = q.size();
            k++;
            for (int i = 0; i < size; ++i)
            {
                TreeNode* node = q.front();
                q.pop();
                if (node->left)
                    q.push(node->left);
                if (node->right)
                    q.push(node->right);
            }
        }
        return k;
    }
};
```

**题解二：递归法**

```cpp
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == NULL)
            return 0;
        int left = maxDepth(root->left);
        int right = maxDepth(root->right);
        return max(left, right) + 1;
    }
};
```

## No39、平衡二叉树

**题目描述**

输入一棵二叉树，判断该二叉树是否是平衡二叉树。

在这里，我们只需要考虑其平衡性，不需要考虑其是不是排序二叉树

**输入**

```cpp
{1,2,3,4,5,6,7}
```

**返回值**

```cpp
true
```

**题解：递归**

```cpp
class Solution {
public:
    bool isBalanced(TreeNode* root) {
        return getDepth(root) != -1;
    }

    int getDepth(TreeNode* root)
    {
        if (root == NULL)
            return 0;
        int left = getDepth(root->left);
        if (left == -1)
            return -1;
        int right = getDepth(root->right);
        if (right == -1)
            return -1;
        return abs(left - right) > 1 ? -1 : 1 + max(left, right);
    }
};
```

## No40、数组中只出现一次的数字

**题目描述**

一个整型数组里除了两个数字之外，其他的数字都出现了两次。请写程序找出这两个只出现一次的数字。

**题解：分组异或**

先对所有数字进行一次异或，得到两个出现一次的数字的异或值。

在异或结果中找到任意为 11 的位。

根据这一位对所有的数字进行分组。

在每个组内进行异或操作，得到两个数字。

```cpp
class Solution {
public:
    vector<int> singleNumbers(vector<int>& nums) {
        int ret = 0;
        for (int n : nums)
            ret ^= n;
        int div = 1;
        while ((div & ret) == 0)
            div <<= 1;
        int a = 0, b = 0;
        for (int n : nums)
        {
            if (div & n)
                a ^= n;
            else
                b ^= n;
        }
        return vector<int>{a, b};
    }
};
```

## No41、和为S的连续整数序列

**题目描述**

小明很喜欢数学,有一天他在做数学作业时,要求计算出9~16的和,他马上就写出了正确答案是100。但是他并不满足于此,他在想究竟有多少种连续的正数序列的和为100(至少包括两个数)。没多久,他就得到另一组连续正数和为100的序列:18,19,20,21,22。现在把问题交给你,你能不能也很快的找出所有和为S的连续正数序列? Good Luck!

**输出描述:**

```
输出所有和为S的连续正数序列。序列内按照从小至大的顺序，序列间按照开始数字从小到大的顺序
```

输入

```
9
```

**返回值**

```
[[2,3,4],[4,5]]
```

**题解：滑动窗口**

```cpp
class Solution {
public:
    vector<vector<int>> findContinuousSequence(int target) {
        vector<vector<int>> result;
        int l = 1, r = 2;
        while (l < r)
        {
            int sum = (l + r) * (r - l + 1) / 2;
            if (sum == target)
            {
                vector<int> path;
                for (int i = l; i <= r; ++i)
                {
                    path.push_back(i);
                }
                result.push_back(path);
                l++;
            }
            else if (sum > target)
                l++;
            else
                r++;
        }
        return result;
    }
};
```

## No42、和为S的两个数字

**题目描述**

输入一个递增排序的数组和一个数字S，在数组中查找两个数，使得他们的和正好是S，如果有多对数字的和等于S，输出两个数的乘积最小的。

**输出描述:**

```cpp
对应每个测试案例，输出两个数，小的先输出
```

**示例1**

**输入**

```cpp
[1,2,4,7,11,15],15
```

**返回值**

```cpp
[4,11]
```

**1、很简单的一个问题**

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> result{-1, -1};
        int l = 0, r = nums.size() - 1;
        while (l < r)
        {
            if (nums[l] + nums[r] == target)
            {
                result[0] = nums[l];
                result[1] = nums[r];
                break;
            }
            else if (nums[l] + nums[r] > target)
            {
                r--;
            }
            else
                l++;
        } 
        return result;
    }
};
```

## No43、左旋转字符串

**题目描述**

汇编语言中有一种移位指令叫做循环左移（ROL），现在有个简单的任务，就是用字符串模拟这个指令的运算结果。对于一个给定的字符序列S，请你把其循环左移K位后的序列输出。例如，字符序列S=”abcXYZdef”,要求输出循环左移3位后的结果，即“XYZdefabc”。是不是很简单？OK，搞定它！

**示例1**

**输入**

```
"abcXYZdef",3
```

**返回值**

```
"XYZdefabc"
```

**题解：**

```cpp
class Solution {
public:
    string reverseLeftWords(string s, int n) 
    {
        reverse(s.begin(), s.begin() + n);
        reverse(s.begin() + n, s.end());
        reverse(s.begin(), s.end());
        return s;
    }
};
```

## No44、反转单词序列

输入一个英文句子，翻转句子中单词的顺序，但单词内字符的顺序不变。为简单起见，标点符号和普通字母一样处理。例如输入字符串"I am a student. "，则输出"student. a am I"。

示例 1：

```cpp
输入: "the sky is blue"
输出: "blue is sky the"
```

示例 2：

```cpp
输入: "  hello world!  "
输出: "world! hello"
解释: 输入字符串可以在前面或者后面包含多余的空格，但是反转后的字符不能包括。
```

示例 3：

```cpp
输入: "a good   example"
输出: "example good a"
解释: 如果两个单词间有多余的空格，将反转后单词间的空格减少到只含一个。
```

**题解：**

```cpp
class Solution {
public:
    string reverseWords(string s) {
        stringstream ss(s);
        string str;
        stack<string> st;
        while (ss >> str)
        {
            st.push(str);
        }
        string ans;
        while(st.size() > 1)
        {
            ans += st.top() + " ";
            st.pop();
        }
        if (!st.empty())
            ans += st.top();
        return ans;
    }
};
```

## No45、扑克牌顺子

**题目描述**

LL今天心情特别好,因为他去买了一副扑克牌,发现里面居然有2个大王,2个小王(一副牌原本是54张^_^)...

他随机从中抽出了5张牌,想测测自己的手气,看看能不能抽到顺子,如果抽到的话,他决定去买体育彩票,嘿嘿！！

“红心A,黑桃3,小王,大王,方片5”,“Oh My God!”不是顺子.....LL不高兴了,他想了想,决定大\小 王可以看成任何数字,并且A看作1,J为11,Q为12,K为13。上面的5张牌就可以变成“1,2,3,4,5”(大小王分别看作2和4),“So Lucky!”。

LL决定去买体育彩票啦。 现在,要求你使用这幅牌模拟上面的过程,然后告诉我们LL的运气如何， 如果牌能组成顺子就输出true，否则就输出false。

为了方便起见,你可以认为大小王是0。

**示例1**

**输入**

```
[6,0,2,0,4]
```

**返回值**

```
true
```

**示例2**

**输入**

```
[0,3,2,6,4]
```

**返回值**

```
true
```

**示例3**

**输入**

```
[1,0,0,1,0]
```

**返回值**

```
false
```

**示例4**

**输入**

```
[13,12,11,0,1]
```

**返回值**

```
false
```

**1、比较容易想到的一种方法**

1、排序

2、计算所有相邻数字间隔总数

3、计算0的个数

4、如果2、3相等，就是顺子

5、如果出现对子，则不是顺子

```cpp
class Solution {
public:
    bool isStraight(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int numOfZreo = 0, numOfInner = 0;
        for (int i = 0; i < nums.size() - 1; ++i)
        {
            if (nums[i] == 0)
                numOfZreo++;
            else if (nums[i] == nums[i + 1])
                return false;
            else
                numOfInner += nums[i + 1] - nums[i] - 1;
        }
        if (numOfInner > numOfZreo)
            return false;
        return true;
    }
};
```

## No46、孩子们的游戏（圆圈中最后剩下的数）

**题目描述**

每年六一儿童节,牛客都会准备一些小礼物去看望孤儿院的小朋友,今年亦是如此。HF作为牛客的资深元老,自然也准备了一些小游戏。其中,有个游戏是这样的:首先,让小朋友们围成一个大圈。然后,他随机指定一个数m,让编号为0的小朋友开始报数。每次喊到m-1的那个小朋友要出列唱首歌,然后可以在礼品箱中任意的挑选礼物,并且不再回到圈中,从他的下一个小朋友开始,继续0...m-1报数....这样下去....直到剩下最后一个小朋友,可以不用表演,并且拿到牛客名贵的“名侦探柯南”典藏版(名额有限哦!!^_^)。请你试着想下,哪个小朋友会得到这份礼品呢？(注：小朋友的编号是从0到n-1)

如果没有小朋友，请返回-1

**示例1**

**输入**

```
5,3
```

**返回值**

```
3
```

**题解一：约瑟夫环的问题**

```cpp
class Solution {
public:
    int lastRemaining(int n, int m) {
        if (n < 1 || m < 1)
            return -1;
        int last = 0;
        for (int i = 2; i <= n; ++i)
            last = (last + m) % i;
        return last;
    }
};
```

**题解二：递归**

```cpp
class Solution {
public:
    int lastRemaining(int n, int m) {
        if (n == 0)
            return -1;
        if (n == 1)
            return 0;
        else
            return (lastRemaining(n - 1, m) + m) % n;
    }
};
```

## No47、求1+2+3+...+N

**题目描述**

求1+2+3+...+n，要求不能使用乘除法、for、while、if、else、switch、case等关键字及条件判断语句（A ? B : C）。

**示例1**

**输入**

```
5
```

**返回值**

```
15
```

**题解：**

```cpp
class Solution {
public:
    int sumNums(int n) {
        n && (n += sumNums(n - 1));
        return n;
    }
};
```

## No48、求两个数相加

**题目描述** 写一个函数，求两个整数之和，要求在函数体内不得使用+、-、*、/四则运算符号。

**示例1**

**输入**

```
1,2
```

**返回值**

```
3
```

**1、这种解法真的太厉害了**

```cpp
int Add(int num1, int num2)
{
    while(num2 != 0)
    {
        int sum = num1 ^ num2;
        int carray = (num1 & num2) << 1;
        num1 = sum;
        num2 = carray;
    } 
    return num1;
}
```

1. **两个数异或**：相当于每一位相加，而不考虑进位；
2. **两个数相与**，并左移一位：相当于求得进位；
3. 将上述两步的结果相加

首先看十进制是如何做的： 5+7=12，三步走

第一步：相加各位的值，不算进位，得到2。

第二步：计算进位值，得到10. 如果这一步的进位值为0，那么第一步得到的值就是最终结果。

第三步：重复上述两步，只是相加的值变成上述两步的得到的结果2和10，得到12。

同样我们可以用三步走的方式计算二进制值相加：

5-101，7-111

第一步：相加各位的值，不算进位，得到010，二进制每位相加就相当于各位做异或操作，101^111。

第二步：计算进位值，得到1010，相当于各位做与操作得到101，再向左移一位得到1010，(101&111)<<1。

第三步重复上述两步， 各位相加 010^1010=1000，进位值为100=(010&1010)<<1。

继续重复上述两步：1000^100 = 1100，进位值为0，跳出循环，1100为最终结果。

什么时候进位制为0也就说明两个数相加到了最终点，也就计算结束了

## No49、字符串转化为整数

**题目描述**

将一个字符串转换成一个整数，要求不能使用字符串转换整数的库函数。 数值为0或者字符串不是一个合法的数值则返回0

**输入描述:**

```
输入一个字符串,包括数字字母符号,可以为空
```

**输出描述:**

```
如果是合法的数值表达则返回该数字，否则返回0
```

**示例1**

**输入**

```
+2147483647
1a33
```

**输出**

```
2147483647
0
```

**题解一：字符流**

```cpp
class Solution {
public:
    int strToInt(string str) {
        //对于全是空格的案例，istringstream不能成功转为int,istringstream会输出空格的长度
        //所以先特俗处理
        int i = 0;
        int len = str.size();
        for(i = 0; i < len; i++)
        {
            if ((int)str[i] != 32)	// 空格的ASSCI值为32
                break;
        }
        if(i == len) 
            return 0;
        
        istringstream iss(str);// 对于转正数或者负数都可以
        int val;
        iss >> val;
        //当为字符时，转化为int失败，会自动输出0
        //当int超出范围，会自动返回数字，因此返回 INT_MIN (−231) 。
        return val;
    }
};
```

**题解二：模拟**

```cpp
class Solution {
public:
    int strToInt(string str) {
        vector<int> temp;
        int i;
        int isPositive = 3;
        //找到i第一个为正号，负号或数字的位置
        for (i = 0; i < str.size(); i++) 
        {
            if (str[i] == ' ') 
                continue;
            else if ('0' <= str[i] && str[i] <= '9') 
                break;
            else if (str[i] == '-') 
            {
                isPositive = 0;
                break;
            }
            else if (str[i] == '+') 
            {
                isPositive = 1;
                break;
            }
            else
                return 0;
        }
        // 下标越界说明全是空格
        if (i == str.size()) 
            return 0;
        int ans = 0;
        int j;
        //下标位置为正号或数字
        if (isPositive != 0) 
        {
            j = isPositive == 1 ? i + 1 : i;
            while (j < str.size() && '0' <= str[j] && str[j] <= '9') 
            {
                if ((long)ans * 10 > INT_MAX) 
                    return INT_MAX;
                else 
                    ans *= 10;
                if ((long)ans + str[j] - '0' > INT_MAX) 
                    return INT_MAX;
                else 
                    ans += str[j] - '0';
                j++;
            }
        }
        //下标位置为负号
        else 
        {
            j = i + 1;
            while (j < str.size() && '0' <= str[j] && str[j] <= '9') 
            {
                if ((long)ans * 10 < INT_MIN) 
                    return INT_MIN;
                else 
                    ans *= 10;
                if ((long)ans -str[j] + '0' < INT_MIN) 
                    return INT_MIN;
                ans -= str[j] - '0';
                j++;
            }
        }
        return ans;
    }
};
```

## No50、数组中重复的数字

**题目描述**

在一个长度为n的数组里的所有数字都在0到n-1的范围内。 数组中某些数字是重复的，但不知道有几个数字是重复的。也不知道每个数字重复几次。请找出数组中第一个重复的数字。 例如，如果输入长度为7的数组{2,3,1,0,2,5,3}，那么对应的输出是第一个重复的数字2。

**返回描述：**

如果数组中有重复的数字，函数返回true，否则返回false。

如果数组中有重复的数字，把重复的数字放到参数duplication[0]中。（ps:duplication已经初始化，可以直接赋值使用。）

**题解：**

1. 用 unordered_map 保存：遍历数组，检查逐个元素是否在 map 中，若不在，则插入，若在，则找到重复的元素，将其返回。
2. 在原数组中修改，利用 `长度为 n 的数组里的所有数字都在 0 到 n-1 的范围内` 的特性，即数字 i 应该放在数组的第 i 个位置上

```cpp
class Solution {
public:
    int findRepeatNumber(vector<int>& nums) 
    {
        int index = 0;
        while (index < nums.size())
        {
            if (nums[index] == index)		// 数字 i 放在数组的第 i 个位置上, index++
            {
                index++;
            }
            else							// 数字 i 不在数组的第 i 个位置上， 则需交换
            {
                if (nums[index] == nums[nums[index]])	// 若交换两个数相等， 则重复
                {
                    return nums[index];
                }
                else
                {
                    swap(nums[index], nums[nums[index]]);	// 交换
                }
            }
        }
        return nums[index];
    }
};
```

## No51、构建乘积数组

**题目描述**

给定一个数组A[0,1,...,n-1],请构建一个数组B[0,1,...,n-1],其中B中的元素B[i]=A[0]*A[1]*...*A[i-1]*A[i+1]*...*A[n-1]，不能使用除法。

（注意：规定B[0] = A[1] * A[2] * ... * A[n-1]，B[n-1] = A[0] * A[1] * ... * A[n-2];）

对于A长度为1的情况，B无意义，故而无法构建，因此该情况不会存在。

**示例1**

**输入**

```
[1,2,3,4,5]
```

**返回值**

```
[120,60,40,30,24]
```

**题解：正反两次遍历**

```cpp
class Solution {
public:
    vector<int> constructArr(vector<int>& a) 
    {
        vector<int> result(a.size(), 1);
        for (int i = 1; i < a.size(); ++i)
        {
            result[i] = result[i - 1] * a[i - 1];
        }
        int temp = 1;
        for (int i = a.size() - 1; i >= 0; --i)
        {
            result[i] *= temp; 
            temp *= a[i];
        }
        return result;
    }
};
```

## No52、正则表达式匹配

**题目描述**

请实现一个函数用来匹配包括'.'和'*'的正则表达式。模式中的字符'.'表示任意一个字符，而'*'表示它前面的字符可以出现任意次（包含0次）。 在本题中，匹配是指字符串的所有字符匹配整个模式。例如，字符串"aaa"与模式"a.a"和"ab*ac*a"匹配，但是与"aa.a"和"ab*a"均不匹配

**示例1**

**输入**

```
"aaa","a*a"
```

**返回值**

```
true
```

**题解：动态规划**

```cpp
class Solution {
public:
    bool isMatch(string s, string p) 
    {
        int m = s.size();
        int n = p.size();

        auto matches = [&](int i, int j) 
        {
            if (i == 0) 
            {
                return false;
            }
            if (p[j - 1] == '.') 
            {
                return true;
            }
            return s[i - 1] == p[j - 1];
        };

        vector<vector<int>> f(m + 1, vector<int>(n + 1));
        f[0][0] = true;
        for (int i = 0; i <= m; ++i) 
        {
            for (int j = 1; j <= n; ++j) 
            {
                if (p[j - 1] == '*') 
                {
                    f[i][j] |= f[i][j - 2];
                    if (matches(i, j - 1)) 
                    {
                        f[i][j] |= f[i - 1][j];
                    }
                }
                else 
                {
                    if (matches(i, j)) 
                    {
                        f[i][j] |= f[i - 1][j - 1];
                    }
                }
            }
        }
        return f[m][n];
    }
};
```

## No53、表示数值的字符串

**题目描述**

请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。例如，字符串"+100","5e2","-123","3.1416"和"-1E-16"都表示数值。 但是"12e","1a3.14","1.2.3","+-5"和"12e+4.3"都不是。

**示例1**

**输入**

```
"123.45e+6"
```

**返回值**

```
true
```

**示例2**

**输入**

```
"1.2.3"
```

**返回值**

```
false
```

**题解**

```cpp
class Solution {
public:
    bool isNumber(string s) 
    {
        bool ret = true, e = false, xs = false, dg = false;

        while (s.back() == ' ') 				// 去除后面的空格
            s.pop_back();
        int i = 0, n = s.length();
        while (i < n && s[i] == ' ') 			// 去除前面的空格
            i++;

        if (i < n && s[i] == '+' || s[i] == '-') 
            i++;

        for (; i < n; i++) 
        {
            if (isdigit(s[i])) 
            {
                dg = true; 
                continue;
            }
            if (s[i] == '.') 
            {
                if (xs || e) 
                    return false;
                xs = true;
            } 
            else if (s[i] == 'e' || s[i] == 'E') 
            {
                if (e) 
                    return false;
                e = true;
                if (!dg) 
                    return false;
                dg = false;
                if (++i < n && (s[i] == '+' || s[i] == '-')) 
                    continue;
                else 
                    --i;
            } 
            else 
            {
                return false;
            }
        }
        return dg;
    }
};
```

## No54、字符流中第一个不重复的字符

**题目描述**

请实现一个函数用来找出字符流中第一个只出现一次的字符。例如，当从字符流中只读出前两个字符"go"时，第一个只出现一次的字符是"g"。当从该字符流中读出前六个字符“google"时，第一个只出现一次的字符是"l"。

```
如果当前字符流没有存在出现一次的字符，返回#字符。
```

**题解：借助哈希表**

这个方法要慢一些

```cpp
class Solution
{
public :
    //Insert one char from stringstream
    void Insert(char ch)
    {
        v.push_back(ch);
        unmp[ch]++;
    }
    //return the first appearence once char in current stringstream
    char FirstAppearingOnce()
    {
        for (auto &ch : v) 
        {
            if (unmp[ch] == 1) 
                return ch;
        }
        return '#';
    }
private ：
    vector<char> v;
    unordered_map<char, int> unmp;
};
```

## No55、链表中环的入口结点

**题目描述**

给一个链表，若其中包含环，请找出该链表的环的入口结点，否则，输出 null。

**题解：快慢指针**

先说个定理：两个指针一个 fast、一个 slow 同时从一个链表的头部出发 fast 一次走 2 步，slow 一次走一步，如果该链表有环，两个指针必然在环内相遇，此时只需要把其中的一个指针重新指向链表头部，另一个不变（还在环内）， 这次两个指针一次走一步，相遇的地方就是入口节点。 

```C++
class Solution {
public:
    ListNode *detectCycle(ListNode *head) 
    {
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast)
            {
                ListNode* slow2 = head;
                while (slow2 != slow)
                {
                    slow2 = slow2->next;
                    slow = slow->next;
                }
                return slow2;
            }
        }
        return nullptr;
    }
};
```

## No56、删除链表中的重复结点

**题目描述**

在一个排序的链表中，存在重复的结点，请删除该链表中重复的结点，重复的结点不保留，返回链表头指针。 例如，链表1->2->3->3->4->4->5 处理后为 1->2->5

**示例1**

**输入**

```
{1,2,3,3,4,4,5}
```

**返回值**

```
{1,2,5}
```

**题解：**

```cpp
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) 
    {
        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode* dummy = new ListNode(-1, head);
        ListNode* prev = dummy;
        ListNode* cur = head;
        
        while (cur)
        {
            bool flag = false;
            while (cur->next && cur->val == cur->next->val)	// 删除节点
            {
                ListNode* tmp = cur;
                cur = cur->next;
                delete tmp;
                tmp = nullptr;
                flag = true;
            } 
            if (flag)						// 删除最后一个重复的节点
            {
                ListNode* tmp = cur;
                cur = cur->next;
                tmp = nullptr;
                delete tmp;
            }
            else
            {
                prev->next = cur;
                prev = prev->next;
                cur = cur->next;                
            }
        }
        prev->next = cur;				// 最后指向 nullptr
        return dummy->next;
    }
};
```

## No57、二叉树的下一个结点

**题目描述**

给定一个二叉树和其中的一个结点，请找出中序遍历顺序的下一个结点并且返回。注意，树中的结点不仅包含左右子结点，同时包含指向父结点的指针。

**题解：**

1. 二叉树为空，则返回空；

2. 节点右孩子存在，则设置一个指针从该节点的右孩子出发，一直沿着指向左子结点的指针找到的叶子节点即为下一个节点；

3. 右孩子不存在，如果节点不是根节点，如果该节点是其父节点的左孩子，则返回父节点；否则继续向上遍历其父节点的父节点，重复之前的判断，返回结果。

```cpp
TreeLinkNode* GetNext(TreeLinkNode* pNode)
{
    if (pNode == nullptr)
        return nullptr;
    if (pNode->right != nullptr)
    {
        pNode = pNode->right;
        while (pNode->left != nullptr)
            pNode = pNode->left;
        return pNode;
    }
    while (pNode->next != nullptr)
    {
        TreeLinkNode* proot = pNode->next;
        if (proot->left == pNode)
            return proot;
        pNode = pNode->next;
    }
    return nullptr;
}
```

## No58、对称的二叉树

**题目描述**

请实现一个函数，用来判断一棵二叉树是不是对称的。注意，如果一个二叉树同此二叉树的镜像是同样的，定义其为对称的。

**示例1**

**输入**

```
{8,6,6,5,7,7,5}
```

**返回值**

```
true
```

**示例2**

**输入**

```
{8,6,9,5,7,7,5}
```

**返回值**

```
false
```

**题解：递归**

```cpp
bool isEqual(TreeNode*node1,TreeNode*node2){
    if (node1==nullptr && node2 ==nullptr)  
        return true;
    if (node1 ==nullptr || node2==nullptr) 
        return false;//减少逻辑判断
    if (node1->val == node2->val) 
        return isEqual(node1->left, node2->right) && isEqual(node1->right, node2->left);	// 注意这里是右左，左右来进行判断
    else
        return false;
}
bool isSymmetrical(TreeNode* pRoot) 
{
    if(pRoot==nullptr) 
        return true;		// 这里是返回true的
    return isEqual(pRoot->left, pRoot->right);
}
```

## No59、按之字形顺序打印二叉树

**题目描述**

请实现一个函数按照之字形打印二叉树，即第一行按照从左到右的顺序打印，第二层按照从右至左的顺序打印，第三行按照从左到右的顺序打印，其他行以此类推。

**示例1**

**输入**

```cpp
{8,6,10,5,7,9,11}
```

**返回值**

```cpp
[[8],[10,6],[5,7,9,11]]
```

**题解：层次遍历**

```cpp
vector<vector<int>> Print(TreeNode* pRoot) 
{
    vector<vector<int>> result;
    if (pRoot == nullptr) 
        return result;
    queue<TreeNode*> q;
    q.push(pRoot);
    int i = 0;
    while (!q.empty()) 
    {
        int len = q.size();		// 利用 len 保存每层的个数
        vector<int> temp;
        while (len--) 
        {
            TreeNode* node = q.front();
            q.pop();
            temp.push_back(node->val);
            if (node->left)      
                q.push(node->left);
            if (node->right)  
                q.push(node->right);;
        }
        i++;
        if (i % 2 == 0)
            reverse(temp.begin(), temp.end());
        result.push_back(temp);
    }
    return result;
}
```

## No60、把二叉树打印成多行

**题目描述**

从上到下按层打印二叉树，同一层结点从左至右输出。每一层输出一行。

**示例1**

**输入**

```cpp
{8,6,10,5,7,9,11}
```

**返回值**

```cpp
[[8],[6,10],[5,7,9,11]]
```

**题解：层次遍历——队列**

```cpp
vector<vector<int>> Print(TreeNode* pRoot) 
{
    vector<vector<int>> result;
    if (pRoot == nullptr) 
        return result;
    queue<TreeNode*> q;
    q.push(pRoot);
    while (!q.empty()) 
    {
        int len = q.size();		// 利用 len 保存每层的个数
        vector<int> temp;
        while (len--) 
        {
            TreeNode* node = q.front();
            q.pop();
            temp.push_back(node->val);
            if (node->left)      
                q.push(node->left);
            if (node->right)  
                q.push(node->right);;
        }
        result.push_back(temp);
    }
    return result;
}
```

## No61、序列化二叉树

**题目描述**

请实现两个函数，分别用来序列化和反序列化二叉树

二叉树的序列化是指：把一棵二叉树按照某种遍历方式的结果以某种格式保存为字符串，从而使得内存中建立起来的二叉树可以持久保存。序列化可以基于先序、中序、后序、层序的二叉树遍历方式来进行修改，序列化的结果是一个字符串，序列化时通过 某种符号表示空节点（#），以 ！ 表示一个结点值的结束（value!）。

二叉树的反序列化是指：根据某种遍历顺序得到的序列化字符串结果str，重构二叉树。

例如，我们可以把一个只有根节点为1的二叉树序列化为"1,"，然后通过自己的函数来解析回这个二叉树。

**题解**

```cpp
class Codec {
public:
    void rserialize(TreeNode* root, string& str) 
    {
        if (root == nullptr) 
        {
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

    TreeNode* deserialize(string data) {
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

## No62、二叉搜索树的第K个节点

**题目描述**

给定一棵二叉搜索树，请找出其中第k大的节点。

**示例1**

**输入**

```c
root = [3,1,4,null,2], k = 1
```

**返回值**

```c
4
```

说明 按结点数值大小顺序第三小结点的值为 4

**题解：二叉搜索树的中序遍历**

```cpp
class Solution {
public:
    int kthLargest(TreeNode* root, int k) 
    {
        if (root == NULL)
            return -1;
        vector<int> v;
        stack<TreeNode*> s;
        while (root || !s.empty())
        {
            if (root)
            {
                s.push(root);
                root = root->left;
            }
            else
            {
                root = s.top();
                s.pop();
                v.push_back(root->val);
                root = root->right;
            }
        }
        return v[v.size() - k];
    }
};
```

## No63、数据流中的中位数

如何得到一个数据流中的中位数？如果从数据流中读出奇数个数值，那么中位数就是所有数值排序之后位于中间的数值。如果从数据流中读出偶数个数值，那么中位数就是所有数值排序之后中间两个数的平均值。

例如，

[2,3,4] 的中位数是 3

[2,3] 的中位数是 (2 + 3) / 2 = 2.5

设计一个支持以下两种操作的数据结构：

- void addNum(int num) - 从数据流中添加一个整数到数据结构中。
- double findMedian() - 返回目前所有元素的中位数。

**示例 1：**

```cpp
输入：
["MedianFinder","addNum","addNum","findMedian","addNum","findMedian"]
[[],[1],[2],[],[3],[]]
输出：[null,null,null,1.50000,null,2.00000]
```

**示例 2：**

```cpp
输入：
["MedianFinder","addNum","findMedian","addNum","findMedian"]
[[],[2],[],[3],[]]
输出：[null,null,2.00000,null,2.50000]
```

**题解：大顶堆 + 小顶堆：大顶堆所有元素均小于等于小顶堆的所有元素**

```cpp
class Solution {
public:
	void Insert(int num)
    {
        count += 1;
        // 元素个数是偶数时,将大顶堆堆顶放入小顶堆
        // 大顶堆所有元素均小于等于小顶堆的所有元素
        if (count % 2 == 0) 
        {
            big_heap.push(num);
            small_heap.push(big_heap.top());
            big_heap.pop();
        }
        else 
        {
            small_heap.push(num);
            big_heap.push(small_heap.top());
            small_heap.pop();
        }
    }

	double GetMedian()
	{
    	if (count & 0x1) 
    	{
        	return big_heap.top();
    	}
    	else 
    	{
        	return double((small_heap.top() + big_heap.top()) / 2.0);
    	}
	}
private:
    int count = 0;
    priority_queue<int, vector<int>, less<int>> big_heap;        // 左边一个大顶堆
    priority_queue<int, vector<int>, greater<int>> small_heap;   // 右边一个小顶堆
};
```

## No64、滑动窗口的最大值

**题目描述**

给定一个数组和滑动窗口的大小，找出所有滑动窗口里数值的最大值。

例如，如果输入数组{2,3,4,2,6,2,5,1}及滑动窗口的大小3，那么一共存在6个滑动窗口，他们的最大值分别为{4,4,6,6,6,5}；

针对数组{2,3,4,2,6,2,5,1}的滑动窗口有以下6个：

{[2,3,4],2,6,2,5,1}， {2,[3,4,2],6,2,5,1}， {2,3,[4,2,6],2,5,1}， {2,3,4,[2,6,2],5,1}， {2,3,4,2,[6,2,5],1}， {2,3,4,2,6,[2,5,1]}。 窗口大于数组长度的时候，返回空

**示例1**

**输入**

```cpp
[2,3,4,2,6,2,5,1],3
```

**返回值**

```cpp
[4,4,6,6,6,5]
```

**题解：**

```cpp
class Solution {
private:
    class MyQueue {
        public:
        deque<int> que;
        void pop(int value)
        {
            if (!que.empty() && value == que.front())
            {
                que.pop_front();
            }
        }
        void push(int value)
        {
            while (!que.empty() && value > que.back())
            {
                que.pop_back();
            }
            que.push_back(value);
        }
        int front()
        {
            return que.front();
        }
    };
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        MyQueue que;
        vector<int> result;
        if (nums.size() == 0 || k == 0)
            return result;
        for (int i = 0; i < k; ++i)
        {
            que.push(nums[i]);
        }
        result.push_back(que.front());
        for (int i = k; i < nums.size(); ++i)
        {
            que.pop(nums[i - k]);
            que.push(nums[i]);
            result.push_back(que.front());
        }
        return result;
    }
};
```

## No65、矩阵中的路径

**题目描述**

请设计一个函数，用来判断在一个矩阵中是否存在一条包含某字符串所有字符的路径。路径可以从矩阵中的任意一个格子开始，每一步可以在矩阵中向左，向右，向上，向下移动一个格子。如果一条路径经过了矩阵中的某一个格子，则该路径不能再进入该格子。

例如，在下面的 3×4 的矩阵中包含单词 "ABCCED"（单词中的字母已标出）。

示例 1：

```cpp
输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
输出：true
```


示例 2：

```cpp
输入：board = [["a","b"],["c","d"]], word = "abcd"
输出：false
```

**题解：回溯法**

```cpp
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) 
    {
        vector<vector<bool>> used(board.size(), vector<bool>(board[0].size(), false));
        for(int i = 0; i < board.size(); i++) 
        {
            for(int j = 0; j < board[0].size(); j++) 
            {
                if(dfs(board, word, i, j, 0, used)) 
                    return true;
            }
        }
        return false;
    }
private:
    bool dfs(const vector<vector<char>>& board, const string& word, int i, int j, int index, vector<vector<bool>>& used) 
    {
        if(i >= board.size() || i < 0 || j >= board[0].size() || j < 0 || board[i][j] != word[index] || used[i][j] == true) 
            return false;
        if(index == word.size() - 1) 
            return true;

        used[i][j] = true;

        bool res = dfs(board, word, i + 1, j, index + 1, used) || dfs(board, word, i - 1, j, index + 1, used) || 
                      dfs(board, word, i, j + 1, index + 1, used) || dfs(board, word, i , j - 1, index + 1, used);

        used[i][j] = false;
        return res;
    }
};

```

## No66、机器人的运动范围

**题目描述**

地上有一个m行和n列的方格。一个机器人从坐标0,0的格子开始移动， 每一次只能向左，右，上，下四个方向移动一格，但是不能进入行坐标和列坐标的数位之和大于k的格子。 例如，当k为18时，机器人能够进入方格（35,37），因为3+5+3+7 = 18。 但是，它不能进入方格（35,38），因为3+5+3+8 = 19。请问该机器人能够达到多少个格子？

**示例1**

**输入**

```
5,10,10
```

**返回值**

```
21
```

**题解：回溯法**

因为是从（0 0 ），开始走的，所以只需要判断向上和向右的情况即可

```cpp
class Solution {
public:
	bool canReach(int k, int x, int y) 
    {
    	int sum = 0;
    	while (x > 0) 
    	{
        	sum += x % 10;
        	x /= 10;
    	}
    	while (y > 0) 
    	{
        	sum += y % 10;
       		y /= 10;
    	}
    	return sum <= k;
	}

	int movingCountCore(int k, int i, int m,int j ,int n, vector<vector<bool>>& visit) 
	{
    	if (i >= m || j >= n || !canReach(k, i, j) || visit[i][j] == true) 
        	return 0;

    	visit[i][j] = true; // 当前已经走过了，并且满足要求，所有后续 return 要加上1

    	return  1 + movingCountCore(k, i + 1, m, j, n, visit) +
        	movingCountCore(k, i, m, j + 1, n, visit);

	}

	int movingCount(int m, int n, int k) 
	{
    	vector<vector<bool>> visit(m,vector<bool>(n,false));
    	return movingCountCore(k, 0,  m, 0, n, visit);
	}
};
```

## No67、剪绳子

**题目描述**

给你一根长度为n的绳子，请把绳子剪成整数长的m段（m、n都是整数，n>1并且m>1），每段绳子的长度记为k[1],...,k[m]。请问k[1]x...xk[m]可能的最大乘积是多少？例如，当绳子的长度是8时，我们把它剪成长度分别为2、3、3的三段，此时得到的最大乘积是18。

**题解一：贪心**

```cpp
int cuttingRope(int n) 
{
    if (n < 4) 
        return n - 1;
    
    int maxNum=1;
    while (n > 4)
    {
        maxNum *= 3;
        n -= 3;
    }
    maxNum *= n;
    return maxNum;
}
```

**题解二：动态规划**

```cpp
class Solution {
public:
    int cuttingRope(int n) 
    {
        if (n == 2)
            return 1;
        if (n == 3)
            return 2;
        
        vector<int> dp(n + 1, 0);
        dp[1] = 1;
        dp[2] = 2;
        dp[3] = 3;
        for (int i = 4; i <= n; ++i)
        {
            for (int j = 1; j <= i / 2; ++j)
            {
                dp[i] = max(dp[i], dp[j] * dp[i - j]);
            }
        }
        return dp[n];
    }
};
```
