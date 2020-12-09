//leetcode
//989.数组形式的整数加法
class Solution {
public:
    vector<int> addToArrayForm(vector<int>& A, int K) {
        //对应位相加，
        vector<int> result;
        int lastNum = K, i = A.size() - 1;
        while (i >= 0 || lastNum > 0) {
            //对应位相加
            if (i >= 0)
                lastNum += A[i--];

            //尾部数字添加到result中，同时k需要丢弃尾部数字
            result.push_back(lastNum % 10);
            lastNum /= 10;
            //取进位及上位，lastNum只关注其个位、十位
        }
        //反转
        reverse(result.begin(), result.end());
        return result;
    }
};
//26.删除排序数组中的重复项
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int cur = 0, prev = 0;
        if (nums.size() == 0) {
            return 0;
        }
        int val = nums[0], flag = 1;
        //设置标记 flag主要起到保证perv的位置为新数组的最后空的一位
        //=1，表示perv不在最后空的位置
        //=0，表示perv在最新的位置
        while (cur <= nums.size() - 1) {
            if (nums[cur] != val) {
                //表示cur发现了新的值，perv保存下来新的值
                //将新的值保存在val中，此时perv不为空，将flag = 1
                nums[prev] = nums[cur];
                val = nums[cur];
                flag = 1;
            }
            else if (flag == 1) {
                //表示当前值和val相同，需要将prev移动新的位置，并且将falg = 0，表示在最新的位置
                cur++;
                prev++;
                flag = 0;
            }
            else {
                //prev在新的位置，并且cur没有发现新的值
                cur++;
            }
        }
        return prev;
    }
};
//27.移除元素
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        //借助建立一个新数组的思想
        int prev = 0, cur = 0;
        if (nums.size() == 0) {
            return 0;
        }
        while (cur <= nums.size() - 1) {
            if (nums[cur] != val) {
                nums[prev] = nums[cur];
                prev++;
                cur++;
            }
            else {
                cur++;
            }
        }
        return prev;
    }
};
//面试题17.04.消失的数字
class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int dst = 0;
        for (int i = 0; i < nums.size(); ++i) {
            dst ^= nums[i];
            dst ^= i;
        }
        dst ^= nums.size();
        return dst;
    }
};
//剑指offer 56-1.数组中数字出现的次数
class Solution {
public:
    vector<int> singleNumbers(vector<int>& nums) {
        int ret = 0;
        for (int n : nums) {
            ret ^= n;
        }
        int div = 1;
        while ((div & ret) == 0) {
            div <<= 1;
        }
        int a = 0, b = 0;
        for (int n : nums) {
            if (n & div) {
                //判断为真
                a ^= n;
            }
            else {
                b ^= n;
            }
        }
        return vector<int>{a, b};
    }
};