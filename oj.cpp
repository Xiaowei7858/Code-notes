//leetcode
//989.������ʽ�������ӷ�
class Solution {
public:
    vector<int> addToArrayForm(vector<int>& A, int K) {
        //��Ӧλ��ӣ�
        vector<int> result;
        int lastNum = K, i = A.size() - 1;
        while (i >= 0 || lastNum > 0) {
            //��Ӧλ���
            if (i >= 0)
                lastNum += A[i--];

            //β��������ӵ�result�У�ͬʱk��Ҫ����β������
            result.push_back(lastNum % 10);
            lastNum /= 10;
            //ȡ��λ����λ��lastNumֻ��ע���λ��ʮλ
        }
        //��ת
        reverse(result.begin(), result.end());
        return result;
    }
};
//26.ɾ�����������е��ظ���
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int cur = 0, prev = 0;
        if (nums.size() == 0) {
            return 0;
        }
        int val = nums[0], flag = 1;
        //���ñ�� flag��Ҫ�𵽱�֤perv��λ��Ϊ����������յ�һλ
        //=1����ʾperv�������յ�λ��
        //=0����ʾperv�����µ�λ��
        while (cur <= nums.size() - 1) {
            if (nums[cur] != val) {
                //��ʾcur�������µ�ֵ��perv���������µ�ֵ
                //���µ�ֵ������val�У���ʱperv��Ϊ�գ���flag = 1
                nums[prev] = nums[cur];
                val = nums[cur];
                flag = 1;
            }
            else if (flag == 1) {
                //��ʾ��ǰֵ��val��ͬ����Ҫ��prev�ƶ��µ�λ�ã����ҽ�falg = 0����ʾ�����µ�λ��
                cur++;
                prev++;
                flag = 0;
            }
            else {
                //prev���µ�λ�ã�����curû�з����µ�ֵ
                cur++;
            }
        }
        return prev;
    }
};
//27.�Ƴ�Ԫ��
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        //��������һ���������˼��
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
//������17.04.��ʧ������
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
//��ָoffer 56-1.���������ֳ��ֵĴ���
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
                //�ж�Ϊ��
                a ^= n;
            }
            else {
                b ^= n;
            }
        }
        return vector<int>{a, b};
    }
};