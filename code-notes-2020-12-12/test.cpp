//leetcode
//203. 移除链表元素
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        if (head == NULL) return head;
        ListNode* H = new ListNode;
        H->next = head;
        ListNode* after = H;
        ListNode* cur = head;
        while (cur != NULL) {
            if (cur->val == val) {
                after->next = cur->next;
                delete cur;
                cur = after->next;
            }
            else {
                after = cur;
                cur = cur->next;
            }
        }
        head = H->next;
        delete H;
        return  head;
    }
};
//88. 合并两个有序数组
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        //倒着放进来
        int last = m + n - 1;
        m -= 1;
        n -= 1;
        while (last >= 0) {
            if (m >= 0 && n >= 0 && nums1[m] <= nums2[n]) {
                nums1[last--] = nums2[n--];
            }
            else if (m >= 0 && n >= 0 && nums1[m] > nums2[n]) {
                nums1[last--] = nums1[m--];
            }
            else {
                break;
            }
        }
        while (m >= 0) {
            nums1[last--] = nums1[m--];
        }
        while (n >= 0) {
            nums1[last--] = nums2[n--];
        }
    }
};
//189. 旋转数组
class Solution {
public:
    void reverse(vector<int>& nums, int start, int end) {
        while (start < end) {
            int temp = nums[start];
            nums[start] = nums[end];
            nums[end] = temp;
            start++;
            end--;
        }
    }
    void rotate(vector<int>& nums, int k) {
        int length = nums.size();
        k %= length;
        reverse(nums, 0, length - 1);
        reverse(nums, 0, k - 1);
        reverse(nums, k, length - 1);
    }
};